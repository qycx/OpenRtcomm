#include <myTypes.h>


#ifndef  __QYMCMAINDEFS_H__
#define  __QYMCMAINDEFS_H__	/*  {  */


// 环境类型的定义
#define		QY_ENVTYPE_MCGUI							0
#define		QY_ENVTYPE_MCDAEMON							1



/////////////////




//////////////////////////////////
//

//  树类型定义
#define		CONST_qyTreeType_general					0
#define		CONST_qyTreeType_switch						1		//  交换机视图
#define		CONST_qyTreeType_usrConnection				2		//  用户接入视图
#define		CONST_qyTreeType_networkSpeed				3		//  网络流量监控视图
//  #define		CONST_qyTreeType_assets					4		//  资产视图
#define		CONST_qyTreeType_cfgSp						5		//  补丁配置列表
#define		CONST_qyTreeType_pc							6		//  计算机管理视图，2006/06/12
#define		CONST_qyTreeType_imObj						7		//  即时通信对象视图，2007/05/04


extern  QY_DMITEM  CONST_qyTreeTypeTable[];



#if  0

// 字符串常量定义
#define		QY_MC_HINT_NODSN							_T(  "无法打开数据库，程序将退出。"  )
#define		QY_MC_HINT_NONEWWINDOW						_T(  "资源限制，不能再打开新窗口了。"  )
#define		QY_MC_HINT_NOIE4							_T(  "此系统须运行在装有4.0以上的IE的环境里"  )
#define		QY_MC_HINT_URL0LEN							_T(  "网址不能为空"  )
#define		QY_MC_HINT_BARID0LEN						_T(  "网吧编码不能为空"  )
#define		QY_MC_HINT_NAME0LEN							_T(  "名称不能为空"  )
#define		QY_MC_HINT_FRDB0LEN							_T(  "法人代表不能为空"  )
#define		QY_MC_HINT_FZR0LEN							_T(  "负责人不能为空"  )
#define		QY_MC_HINT_AQY0LEN							_T(  "安全员不能为空"  )
#define		QY_MC_HINT_ADDR0LEN							_T(  "地址不能为空"  )
#define		QY_MC_HINT_TEL0LEN							_T(  "电话不能为空"  )
#define		QY_MC_HINT_STATUS0LEN						_T(  "状态不能为空"  )
#define		QY_MC_HINT_GUESTNAME0LEN					_T(  "姓名不能为空"  )
#define		QY_MC_HINT_CERTID0LEN						_T(  "证件号码不能为空"  )
#define		QY_MC_HINT_PCID0LEN							_T(  "顾客机器号不能为空"  )
#define		QY_MC_HINT_OFFICE0LEN						_T(  "单位名称不能为空"  )
#define		QY_MC_HINT_COUNTRY0LEN						_T(  "国家名不能为空"  )
#define		QY_MC_HINT_BARIDFIXEDLEN					_T(  "网吧编码须输满10位"  )


