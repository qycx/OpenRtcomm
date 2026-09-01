
#include	"stdafx.h"
#include	<windows.h>
#include	<stdlib.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyTCharCommProc.h"
#include	"qysyncCommProc.h"

#include	"qyString.h"

static  const  TCHAR	*	CONST_str_null	=	_T(  ""  );

CQyString::CQyString(  )
{
	this->m_ptBuf  =  (  TCHAR  *  )CONST_str_null;

	//  traceLog(  _T(  "CQyString(  )"  )  );
}



CQyString::CQyString(  LPCTSTR  val  )
{
	this->m_ptBuf  =  (  TCHAR  *  )CONST_str_null;
	
	if  (  !val  )  return;

	unsigned  int  uiBufCnt  =  lstrlen(  val  )  +  1;
	TCHAR  *  ptBuf  =  (  TCHAR  *  )mymalloc(  sizeof(  TCHAR  )  *  uiBufCnt  );
	if  (  !ptBuf  )  return;

	lstrcpyn(  ptBuf,  val,  uiBufCnt  );

	m_ptBuf  =  ptBuf;

	//  traceLog(  _T(  "CQyString(  LPCTSTR  )"  )  );
}

CQyString::CQyString(  char  *  val  )
{
	this->m_ptBuf  =  (  TCHAR  *  )CONST_str_null;
	
	if  (  !val  )  return;

	unsigned  int  uiBufCnt  =  strlen(  val  )  +  1;
	TCHAR  *  ptBuf  =  (  TCHAR  *  )mymalloc(  sizeof(  TCHAR  )  *  uiBufCnt  );
	if  (  !ptBuf  )  return;

	myUtf82TChar(  val,  ptBuf,  uiBufCnt  );
	ptBuf[uiBufCnt  -  1]  =  0;

	this->m_ptBuf  =  ptBuf;

	//  traceLog(  _T(  "CQyString(  char  *  )"  )  );

	return;
}


// copy construct
CQyString::CQyString(  const  CQyString  &  rightSides  )
{
	this->m_ptBuf  =  (  TCHAR  *  )CONST_str_null;

	stringCpy(  rightSides  );

	//  traceLog(  _T(  "CQyString(  const  CQyString  &  )"  )  );
}


//
CQyString::~CQyString(  )
{
	clear(  );

	//  traceLog(  _T(  "~CQyString(  )"  )  );
}


void  CQyString::clear(  )
{
	//  traceLog(  _T(  "CQyString(  )::clear(  )"  )  );

	if  (  m_ptBuf  !=  CONST_str_null  )  {
		myfree(  m_ptBuf  );
		m_ptBuf  =  (  TCHAR  *  )CONST_str_null;
	}
}

void  CQyString::stringCpy(  LPCTSTR  src  )
{
	unsigned  int  len_str  =  src  ?  lstrlen(  src  )  :  0;
	unsigned  int  uiBufCnt  =  len_str  +  1;
	TCHAR  *  ptBuf  =  (  TCHAR  *  )mymalloc(  sizeof(  TCHAR  )  *  uiBufCnt  );
	if  (  !ptBuf  )  goto  errLabel;
	if  (  len_str  )  {
		memcpy(  ptBuf,  src,  len_str  *  sizeof(  TCHAR  )  );
	}
	ptBuf[uiBufCnt  -  1]  =  0;

	clear(  );

	m_ptBuf  =  ptBuf;

errLabel:
	return;
}


void  CQyString::concatCpy(  LPCTSTR  src1,  LPCTSTR  src2  )
{
	unsigned  int  len_str1  =	src1  ?  lstrlen(  src1  )  :  0;
	unsigned  int  len_str2  =  src2  ?  lstrlen(  src2  )  :  0;
	unsigned  int  uiBufCnt  =  len_str1  +  len_str2  +  1;
	TCHAR  *  ptBuf  =  (  TCHAR  *  )mymalloc(  sizeof(  TCHAR  )  *  uiBufCnt  );
	if  (  !ptBuf  )  goto  errLabel;
	if  (  len_str1  )  {
		memcpy(  ptBuf,  src1,  len_str1  *  sizeof(  TCHAR  )  );
	}
	if  (  len_str2  )  {
		memcpy(  ptBuf  +  len_str1,  src2,  len_str2  *  sizeof(  TCHAR  )  );
	}
	ptBuf[uiBufCnt  -  1]  =  0;

	clear(  );

	m_ptBuf  =  ptBuf;

errLabel:
	return;
}


//
CQyString::operator LPCTSTR(  )  const
{  
	return  m_ptBuf;  
}


//
CQyString  &  CQyString::operator  =  (  const  CQyString  &  rightSides  )
{
	int		iErr	=	-1;

	if  (  this  !=  &rightSides  )  {
		stringCpy(  rightSides  );
	}

	//  traceLog(  _T(  "CQyString(  operator =   )"  )  );

	return  *this;
}


CQyString  &  CQyString::operator  +=  (  const  CQyString  &  rightSides    )
{
	concatCpy(  *this,  rightSides  );
	return  *this;
}


CQyString  operator+  (  CQyString  &  src1,  CQyString  &  src2  )
{
	CQyString	s;

	s.concatCpy(  src1,  src2  );

	//  traceLog(  _T(  "CQyString(  operator +   )"  )  );

	return  s;  
}

CQyString  operator+  (  CQyString  &  src1,  LPCTSTR  str2  )
{
	CQyString	s;
	s.concatCpy(  src1,  str2  );
	return  s;
}


CQyString  operator+  (  CQyString  &  src1,  char  *  str2  )
{
	CQyString	s;
	s.concatCpy(  src1,  CQyString(  str2  )  );
	return  s;
}


//

CQyString  operator+  (CQyString src1, CQyString src2)
{
	CQyString	s;

	s.concatCpy(src1, src2);

	//  traceLog(  _T(  "CQyString(  operator +   )"  )  );

	return  s;
}



//
TCHAR  CQyString::operator [](  int  nIndex  )
{
	int  nLen  =  GetLength(  );
	if  (  nIndex  <  0  ||  nIndex  >=  nLen  )  return  0;
	return  m_ptBuf[nIndex];
}


//
CQyString  &  CQyString::Trim(  )
{
	if  (  m_ptBuf  !=  CONST_str_null  )  {
		tTrim(  m_ptBuf  );
	}
	return  *this;
}


LPCTSTR  CQyString::GetBuffer(  int nMinBufferLength  )
{
	return  m_ptBuf;
}

unsigned  int  CQyString::GetLength(  )
{
	return  lstrlen(  m_ptBuf  );
}



 
