

#include	"stdafx.h"
//#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

#include	"qmCommon.h"


#include	"qnmCommProc_mis.h"

  QY_DMITEM  CONST_hdAccl_table[]  = 
{
	{	CONST_hdAccl_auto,							_T(  "Auto"  ),													},
	{	CONST_hdAccl_msdk_software,					_T(  "Not use hardware accl"  ),								},
	{	CONST_hdAccl_msdk_hardware,					_T(  "Use hardware accl"  ),									},
	{	CONST_hdAccl_nv,							_T(  "Nv"  ),													},
	{	CONST_hdAccl_amf,							_T(  "Amf"  ),													},	//  2015/04/30
	{	-1,									NULL,					},
};


int getMcuPolicy( TCHAR * rootKey_qnmScheduler, LPCTSTR  smCfgFile,  MCU_policy * p )
{
		//
	TCHAR			*	pRegVal				=	NULL;
	char				buf[256];
	QY_REG				reg;
	unsigned  char		ucCmd;
	unsigned  int		uiCapType;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR			*	pT;
	long				lVal;
	TCHAR				rootKeyStr[256]		=  _T(  ""  );

	//


	if  (  !p  )  return  -1;

	memset(  p,  0,  sizeof(  p[0]  )  );

	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_LOCAL_MACHINE;
	lstrcpyn(  reg.rootKey,  CQyString(  rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

		//  2014/03/29
	ucCmd  =  DEFAULT_hdAccl;
	pRegVal  =  _T(  CONST_regValName_ucHardwareAccl  );
	if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  buf,  sizeof(  buf  ),  0  )
		&&  atol(  buf  )  )
	{
		ucCmd  =  (  unsigned  char  )atol(  buf  );
	}
	p->ucHardwareAccl  =  ucCmd;

	//
	Qm_initCfg  qi =  {0};
	if  (  bGetQmInitCfg(  (TCHAR*)smCfgFile,  &qi  )  )  {
		if  (  qi.ucHardwareAccl  )  {
			p->ucHardwareAccl  =  qi.ucHardwareAccl;
		}
	}
	
	//
	return 0;
}