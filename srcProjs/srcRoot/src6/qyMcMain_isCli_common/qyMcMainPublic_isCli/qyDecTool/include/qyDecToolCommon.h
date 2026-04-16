

#ifndef  __qyDecToolCommon_h__
#define  __qyDecToolCommon_h__

//
#include	"ctxQmcDvt.h"


class CQyDecTool
{
public:
    CQyDecTool();
    virtual ~CQyDecTool();

	//
	struct				{
		void		*	pQyMcParam;		//  暂时用一下这个变量，最好是在小模块中逐渐取消这个变量
		//
		CCtxQmcDvt	*	pCtx;

		//
	}					m_var;

	//
    virtual int init(  LPCTSTR  cmdLine  );
    virtual int run();
    virtual void exit();

};








#endif