//	#define		QY_MC_HINT_URLEXISTS						_T(  "网址已存在"  )
//	#define		QY_MC_HINT_KEYTYPENAMEEXISTS				_T(  "类别名已存在"  )
#define		QY_MC_HINT_INSERTFAILED						_T(  "数据库错误，不能完成添加操作"  )
#define		QY_MC_HINT_MODIFYFAILED						_T(  "数据库错误，不能完成修改操作"  )
#define		QY_MC_HINT_UPDATEFAILED						_T(  "数据库错误，不能完成修改操作"  )
#define		QY_MC_HINT_DELFAILED						_T(  "数据库错误，不能完成删除操作"  )
#define		QY_MC_HINT_DELETEFAILED						QY_MC_HINT_DELFAILED
#define		QY_MC_HINT_DBERR							_T(  "数据库错误，操作失败"  )
#define		QY_MC_HINT_CANBARINFOUPDATE					_T(  "网吧信息已修改，保存吗?"  )
#define		QY_MC_HINT_CANGUESTREGISTER					_T(  "登记信息是否确认?"  )
#define		QY_MC_HINT_CANPCINFOUPDATE					_T(  "机器信息已修改，保存吗?"  )
#define		QY_MC_HINT_CANPCINFODEL						_T(  "机器将被删除，继续吗?"  )
#define		QY_MC_HINT_CANBARDEL						_T(  "网吧将被删除，继续吗?"  )
#define		QY_MC_HINT_PCNOID							_T(  "没有空闲的机器了(有机器但未被分配机器号)"  )
#define		QY_MC_HINT_NOSPAREPC						_T(  "没有空闲的机器了"  )
#define		QY_MC_HINT_NOSPAREKEYTYPECODE				_T(  "没有可用的类别了(仅限于使用255种类别)"  )
#define		QY_MC_HINT_NOGUEST							_T(  "该机器上没有顾客上网"  )
#define		QY_MC_HINT_NOPCID							_T(  "没有这台机器"  )
#define		QY_MC_HINT_GETDISCOUNTFAILED				_T(  "取不到折扣"  )
#define		QY_MC_HINT_DISCOUNTERR						_T(  "折扣值有误"  )
#define		QY_MC_HINT_ISFEEOK							_T(  "继续吗?"  )
#define		QY_MC_HINT_FEEERR							_T(  "计费错误"  )
#define		QY_MC_HINT_KEYTYPENAME0LEN					_T(  "类别名字不能为空"  )
#define		QY_MC_HINT_KEYTYPEBEINGUSED					_T(  "该类别尚在使用中，须在属于该类别的网址都删除后，才能删除"  )
#define		QY_MC_HINT_DISTRIBUTINGPOLICYFAILED			_T(  "下发策略失败，请重试"  )

#endif 

//
// 字符串常量定义
extern TCHAR* QY_MC_HINT_NODSN;
extern TCHAR* QY_MC_HINT_NONEWWINDOW;
extern TCHAR* QY_MC_HINT_NOIE4;
extern TCHAR* QY_MC_HINT_URL0LEN;
extern TCHAR* QY_MC_HINT_BARID0LEN;
extern TCHAR* QY_MC_HINT_NAME0LEN;
extern TCHAR* QY_MC_HINT_FRDB0LEN;
extern TCHAR* QY_MC_HINT_FZR0LEN;
extern TCHAR* QY_MC_HINT_AQY0LEN;
extern TCHAR* QY_MC_HINT_ADDR0LEN;
extern TCHAR* QY_MC_HINT_TEL0LEN;
extern TCHAR* QY_MC_HINT_STATUS0LEN;

extern TCHAR* QY_MC_HINT_GUESTNAME0LEN;
extern TCHAR* QY_MC_HINT_CERTID0LEN;
extern TCHAR* QY_MC_HINT_PCID0LEN;
extern TCHAR* QY_MC_HINT_OFFICE0LEN;
extern TCHAR* QY_MC_HINT_COUNTRY0LEN;
extern TCHAR* QY_MC_HINT_BARIDFIXEDLEN;



