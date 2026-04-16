

#include	"stdafx.h"
#include	<tchar.h>

#ifndef	 __WINCE__
	#include	<vfw.h>
	#include	<winsvc.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
	#include	<time.h>
#endif
#include	<WinSock2.h>

#include	"qmCommon.h"
//  #include	"qyCusResPublic.h"


#if  0
 QY_DMITEM	CONST_qnmPlatformTable[]  =
{
#if  0
	{  CONST_qyPlatform_win98,		_T(  "Win98"  ),				},	//  4
	{  CONST_qyPlatform_winme,		_T(  "WinMe"  ),				},	//  5
	{  CONST_qyPlatform_nt,			_T(  "WinNT"  ),				},	//  6
	{  CONST_qyPlatform_win2k,		_T(  "Win2000"  ),				},	//  7
#endif
	{  CONST_qyPlatform_winxp,		_T(  "XP"  ),				},	//  8
	{  CONST_qyPlatform_win2003,	_T(  "Win2003"  ),				},	//  9
	{  CONST_qyPlatform_winVista,	_T(  "Vista"  ),				},
	{  CONST_qyPlatform_win2008,	_T(  "Win2008"  ),				},
	{  CONST_qyPlatform_win7,		_T(  "Win7"  ),					},
	{	CONST_qyPlatform_win2008R2,	_T(  "Win2008R2"  ),			},
	{  -1,							NULL,					},
};
#endif





/*
 //  浏览选择目录例子程序
 int  testCfgDir(  )
{
	BROWSEINFO		bi  =  {  0  };
    TCHAR			path[MAX_PATH];

	bi.ulFlags  =  BIF_RETURNONLYFSDIRS;
    bi.lpszTitle  =  _T(  "Pick a Directory"  );
    //  bi.pszDisplayName;
    LPITEMIDLIST  pidl  =  SHBrowseForFolder(  &bi  );
    if  (  pidl  !=  0  )  {
        // get the name of the folder
        if  (  SHGetPathFromIDList(  pidl,  path  )  )  {
            traceLogA(  "Selected Folder: %s",  path  );
			qySetRegCfg(  CONST_qyRootKey_qnmScheduler,  CONST_regValName_cntIp,  path  );
        }

        // free memory used
        IMalloc  *  imalloc  =  0;
        if  (  SUCCEEDED(  SHGetMalloc(  &imalloc  )  )  )  {
            imalloc->Free(  pidl  );
            imalloc->Release(  );
        }
    }	

	return  0;

}
*/

#ifndef  __WINCE__

//$--HrGetServiceStatus------------------------------------------------------ 
//  Get the current state of a service on a given machine. 
// ----------------------------------------------------------------------------- 
 extern  "C"  int  qyGetServiceStatus(						// RETURNS: return code     
						IN LPTSTR  lpszMachineName,          // machine name     
						IN LPTSTR  lpszServiceName,          // service name     
						OUT DWORD  *  lpdwCurrentState  )   // current state 
{    
	 int			 iRet				=	-1;
	 SC_HANDLE       schSCManager		=	NULL;     
	 SC_HANDLE       schService			=	NULL;     
	 DWORD           fdwDesiredAccess	=	0;     
	 SERVICE_STATUS  ssServiceStatus	=	{  0  };     
	 BOOL            fRet				=	FALSE;      
	 
	 //  hr = CHK_HrGetServiceStatus(         lpszMachineName,         lpszServiceName,         lpdwCurrentState);      
	 //  if(FAILED(hr))         RETURN(hr);      

	 *lpdwCurrentState = 0;      
	 fdwDesiredAccess = GENERIC_READ;      
	 schSCManager = OpenSCManager(  lpszMachineName,    // address of machine name string          
									NULL,               // address of database name string          
									fdwDesiredAccess    // type of access      
									);      
	 if  (  schSCManager  ==  NULL  )  goto  cleanup;     
	       
	 schService = OpenService(  schSCManager,       // handle of service control manager database           
								lpszServiceName,    // address of name of service to start          
								fdwDesiredAccess    // type of access to service      
								);      
	 if  (  schService  ==  NULL  )  goto  cleanup;     
	       
	 fRet = QueryServiceStatus(  schService,         // handle of service          
								 &ssServiceStatus    // address of service status structure       
								 );      
	 if  (  fRet  ==  FALSE  )  goto  cleanup;
	 
	 *lpdwCurrentState  =  ssServiceStatus.dwCurrentState;  

	 iRet  =  0;

cleanup:      
	 
	 if  (  schService  )  CloseServiceHandle(schService);     
	 if  (  schSCManager  )  CloseServiceHandle(schSCManager);      

	 return(  iRet  ); 

} 

