#ifndef _NoticeWidget_H_
#define _NoticeWidget_H_

#include <QWidget>
#include <QTimer>
#include <QList>
#include <qlabel.h>
#include <QVBoxLayout>
#include <QApplication>

//定时器间隔，单位ms
#define TIMER_INTERVAL_MS   50

//默认提示时间1s
#define NOTICE_DEF_DELAY_CNT     (1000/TIMER_INTERVAL_MS)

//透明度最大值255，也就是不透明
#define TRANSPARENT_MAX_VAL 210

//透明度递减值
#define TRANSPARENT_CUT_VAL (TRANSPARENT_MAX_VAL/NOTICE_DEF_DELAY_CNT + 1)

//大小比例
#define SIZE_SCALE  0.4

//高度补偿
#define PATCH_HEIGHT    10

//样式，字体颜色：白色；圆角；背景色透明度
//#define STYLE_SHEET "color:%1;font-size:20px;font-weight:bold;border-radius:8px;background-color:rgba(38, 180, 249, %2);"
#define STYLE_SHEET "color:%1;font-size:20px;font-weight:bold;border-radius:8px;background-color:rgba(30, 39, 71, %2);"

class NoticeWidget :public QWidget
{
    Q_OBJECT

public:
    static void showNotice(QWidget* parent, const QString& msg, const QString& fontColor, const int delay_ms = 2000);

public:
    explicit NoticeWidget(QWidget* parent = 0);
    ~NoticeWidget();

private:
    void SetMesseage(const QString& msg, const QString& fontColor , int delay_ms);
    void ChangeSize();

public slots:
    void OnTimerTimeout();

private:
    QWidget* mParentPtr = nullptr;
    QTimer* mTimerPtr =nullptr;
    int mTimerCount = 0;
    int mBaseWidth = 0;  //按一行时算的宽度
    int mBaseHeight = 0; //一行高度
    int mMinHeight = 0; //最小高度
    int mTransparentVal = 0;//透明度0~255，值越小越透明
    QList<int> mListLinesLen;
    QString mFontColor; //字体颜色

    QLabel* _label = nullptr;
    QVBoxLayout* _layout = nullptr;


};

#endif // _NoticeWidget_H_