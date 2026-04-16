
#ifndef  __ctxCaller_h__
#define  __ctxCaller_h__    //  {

class CTX_caller  {
    //
public:


    //
    struct {
        int             type;
        //
        int             dwThreadId;
        //
        WCHAR           tWho[32];
    }   m_var;

    //
    CTX_caller(LPCTSTR  who )
    {
        memset(&m_var, 0, sizeof(m_var));

        if (who) {
            lstrcpyn(m_var.tWho, who, mycountof(m_var.tWho));
        }

        //
        return;
    }

    ~CTX_caller()
    {

    }

};



#endif  //  }

