
#ifndef  __talkProcTmpl_h__
#define  __talkProcTmpl_h__     //  {


#include <qyDefs_open.h>
//
#include    "qyMcMainCommon.h"
#include <qnmCommProc_mis.h>



//
class CCtxQmc;

//
//
typedef  struct  __talkExtVar_t {

    //
    CCtxQmc* pProcInfo;
       

    //
    struct {										//  这个结构是从mcu下发下来的策略
        //
        bool											bNoVDownload;
        //
        int                                             iTaskId;

    }													confCtrl;



    //
}        TalkExtVar;


//
//  talk additional var
class  TalkAddlVarTmpl {

public:
    TalkAddlVarTmpl() {

    }
    virtual ~TalkAddlVarTmpl()
    {
        int  ii = 0;

    }

};



//
class TalkExtTmpl {


    /////////////////////////
    //
public:
    TalkExtVar   m_var;

    //
public:
    TalkExtTmpl();
    virtual ~TalkExtTmpl();

    //
    virtual TalkAddlVarTmpl* new_talkAddlVar();

    //
    virtual int  gui_onTimer(void* p0, void* pVar, void* p2);

    //
    virtual int confData_init();
    virtual int confData_exit();
    
    //
    virtual int cli_switchTransmissionMode(__int64 talkerId, int  iTaskId,  atbool  bNoVDownloadVal)  =  mynull;

    //    
    //  对传输终端,不下载video. 
    virtual  bool  bNoVDownload(int iTaskId)=mynull;

    //
    virtual int doOp_switchTransmissionMode(__int64  idInfo_imGrp_related, bool b_noVDownload) = mynull;

    
    //
    virtual int procMsg_locDataReq(void* pm_var, MIS_MSGU* pMsg, LocDataReq  *  pReq ) = mynull;
       

    //
    virtual int  getConfLayoutStatus(HWND  hDlgTalk, int  iTaskId, ConfLayoutStatus* pStatus, LPCTSTR  hint) = mynull;

    //
    virtual int getConfTmpCtrl(HWND  hDlgTalk, int  iTaskId, ConfTmpCtrl* pConfTmpCtrl) = mynull;

};


#endif  //  }


