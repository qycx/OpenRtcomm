
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<stdio.h>
//
//#include	<WinSock2.h>

#if 0
#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#endif

#include	"qytcharcommproc.h"

//
extern  "C"  void  tTrim_open(TCHAR * buf)
{
	TCHAR* p;
	unsigned  int		len = lstrlen(buf);

	if (!buf || !(len = lstrlen(buf)))  return;
	p = buf + len - 1;

	while (_istspace(*p) && p >= buf)  p--;
	p[1] = 0;

	if (p >= buf) {
		p = buf;
		while (_istspace(*p))  p++;
		lstrcpy(buf, p);
	}

	return;

}



//
extern  "C"  void  safeStrnCpy_open(char* strIn, char* strOut, unsigned  int  size)
{
	if (!size || !strIn || !strOut)  return;
	unsigned  int	len = min(size - 1, (unsigned  int)strlen(strIn));
	memcpy(strOut, strIn, len);
	strOut[len] = 0;
	return;
}



//

 //  ½«ÆÕÍ¨µÄ×Ö·û´®×ª³Éutf8±àÂëµÄ
extern  "C"  char* myStr2Utf8(char* buf, unsigned  int  size)
{
	int				iErr = -1;
	WCHAR				wBuf[512];
	int				len;
	int				cchMulti;
	unsigned  int		uiCodePage = CP_ACP;		//  2005/01/14

	if (!buf || !buf[0] || !size)  goto  errLabel;

	if (strlen(buf) >= size)  buf[size - 1] = 0;	//  ÐÞÕûÒ»ÏÂ

	memset(wBuf, 0, sizeof(wBuf));
	len = MultiByteToWideChar(uiCodePage, 0, buf, -1, NULL, NULL);
	if (len <= 0 || len > sizeof(wBuf) / sizeof(wBuf[0]))  goto  errLabel;
	if (len != MultiByteToWideChar(uiCodePage, 0, buf, -1, wBuf, len))  goto  errLabel;

	cchMulti = WideCharToMultiByte(CP_UTF8, 0, wBuf, len, NULL, 0, NULL, NULL);
	if (cchMulti <= 0 || cchMulti >= (int)size)  goto  errLabel;
	if (cchMulti != WideCharToMultiByte(CP_UTF8, 0, wBuf, len, buf, cchMulti, NULL, NULL))  goto  errLabel;

	buf[cchMulti] = 0;

	iErr = 0;
errLabel:
	return  iErr ? NULL : buf;

}


//  ½«utf8±àÂëµÄ×Ö·û´®×ª³ÉÆÕÍ¨µÄ
extern  "C"  char* myUtf82Str(char* buf, unsigned  int  size)
{
	int				iErr = -1;
	WCHAR				wBuf[512];
	int				len;
	int				cchMulti;
	unsigned  int		uiCodePage = CP_ACP;		//  2005/01/14

	if (!buf || !buf[0] || !size)  goto  errLabel;

	if (strlen(buf) >= size)  buf[size - 1] = 0;	//  ÐÞÕûÒ»ÏÂ

	memset(wBuf, 0, sizeof(wBuf));
	len = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, NULL);
	if (len <= 0 || len > sizeof(wBuf) / sizeof(wBuf[0]))  goto  errLabel;
	if (len != MultiByteToWideChar(CP_UTF8, 0, buf, -1, wBuf, len))  goto  errLabel;

	cchMulti = WideCharToMultiByte(uiCodePage, 0, wBuf, len, NULL, 0, NULL, NULL);
	if (cchMulti <= 0 || cchMulti >= (int)size)  goto  errLabel;
	if (cchMulti != WideCharToMultiByte(uiCodePage, 0, wBuf, len, buf, cchMulti, NULL, NULL))  goto  errLabel;

	buf[cchMulti] = 0;

	iErr = 0;
errLabel:
	return  iErr ? NULL : buf;

}



extern  "C"  WCHAR * myStr2WChar(const  char* str, WCHAR * wBuf, unsigned  int  wBufSize)
{
	int		iErr = -1;
	int		wBufSizeNeeded = 0;

	wBufSizeNeeded = MultiByteToWideChar(CP_ACP, 0, str, -1, wBuf, 0);
	if (wBufSizeNeeded > (int)wBufSize)  goto  errLabel;
	if (wBufSizeNeeded != MultiByteToWideChar(CP_ACP, 0, str, -1, wBuf, wBufSize))  goto  errLabel;
	iErr = 0;
errLabel:
	return  (WCHAR*)(iErr ? L"" : wBuf);
}

