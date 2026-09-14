

#ifndef  __myTalkExt_h__
#define  __myTalkExt_h__	//  {

//
#include	"talkExtTmpl.h"


//
class myTalkExt : public TalkExtTmpl {


	//
	virtual int confData_init()
	{
		return 0;
	}
	virtual int confData_exit()
	{
		return  0;
	}

	//
	virtual bool bNoVDownload(int iTaskId);
	
	//
	virtual int doOp_switchTransmissionMode(__int64  idInfo_imGrp_related, bool b_noVDownload);
	
	



	//
	virtual int procMsg_locDataReq(void* pm_var, MIS_MSGU* pMsg, LocDataReq* pReq)
	{
		return 0;
	}

	//
	virtual int  getConfLayoutStatus(HWND  hDlgTalk, int  iTaskId, ConfLayoutStatus* pStatus, LPCTSTR  hint)
	{
		return  0;
	}



};



#endif  //  }




