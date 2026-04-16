#ifndef CLOUD_DISK_WIDGET_H_
#define CLOUD_DISK_WIDGET_H_


#include <QWidget>
#include "ui_CloudDiskWidget.h"
#include "WinBasic.h"

#include    "qyMcMainCommon_qt.h"
#include    "dlgOfflineResProc.h"
#include <QMimeData>


//
class CloudDiskWidget : public WinBasic
{
    Q_OBJECT

        //
public:
        DlgOfflineRes_var  m_var;
        int table_row;
        int id;

public:
    //static void ShowDialog(QWidget* parent = Q_NULLPTR);
public:
    CloudDiskWidget(QWidget *parent = Q_NULLPTR);
    ~CloudDiskWidget();
    //
    BOOL  bSetDlgInfo(int  iWndContentType, int  iSubType, LPCTSTR  title);
    int init();
    BOOL  bDisplay_usIndex_page();
    BOOL  bRefresh();
    int  getDisplayStr_res_retrieved(RES_inProcess* pMem, TCHAR* tBuf, int  cnt);
    int  getDisplayStr_res_beingProced(RES_inProcess* pMem, TCHAR* tBuf, int  cnt);

    BOOL  bDisplay();
    BOOL  bRefreshBtns();
    BOOL  ResesDisplay();

    //
    LRESULT OnQyComm(WPARAM, LPARAM);
    void OnBnClickedButtondelete();
    void OnBnClickedButtondownload();

   

    //
private:
    void dragEnterEvent(QDragEnterEvent* event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent* event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent* event) Q_DECL_OVERRIDE;

    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
    bool postMessageQt(MSG* message, qintptr* result);
    void paintEvent(QPaintEvent* event);
    virtual void closeEvent(QCloseEvent* ev);
    void clearTableWidget(QTableWidget* table);
    //刷新文件列表
    void reloadFileList();
    //获取当前选中id
    QString getCurrentId();
    //更新状态显示
    void updateProcessStatus(QString id, QString txt);
    //上传或者下载后 删除状态
    void removeProcessStatus(QString id);

    void dlgOfflineRes_upload_qt(QString strFileName);

    void removeProessAll();
private slots:
    void slot_edit_return();
    void slot_button_page();
    void slot_button_file();
    void slot_onTableClicked(int row, int col);
    void on_btnSearch_clicked();
private:
    Ui::CloudDiskWidget ui;
};
#endif