extern  "C"  char* myWChar2Str(LPCWSTR  wStr, char* buf, unsigned  int  bufSize)
{
	int		iErr = -1;
	int		bufSizeNeeded = 0;

	bufSizeNeeded = WideCharToMultiByte(CP_ACP, 0, wStr, -1, buf, 0, NULL, NULL);
	if (bufSizeNeeded > (int)bufSize)  goto  errLabel;
	if (bufSizeNeeded != WideCharToMultiByte(CP_ACP, 0, wStr, -1, buf, bufSize, NULL, NULL))  goto  errLabel;
	iErr = 0;
errLabel:
	return  (char*)(iErr ? "" : buf);
}


extern  "C"  char* myWChar2Utf8(LPCWSTR  wStr, char* buf, unsigned  int  bufSize)
{
	int		iErr = -1;
	int		bufSizeNeeded = 0;
	UINT	uiCodePage = CP_UTF8;

	bufSizeNeeded = WideCharToMultiByte(uiCodePage, 0, wStr, -1, buf, 0, NULL, NULL);
	if (bufSizeNeeded > (int)bufSize)  goto  errLabel;
	if (bufSizeNeeded != WideCharToMultiByte(uiCodePage, 0, wStr, -1, buf, bufSize, NULL, NULL))  goto  errLabel;
	iErr = 0;
errLabel:
	return  iErr ? NULL : buf;
}

extern  "C"  WCHAR * myUtf82WChar(char* str, WCHAR * wBuf, unsigned  int  wBufSize)
{
	int		iErr = -1;
	int		wBufSizeNeeded = 0;
	UINT	uiCodePage = CP_UTF8;

	wBufSizeNeeded = MultiByteToWideChar(uiCodePage, 0, str, -1, wBuf, 0);
	if (wBufSizeNeeded > (int)wBufSize)  goto  errLabel;
	if (wBufSizeNeeded != MultiByteToWideChar(uiCodePage, 0, str, -1, wBuf, wBufSize))  goto  errLabel;
	iErr = 0;
errLabel:
	return  iErr ? NULL : wBuf;
}



//
 extern  "C"  TCHAR  *  myStr2TChar(  char  *  buf,  TCHAR  *  tBuf,  unsigned  int  tBufSize  )
{
	int		iErr	=	-1;
	#ifndef	UNICODE
			safeStrnCpy_open(  buf,  tBuf,  tBufSize  );			
	#else
			if  (  !myStr2WChar(  buf,  tBuf,  tBufSize  )  )  goto  errLabel;
	#endif

	iErr  =  0;

#ifdef  UNICODE
errLabel:
#endif

	return  iErr  ?  NULL  :  tBuf;

}

 extern  "C"  char  *  myTChar2Str(  LPCTSTR  tBuf,  char  *  buf,  unsigned  int  bufSize  )
{
	 int	iErr	=	-1;
	 #ifndef  UNICODE
			  safeStrnCpy_open(  (  char  *  )tBuf,  buf,  bufSize  );
	 #else
			  if  (  !myWChar2Str(  (  LPTSTR  )tBuf,  buf,  bufSize  )  )  goto  errLabel;
	 #endif
	 iErr  =  0;

#ifdef  UNICODE
errLabel:
#endif
	 return  iErr  ?  NULL  :  buf;

}


 extern  "C"  char  *  myTChar2Utf8(  LPCTSTR  tBuf,  char  *  buf,  unsigned  int  bufSize  )
{
	 int	iErr	=	-1;
	 #ifndef  UNICODE
			  safeStrnCpy_open(  (  char  *  )tBuf,  buf,  bufSize  );
			  myStr2Utf8(  buf,  bufSize  );
	 #else
			  if  (  !myWChar2Utf8(  tBuf,  buf,  bufSize  )  )  goto  errLabel;
	 #endif
	 iErr  =  0;
#ifdef  UNICODE
errLabel:
#endif
	 return  iErr  ?  NULL  :  buf;

}

 extern  "C"  TCHAR  *  myUtf82TChar(  char  *  buf,  TCHAR  *  tBuf,  unsigned  int  tBufSize  )
{
	int		iErr  =  -1;
	#ifndef  UNICODE
			 safeStrnCpy_open(  buf,  tBuf,  tBufSize  );  if  (  !myUtf82Str(  tBuf,  tBufSize  )  )  goto  errLabel;
	#else
			 if  (  !myUtf82WChar(  buf,  tBuf,  tBufSize  )  )  goto  errLabel;
	#endif
	
	iErr  =  0;

errLabel:
	return  iErr  ?  NULL  :  tBuf;
}


 //  2005/11/27
 extern  "C"  WCHAR  *  myTChar2WChar(  LPCTSTR  tBuf,  WCHAR  *  wBuf,  unsigned  int  wBufSize  )
{
	int		iErr	=	-1;

	#ifndef  UNICODE
			 if  (  !myStr2WChar(  tBuf,  wBuf,  wBufSize  )  )  goto  errLabel;
	#else
			 lstrcpyn(  wBuf,  tBuf,  wBufSize  );
	#endif
	iErr  =  0;

#ifndef  UNICODE
errLabel:
#endif

	return  (WCHAR*)(iErr  ?  L""  :  wBuf);
}

 //  2005/11/27
 extern  "C"  TCHAR  *  myWChar2TChar(  LPCWSTR  wBuf,  TCHAR  *  tBuf,  unsigned  int  tBufSize  )
{
	int		iErr	=	-1;

	#ifndef  UNICODE
			 if  (  !myWChar2Str(  wBuf,  tBuf,  tBufSize  )  )  goto  errLabel;
	#else
			 lstrcpyn(  tBuf,  wBuf,  tBufSize  );
	#endif
	iErr  =  0;

#ifndef  UNICODE
errLabel:
#endif

	return  (TCHAR*)(iErr  ?  _T(  ""  )  :  tBuf);
}



