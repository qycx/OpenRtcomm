
#ifndef  __ctxFw_and_h__
#define  __ctxFw_and_h__	//  {

//
#include	"IsFw.h"


//
class  CtxFw_and {
	//
public:
	TCHAR  m_smCfgFileName[MAX_PATH + 1]{};

	//
	IsFw	fw_and;
	IsFw	fw_hg;
	//
public:
	CtxFw_and();
	virtual ~CtxFw_and();

};




#endif  //  }



