#include "noticewidget.h"
#include "qdebug.h"

//#include <QDesktopWidget>
#include    <qscreen.h>

#include    <tchar.h>
#include    "qyMcMainCommon_qt.h"
#include    "ctxQmc_sm.h"




NoticeWidget::NoticeWidget(QWidget* parent)

{

    this->setAttribute(Qt::WA_DeleteOnClose, true);
   
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  //定时器，定时消失
    mTimerPtr = new QTimer();
    connect(mTimerPtr, SIGNAL(timeout()), this, SLOT(OnTimerTimeout()), Qt::UniqueConnection);
    mTimerPtr->setInterval(1000);
    mTimerPtr->start();




}

NoticeWidget::~NoticeWidget()
{
    if (mTimerPtr) {
        if (mTimerPtr->isActive()) {
            mTimerPtr->stop();
        }
        delete mTimerPtr;
    }


    if (_label) {
        delete _label;
        _label = nullptr;
    }
    if (_layout) {
        delete _layout;
        _layout = nullptr;
    }
    
    deleteLater();
}

void NoticeWidget::OnTimerTimeout()
{
     mTimerCount = mTimerCount - 1000;

    if (mTimerCount <= 0) {
    
        close();
    
    }
    
}

//设置要显示的消息
void NoticeWidget::SetMesseage(const QString& msg, const QString& fontColor , int delay_ms)
{
    QStringList strList = msg.split("\n");
    QFontMetrics fontMetrics(font());
    mListLinesLen.clear();

    int tmpW = 0;
    int maxLineLen = 1; //最长那一行的长度
    foreach(QString s, strList) {
        tmpW = fontMetrics.horizontalAdvance(s);
        mListLinesLen.append(tmpW);
        if (maxLineLen < tmpW) {
            maxLineLen = tmpW;
        }
    }

    mParentPtr = parentWidget();
    mBaseWidth = fontMetrics.horizontalAdvance(msg);
    mBaseHeight = fontMetrics.lineSpacing() + PATCH_HEIGHT;
    mMinHeight = (mBaseWidth * mBaseHeight) / maxLineLen + 1;//面积除以最长的宽就是最小的高

    //设置宽高
    ChangeSize();

    //换行
    //setWordWrap(true);

    //设置显示内容
   // setText(msg);

    //居中
    if (nullptr != mParentPtr) {
        move((mParentPtr->width() - width()) >> 1, mParentPtr->height());
    }

    

    setVisible(true);//显示
    setStyleSheet(QString(STYLE_SHEET).arg(fontColor).arg(TRANSPARENT_MAX_VAL));//设置样式，不透明
    mTimerCount = delay_ms / TIMER_INTERVAL_MS + 1;//延时计数计算
    mTransparentVal = TRANSPARENT_MAX_VAL;
}

//跟随父窗口大小变化
void NoticeWidget::ChangeSize()
{
    if (nullptr != mParentPtr) {
        double wd = mParentPtr->width() * SIZE_SCALE;//宽度占父窗口的80%
        //提示内容多少决定提示框面积，长方形面积s=mBaseHeight*mBaseWidth
        //面积s固定，当mBaseWidth跟随窗体宽度变大而增大，那么mBaseHeight应当变小，才维持s固定
        int newH = (mBaseHeight * mBaseWidth) / wd + PATCH_HEIGHT;
        if (newH < (mMinHeight + mBaseHeight)) {//设定最小高度
            newH = mMinHeight + mBaseHeight;
        }
        else {
            foreach(int lineLen, mListLinesLen) {
                if (lineLen > wd) {//某一行长度大于当前宽度就会发生折行，高度需要增加
                    newH += mBaseHeight;
                }
            }
        }

        setFixedSize((int)wd, newH);
    }
}

//显示消息，可通过设置delay_ms=0来立即关闭显示
void NoticeWidget::showNotice(QWidget* parent, const QString& msg, const QString& fontColor , const int delay_ms)
{
    CCtxQmc_sm* pProcInfo = (CCtxQmc_sm*)QY_GET_procInfo_isCli();

    if (IsWindow(pProcInfo->m_var.hWnd_noticeWidget)) {
        MACRO_SetForegroundWindow(pProcInfo->m_var.hWnd_noticeWidget);
        return;
    }
    NoticeWidget* dlg = new NoticeWidget(parent);
    pProcInfo->m_var.hWnd_noticeWidget = (HWND)dlg->winId();
   
    //QRect rc = QGuiApplication::screenAt(QCursor().pos())->geometry();

   // 
 /*   QLabel * txt_lab = new QLabel( , &);
    txt_lab->setAlignment(Qt::AlignCenter);*/

    QRect rc = QApplication::primaryScreen()->geometry();


    QString labelSheet;
    if (rc.width() > 3500) {
        dlg->resize(1600, 100);
        labelSheet = "color:#f60;font-size:44px;font-weight:bold;";
    }
    else {
        dlg->resize(800, 50);
        labelSheet = "color:#f60;font-size:22px;font-weight:bold;";
    }

    dlg->resize(800, 50);

    dlg->move(((rc.width() - dlg->width()) / 2), rc.height() - dlg->height());

    dlg->_label = new QLabel(dlg);
    
    dlg->_label->setText(msg);
 
    dlg->_label->setAlignment(Qt::AlignCenter);
    dlg->_label->setStyleSheet(labelSheet);
    dlg->setStyleSheet("background-color:rgb(30, 39, 71);");


    dlg->_layout = new QVBoxLayout(dlg);
    dlg->_layout->addWidget(dlg->_label);


    dlg->show();


    dlg->mTimerCount = delay_ms;

   // 

#if 0
    if (pt.isNull())
    {
        pt = QCursor::pos();
    }
    else
    {
        pt.setX(pt.x() - dlg->width() / 2);
        pt.setY(pt.y() - dlg->height());
    }
    dlg->show();
    dlg->activateWindow();

    dlg->move(pt);
#endif



    /*
    if (mTimerPtr->isActive()) {
        mTimerPtr->stop();
        setVisible(false);
        close();
        
    }

    //消息为空直接返回
    if (msg.isEmpty() || 0 >= delay_ms) {
        return;
    }

    mFontColor = fontColor;

    setParent(parent);
    SetMesseage(msg, fontColor,delay_ms);
    mTimerPtr->start(TIMER_INTERVAL_MS);//开始计数

    show();
    */
   
}
