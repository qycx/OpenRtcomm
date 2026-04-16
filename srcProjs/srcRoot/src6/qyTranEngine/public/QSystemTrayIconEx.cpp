#include "QSystemTrayIconEx.h"
#include <QApplication>
#include <QWidget>
#include <QIcon>
#include <QDebug>
//#include <process.h>
#include <QEvent>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include "TipViewIM.h"
#include	"stdafx.h"
#include	"qyMcMainCommon_qt.h"

//
#define WM_TRAYNOTIFY (WM_USER+123)

static qint64	_tick_icon = 0;



static QSystemTrayIcon*	tray_icon = nullptr;
static bool bEnter = false;
static QTimer* t_close = nullptr;
QSystemTrayIconEx::QSystemTrayIconEx(QIcon icon, QObject *parent)
	: QObject(parent)
{
	CCtxQyMc* pQyMc = g_pQyMc;

	//
	icon_ = icon;
	tray_icon = new QSystemTrayIcon(parent);
	//
	tray_icon->setToolTip(QString::fromUtf16((char16_t*)pQyMc->cfg.qyMcTitle)); 
	//
	tray_icon->setIcon(icon);
	tray_icon->show();
	t_close = new QTimer(parent);
	connect(t_close, &QTimer::timeout, [this]()
	{
		QRect rc = tray_icon->geometry();
		QPoint pt = QCursor::pos();
		if (rc.contains(pt))
		{
			if (!bEnter)
			{
				bEnter = true;
				if (TipViewIM::listSessions().size() > 0)
				{
					TipViewIM* tip = TipViewIM::ShowTipView(rc);
					if (tip)
					{
						connect(tip, &TipViewIM::lose, [this]()
						{
							tray_time_star(nullptr, false);
						});
						connect(tip, &TipViewIM::open_session, [this](qint64 sid, QString sname)
						{
							emit open_session(sid, sname);
							if (TipViewIM::listSessions().size() == 0)
							{
								tray_time_star(nullptr, false);
							}
						});
					}
				}
			}
		}
		else
		{
			if (bEnter)
			{
				bEnter = false;
				TipViewIM::CloseTipView();
			}
		}
		int c = 0;
	});

	_m_menu = new QMenu();
	tray_icon->setContextMenu(_m_menu);
	connect(tray_icon, &QSystemTrayIcon::activated, this, &QSystemTrayIconEx::iconIsActived);
}

void QSystemTrayIconEx::add_new_session(SessionInfo session)
{
	TipViewIM::addListSession(session);
}

void QSystemTrayIconEx::remove_session(qint64 userId)
{
	TipViewIM::removeSession(userId);
	if (TipViewIM::listSessions().size() == 0)
	{
		tray_time_star(nullptr, false);
	}
}


QSystemTrayIconEx::~QSystemTrayIconEx()
{
	if (this->m_tray_time) {
		delete this->m_tray_time;
	}

}

void QSystemTrayIconEx::AddMenu(QAction* action)
{
	if (_m_menu)
	{
		_m_menu->addAction(action);
		_m_menu->addSeparator();
	}
}

void QSystemTrayIconEx::tray_time_star(QWidget* parent, bool bstar /*= false*/)
{
	if (t_close)
	{
		if (bstar)
		{
			if (!t_close->isActive())
			{
				t_close->start(100);
			}
			
		}
		else
		{
			t_close->stop();
		}
	}
	_tick_icon = 0;
	//static QTimer* tray_time = nullptr;
	QTimer* tray_time = this->m_tray_time;
	if (tray_time == nullptr)
	{
		//tray_time = new QTimer(this);
		this->m_tray_time = new QTimer(this);
		tray_time = m_tray_time;

		//
		connect(tray_time, &QTimer::timeout, this, [this]()
		{
			if (_tick_icon % 2)
			{
				tray_icon->setIcon(icon_);
			}
			else
			{
				QIcon icon = QIcon("1");
				tray_icon->setIcon(icon);
			}
			_tick_icon++;
		});
		tray_time->setInterval(500);
	}
	tray_time->stop();
	if (bstar)
	{
		QApplication::alert(parent);
		tray_time->start();
	}
	else
	{
		tray_time->stop();
		tray_icon->setIcon(icon_);
	}
}



void QSystemTrayIconEx::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
	{
		emit LButton_Click();
		TipViewIM::CloseTipView();
		TipViewIM::ClearSessions();
		tray_time_star(nullptr, false);
		break;
	}
	//双击托盘显示窗口
	case QSystemTrayIcon::DoubleClick:
	{
		emit LButton_DBClick();
		break;
	}
	default:
	{

	}
	break;
	}
}
