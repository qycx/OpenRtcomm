#include "TipViewIM.h"
#include <QTimer>
#include <QDesktopWidget>
#include <QMutex>

static QMutex     _mutex;
static TipViewIM* _hins = nullptr;
QList<SessionInfo> TipViewIM::_list_sessions;

TipViewIM::TipViewIM()
    : WinBaseDialog( nullptr)
{
    this->setAutoFillBackground(false);  //这个不设置的话就背景变黑
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    ui.setupUi(this);
    int count = 0;
    _mutex.lock();
    //for each (auto item in _list_sessions)
    for (int i = 0; i < _list_sessions.size(); i++)
    {
        count += _list_sessions.at(i).unread_count;
    }
    _mutex.unlock();
    QString msg = QString("%1 (%2)").arg(QString::fromLocal8Bit("新消息")).arg(count);
    ui.label->setText(msg);
    ui.listView->setTipSession(_list_sessions);
    connect(ui.listView, &TipListView::open_session, [this](qint64 sid, QString sname)
        {
            removeSession(sid);
            emit open_session(sid, sname);
            _bMouseEnter = false;
            this->close();
        });
}

void TipViewIM::closeEvent(QCloseEvent * event)
{
    if (_bMouseEnter)
    {
        event->ignore();
    }
}

void TipViewIM::enterEvent(QEvent *event)
{
    _bMouseEnter = true;
}

void TipViewIM::leaveEvent(QEvent *event)
{
    _bMouseEnter = false;
    CloseTipView();
}

TipViewIM::~TipViewIM()
{
    _hins = nullptr;
}

TipViewIM* TipViewIM::ShowTipView(QRect rect)
{
    if (!_hins)
    {
        _hins = new TipViewIM();
        _hins->show();


        int desktop_width = QApplication::desktop()->width();
        QSize sz = _hins->size();
        if (_list_sessions.size() > 1)
        {
            sz.setHeight(sz.height() + (_list_sessions.size() - 1) * 48);
        }
        QRect rc;
        int x = (rect.left() + rect.width() / 2) - (sz.width() / 2);
        if (x + sz.width() > desktop_width)
        {
            x = desktop_width - sz.width();
        }
        int mar = _hins->ui.horizontalLayout->margin();
        rc.setLeft(x);
        rc.setTop(rect.top() - sz.height() + mar);
        rc.setSize(sz);
        _hins->setGeometry(rc);
    }
    return _hins;
}


void TipViewIM::CloseTipView()
{
    if (_hins)
    {
        QTimer* t_close = new QTimer(_hins);
        connect(t_close, &QTimer::timeout, [t_close]()
            {
                t_close->stop();
                _hins->close();
            });
        t_close->start(500);
    }

}

void TipViewIM::button_lose()
{
    emit lose();
    _mutex.lock();
    _list_sessions.clear();
    _mutex.unlock();
    _bMouseEnter = false;
    this->close();
}

QList<SessionInfo> TipViewIM::listSessions()
{
    return _list_sessions;
}

void TipViewIM::ClearSessions()
{
    _mutex.lock();
    _list_sessions.clear();
    _mutex.unlock();
}

void TipViewIM::addListSession(SessionInfo session)
{
    _mutex.lock();
    for (int i = 0; i < _list_sessions.size(); i++)
    {
        if (_list_sessions[i].session_id==session.session_id)
        {
            _list_sessions[i].unread_count += session.unread_count;
            _mutex.unlock();
            return;
        }
    }
    _list_sessions.append(session);
    _mutex.unlock();
}

void TipViewIM::removeSession(qint64 sid)
{
    _mutex.lock();
    for (int i = 0; i < _list_sessions.size(); i++)
    {
        if (_list_sessions[i].session_id==sid)
        {
            _list_sessions.removeAt(i);
            break;
        }
    }
    _mutex.unlock();
}