#if  0  
 extern  "C"  void  iitTrim(  TCHAR  *  buf  )
{
        TCHAR			*	p;
		unsigned  int		len		=	lstrlen(  buf  );

		if  (  !buf  ||  !(  len  =  lstrlen(  buf  )  )  )  return;
        p  =  buf  +  len  -  1;

        while  (  _istspace(  *p  )  &&  p  >=  buf  )  p  --;
        p[1]  =  0;

        if  (  p  >=  buf  )  {
            p  =  buf;
            while  (  _istspace(  *p  )  )  p  ++;
			lstrcpy(  buf,  p  );
        }

        return;

}
#endif

 extern  "C"  int  tQyQuoteFileName(  TCHAR  *  fileName,  unsigned  int  charSize  )
{

	//  extern  "C"  int  qyQuoteFileName(  char  *  fileName,  unsigned  int  size  )

	 unsigned  int	len;
	 TCHAR			quotedFileName[MAX_PATH  +  1];

	 tTrim_open(  fileName  );
	 if  (  fileName[0]  ==  '\"'  )  return  0;
	 len  =  lstrlen(  fileName  );
	 if  (  len  >=  charSize  -  2  ||  len  +  2  >  MAX_PATH  )  return  -1;
	 _sntprintf(  quotedFileName,  sizeof(  quotedFileName  )  /  sizeof(  TCHAR  ),  _T(  "\"%s\""  ),  fileName  );
	 lstrcpy(  fileName,  quotedFileName  );
	 return  0;	 
}

 extern  "C"  int  tmp_trailDir(TCHAR * dir, unsigned  int  size)
 {
	 unsigned  int	len;

	 tTrim_open(dir);
	 len = lstrlen(dir);
	 //
	 if (len >= 1 && size >= len + 1) {
		 if (dir[len - 1] == '\\')  return  0;
	 }
	 //
	 if (len + 2 > size)  return  -1;
	 dir[len] = '\\';
	 dir[len + 1] = 0;
	 return  0;

 }


 extern  "C"  int  tTrailDir(  TCHAR  *  dir,  unsigned  int  size  )
{
#if  0
	 unsigned  int	len;

	 tTrim(  dir  );
	 len  =  lstrlen(  dir  );
	 if  (  dir[len  -  1]  ==  '\\'  )  return  0;
	 if  (  len  +  2  >  size  )  return  -1;
	 dir[len]  =  '\\';
	 dir[len  +  1]  =  0;
	 return  0;
#endif
	 //
	 return  tmp_trailDir(  dir,  size  );
	
}


 //
 extern  "C"  int  tQyStrCat_open(  TCHAR  *  str1,  TCHAR  *  str2,  TCHAR  *  containedBuf,  unsigned  int  bufSize  ) 
{
	 int  iErr  =  -1;

	 if  (  str2  ==  containedBuf  )  {
		 //traceLogA(  "qyStrCat( ): str2 can't be the place to contain."  );
		 goto  errLabel;
	 }
	 if  (  lstrlen(  str1  )  +  lstrlen(  str2  )  >=  (  int  )bufSize  )  {
		 //traceLogA(  "qyStrCat( ): buf too small."  );
		 goto  errLabel;
	 }
	 _sntprintf(  containedBuf,  bufSize,  _T(  "%s%s"  ),  str1,  str2  );
	 iErr  =  0;

errLabel:

	 return  iErr;

}

