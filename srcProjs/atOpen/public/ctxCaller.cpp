
#include	"StdAfx.h"
#include    "ctxCaller.h"
#include <tmpDefs_open.h>



CTX_caller::CTX_caller(LPCTSTR  who)
{
    memset(&m_var, 0, sizeof(m_var));
    
    //
#if  0
    //m_var.bDbg_showSth = true;
#endif 

    //
    if (who) {
        lstrcpyn(m_var.tWho, who, mycountof(m_var.tWho));
    }

    //
    return;
}

CTX_caller::~CTX_caller()
{

}
