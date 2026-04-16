

#include	"stdafx.h"
#include	<WinSock2.h>
#include	<mmsystem.h>
#include	"qmCommon.h"

//
 int  mySaveSecret(  HKEY  hKeyRoot,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  char  *  cfgVal,  int  cb   )
{
	int  iErr  =  -1;
	
	char  oBuf[2048]; 
	int  size  =  mycountof(  oBuf  );
 
	if  (  !hKeyRoot  ||  !rootKey  )  return  -1;
	if  (  !cfgName  ||  !cfgVal  ||  !cb  )  return -1;

	if  (  myProtectData(  cfgVal,  cb,  oBuf,  &size  )  )  goto  errLabel;
	
	QY_REG  reg; 
	memset(  &reg,  0,  sizeof(  reg  )  ); 
	reg.uiType  =  REG_BINARY;
	_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  rootKey  );
	reg.hKeyRoot0  =  hKeyRoot;

	//
	if  (  tmpSetRegCfgEx(  &reg,  cfgName,  oBuf,  size  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}


//
int  myGetSecret(  HKEY  hKeyRoot,  LPCTSTR  rootKey,  LPCTSTR  cfgName,  char  *  cfgVal,  int  *pcb   )
{
	int  iErr  =  -1;

	if  (  !hKeyRoot  ||  !rootKey  )  return  -1;
	if  (  !cfgName  ||  !cfgVal  ||  !pcb  )  return  -1;


	 QY_REG  reg;

	 memset(  &reg,  0,  sizeof(  reg  )  );
 reg.uiType  =  REG_BINARY;
 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  rootKey  );
 reg.hKeyRoot0  =  hKeyRoot;
 //

 //
 char  tt[2048];
 unsigned  int  tsize  =  mycountof(  tt  );
 if  (  tmpGetRegCfgEx(  &reg,  cfgName,  tt,  &tsize  )  )  goto  errLabel;

 if  (  myUnprotectData(  tt,  tsize,  cfgVal,  pcb  )  )  goto  errLabel;

 iErr  =  0;
errLabel:
 return  iErr;
}





