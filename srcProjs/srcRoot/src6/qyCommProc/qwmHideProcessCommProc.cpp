
#include	<windows.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qwmHideProcessCommProc.h"

 extern  "C"  int  getModuleDirAndFinalName(  TCHAR  *  dirName,  unsigned  int  size,  TCHAR  *  finalName,  unsigned  int  finalNameSize    )
{
	TCHAR	svFileName[MAX_PATH  +  1]	=	_T(  ""  );
	TCHAR  *  pFinalModuleName			=	NULL;
	
 	GetModuleFileName(  NULL,  svFileName,  mycountof(  svFileName  )  );
	for  (  pFinalModuleName  =  svFileName  +  lstrlen(  svFileName  )  -  1;  pFinalModuleName  >  svFileName;  pFinalModuleName  --  )  {
		 if  (  *pFinalModuleName  ==  '\\'  )  {	
			 pFinalModuleName  ++  ;	 
			 if  (  finalName  &&  finalNameSize  )  lstrcpyn(  finalName,  pFinalModuleName,  finalNameSize  );
			 *pFinalModuleName  =  0;			 
			 if  (  dirName  &&  size  )  lstrcpyn(  dirName,  svFileName,  size  );
			 return  0;
		 }
	}

	return  -1;
}

 QY_DMITEM  CONST_permitToHideTable[]  =
{
	{	0,		_T(  "qwmSvr.exe"  ),		},
	{	0,		_T(  "qyWMonSvr2k.exe"  ),	},
#ifdef  __DEBUG__
	{	0,		_T(  "testRd.exe"  ),		},
#endif
	{	-1,		NULL,				},
};

 BOOL  bMyPermittedProcess(  )
{
	 BOOL			bRet				=	FALSE;
	 QY_DMITEM  *	pItem				=	NULL;
	 TCHAR			dirName[512]		=	_T(  ""  );
	 TCHAR			finalName[512]		=	_T(  ""  );
	 
	 if  (  getModuleDirAndFinalName(  dirName,  sizeof(  dirName  ),  finalName,  sizeof(  finalName  )  )  )  goto  errLabel;
	 //  验文件名
	 for  (  pItem  =  CONST_permitToHideTable;  pItem->type  !=  -1;  pItem  ++  )  {
		  if  (  !lstrcmpi(  pItem->des,  finalName  )  )  break;
	 }
	 if  (  pItem->type  ==  -1  )  goto  errLabel;

	 #ifndef  __DEBUG__
	 
			  //  验目录, 必须是系统目录的
			  GetSystemDirectory(  finalName,  sizeof(  finalName  )  );
			  if  (  finalName[lstrlen(  finalName  )  -  1]  !=  '\\'  )  {
				  finalName[lstrlen(  finalName  )  +  1]  =  0;
				  finalName[lstrlen(  finalName  )]  =  '\\';
			  }
			  if  (  lstrcmpi(  finalName,  dirName  )  )  goto  errLabel;
	 #endif

	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}

 /*
*/
