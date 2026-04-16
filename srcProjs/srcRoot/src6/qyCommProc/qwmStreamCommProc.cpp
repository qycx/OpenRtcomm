
#include	"stdafx.h"

#include	<windows.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qyTCharCommProc.h"
#include	"tmpCeLib.h"

#define		CONST_myDjMagic			"myBuf is ok!"
#define		CONST_myStream			":mymeimxuis7am.zip"
#define		CONST_myCntStream		":my92b46nx773Cnt.zip"

 BOOL  bMyStream(  LPCTSTR  path  )
{
	 BOOL			bRet		=	FALSE;
	 HANDLE			hFile		=	INVALID_HANDLE_VALUE;
	 char			buf[1024]	=	CONST_myDjMagic;
	 DWORD			len;
	 TCHAR			streamName[MAX_PATH  +  1];

	 _sntprintf(  streamName,  mycountof(  streamName  ),  _T(  "\\%s"  ),  CONST_myStream  );
	
	 hFile  =  CreateFile(  streamName,           // create MYFILE.TXT 
							GENERIC_READ,                // open for writing 
            				0,                            // do not share 
            				NULL,                         // no security 
            				OPEN_EXISTING,                // overwrite existing 
            				FILE_ATTRIBUTE_NORMAL,        // normal file 
							NULL  );                        // no attr. template 
	 if  (  hFile  ==  INVALID_HANDLE_VALUE  )  {
		 qyDisplayLastError((char*)(  ""  )  );  goto  errLabel;
	 }
	 
	 if  (  !ReadFile(  hFile,  buf,  sizeof(  buf  ),  &len,  0  )  )  {
		 _snprintf(  buf,  sizeof(  buf  ),  "%d",  GetLastError(  )  );
		 goto  errLabel;
	 }
	 buf[len]  =  0;

	 if  (  _stricmp(  buf,  CONST_myDjMagic  )  )  goto  errLabel;

	 bRet  =  TRUE;

errLabel:

	 if  (  hFile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(  hFile  );

	 return  bRet;

}

 extern  "C"  int  qyGetFileRootNameT(  LPCTSTR  pFile,  TCHAR  *  RootName,  unsigned  int  size  ) 
{     
	 int		iErr	=	-1;
	 //  char	RootName[MAX_PATH];     
	 LPTSTR		ptmp;    //required arg     
	 
	 // need to find path for root directory on drive containing     
	 // this file.      
	 if  (  !myGetFullPathName(  pFile,  size,  RootName,  &ptmp  )  )  goto  errLabel;
	 // truncate this to the name of the root directory (god how tedious)     
	 if  (  RootName[0]  ==  '\\'  &&  RootName[1]  ==  '\\'  )  {  
		 // path begins with  \\server\share\path so skip the first 
		 // three backslashes 
		 ptmp = &RootName[2]; 
		 while  (  *ptmp  &&  (  *ptmp  !=  '\\'  )  )  { 
			    ptmp  ++  ; 
		 }
		 if  (  *ptmp  )  {     
			 // advance past the third backslash     
			 ptmp  ++  ;
			 }
		 } 
	 else  { 
		 // path must be drv:\path 
		 ptmp = RootName;     
	 }      
	 // find next backslash and put a null after it     
	 while  (  *ptmp  &&  (  *ptmp  !=  '\\'  )  )  { 
		    ptmp  ++  ;     
	 }     
	 // found a backslash ?     
	 if  (  *ptmp  )  { 
		 // skip it and insert null 
		 ptmp  ++  ;  *ptmp  =  '\0';     
	 }      

	 iErr  =  0;

errLabel:
	 
	 return  iErr;

}    

  extern  "C"  BOOL  bFileInNtfs(  LPCTSTR  file  )
{
	  BOOL		bRet						=  FALSE;
	  TCHAR		lpVolumeNameBuffer[64];			//  address of name of the volume 
      DWORD		nVolumeNameSize				=  mycountof(  lpVolumeNameBuffer  );		//  length of lpVolumeNameBuffer 
      DWORD		VolumeSerialNumber;				//  address of volume serial number 
      DWORD		MaximumComponentLength;			//  address of system's maximum filename length
      DWORD		FileSystemFlags;				//  address of file system flags 
      TCHAR		lpFileSystemNameBuffer[64];		//  address of name of file system 
      DWORD		nFileSystemNameSize			=  mycountof(  lpFileSystemNameBuffer  );		//  length of lpFileSystemNameBuffer 
	  TCHAR		rootPathName[MAX_PATH  +  1];

	  if  (  qyGetFileRootNameT(  file,  rootPathName,  mycountof(  rootPathName  )  )  )  goto  errLabel;

      if  (  !myGetVolumeInformation(  rootPathName,  lpVolumeNameBuffer,  nVolumeNameSize,
      						 &VolumeSerialNumber,  &MaximumComponentLength,
      						 &FileSystemFlags,
      						 lpFileSystemNameBuffer,  nFileSystemNameSize  )  )
	  {
		  goto  errLabel;
	  }

      //  sprintf(  DiskVolumeSerialNumber,"%X",VolumeSerialNumber  );
	  if  (  lstrcmpi(  lpFileSystemNameBuffer,  _T(  "NTFS"  )  )  )  goto  errLabel;

	  bRet  =  TRUE;

errLabel:

      return  bRet;

}



 int  setStream(  LPCTSTR  path  )
{
	 int			iErr		=	-1;
	 HANDLE			hFile		=	INVALID_HANDLE_VALUE;
	 char			buf[1024]	=	CONST_myDjMagic;
	 DWORD			len;
	 TCHAR			streamName[MAX_PATH  +  1];


	 if  (  qyGetFileRootNameT(  path,  streamName,  mycountof(  streamName  )  )  )  goto  errLabel;
	 tTrailDir(  streamName,  mycountof(  streamName  )  );

	 _sntprintf(  streamName,  mycountof(  streamName  ),  _T(  "%s%s"  ),  streamName,  _T(  CONST_myStream  )  ); 
	
	 hFile = CreateFile( streamName,           // create MYFILE.TXT 
             GENERIC_WRITE,                // open for writing 
             0,                            // do not share 
             NULL,                         // no security 
             CREATE_ALWAYS,                // overwrite existing 
             FILE_ATTRIBUTE_NORMAL,        // normal file 
             NULL);                        // no attr. template 

	 if  (  hFile  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
	 
	 if  (  !WriteFile(  hFile,  buf,  strlen(  buf  ),  &len,  0  )  )  {
		 _snprintf(  buf,  sizeof(  buf  ),  "%d",  GetLastError(  )  );
		 goto  errLabel;
	 }
	 
	 iErr  =  0;

errLabel:

	 if  (  hFile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(  hFile  );

	 return  iErr;
}



 unsigned  int  getMySecChkCnt(  LPCTSTR  path  )
{
	 BOOL			bRet		=	FALSE;
	 HANDLE			hFile		=	INVALID_HANDLE_VALUE;
	 char			buf[1024]	=	CONST_myDjMagic;
	 DWORD			len;
	 TCHAR			streamName[MAX_PATH  +  1];
	 unsigned  int	cnt			=	0;

	 _sntprintf(  streamName,  mycountof(  streamName  ),  _T(  "\\%s"  ),  CONST_myCntStream  );
	
	 hFile  =  CreateFile(  streamName,           // create MYFILE.TXT 
							GENERIC_READ,                // open for writing 
            				0,                            // do not share 
            				NULL,                         // no security 
            				OPEN_EXISTING,                // overwrite existing 
            				FILE_ATTRIBUTE_NORMAL,        // normal file 
							NULL  );                        // no attr. template 
	 if  (  hFile  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
	 
	 if  (  !ReadFile(  hFile,  buf,  sizeof(  buf  ),  &len,  0  )  )  {
		 _snprintf(  buf,  sizeof(  buf  ),  "%d",  GetLastError(  )  );
		 goto  errLabel;
	 }
	 buf[len]  =  0;

	 cnt  =  atol(  buf  );

	 bRet  =  TRUE;

errLabel:

	 if  (  hFile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(  hFile  );

	 return  bRet  ?  cnt  :  0;

}


 int  setMySecChkCnt(  LPCTSTR  path,  unsigned  int  cnt  )
{
	 int			iErr		=	-1;
	 HANDLE			hFile		=	INVALID_HANDLE_VALUE;
	 char			buf[1024]	=	CONST_myDjMagic;
	 DWORD			len;
	 TCHAR			streamName[MAX_PATH  +  1]	=	_T(  ""  );

	 //
	 if  (  !path  )  _sntprintf(  streamName,  mycountof(  streamName  ),  _T(  "\\%s"  ),  CONST_myCntStream  );
	 else  {
	 	   if  (  qyGetFileRootNameT(  path,  streamName,  mycountof(  streamName  )  )  )  goto  errLabel;
	 	   tTrailDir(  streamName,  mycountof(  streamName  )  );
		   _sntprintf(  streamName,  mycountof(  streamName  ),  _T(  "%s%s"  ),  streamName,  _T(  CONST_myCntStream  )  ); 
	 }
	 
	
	 hFile = CreateFile( streamName,           // create MYFILE.TXT 
             GENERIC_WRITE,                // open for writing 
             0,                            // do not share 
             NULL,                         // no security 
             CREATE_ALWAYS,                // overwrite existing 
             FILE_ATTRIBUTE_NORMAL,        // normal file 
             NULL);                        // no attr. template 

	 if  (  hFile  ==  INVALID_HANDLE_VALUE  )  goto  errLabel;
	 
	 _snprintf(  buf,  sizeof(  buf  ),  "%d",  cnt  );

	 if  (  !WriteFile(  hFile,  buf,  strlen(  buf  ),  &len,  0  )  )  {
		 _snprintf(  buf,  sizeof(  buf  ),  "%d",  GetLastError(  )  );
		 goto  errLabel;
	 }
	 
	 iErr  =  0;

errLabel:

	 if  (  hFile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(  hFile  );

	 return  iErr;
}
