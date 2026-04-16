

//  #include	<afxtempl.h>
#include	<WinSock2.h>
#include	<windows.h>
#include	"qyCommonEx.h"


//  CArray<VARIABLE_INFO, VARIABLE_INFO> m_arrVarInfo;

static  BOOL  bQyUpdatePeVar(  char  *  pBuffer,  DWORD  dwLen,  char  *  symbol,  char  *  data,  DWORD  dataLen  );

 //  extern  "C"  BOOL  bQyUpdateImageData(  char  *  svPath,  char  *  symbol,  char  *  data,  unsigned  int  dataLen  )
 extern  "C"  BOOL  bQyUpdateImageData(  LPCTSTR  svPath,  char  *  symbol,  char  *  data,  unsigned  int  dataLen  )
{
	BOOL				bRet			=	FALSE;
	HANDLE				hSvrFile		=	NULL;
	HANDLE				m_hSvrMapping	=	NULL;
	void		*		m_pSvrView		=	NULL;
	DWORD				m_dwRawFileSize;			// Size of server file map without all the plugins

	// Open server file
	hSvrFile  =  CreateFile(  svPath,  GENERIC_READ  |  GENERIC_WRITE,  0,  NULL,  OPEN_EXISTING,  0,  NULL  );
	if  (  hSvrFile  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
	m_dwRawFileSize  =  GetFileSize(  hSvrFile,  NULL  );
	
	// Memory map it
	m_hSvrMapping  =  CreateFileMapping(  hSvrFile,  NULL,  PAGE_READWRITE,  0,  0,  NULL  );
	CloseHandle(  hSvrFile  );  hSvrFile  =  NULL;
	if  (  m_hSvrMapping  ==  NULL  )  goto  errLabel;
	
	m_pSvrView  =  (  BYTE  *  )MapViewOfFile(  m_hSvrMapping,  FILE_MAP_ALL_ACCESS,  0,  0,  0  );
	if  (  m_pSvrView  ==  NULL  )  goto  errLabel;

	if  (  !bQyUpdatePeVar(  (  char  *  )m_pSvrView,  m_dwRawFileSize,  symbol,  data,  dataLen  )  )  goto  errLabel;

	if  (  !FlushViewOfFile(  m_pSvrView,  0  )  )  {
		qyDisplayLastError(  ""  );
		goto  errLabel;
	}

	bRet  =  TRUE;

errLabel:

	if  (  m_pSvrView  )  UnmapViewOfFile(m_pSvrView);
	if  (  m_hSvrMapping  )  CloseHandle(  m_hSvrMapping  );
	if  (  hSvrFile  )  CloseHandle(  hSvrFile  );

	return  bRet;

}

 static  BOOL  bQyUpdatePeVar(  char  *  pBuffer,  DWORD  dwLen,  char  *  symbol,  char  *  data,  DWORD  dataLen  )  
{
	BOOL		bRet	=  FALSE;
	DWORD		pos;
	DWORD		symLen  =  strlen(  symbol  );
	
	if  (  symLen  >  dwLen  )  goto  errLabel;		//  2003/11/04

	for  (  pos  =  0;  pos  <  dwLen  -  symLen;  pos  ++  )  {
		
		 if  (  memcmp(  pBuffer  +  pos,  symbol,  symLen  )  )  continue;

		 pos  +=  symLen;
		 if  (  dwLen  -  symLen  -  pos  <  dataLen  )  goto  errLabel;
		 memcpy(  pBuffer  +  pos,  data,  dataLen  );
		 break;
		
	}

	bRet  =  TRUE;

errLabel:

	return  bRet;

}


 //  暂时不用此函数。
 /*
 void  qyAddVariables(  char  *  pBuffer,  DWORD  dwLen,  int  nPlugin  )
{
	DWORD pos;
	for(pos=0;pos<dwLen-9;pos++) {
		if(memcmp(pBuffer+pos,"<**CFG**>",9)==0) {
			pos+=9;
			// Get category name
			VARIABLE_INFO vi;
			lstrcpyn(vi.svCategory,pBuffer+pos,256);
			pos+=(lstrlen(pBuffer+pos)+1);
			
			// Go through all variables
			while(*(pBuffer+pos)!='\0') {
				DWORD dwValPos;
				vi.VarType=*(pBuffer+pos);
				if(vi.VarType=='B') {
					pos+=2;
					// Get Name and Value
					DWORD dwStart=pos;
					while(*(pBuffer+pos)!='=') pos++;
					lstrcpyn(vi.svVarName,pBuffer+dwStart,min(pos-dwStart+1,256));
					pos++;
					dwValPos=pos;
					lstrcpyn(vi.svVarValue,pBuffer+pos,256);
					vi.nStrLen=1;
					pos+=2;
				} else if(vi.VarType=='N') {
					// Get Number Range
					pos+=2;
					vi.nNumLo=atoi(pBuffer+pos);
					while(*(pBuffer+pos)!=',') pos++;
					pos++;
					vi.nStrLen=pos;
					vi.nNumHi=atoi(pBuffer+pos);
					while(*(pBuffer+pos)!=']') pos++;
					vi.nStrLen=pos-vi.nStrLen;
					pos+=2;
					
					// Get Name and Value
					DWORD dwStart=pos;
					while(*(pBuffer+pos)!='=') pos++;
					lstrcpyn(vi.svVarName,pBuffer+dwStart,min(pos-dwStart+1,256));
					pos++;
					dwValPos=pos;
					lstrcpyn(vi.svVarValue,pBuffer+pos,256);
					pos+=(vi.nStrLen+1);
				} else if(vi.VarType=='S') {
					// Get Number Range
					pos+=2;
					vi.nStrLen=atoi(pBuffer+pos);
					while(*(pBuffer+pos)!=']') pos++;
					pos+=2;
					
					// Get Name and Value
					DWORD dwStart=pos;
					while(*(pBuffer+pos)!='=') pos++;
					lstrcpyn(vi.svVarName,pBuffer+dwStart,min(pos-dwStart+1,256));
					pos++;
					lstrcpyn(vi.svVarValue,pBuffer+pos,256);
					dwValPos=pos;
					pos+=(vi.nStrLen+1);
				} else {
					traceLogA("Error parsing variables. Variable list could not be determined.");
					return;
				}
				
				// Add to variable info array
				vi.nPlugin=nPlugin;
				vi.dwPos=dwValPos;
				m_arrVarInfo.Add(vi);
				
			}
		}
	}

}
*/




