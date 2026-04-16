
#ifndef __QYWMCOMM_H__
#define __QYWMCOMM_H__	/* { */


// 以下Windows的自定义消息

//
#define CONST_wmComm_EV_RXCHAR		WM_USER+7				// A character was received and placed in the input buffer. 



//
#define		CONST_qyWm_comm						(  WM_USER  +  11  )
#define		QY_WM_COMM							CONST_qyWm_comm			//  只能用SendMessage( )发送
#define		QY_WM_PUTDATA						WM_USER + 13			//  只能用SendMessage( )发送
#define		CONST_qyWm_postComm					(  WM_USER  +  14  )	//  主要用PostMessenger(  )发送，用wParam, lParam来表示发送信息
#define		CONST_qyWm_trayNotify				(  WM_USER  +  15  )	//  系统托盘

#define		CONST_qyWm_graphNotify_mediaFile	(  WM_USER  +  16  )	//  2009/05/05
#define		CONST_qyWm_graphNotify_mediaDevice	(  WM_USER  +  17  )	//  2012/02/27
#define		CONST_qyWm_postVideoAmplifierOk  	(  WM_USER  +  18  )	
#define		CONST_qyWm_postVideoAmplifierCancel	(  WM_USER  +  19  )	
#define		CONST_qyWm_postRaiseShare       	(  WM_USER  +  20  )



//  以下为WMBUF的头结构

#define		MACRO_qyWmBuf_commHead 				unsigned  int		uiType;		\
												HWND				hWndSrc;	\
												int					unused;	

typedef  struct  __qyWmBufCommHead_t			{
				 MACRO_qyWmBuf_commHead
}				 QY_WMBUF_COMMHEAD;


typedef  struct  __qyWmBufComm_t				{
				 MACRO_qyWmBuf_commHead

				 union							{
					//  char						buf[1024];
					struct						{
						BOOL					bLeftStopped;
						BOOL					bRightStopped;
					}							mcRootDaemonRefreshStopped;
					struct						{
						BOOL					bLeftStopped;
						BOOL					bRightStopped;
						BOOL					bBottomStopped;
					}							mcBarDaemonRefreshStopped;
					struct						{
						int						iViewType;
					}							getViewType;
					struct						{
						int						iDocType;
					}							getDocInfo;
					struct						{
						int						iDocType;
						void		*			pBarCfg;
					}							tellDocInfo;
					struct						{
						int						barId;
					}							newMonBar;
					struct						{
						int						id;
					}							itemChanged;
					void			*			pWeb;
					struct						{
						HWND					hList;								//  对于有多个listCtrl的对话框有用
						TCHAR					colName[CONST_qyMaxLabelLen  +  1];
						int						nCol;
					}							getnCol;
					struct						{
						char					bOk;
						int						IDD;
					}							chkPage;
					struct						{
						int						curnRow;
					}							refreshData;						//  2003/9/5.
					struct						{
						HWND					hWnd;
						void			*		pIDropTarget;
					}							getIDropTarget;						//  2007/05/25
					//
					struct						{							
						int						iTaskId_activated;					
					}							activateImTask;
					//
					struct						{
						unsigned  int			uiCmd;
						BOOL					bManager;
						int						curnItem;
					}							requestToSpeak;
					struct						{
						int						iTaskId;
						BOOL					bNotExists;							//  2009/09/10
						//
						BOOL					bChked;								//  2009/09/13
						//
					}							chkTask;
					struct						{
						int						iIndex_sharedObject;
						int						iTaskId;							//  2014/12/23
						BOOL					bNotExists;

					}							chkSharedObject;					//  2009/09/13
					struct						{
						int						iTaskId;
						struct					{
							unsigned  __int64	ui64Id;						
						}						idInfo;
					}							freeCapImage;						//  2010/09/12
					struct						{
					}							freeCapImages;						//  2010/12/27
					
					//  2015/08/03
					struct						{
						void				*	pPROC_offlineRes_u;
						//
						unsigned  __int64		ui64Id_req;
						//
						unsigned  int			uiTranNo_wait;

						//
						int						iTaskId;
						unsigned  int			uiTranNo_real;

					}							procOfflineRes;

					//
					struct {
						void* pObjAddr;
						//
					}							getObjAddr;

				 }								u;						
}		QY_WMBUF_COMM;


