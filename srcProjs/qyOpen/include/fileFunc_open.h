

#ifndef  __fileFunc_open_h__
#define  __fileFunc_open_h__	//  {

//
extern  "C"  BOOL  bDir(LPCTSTR  dir);
extern  "C"  bool  bFileExists(  LPCTSTR  fileName  );


//
typedef  struct  __tmpFileResult_t		{
				 TCHAR					fileName[256];
				 unsigned  __int64		ui64FileLen;
}		 TmpFileResult;

//
typedef  int  (*PF_enumUsrDir)(LPVOID  p0, LPVOID  p1, TmpFileResult  *  p2);



extern  "C"  int  enumUsrDir_open(LPCTSTR  usrsRootDir, PF_enumUsrDir  pF, void* p0, void* p1);


#endif  //  }

