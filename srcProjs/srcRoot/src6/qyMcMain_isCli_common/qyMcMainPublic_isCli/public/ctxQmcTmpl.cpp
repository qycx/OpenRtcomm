
#include	"stdafx.h"
#include	<tchar.h>

#include	"ctxQmcTmpl.h"



CCtxQmcTmpl::CCtxQmcTmpl(  )
{
	//
	this->pQyMc  =  NULL;					
	this->pSgiParam  =  NULL;
	this->who_showInfo[0]  =  0;

	//
	int  size  =  &this->_end  -  &this->_start;
	memset(  &this->_start,  0,  size  );

	//
	size  =  &this->_end_private  -  &this->_start_private;
	memset(  &this->_start_private,  0,  size  );

}


CCtxQmcTmpl::~CCtxQmcTmpl(  )
{
}




BOOL  CCtxQmcTmpl::bCtxQuit(  )
{
	return  this->bQuit_internal;
}

	
int  CCtxQmcTmpl::setCtxQuit(  )
{
	this->bQuit_internal  =  TRUE;
	return  0;
}

