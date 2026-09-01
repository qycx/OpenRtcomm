
#include	"stdafx.h"

#include	"talkExtTmpl.h"
#include	"ctxQmc.h"


TalkExtTmpl::TalkExtTmpl()
{
	memset(&m_var, 0, sizeof(m_var));
}


TalkExtTmpl::~TalkExtTmpl()
{
	int  ii = 0;
	
}


TalkAddlVarTmpl* TalkExtTmpl::new_talkAddlVar()
{
	return new TalkAddlVarTmpl();
}

//
int TalkExtTmpl::gui_onTimer(void* p0, void* pVar, void* p2)
{
	return  0;
}



int TalkExtTmpl::confData_init()
{
	return  0;
 }

int TalkExtTmpl::confData_exit()
{
	return  0;
}





