#include "WinMsgBox.h"
#include "ui_WinMsgBox.h"
#include <QPainter>

WinMsgBox::WinMsgBox(QWidget *parent) :
    QWidget(parent), m_eventLoop(NULL)
  , m_chooseResult(ID_CANCEL), ui(new Ui::WinMsgBox)
{
    ui->setupUi(this);
    initWindow();
}

void WinMsgBox::initWindow()
{
    loadStyleSheet("WinMsgBox");
    Qt::WindowFlags flags = this->windowFlags();
    this->setWindowFlags(flags | Qt::Window |Qt::FramelessWindowHint);
    connect(ui->pButtonOk, SIGNAL(clicked()), this, SLOT(onOkClicked()));
    connect(ui->pButtonCancel, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
     

    winTitle = new WinTitle(this);
    winTitle->setButtonType(MIN_BUTTON);
    winTitle->move(0, 0);
    connect(winTitle, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect(winTitle, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked())); 
   
    ui->MessageContent->setWordWrap(true);
    ui->MessageContent->setAlignment(Qt::AlignTop);
    ui->MessageContent->setFixedWidth(240); 
    QRect rect = ui->MessageContent->geometry();
    ui->MessageContent->setGeometry(rect.x()-15, rect.y(), rect.width(), rect.height());
 
 
}

void WinMsgBox::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/Resources/QSS/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        this->setStyleSheet("");
        QString qsstyleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(qsstyleSheet);
    }
    file.close();
}

void WinMsgBox::onButtonMinClicked()
{
    showMinimized();
}

void WinMsgBox::onButtonCloseClicked()
{
    close();
}



void WinMsgBox::mouseMoveEvent(QMouseEvent* e)
{
    if (m_mousePressed && (e->buttons() == Qt::LeftButton)) {
        if (mousePoint != QPoint(0, 0)) {
            move(e->globalPos() - mousePoint);
        }
        e->accept();
    }
}
void WinMsgBox::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        m_mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}
void WinMsgBox::mouseReleaseEvent(QMouseEvent*)
{
    m_mousePressed = false;
}


void WinMsgBox::setContentText(QString contentText)
{
  
    ui->MessageContent->setText(contentText); 
    ui->MessageContent->adjustSize();  
}

void WinMsgBox::setMessageType(MessageType messageType)
{
    switch (messageType)
    {
    case MESSAGE_INFORMATION:
        ui->MessageIcon->setPixmap(QPixmap(":/Resources/Images/WinMain/information.png"));
        break;
    case MESSAGE_WARNNING:
        ui->MessageIcon->setPixmap(QPixmap(":/Resources/Images/WinMain/warnning.png"));
        break;
    case MESSAGE_QUESTION:
        ui->MessageIcon->setPixmap(QPixmap(":/Resources/Images/WinMain/question.png"));
        break;
    default:
        break;
    }
}

void WinMsgBox::setButtonType(MessageButtonType buttonType)
{
    switch (buttonType)
    {
    case BUTTON_OK:
    {
        ui->pButtonOk->setText(QStringLiteral("确定"));
        ui->pButtonCancel->setVisible(false);
    }
        break;
    case BUTTON_OK_AND_CANCEL:
    {
        ui->pButtonOk->setText(QStringLiteral("确定"));
        ui->pButtonCancel->setText(QStringLiteral("取消"));
    }
          break;
    case BUTTON_CLOSE:{
        ui->pButtonOk->setVisible(false);
        ui->pButtonCancel->setText(QStringLiteral("关闭"));
    }
        break;
    default:
        break;
    }
}

void WinMsgBox::setMessageContent(QString messageContent)
{
    ui->MessageContent->setText(messageContent);
}

// 显示提示框
// isModelWindow 参数设置提示框是否是模态
int WinMsgBox::showWinMsgBox(QWidget* parent, const QString &title, const QString &contentText, MessageType messageType, MessageButtonType messageButtonType, bool isModelWindow)
{
    WinMsgBox * myMessageBox = new WinMsgBox(parent);
    myMessageBox->setContentText(contentText);
    myMessageBox->setMessageType(messageType);
    myMessageBox->setButtonType(messageButtonType);
    if (isModelWindow)
    {
        return myMessageBox->exec();
    }
    else
    {
        myMessageBox->show();
    }

    return 0;
}

int WinMsgBox::exec()
{
    this->setWindowModality(Qt::WindowModal);
    show();
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();
    return m_chooseResult;
}

void WinMsgBox::onOkClicked()
{
    m_chooseResult = ID_OK;
    close();
}

void WinMsgBox::onCancelClicked()
{
    m_chooseResult = ID_CANCEL;
    close();
}

void WinMsgBox::closeEvent(QCloseEvent *event)
{
    if (m_eventLoop != NULL)
    {
        m_eventLoop->exit();
    }
   // event->accept();
}

WinMsgBox::~WinMsgBox()
{
    delete ui;
    if (winTitle) {
        delete winTitle;
        winTitle = nullptr;
    }
}
