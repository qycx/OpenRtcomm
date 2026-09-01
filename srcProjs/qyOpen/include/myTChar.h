
#ifndef  __myTChar_h__
#define  __myTChar_h__	//  {

//T函数申明

#ifdef UNICODE
# define my_tcsistr wcsistr
#else
# define my_tcsistr stristr
#endif


//
extern  "C"  __declspec(  dllexport  )  char* stristr (const char * str1,const char * str2);
extern  "C"  __declspec(  dllexport  )  WCHAR* wcsistr (const WCHAR * str1,const WCHAR * str2);





#endif  }


