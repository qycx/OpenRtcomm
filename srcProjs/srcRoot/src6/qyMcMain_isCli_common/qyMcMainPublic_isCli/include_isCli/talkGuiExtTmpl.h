
#ifndef  __talkGuiExtTmpl_h__
#define  __talkGuiExtTmpl_h__	//  {

//
#include	"myTypes.h"


//
class  CCtxQmc;

//
class  TalkGuiExtTmpl {

public:
	struct {
		//
		CCtxQmc* pProcInfo;

	}	m_var;

public:
	TalkGuiExtTmpl();


	virtual ~TalkGuiExtTmpl() {
		return;
	}


	//
	virtual int refreshTransmissionMode(void* hDlgTalkParam, void  *  pm_var) = mynull;

	

};



#endif  //  }

