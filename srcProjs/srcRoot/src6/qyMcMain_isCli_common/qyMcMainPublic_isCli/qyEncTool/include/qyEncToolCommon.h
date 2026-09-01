
#ifndef  __qyEncToolCommon_h__
#define  __qyEncToolCommon_h__	//  {

//
#include	"ctxQmcEvt.h"


class CQyEncTool
{
public:
    CQyEncTool();
    virtual ~CQyEncTool();

	//
	struct				{
		//void		*	pQyMcParam;		//  暂时用一下这个变量，最好是在小模块中逐渐取消这个变量
		//
		CCtxQmcEvt	*	pCtx;


	}					m_var;

	//
    virtual int init(  LPCTSTR  cmdLine  );
    virtual int run();
    virtual void exit();

};



#endif  //  }