//  2016/05/24
typedef  struct  __qyWmBufCommand_t				{
				 MACRO_qyWmBuf_commHead

				 //
				 int							iCmdId;				
				 HWND							hParent_expected;

}		 QY_wmBuf_command;



//
typedef  struct  __qyWmBufPutData_t				{
				 MACRO_qyWmBuf_commHead
				 union							{
						 char					buf[65536  *  2];		
				 }								u;
	
	#define MAX_QY_WMBUF_PUTDATALEN		sizeof( ( ( QY_WMBUF_PUTDATA * )0 )->u )
	
}					               QY_WMBUF_PUTDATA;


typedef  struct  __qyWmBufAddIp_t				{
				 MACRO_qyWmBuf_commHead

				 char							ipBuf[CONST_qyMaxIpLen  +  1];
				 char							startIpBuf[CONST_qyMaxIpLen  +  1];
				 char							endIpBuf[CONST_qyMaxIpLen  +  1];
				 WCHAR							desBuf[256];
				 char							errBuf[256];
}		 QY_WMBUF_ADDIP;


typedef  struct  __qyWmBufGetIdcInfo_t			{
				 MACRO_qyWmBuf_commHead

				 HWND							hCtrl;
				 int							flg;
				 //  char					*		p;
}		 QY_WMBUF_GETIDCINFO;


//  处理TreeView的消息格式
typedef  struct  __qyWmBufProcTv_t				{
				 MACRO_qyWmBuf_commHead

				 HANDLE							hItem;
				 char							mac[12  +  1];
}		 QY_WMBUF_PROCTV;


//  2004/07/28
typedef  struct	 __qyWmBufFocusOnItem_t			{
				 MACRO_qyWmBuf_commHead
				 BOOL							bRoot;				//
				 HANDLE							htItem;				//  从该节点开始查找
				 TCHAR							name[255  +  1];	//  将聚焦的节点名字
}		 QY_WMBUF_FOCUSONITEM;



// 以下QY_WMBUF_*的类型

#define		QY_WMPARAM_MCPUTROOTDISPLAYDATA							3			//  QY_WM_PUTDATA送rootList的显示参数
#define		QY_WMPARAM_GETVIEWTYPE									8			//  QY_WM_COMM 取iViewType 
// #define  QY_WMPARAM_MCWAITTODESTROY								9			//  QY_WM_COMM要求停止后台刷新, 等待后台刷新完成, 以准备窗口释放
#define		QY_WMPARAM_GETDOCINFO									11			//  QY_WM_COMM要求取得docInfo
#define		QY_WMPARAM_TELLDOCINFO									12			//  QY_WM_COMM要求告知docInfo
#define		QY_WMPARAM_UPDATEBAR									13			//  QY_WM_COMM要求更新工具栏显示
#define		QY_WMPARAM_ITEMCHANGED									14			//	QY_WM_COMM要求相关视跟着刷新
#define		QY_WMPARAM_PREPARETOCLOSE								15			//	QY_WM_COMM要求子窗口退出
#define		QY_WMPARAM_NEWWEBBROWSER								16			//  QY_WM_COMM要求建立一新的浏览窗口
#define		CONST_qyWmParam_refreshData								17			//  QY_WM_COMM要求刷新文档
#define		QY_WMPARAM_REFRESHDATA									CONST_qyWmParam_refreshData			
#define		CONST_qyWmParam_getnCol									18			//  QY_WM_COMM从CQyVirtualListView中根据列名取列位置
#define		CONST_qyWmParam_chkPage									19			//  QY_WM_COMM从ActivePage中校验数据
#define		CONST_qyWmParam_export									20			//  CONST_qyWm_comm
#define		CONST_qyWmParam_show									21			//  CONST_qyWm_comm
#define		CONST_qyWmParam_addIp									22			//  CONST_qyWm_comm, 添加IP  
#define		CONST_qyWmParam_getIdcInfo								23			//  CONST_qyWm_comm, 取与控件关联的信息
#define		CONST_qyWmParam_getSelInfo								24			//  CONST_qyWm_comm, 读取被选中的项内容和其他信息
#define		CONST_qyWmParam_refreshTvItem							25			//  CONST_qyWm_comm, 刷新树窗口节点
#define		CONST_qyWmParam_refreshOthers							26			//  CONST_qyWm_comm, 刷新另一窗口
#define		CONST_qyWmParam_delItem									27			//  CONST_qyWm_comm, 删除一节点
#define		CONST_qyWmParam_showSecChkEvent							28			//  CONST_qyWm_comm, 显示检查事件
#define		CONST_qyWmParam_setFocusOnRightView						29			//  CONST_qyWm_comm, 将聚焦右边视图
#define		CONST_qyWmParam_focusOnItem								30			//  CONST_qyWm_comm, 将聚焦某节点
#define		CONST_qyWmParam_focusOnItem1							31			//  CONST_qyWm_comm, 将聚焦某节点, 从rightView发起，由frame来存储此数据包，返回对rightView的控制，然后通过此数据包来接着让leftView执行变焦工作
//
#define		CONST_qyWmParam_getDropTarget							33			//  dropTarget
#define		CONST_qyWmParam_activateImTask							34			//  2007/08/11

