#include "CDlgTalkMoreMenu.h"
#include <QDebug>
#include <QIcon>
#include <QPainter>
#include <QtCore>
#include "CloudDiskWidget.h"
#include "CDlgTalk_grp_members.h"
#include <isCliHelpPublic.h>

#define SHADOW_WIDTH 10 // 阴影边框宽度;
CDlgTalkMoreMenu::CDlgTalkMoreMenu(QWidget* parent)
    : WinBasic(true, parent)
{
    ui.setupUi(this);

    memset(&m_var, 0 , sizeof(m_var));

    this->setAttribute(Qt::WA_DeleteOnClose, true);
    ui.toolBtnDish->setIcon(QIcon(":/Resources/Images/WinMain/aio_dish.png"));
    ui.toolBtnDish->setIconSize(QSize(64, 64));
    ui.toolBtnDish->setText(u8"网盘");
    ui.toolBtnDish->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui.toolBtnFacility->setIcon(QIcon(":/Resources/Images/WinMain/aio_facility.png"));
    ui.toolBtnFacility->setIconSize(QSize(64, 64));
    ui.toolBtnFacility->setText(u8"设备选择");
    ui.toolBtnFacility->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui.toolBtnFullScreen->setIcon(QIcon(":/Resources/Images/WinMain/aio_fullscreen.png"));
    ui.toolBtnFullScreen->setIconSize(QSize(64, 64));
    ui.toolBtnFullScreen->setText(u8"全屏");
    ui.toolBtnFullScreen->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui.toolBtnMember->setIcon(QIcon(":/Resources/Images/WinMain/aio_member.png"));
    ui.toolBtnMember->setIconSize(QSize(64, 64));
    ui.toolBtnMember->setText(u8"成员");
    ui.toolBtnMember->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui.toolBtnMember->setVisible(false);  //暂时不用

    //ui.toolBtnRemoteVideo->setIcon(QIcon(":/Resources/Images/WinMain/remoteVideo.png"));
    //ui.toolBtnRemoteVideo->setIconSize(QSize(64, 64));
    //ui.toolBtnRemoteVideo->setText(u8"远程视频");
    //ui.toolBtnRemoteVideo->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //ui.toolBtnShow->setIcon(QIcon(":/Resources/Images/WinMain/aio_show.png"));
    //ui.toolBtnShow->setIconSize(QSize(64, 64));
    //ui.toolBtnShow->setText(u8"双屏显示");
    //ui.toolBtnShow->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui.toolBtnThis->setIcon(QIcon(":/Resources/Images/WinMain/aio_this_video.png"));
    ui.toolBtnThis->setIconSize(QSize(64, 64));
    ui.toolBtnThis->setText(u8"本地视频");
    ui.toolBtnThis->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    ui.toolBtnMake->setIcon(QIcon(":/Resources/Images/WinMain/aio_make.png"));
    ui.toolBtnMake->setIconSize(QSize(64, 64));
    ui.toolBtnMake->setText(u8"发言人");
    ui.toolBtnMake->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui.toolBtnMake->setVisible(false);//暂时不用

    ui.toolBtnController->setIcon(QIcon(":/Resources/Images/WinMain/aio_contr.png"));
    ui.toolBtnController->setIconSize(QSize(64, 64));
    ui.toolBtnController->setText(u8"会议控制");
    ui.toolBtnController->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    ui.toolBtnDeviceCap->setIcon(QIcon(":/Resources/Images/WinMain/aio_device_screen.png"));
    ui.toolBtnDeviceCap->setIconSize(QSize(64, 64));
    ui.toolBtnDeviceCap->setText(u8"设备屏幕共享");    
    ui.toolBtnDeviceCap->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui.toolBtnDeviceCap->setStyleSheet("font-size:12px");
}

CDlgTalkMoreMenu::~CDlgTalkMoreMenu()
{
    disconnect(this);

   /* if (grp_members) {
        delete grp_members;
        grp_members = nullptr;
    }*/
}

//点击网盘
void CDlgTalkMoreMenu::on_toolBtnDish_clicked()
{
    emit signal_dish_select();
}

//变更设备共享状态
void CDlgTalkMoreMenu::up_device_screen_status(bool is_open) 
{
    if (is_open) {
        //
        _is_open = is_open;
        ui.toolBtnDeviceCap->setText(u8"停止共享");
    }
    else {
       //
        _is_open = is_open;
        ui.toolBtnDeviceCap->setText(u8"设备屏幕共享");
    }
}

//设备采集
void CDlgTalkMoreMenu::on_toolBtnDeviceCap_clicked() 
{
    //判断是开始共享 还是结束共享
    if (_is_open) {
        emit signal_device_screen_close();
    }
    else {
        emit signal_device_screen();
    }
  
}

void CDlgTalkMoreMenu::on_toolBtnFacility_clicked()
{
    emit signal_device_select();
}


CDlgTalkMoreMenu* CDlgTalkMoreMenu::showDialog(QPoint pt, bool device_screen_status, QWidget* parent)
{
    CDlgTalkMoreMenu* dlg = new CDlgTalkMoreMenu(parent);
    if (pt.isNull())
    {
        pt = QCursor::pos();
    }
    else
    {
        pt.setX(pt.x() - dlg->width() / 2);
        pt.setY(pt.y() - dlg->height());
    }
    
    dlg->up_device_screen_status(device_screen_status);
    dlg->show();
    dlg->activateWindow();

    dlg->move(pt);
    return dlg;
}


bool CDlgTalkMoreMenu::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == this && QEvent::WindowDeactivate == event->type())
    {
        this->close();
        return true;
    }
    return false;
}

void CDlgTalkMoreMenu::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));

    QColor color(0, 0, 0, 10);
    for (int i = 0; i < SHADOW_WIDTH; i++)
    {
        color.setAlpha(120 - qSqrt(i) * 40);
        painter.setPen(color);
        // 方角阴影边框;
     // painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
        // 圆角阴影边框;
        painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
    }
}

void CDlgTalkMoreMenu::on_toolBtnFullScreen_clicked()
{
    emit signal_full_screen();
    this->close();
}

//本地视频隐藏显示
void CDlgTalkMoreMenu::on_toolBtnThis_clicked()
{
    emit signal_this_video();
}

//会议控制按钮显示
void CDlgTalkMoreMenu::on_toolBtnController_clicked() 
{
    emit signal_controller();
}

//
void CDlgTalkMoreMenu::on_toolBtnMember_clicked() 
{
  //  if (!grp_members) {
    //CDlgTalk_grp_members* grp_members = new CDlgTalk_grp_members();
    //
    ////}
    //grp_members->show();
    emit signal_grp_members();

}

//
void CDlgTalkMoreMenu::isShowBtnController(bool isShow)
{
    ui.toolBtnController->setVisible(isShow);
}

void CDlgTalkMoreMenu::on_toolBtnMake_clicked() {
    emit signal_make_list();
}

void CDlgTalkMoreMenu::isShowBtnMake(bool isShow) {
    ui.toolBtnMake->setVisible(isShow);
}

void CDlgTalkMoreMenu::isShowBtnMember(bool isShow) {
    ui.toolBtnMember->setVisible(isShow);
}

