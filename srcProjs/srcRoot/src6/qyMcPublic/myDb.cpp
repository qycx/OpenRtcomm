
#include	"stdafx.h"

//  #include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>
#include	<tchar.h>

//#include	"qyMcMainCommon.h"

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"


#include	"myDb.h"





//
CMyDb::CMyDb(  ) 
{  
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CMyDb::~CMyDb(  )  
{  
	if  (  m_var.bInited  )  qyCloseDb(  );
}


#if  0	//  2014/05/19
#define		CONST_uiMaxQNodes_qyImObjTab			1000
#define		CONST_uiMaxQNodes_qyImObjRegInfoTab		1000
#define		CONST_uiMaxQNodes_qyImObjRegInfoTab1	1000
#define		CONST_uiMaxQNodes_qyImGrpInfoTab		1000
#define		CONST_uiMaxQNodes_qyImGrpMemTab			3000
#define		CONST_uiMaxQNodes_qyImObjRuleTab		1000
#define		CONST_uiMaxQNodes_qyDynBmpTab			1000
#endif
//  2014/05/19
#define		CONST_uiMaxQNodes_qyImObjTab			3000
#define		CONST_uiMaxQNodes_qyImObjRegInfoTab		3000
#define		CONST_uiMaxQNodes_qyImObjRegInfoTab1	3000
#define		CONST_uiMaxQNodes_qyImGrpInfoTab		3000
#define		CONST_uiMaxQNodes_qyImGrpMemTab			10000
#define		CONST_uiMaxQNodes_qyImObjRuleTab		1000
#define		CONST_uiMaxQNodes_qyDynBmpTab			1000


#ifdef  __DEBUG__
	#define		CONST_uiMaxQNodes_qyImTaskTab			2000	//100	//10	//  1000
	#define		CONST_uiMaxQNodes_qyImMsgTab			10
#else
	#define		CONST_uiMaxQNodes_qyImTaskTab			10000
	#define		CONST_uiMaxQNodes_qyImMsgTab			1000
#endif


BOOL  CMyDb::bQyOpenDb(  LPCWSTR  connectStr  )
{
	BOOL	bRet	=	FALSE;

	TCHAR			*	pTabName;
	unsigned  int		uiMaxQNodes;
	int					index	=	0;

	pTabName  =  (TCHAR *)CONST_tabName_qyImObjTab;
	uiMaxQNodes  =  CONST_uiMaxQNodes_qyImObjTab;
	if  (  initGenericQ(  pTabName,  pTabName,  0,  uiMaxQNodes,  mymalloc,  myfree,  &m_var.q_tabs[index]  )  )  goto  errLabel;
	m_var.pQ_qyImObjTab  =  &m_var.q_tabs[index];
	index  ++  ;
	pTabName  = (TCHAR*)CONST_tabName_qyImObjRegInfoTab;
	uiMaxQNodes  =  CONST_uiMaxQNodes_qyImObjRegInfoTab;
	if  (  initGenericQ(  pTabName,  pTabName,  0,  uiMaxQNodes,  mymalloc,  myfree,  &m_var.q_tabs[index]  )  )  goto  errLabel;
	m_var.pQ_qyImObjRegInfoTab  =  &m_var.q_tabs[index];
	index  ++  ;
	pTabName  = (TCHAR*)CONST_tabName_qyImObjRegInfoTab1;
	uiMaxQNodes  =  CONST_uiMaxQNodes_qyImObjRegInfoTab1;
	if  (  initGenericQ(  pTabName,  pTabName,  0,  uiMaxQNodes,  mymalloc,  myfree,  &m_var.q_tabs[index]  )  )  goto  errLabel;
	m_var.pQ_qyImObjRegInfoTab1  =  &m_var.q_tabs[index];
	index  ++  ;
	pTabName  = (TCHAR*)CONST_tabName_qyImGrpInfoTab;
	uiMaxQNodes  =  CONST_uiMaxQNodes_qyImGrpInfoTab;
	if  (  initGenericQ(  pTabName,  pTabName,  0,  uiMaxQNodes,  mymalloc,  myfree,  &m_var.q_tabs[index]  )  )  goto  errLabel;
	m_var.pQ_qyImGrpInfoTab  =  &m_var.q_tabs[index];
	index  ++  ;
	pTabName  = (TCHAR*)CONST_tabName_qyImGrpMemTab;
	uiMaxQNodes  =  CONST_uiMaxQNodes_qyImGrpMemTab;
	if  (  initGenericQ(  pTabName,  pTabName,  0,  uiMaxQNodes,  mymalloc,  myfree,  &m_var.q_tabs[index]  )  )  goto  errLabel;
	m_var.pQ_qyImGrpMemTab  =  &m_var.q_tabs[index];
	index  ++  ;

	pTabName  = (TCHAR*)CONST_tabName_qyImObjRuleTab;
	uiMaxQNodes  =  CONST_uiMaxQNodes_qyImObjRuleTab;
	if  (  initGenericQ(  pTabName,  pTabName,  0,  uiMaxQNodes,  mymalloc,  myfree,  &m_var.q_tabs[index]  )  )  goto  errLabel;
	m_var.pQ_qyImObjRuleTab  =  &m_var.q_tabs[index];
	index  ++  ;

	pTabName  = (TCHAR*)CONST_tabName_qyImTaskTab;
	uiMaxQNodes  =  CONST_uiMaxQNodes_qyImTaskTab;
	if  (  initGenericQ(  pTabName,  pTabName,  0,  uiMaxQNodes,  mymalloc,  myfree,  &m_var.q_tabs[index]  )  )  goto  errLabel;
	m_var.pQ_qyImTaskTab  =  &m_var.q_tabs[index];
	index  ++  ;
	
	pTabName  = (TCHAR*)CONST_tabName_qyImMsgTab;
	uiMaxQNodes  =  CONST_uiMaxQNodes_qyImMsgTab;
	if  (  initGenericQ(  pTabName,  pTabName,  0,  uiMaxQNodes,  mymalloc,  myfree,  &m_var.q_tabs[index]  )  )  goto  errLabel;
	m_var.pQ_qyImMsgTab  =  &m_var.q_tabs[index];
	index  ++  ;
	
	pTabName  = (TCHAR*)CONST_tabName_qyDynBmpTab;
	uiMaxQNodes  =  CONST_uiMaxQNodes_qyDynBmpTab;
	if  (  initGenericQ(  pTabName,  pTabName,  0,  uiMaxQNodes,  mymalloc,  myfree,  &m_var.q_tabs[index]  )  )  goto  errLabel;
	m_var.pQ_qyDynBmpTab  =  &m_var.q_tabs[index];
	index  ++  ;
	//
	if  (  index  >  mycountof(  m_var.q_tabs  )  )  goto  errLabel;

	bRet  =  TRUE;

errLabel:
	if  (  bRet  )  {
		m_var.bInited  =  TRUE;
	}
	if  (  !bRet  )  {
		qyCloseDb(  );
	}
	return  bRet;
}


void  CMyDb::qyCloseDb(  )
{
	int	i;

	for  (  i  =  0;  i  <  mycountof(  m_var.q_tabs  );  i  ++  )  {
		 exitGenericQ(  &m_var.q_tabs[i]  );
	}

	m_var.bInited  =  FALSE;
}



