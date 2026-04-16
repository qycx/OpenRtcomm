
#define  __noDbg_new__

#include "WinEmotion.h"  
#include <QPainter>
#include <QFocusEvent>
#include <QMovie>
#include <QScrollBar>
#include <QStyleOption> 
#include "WinEmotionlabelItem.h" 
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <qdir.h>
#include    "stdafx.h"
#include    "qyMcMainCommon_qt.h"
#include    "ctxQmc_qt.h"

//
const int emotionColumn = 14;
int emotionRow = ceil(100 / 14);

WinEmotion::WinEmotion(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::WinEmotion)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);
    initControl();
}

WinEmotion::~WinEmotion()
{
    delete ui;
    //if (winEmotionLabel)
    //{
    //	delete winEmotionLabel;
    //	winEmotionLabel = nullptr;
    //}
}

void WinEmotion::initControl()
{
    //ui->scrollArea->verticalScrollBar()->setSingleStep(32);
    //for (int row = 0; row < emotionRow; row++)
    //{
    //	for (int column = 0; column < emotionColumn; column++)
    //	{
    //		winEmotionLabel = new WinEmotionlabelItem(this);
    //		//winEmotionLabel->setEmotionName(row * emotionColumn + column);
    //		connect(winEmotionLabel, &WinEmotionlabelItem::emotionClicked, this, &WinEmotion::addEmotion);
    //		ui->gridLayout->addWidget(winEmotionLabel, row, column);
    //	}
    //}
    CCtxQyMc* pQyMc = g_pQyMc;
    CCtxQmc_qt* pProcInfo = (CCtxQmc_qt*)pQyMc->get_pProcInfo();

    QString emojiPath = QString::fromUtf16((char16_t*)pProcInfo->m_var.installDir_qt) + "/resource/emoji/";
    //
    QFile f(emojiPath + "emoji.json");
    f.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();
    QJsonArray arry = doc.array();

    QMap<int, QString> map_emoj;
    for (size_t i = 0; i < arry.size(); i++)
    {
        QJsonObject root = arry[i].toObject();
        map_emoj[root["idx"].toString().toInt()] = root["file"].toString();

    }
    QList<QString> result_file = map_emoj.values();
    emotionRow = ceill((double)result_file.size() / (double)emotionColumn);
    QFile file(":/Resources/QSS/WinEmotion.css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        this->setStyleSheet("");
        QString qsstyleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(qsstyleSheet);
    }
    file.close();
    this->setFixedHeight(emotionRow * 40 + 30);
    ui->scrollArea->verticalScrollBar()->setSingleStep(40);
    int index = 0;
    for (int row = 0; row < emotionRow; row++)//行数
    {
        for (int i = 0; i < emotionColumn; ++i)//列数
        {
            if (index < result_file.size() - 1)
            {
                WinEmotionlabelItem* pItem = new WinEmotionlabelItem(this);
                pItem->setEmotionName(emojiPath, result_file[index]);
                connect(pItem, &WinEmotionlabelItem::emotionClicked, this, &WinEmotion::addEmotion);
                ui->gridLayout->addWidget(pItem, row, i);
            }
            index++;
        }
    }
}

void WinEmotion::addEmotion(QString code)
{
    hide();
    emit signalWinEmotionHide();
    emit signalEmotionItemClicked(code);
}

void WinEmotion::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    __super::paintEvent(event);
}

void WinEmotion::showEvent(QShowEvent* event)
{
    setFocus();
    __super::showEvent(event);
}

void WinEmotion::focusOutEvent(QFocusEvent* event)
{
    QWidget* widget = qApp->widgetAt(QCursor::pos());
    if (widget != this && widget != ui->emotionWidget)
    {
        hide();
        emit signalWinEmotionHide();
    }
    __super::focusOutEvent(event);
}
