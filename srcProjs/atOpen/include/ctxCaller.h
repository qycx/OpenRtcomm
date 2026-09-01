
#ifndef  __ctxCaller_h__
#define  __ctxCaller_h__    //  {

class CTX_caller  {
    //
public:

    //
    struct {
        int                 type;
        //
        int                 dwThreadId;
        //
        WCHAR               tWho[32];
        //
        bool                bDbg_showSth;

        //
        bool				m_bShowInfo;
        TCHAR       *       m_pHint;
        //
        unsigned  int		m_uiStep;


    }   m_var;




    //
    CTX_caller(LPCTSTR  who);
    ~CTX_caller();


};



#endif  //  }