//	TCHAR*		QY_MC_HINT_URLEXISTS						=(TCHAR*)_T((  "网址已存在"  )
//	TCHAR*		QY_MC_HINT_KEYTYPENAMEEXISTS				=(TCHAR*)_T((  "类别名已存在"  )
extern TCHAR* QY_MC_HINT_INSERTFAILED;
extern TCHAR* QY_MC_HINT_MODIFYFAILED;
extern TCHAR* QY_MC_HINT_UPDATEFAILED;
extern TCHAR* QY_MC_HINT_DELFAILED;
//TCHAR* QY_MC_HINT_DELETEFAILED						QY_MC_HINT_DELFAILED
extern TCHAR* QY_MC_HINT_DBERR;
extern TCHAR* QY_MC_HINT_CANBARINFOUPDATE;
extern TCHAR* QY_MC_HINT_CANGUESTREGISTER;
extern TCHAR* QY_MC_HINT_CANPCINFOUPDATE;
extern TCHAR* QY_MC_HINT_CANPCINFODEL;
extern TCHAR* QY_MC_HINT_CANBARDEL;
extern TCHAR* QY_MC_HINT_PCNOID;
extern TCHAR* QY_MC_HINT_NOSPAREPC;
extern TCHAR* QY_MC_HINT_NOSPAREKEYTYPECODE;
extern TCHAR* QY_MC_HINT_NOGUEST;
extern TCHAR* QY_MC_HINT_NOPCID;
extern TCHAR* QY_MC_HINT_GETDISCOUNTFAILED;
extern TCHAR* QY_MC_HINT_DISCOUNTERR;
extern TCHAR* QY_MC_HINT_ISFEEOK;
extern TCHAR* QY_MC_HINT_FEEERR;
extern TCHAR* QY_MC_HINT_KEYTYPENAME0LEN;
extern TCHAR* QY_MC_HINT_KEYTYPEBEINGUSED;
extern TCHAR* QY_MC_HINT_DISTRIBUTINGPOLICYFAILED;










//	#define		CONST_qnmHint_endIpLtStartIp				_T(  "结束IP小于起始IP"  )
//	#define		CONST_qnmHint_startIpDup					_T(  "配置网段重复"  )
//	#define		CONST_qnmHint_startIp0						_T(  "起始IP不能为空"  )

/*
//  操作提示
#define		CONST_qyHint_netMcDelPcs					_T(  "将删除与这些PC有关的PC信息、用户信息、单机策略、网络连接、系统日志、NetStat、打印机、进程、补丁等相关信息，确认吗?"  ) 
#define		CONST_qyHint_netMcDelPcUsr					_T(  "将删除此注册信息，确认吗?"  )
#define		CONST_qyHint_netMcDelPcUsrInTab1			CONST_qyHint_netMcDelPcUsr
#define		CONST_qyHint_netMcDelPcRule					_T(  "将删除此规则，确认吗?"  )
#define		CONST_qyHint_netMcDelProxy					_T(  "将删除此代理信息，确认吗?"  )
#define		CONST_qyHint_netMcDelPcSp					_T(  "将删除此补丁信息，确认吗?"  )
*/


//  pc的使用状态
//  #define		QY_STATUS_OK						0								//  空闲
//	#define		QY_STATUS_DEL						2								//  被删除
//  #define		QY_PCSTATUS_GUESTUSING					(  QY_STATUS_BASE + 1  )		//  顾客正使用
//  #define		QY_PCSTATUS_IEACTIVE					(  QY_STATUS_BASE + 2  )		//	未登记使用
//  #define		QY_PCSTATUS_LOST						(  QY_STATUS_BASE + 3  )		//	未联络





// 杂项
#define		CONST_qyAnyStr							_T(  ""  )			//  选择条件为空表示任选
#define		IDC_QY_WEBVIEW							1					//  webView的子窗口ID定义
#define		CONST_rollLog_url_nColumn				2					//  滚动日志中的url的列位置
//
//#define		QY_MC_DLGFACENAME						_T(  "仿宋体"  )	//  对话框的字体
extern TCHAR* QY_MC_DLGFACENAME;


//
typedef  void  *	(  *  PF_qyLvConvrtProc  )(  void * pVoid,  void  *  pQuery,  void  *  pQyRcdset,  int  nSubItem,  TCHAR  *  output,  unsigned  int  cchSize  );
//  typedef  int		(  *  PF_qyMcProcSel  )(  void  *  pQyMc,  void  *  p0,  void  *  p1  );
//  typedef  int		(  *  PF_qyMcProcEvent  )(  void  *  pQyMc,  void  *  p0,  void  *  eventInfo  );


#endif	/*  }  */



