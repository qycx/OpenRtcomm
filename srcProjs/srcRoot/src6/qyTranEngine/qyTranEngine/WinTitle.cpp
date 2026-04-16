#include "WinTitle.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QFile>
#include <QMouseEvent>
#include <QDebug>

#define BUTTON_HEIGHT 27		// 按钮高度;
#define BUTTON_WIDTH 27			// 按钮宽度;
#define TITLE_HEIGHT 32			// 标题栏高度;

WinTitle::WinTitle(QWidget* parent)
	: QWidget(parent)
	, m_isPressed(false)
	, m_buttonType(MIN_MAX_BUTTON)
{
	initControl();
}

WinTitle::~WinTitle()
{
}

// 初始化控件;
void WinTitle::initControl()
{
	m_pIcon = new QLabel(this);
	m_pTitleContent = new QLabel(this);

	m_pButtonMin = new WinQPushButton(":/Resources/Images/Title/min.png", 4, this);
	m_pButtonRestore = new WinQPushButton(":/Resources/Images/Title/restore.png", 4, this);
	m_pButtonMax = new WinQPushButton(":/Resources/Images/Title/max.png", 4, this);
	m_pButtonClose = new WinQPushButton(":/Resources/Images/Title/close.png", 4, this);

	m_pButtonMin->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pButtonRestore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pButtonMax->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pButtonClose->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

	m_pTitleContent->setObjectName("TitleContent");
	m_pButtonMin->setObjectName("ButtonMin");
	m_pButtonRestore->setObjectName("ButtonRestore");
	m_pButtonMax->setObjectName("ButtonMax");
	m_pButtonClose->setObjectName("ButtonClose");

	QHBoxLayout* mylayout = new QHBoxLayout(this);
	mylayout->addWidget(m_pIcon);
	mylayout->addWidget(m_pTitleContent);
	mylayout->addWidget(m_pButtonMin);
	mylayout->addWidget(m_pButtonRestore);
	mylayout->addWidget(m_pButtonMax);
	mylayout->addWidget(m_pButtonClose);
	mylayout->setContentsMargins(5, 0, 0, 0);
	mylayout->setSpacing(0);

	m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setFixedHeight(TITLE_HEIGHT);
	this->setWindowFlags(Qt::FramelessWindowHint);
	m_isParent = false;

	connect(m_pButtonMin, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
	connect(m_pButtonRestore, SIGNAL(clicked()), this, SLOT(onButtonRestoreClicked()));
	connect(m_pButtonMax, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
	connect(m_pButtonClose, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));
}

// 设置标题栏图标;
void WinTitle::setTitleIcon(QString filePath)
{
	QPixmap titleIcon(filePath);
	m_pIcon->setFixedSize(titleIcon.size());
	m_pIcon->setPixmap(titleIcon);
}

// 设置标题内容;
void WinTitle::setTitleContent(QString titleContent, QString color)
{
	m_pTitleContent->setText(titleContent);
	m_pTitleContent->setStyleSheet(QString("color:%1;").arg(color));
	m_titleContent = titleContent;
}

// 设置标题栏长度;
void WinTitle::setTitleWidth(int width)
{
	this->setFixedWidth(width);
}

void WinTitle::setParent(bool m_isParent)
{
	this->m_isParent = m_isParent;
}

void WinTitle::showNormal()
{
	m_pButtonRestore->setVisible(false);
	m_pButtonMax->setVisible(true);
}

// 设置标题栏上按钮类型;
// 由于不同窗口标题栏上的按钮都不一样，所以可以自定义标题栏中的按钮;
// 这里提供了四个按钮，分别为最小化、还原、最大化、关闭按钮，如果需要其他按钮可自行添加设置;
void WinTitle::setButtonType(ButtonType buttonType)
{
	m_buttonType = buttonType;

	switch (buttonType)
	{
	case MIN_BUTTON:
	{
		m_pButtonRestore->setVisible(false);
		m_pButtonMax->setVisible(false);
	}
	break;
	case MIN_MAX_BUTTON:
	{
		m_pButtonRestore->setVisible(false);
		m_pButtonMax->setVisible(true);
		m_pButtonMin->setVisible(true);
	}
	break;
	case ONLY_CLOSE_BUTTON:
	{
		m_pButtonMin->setVisible(false);
		m_pButtonRestore->setVisible(false);
		m_pButtonMax->setVisible(false);
	}
	break;
	default:
		break;
	}
}

// 保存窗口最大化前窗口的位置以及大小;
void WinTitle::saveRestoreInfo(const QPoint point, const QSize size)
{
	m_restorePos = point;
	m_restoreSize = size;
}

// 获取窗口最大化前窗口的位置以及大小;
void WinTitle::getRestoreInfo(QPoint& point, QSize& size)
{
	point = m_restorePos;
	size = m_restoreSize;
}

// 绘制标题栏背景色;
void WinTitle::paintEvent(QPaintEvent* event)
{
	//设置背景色;
	//QPainter painter(this);
	//QPainterPath pathBack;
	//pathBack.setFillRule(Qt::WindingFill);
	//pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
	//painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	//painter.fillPath(pathBack, QBrush(m_colorBackGround));

	//QPainter* painter = new QPainter(this);
	//painter->fillRect(this->rect(), QColor(22, 154, 218));


	// 当窗口最大化或者还原后，窗口长度变了，标题栏的长度应当一起改变;
	if (this->width() != this->parentWidget()->width())
	{
		this->setFixedWidth(this->parentWidget()->width());
	}
	QWidget::paintEvent(event);
}

// 双击响应事件，主要是实现双击标题栏进行最大化和最小化操作;
void WinTitle::mouseDoubleClickEvent(QMouseEvent* event)
{
	// 只有存在最大化、还原按钮时双击才有效;
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		// 通过最大化按钮的状态判断当前窗口是处于最大化还是原始大小状态;
		// 或者通过单独设置变量来表示当前窗口状态;
		if (m_pButtonMax->isVisible())
		{
			onButtonMaxClicked();
		}
		else
		{
			onButtonRestoreClicked();
		}
	}

	return QWidget::mouseDoubleClickEvent(event);
}


// 以下为按钮操作响应的槽;
void WinTitle::onButtonMinClicked()
{
	emit signalButtonMinClicked();
}

void WinTitle::onButtonRestoreClicked()
{
	m_pButtonRestore->setVisible(false);
	m_pButtonMax->setVisible(true);
	emit signalButtonRestoreClicked();
}

void WinTitle::onButtonMaxClicked()
{
	m_pButtonMax->setVisible(false);
	m_pButtonRestore->setVisible(true);
	emit signalButtonMaxClicked();
}

void WinTitle::onButtonCloseClicked()
{
	emit signalButtonCloseClicked();
}
