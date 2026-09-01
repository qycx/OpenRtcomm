

#ifndef  __qmcExtTmpl_h__
#define  __qmcExtTmpl_h__   //  {

//
#include    "myTypes_basic.h"
#include    "qmcStruct_defs.h"


//


//
class CCtxQmc;


//
typedef  struct  __qmcExtVar_t {

    //
    CCtxQmc* pProcInfo;




    //
}        QmcExtVar;


//
//
class QmcExtTmpl {


    /////////////////////////
    //
public:
    QmcExtVar   m_var;

    //
public:
    QmcExtTmpl();
    virtual ~QmcExtTmpl();


    //
    virtual atbool bQyMcLogon_post(void* p0) = 0;
    virtual void qyMcLogoff_pre(void* p0) = 0;

    //
    virtual int doAnHgData(AnHgData* p) = 0;
    



};



#endif  //  }



