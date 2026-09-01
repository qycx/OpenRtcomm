// QnmSvrMgrModuleDaemon.h: interface for the CQnmSvrMgrModuleDaemon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QNMSVRMGRMODULEDAEMON_H__9656ADA4_E50C_48EE_AA22_7847CD197215__INCLUDED_)
#define AFX_QNMSVRMGRMODULEDAEMON_H__9656ADA4_E50C_48EE_AA22_7847CD197215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef  struct  __qnmSvrMgrDaemon_t		{

				 struct						{
					 char					procHhMmSs[CONST_qyTimeLen  +  1];
					 WCHAR					showWho[32  +  1];
				 }							cfg;

				 QY_ENV						env;
				 QY_LOG_CTX					logCtx;

				 char						documentsAndSettingsDir[CONST_qyMaxPathLen  +  1];

				 struct						{
					 unsigned  char			ucbInited;
				 }							status;

}		 QNM_SVRMGR_DAEMON;

class CQnmSvrMgrModuleDaemon : public CQyGenericDaemon  
{
public:
	CQnmSvrMgrModuleDaemon();
	virtual ~CQnmSvrMgrModuleDaemon();

	QNM_SVRMGR_DAEMON		var;


};

#endif // !defined(AFX_QNMSVRMGRMODULEDAEMON_H__9656ADA4_E50C_48EE_AA22_7847CD197215__INCLUDED_)
