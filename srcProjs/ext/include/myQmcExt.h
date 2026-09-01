
#ifndef  __myQmcExt_h__
#define  __myQmcExt_h__		//  {

#include	"qmcExtTmpl.h"

class myQmcExt:public QmcExtTmpl {



        /////////////////////////
        //
    public:
        //MapExtVar   m_var;

        //
    public:
        myQmcExt();
        virtual ~myQmcExt();

        //
        virtual atbool bQyMcLogon_post(void* p0);
        virtual void qyMcLogoff_pre(void* p0);


        //
        virtual int doAnHgData(AnHgData* p);

        



};








#endif  //  }