//
#define		CONST_qyWmParam_getObjAddr								35


//
#define		CONST_qyWmParam_requestToSpeak							38			//  2009/02/24
#define		CONST_qyWmParam_chkTask									39			//  2009/09/10
#define		CONST_qyWmParam_chkSharedObject							40			//  2009/09/13
#define		CONST_qyWmParam_freeCapImage							41			//  2010/09/12
#define		CONST_qyWmParam_freeCapImages							42			//  2010/12/27

//  2015/08/03
#define		CONST_qyWmParam_procOfflineRes							70			//  2015/08/03
#define		CONST_qyWmParam_command									71			//  2016/05/24

//
//  CONST_qyWm_postComm wParam
#define		CONST_qyWmParam_setActiveWindow							201			//  
#define		CONST_qyWmParam_idcInited								202			//  
#define		CONST_qyWmParam_refreshContent							203			//  
#define		CONST_qyWmParam_refreshLayout							204			//  2010/12/22

//
#define		CONST_qyWmParam_msgArrive								210			//  
#define		CONST_qyWmParam_guiMsgArrive							211			//  2009/03/24
#define		CONST_qyWmParam_gpsMsgArrive							212			//  2012/04/20

//
#define		CONST_qyWmParam_avRecord_start							360			//  2008/10/05, 
#define		CONST_qyWmParam_task_end								362			//

//
//  #define		CONST_qyWmParam_chkTmpMemorys						363			//  2010/09/17

#define		CONST_qyWmParam_broadcastRecorderStatus					365			//  2009/02/27
#define		CONST_qyWmParam_notifyQmShmCmdStatus					366			//  2009/12/21
#define		CONST_qyWmParam_mouseMove								367			//  2009/12/29
#define		CONST_qyWmParam_notifyProgressEnd						368			//  2010/08/14
#define		CONST_qyWmParam_bNeedRefresh_activeMems_from			369			//  2012/04/01
#define		CONST_qyWmParam_gps										370			//  2012/04/18
#define		CONST_qyWmParam_curSharedObjUsrChanged_mgr				371			//  2012/05/12
#define		CONST_qyWmParam_curSharedObjUsrChanged_shadow			372			//  2012/05/12
#define		CONST_qyWmParam_toStartLocalAudioPlayer					373			//  2013/05/26
#define		CONST_qyWmParam_doPost_drawCapImages					374			//  2014/04/12
#define		CONST_qyWmParam_invalidate_bgWall						375			//  2016/03/15
#define		CONST_qyWmParam_freeCapImageBySth_bgWall				376
#define		CONST_qyWmParam_misMsgInited							377			//  2018/10/30
#define		CONST_qyWmParam_confAccepted							378			//  2018/11/01
#define		CONST_qyWmParam_closeConsoleWall						379
#define		CONST_qyWmParam_needRefreshImgs							380

//
#define		CONST_qyWmParam_endThread								402			//  2010/05/03


//  2016/06/29. qisMsg_open.h
//  CONST_qisMsg_ex_min		3000
//  CONST_qisMsg_ex_max		3999


//
#define		CONST_qyWmParam_misMsg_base								5000		//  misMsg wmBuf iType


extern  QY_DMITEM  CONST_wmBufTypeTable[];


// 以下QY_WM_*的返回值
#define		CONST_qyWmRc_ok											6543
#define		CONST_qyWmRc_err										-1
#define		CONST_qyWmRc_delay										6544
#define		QY_RC_WMOK												CONST_qyWmRc_ok		// 成功
#define		QY_RC_WMDELAY											CONST_qyWmRc_delay	// 随后再发响应信息


#endif /* } */


