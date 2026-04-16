/*
CodeTable:
	Chinese		---	 1X
	Japanese	---	 2X
	Korean		---  3X
	English		---  4X
note:X explain the actual coding mathod
*/
#define LANGUAGE_CODE_NUMBER 17
char *pLanguageToken[] = 
{
	"gb2312",
	"cn-gb",			
	"cn-gbk",			//0-2	return 11

	"big5",
	"cn-big5",			//3-4	return 12

	"hz-gb-2312",		//5		return 13
		
	"iso-2022-cn",		//6 return 14
	
	"iso-2022-cn-ext",	//7 return 15

	"jis",
	"iso-2022-jp",		//8-9 return 21
		
	"shift-JIS",
	"sjis",				//10-11 return 22

	"ksc",
	"euc-kr",			//12-13 return 31

	"iso-2022-kr",		//14 return 32

	"iso-8859-1",
	"us-ascii"			//15-16 return 41
};

