
#include	"stdafx.h"
#include	"myTChar.h"




//
extern  "C"  __declspec(  dllexport  )  char* stristr (const char * str1,const char * str2)
{
	char *cp = (char *) str1;
	char *s1, *s2;

	//
	if  (  !str1  ||  !str2  )  return  NULL;

	//
if ( !*str2 )
return((char *)str1);


while (*cp)
{
s1 = cp;
s2 = (char *) str2;


while (*s1 && *s2)
{
char ch1=*s1,ch2=*s2;
if (isascii(*s1) && isupper(*s1) ) ch1 = _tolower(*s1);
if (isascii(*s2) && isupper(*s2) ) ch2 = _tolower(*s2);


if(ch1-ch2==0) s1++, s2++;
else break;
}

if (!*s2)
return(cp);


cp++;
}


return(NULL);


}


//
extern  "C"  __declspec(  dllexport  )  WCHAR* wcsistr (const WCHAR * str1,const WCHAR * str2)
{
	WCHAR *cp = (WCHAR *) str1;
	WCHAR *s1, *s2;

	//
	if  (  !str1  ||  !str2  )  return  NULL;

	//
if ( !*str2 )
return((WCHAR *)str1);


while (*cp)
{
s1 = cp;
s2 = (WCHAR *) str2;


while (*s1 && *s2)
{
WCHAR ch1=*s1,ch2=*s2;
if (iswascii(*s1) && iswupper(*s1) ) ch1 = towlower(*s1);
if (iswascii(*s2) && iswupper(*s2) ) ch2 = towlower(*s2);


if(ch1-ch2==0) s1++, s2++;
else break;
}


if (!*s2)
return(cp);


cp++;
}


return(NULL);


}


