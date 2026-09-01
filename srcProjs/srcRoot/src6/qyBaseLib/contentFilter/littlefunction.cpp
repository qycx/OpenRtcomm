
#include <ctype.h>
#include <windows.h>

#include "cfcommon.h"
#include "contentfilter.h"
#include "vardefine.h"



//This Function return the True length we appand
int memCp ( SESSION_INFO *pSessionInfo, char *ptr, int len)

{
	int store=-1;
	int isCIn=0;
	int Courent=0;
	int True_Copy=0;	
	char Char_Judge_E;
	int count;
	count = min (pSessionInfo->bSize-pSessionInfo->bLen , len); 
	
	do { 
	  do {
		if (Courent < count-1) {
		isCIn = 0;	
		if ( *(ptr + Courent)=='<' ) {
				store = Courent;
		do {	
			Courent++;
			if ( !isascii( *(ptr+Courent) ) ){
				isCIn = 1;	
				break;
			}
		
		}while (  !( *( ptr + Courent ) == '>' ) && (Courent < count-1) );
		
		if ( ( *( ptr + Courent ) == '>' ) && (store != -1) ) {
			Courent++;
			store = -1;
			}
		else {
			Courent = store + 1;
			}
		};		
            //drop the string between <>;
/*
		if (Courent < count-1){

		if ( (*(ptr + Courent) ==' ')|| ( *(ptr + Courent)=='	' ) ) {

			Char_Judge_E= *(ptr + Courent - 1);
			if ( !( ( (Char_Judge_E >= 'a') && (Char_Judge_E <= 'z')
		) || ( (Char_Judge_E >= 'A') && (Char_Judge_E <= 'Z') ) ) ){
			if ( isasiiChar_Judge_E 

		 do {
			Courent++;

			}while( ((*(ptr + Courent ))==' '|| 
			( *(ptr +Courent)=='	') ) && ( Courent <count -1 ) );

		      };

		   };

		};
	//drop the blank;*/	
		if (Courent < count-1){
			if ((*(ptr+Courent) == 13) || ( *(ptr + Courent))==10 ){
		    		do {
					Courent++;
				}while ( ( ( *(ptr + Courent ) == 13)||
				(*(ptr+Courent)==10)) && (Courent < count -1) );

/*	if( (pSessionInfo->bLen < pSessionInfo->bSize) 
				&& ( Courent < count) && 
				( (pSessionInfo->pTmpB + 
				pSessionInfo->bLen - 1 ) !=' ' )){ 
   		    	*(pSessionInfo->pTmpB + pSessionInfo->bLen) 
				= ' ';
				pSessionInfo->bLen++;
				Courent ++;
				True_Copy++;
				}*/
	   		};
		};	
		if (Courent < count-1){

		if ( (*(ptr + Courent) ==' ')|| ( *(ptr + Courent)=='	' ) ) {

			Char_Judge_E= *(ptr + Courent - 1);
			if ( !( ( (Char_Judge_E >= 'a') && (Char_Judge_E <= 'z')
		) || ( (Char_Judge_E >= 'A') && (Char_Judge_E <= 'Z') ) ) ){

		 do {
			Courent++;

			}while( ((*(ptr + Courent ))==' '|| 
			( *(ptr +Courent)=='	') ) && ( Courent <count -1 ) );
			};

		   };

		};
	//drop the blank;	
		 };
		
		do
		{
		
		if (Courent >= count-6) break;

		if ( 	*(ptr + Courent) =='&' 
			&&  *(ptr + Courent + 1 ) =='n' 
			&&  *(ptr + Courent + 2 ) =='b' 
			&&  *(ptr + Courent + 3 ) =='s' 
			&&  *(ptr + Courent + 4 ) =='p' 
			&&  *(ptr + Courent + 5 ) ==';' ) {
				Courent +=6;
				}
				else break;
	
		debuglog("CF frankmemcp &nbsp now ptr is %c",*(ptr + Courent) );
			
		}while ( *(ptr + Courent) == '&' );
	
	}while( (  *(ptr+Courent) == '<' || *(ptr+Courent) == 13 
			|| *(ptr+Courent) == 10  ) 
			&& (Courent < count-1) && ( isCIn == 0) );

	if( (pSessionInfo->bLen < pSessionInfo->bSize) && ( Courent < count) ){
       	*(pSessionInfo->pTmpB + pSessionInfo->bLen) = *( ptr + Courent );
	pSessionInfo->bLen++;
	Courent ++;
	True_Copy++;
		}
	else { 

			debuglog("CF out range!!!");
		break;
	 	};
	}while ( Courent < count );

	return True_Copy;
}

//This function return the Content_Type in html page.
int	getContentType(char *p)
{
	int iContentType;

	iContentType = CF_CONTENT_TEXT_HTML;

/*	if ( !strncasecmp(p , TEXTHTML , strlen(TEXTHTML) ) ) {
		iContentType = CF_CONTENT_TEXT_HTML;
		}
	else { if ( !strncasecmp( p , TEXTPLAIN , strlen(TEXTPLAIN) ) ) {
		iContentType = CF_CONTENT_TEXT_PLAIN;
		}
	else { if ( !strncasecmp( p , TEXTENRICHED , strlen(TEXTENRICHED) ) ) {
		iContentType = CF_CONTENT_TEXT_ENRICHED;
		}
	else { if ( !strncasecmp( p , TEXTRICHTEXT , strlen(TEXTRICHTEXT) ) ) {
		iContentType = CF_CONTENT_TEXT_RICHTEXT;
		}
	else { if ( !strncasecmp( p , TEXTXDIV , strlen(TEXTXDIV) ) ) {
		iContentType = CF_CONTENT_TEXT_XDVI;
		}
	else { if ( !strncasecmp( p , TEXTXC , strlen(TEXTXC) ) ) {
		iContentType = CF_CONTENT_TEXT_XC;
		}
	else { iContentType = CF_CONTENT_TYPE_UNKNOWN;
		}
					}
				}
			}
		}
	}*/
	debuglog("CF getContentType( )",p,10 );
	
	return iContentType;
}



