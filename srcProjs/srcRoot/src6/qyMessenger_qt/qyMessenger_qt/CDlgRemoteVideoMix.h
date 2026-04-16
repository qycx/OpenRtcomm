#pragma once

#include <QMainWindow>
#include "ui_CDlgRemoteVideoMix.h"

#include	"stdafx.h"

#include	<tchar.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include <QPushButton>
#include <QFileSystemModel>

#ifdef  __useMfc__
#include	<afxmt.h>
#include	<afxdb.h>
#endif

#include "qyMcMainCommon.h"
#include "qyCfg.h"
#include "qyWmComm.h"
#include "qyCommProc.h"



//#include "commonSock.h"
#include "qyDefs_open.h"



//#include "qyAuthCommon.h"
//#include "qyCommonFunc5.h"
#include "qnmCommProc.h"


#include "qnmCommProc_mis.h"

#include "qyMcMainCommon.h"
#include "ctxQmc.h"
#include "qyCusResTemp.h"
#include "qmcStruct_defs.h"

#include "funcsForIsCliHelp.h"

#include <QTimer>
#include <QSortFilterProxyModel>
#include <QDateTime>

#include "dlgobjsproc.h"
#include "dlgtalkproc.h"

#include <QThread>



QT_BEGIN_NAMESPACE
namespace Ui { class CDlgRemoteVideoMixClass; };
QT_END_NAMESPACE

class CDlgRemoteVideoMix;
class ZoomLabel;

class Worker : public QObject
{
	Q_OBJECT
public:
	Worker(CDlgRemoteVideoMix* mix, const std::wstring& path);
	virtual ~Worker();
	void stop();
	void ChangePath(const std::wstring& path);
private:
	bool m_isRun = false;
	std::wstring m_path;
	bool m_isPathChange = false;
	CDlgRemoteVideoMix* m_mix = nullptr;
public slots:
	void doWork();
signals:
	void progress(int value);
	void workFinished();
};



class FileSystemSortProxyModel : public QSortFilterProxyModel
{
public:
	FileSystemSortProxyModel(QObject* parent = nullptr) : QSortFilterProxyModel(parent) {}

protected:
	bool lessThan(const QModelIndex& left, const QModelIndex& right) const override
	{
		QFileSystemModel* fsm = qobject_cast<QFileSystemModel*>(sourceModel());
		if (!fsm) return QSortFilterProxyModel::lessThan(left, right);

		// 获取文件信息
		QFileInfo leftInfo = fsm->fileInfo(left);
		QFileInfo rightInfo = fsm->fileInfo(right);

		// 如果是目录，优先显示
		if (leftInfo.isDir() && !rightInfo.isDir())
			return sortOrder() == Qt::AscendingOrder;
		if (!leftInfo.isDir() && rightInfo.isDir())
			return sortOrder() == Qt::DescendingOrder;

		// 按修改日期排序
		return leftInfo.lastModified() < rightInfo.lastModified();
	}
};

class CDlgRemoteVideoMix : public QMainWindow
{
	Q_OBJECT

public:
	CDlgRemoteVideoMix(QWidget *parent = nullptr);
	~CDlgRemoteVideoMix();

	void Init(HWND hCurTalk, DLG_TALK_var* pMgrVar, QY_wmBuf_command* pWmBuf, TALKER_shadow_mgr* pShadowMgr, HWND	hMgr, HWND	hShow);

	bool OnInitDialog();

	int dlgObjs_OnOK(HWND  hDlg, void* pVarParam, int iItemSelected);

	void InsertButton(int buttonId, QPushButton* btn);
	void DeleteButton(int buttonId);
	void DeleteAllButton();
	void SetButtonText(int buttonId, const QString& text);

	HWND GetVideoWindow();
	QRect GetVideoGeometry();

	void startWork();
	void stopWork();

	void doNewFile(const QString& fileName);



	DLG_objs_var	m_var;

public slots:
	void handleButtonClick(int buttonId);
	void onTimeout();
	void onTimeoutReflash();
	void onItemDoubleClicked(const QModelIndex& index);
	void onItemDoubleClicked_bak(const QModelIndex& index);
	void onDirectoryLoaded(const QString& path);
	void updateProgress(int value);
	void onWorkFinished();
	void onNewFile(const QString& fileName);
	void onSaveClick();
	void onSoundClick();

signals:
	void to_remotevideo_resize();
	void to_remotevideo_close();
	void new_file(const QString& fileName);

protected:
	void InitControl();
	void InitControl_bak();

	void InitListViewFile();

	void SetIsSaveButtonText(bool isSave);
	void SetSoundButtonText(bool isSave);

	void doButtonClick(int buttonId);
	void resizeEvent(QResizeEvent* event) override;
	void layoutControl(const QSize& size);

	void closeEvent(QCloseEvent* event) override;
	bool eventFilter(QObject* obj, QEvent* event) override;

	void SetControlVisable(bool visible);

	void ReadData();

	void traverseDirectory(const QModelIndex& parentIndex);

private:
	Ui::CDlgRemoteVideoMixClass *ui;

	HWND m_hCurTalk;
	DLG_TALK_var* m_pMgrVar;
	QY_wmBuf_command* m_pWmBuf;
	TALKER_shadow_mgr* m_pShadowMgr;
	HWND m_hMgr;
	HWND m_hShow;

	QTimer* m_imgTimer = nullptr;
	QTimer* m_timerReflash = nullptr;

	bool m_isFullscreen = false;
	QRect m_normalGeometry;

	DYN_BMP_RULE				m_dynBmpRule_selected;

	QMap<int, QPushButton*> m_mapButton;

	QString m_path;

	FileSystemSortProxyModel* m_proxyModel;
	QFileSystemModel* m_fileSystemModel;

	QThread* m_thread = nullptr;
	Worker* m_worker = nullptr;

	ZoomLabel* m_ZoomLabelImg = nullptr;

	bool m_isSaveICFile = false;
	bool m_isPlaySound = false;
};