#endif


 extern  "C"  BOOL  bBoolSame(  BOOL  b1,  BOOL  b2  )
{
	 if  (  b1  &&  b2  )  return  TRUE;
	 if  (  !b1  &&  !b2  )  return  TRUE;
	 return  FALSE;
}


 extern  "C"  BOOL  bMacLocal(  QY_ENV  *  pEnv,  char  *  mac  )
{	 
	 QWM_MACS_INFO				macsInfo;

	 if  (  !mac  )  return  FALSE;

	 memset(  &macsInfo,  0,  sizeof(  macsInfo  )  );
	 getQwmSortedMacs(  pEnv,  &macsInfo  );
	 for  (  int  i  =  0;  i  <  macsInfo.nMacs;  i  ++  )  {
		  if  (  !memcmp(  mac,  macsInfo.macs[i],  CONST_qyMacLen  )  )  return  TRUE;
	 }

	 return  FALSE;
}


 extern  "C"  BOOL  bMacsInfoValid(  QWM_MACS_INFO  *  pMacsInfo  )
{
	 int	i;

	 if  (  !pMacsInfo->nMacs  ||  pMacsInfo->nMacs  >  sizeof(  pMacsInfo->macs  )  /  sizeof(  pMacsInfo->macs[0]  )  )  return  FALSE;
	 for  (  i  =  0;  i  <  pMacsInfo->nMacs;  i  ++  )  {
		  if  (  !bMacValid(  (  char  *  )pMacsInfo->macs[i]  )  )  return  FALSE;
	 }

	 return  TRUE;
}


 BOOL  bIfIndexValid(  int  ifIndex  )
{
	 return  (  ifIndex  >  0  );
}


#ifdef  __useMfc__
 CTime getCTimeByQyTime(  char  *  timeBuf  )
{
	 char	year[5],  month[3],  day[3],  hour[3],  minute[3],  second[3];
	 memcpy(  year,  timeBuf,  4  );  year[4]  =  0;  timeBuf  +=  4;
	 memcpy(  month,  timeBuf,  2  );  month[2]  =  0;  timeBuf  +=  2;
	 memcpy(  day,  timeBuf,  2  );  day[2]  =  0;  timeBuf  +=  2;
	 memcpy(  hour,  timeBuf,  2  );  hour[2]  =  0;  timeBuf  +=  2;
	 memcpy(  minute,  timeBuf,  2  );  minute[2]  =  0;  timeBuf  +=  2;
	 memcpy(  second,  timeBuf,  2  );  second[2]  =  0;  timeBuf  +=  2;

	 CTime  t(  atol(  year  ),  atol(  month  ),  atol(  day  ),  atol(  hour  ),  atol(  minute  ),  atol(  second  )  );

	 return  t;

}
#endif



  int  getCustomComm(  QNM_CUSTOM_COMM  *  pCustom  )
{
	char	buf[128];

	if  (  !pCustom  )  return  -1;
	
	pCustom->nDwLevels  =  DEFAULT_nDwLevels;
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_nDwLevels  ),  buf,  sizeof(  buf  )  )
		&&  atol(  buf  )  <=  CONST_maxnDwLevels  
			&&  atol(  buf  )  >=  CONST_minnDwLevels  )
	{
		pCustom->nDwLevels  =  (  unsigned  char  )atol(  buf  );
	}
	pCustom->nZcbhs  =  DEFAULT_nZcbhs;
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_nZcbhs  ),  buf,  sizeof(  buf  )  )
		&&  atol(  buf  )  <=  CONST_maxnZcbhs  
			&&  atol(  buf  )  >=  CONST_minnZcbhs  )
	{
		pCustom->nZcbhs  =  (  unsigned  char  )atol(  buf  );
	}
	return  0;
}
