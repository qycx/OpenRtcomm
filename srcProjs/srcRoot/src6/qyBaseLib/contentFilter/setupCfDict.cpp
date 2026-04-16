

#include <ctype.h>
#include <stddef.h>
#include <windows.h>
#include "cfCommon.h"
#include "contentfilter.h"
#include "cfcomm.h"
#include "zhfunc.h"


#define DICT_CFG_FILE	"dict.dat"

CF_DICT *gpCFDict[TOTAL_CF_DICTS] , gpCFDictVar[TOTAL_CF_DICTS];



extern void cfInsertKey(char *pcSentence);


int setCFDicts( QY_CF_GBUF_STRUCT *pGBuf )
{

	pGBuf->cfDictCnt = TOTAL_CF_DICTS;

#ifndef __WITH_9C__

	pGBuf->pCFDict[CF_DICT_GB_IND] = ( CF_DICT * )pGBuf->shmAddr;
	pGBuf->pCFDict[CF_DICT_BIG5_IND] = ( CF_DICT * )( pGBuf->shmAddr + pGBuf->shmSize / 2 );

#else
	//added by frank to malloc gpCFDict

	pGBuf->pShmCfgSpace = ( SHM_CFG_SPACE * )pGBuf->shmAddr;
	pGBuf->pCFDict[0] = ( CF_DICT * )( pGBuf->shmAddr + SHM_CFG_SPACE_LEN );
	gpCFDict[0] = pGBuf->pCFDict[0];
	gpCFDict[0]->size = pGBuf->shmSize - SHM_CFG_SPACE_LEN;
	gpCFDict[0]->pStart = ( char * )gpCFDict[0] + 
		offsetof( CF_DICT, pEnd ) + sizeof( gpCFDict[0]->pEnd );
	gpCFDict[0]->pEnd = gpCFDict[0]->pStart;

#endif

	return 0;
}

 int getCFDictAvailable( CF_DICT *p )
{
	int size;
	size = gpCFDict[0]->size - ( int )( ( char * )p->pEnd - ( char * )p );
	return size;
}


 int getPhrase( FILE *fp, char *buf, unsigned int len ,int *lang,int *level)
{
	int c,preC;
	char *p;
	int isEn = 1;
	*level = CF_DENY;
	while ( ( c = fgetc( fp ) ) != '\"' && c != EOF );
	if ( c != '\"' ) return -1;
	p = buf;
//added by frank
	preC = c = fgetc( fp );
	
	if (  c=='W' ) {
		*level = CF_WARNING;
		c = fgetc( fp );
		}
	else { if ( c=='D' ) {
		*level = CF_DENY;
		c = fgetc( fp );
		}	
	else { if ( c == 'A' ) {
		*level = CF_ALERT;
		c = fgetc( fp );
		}
	}
	}	
	while ( len && ( ( preC == '\\') || ( c != '\"' ) )  && c != EOF ) {


	//judge if c is \ ,true drop it and read the next, fauls cp it to p.


		if ( c == '\\' ){ 
			preC = c;
			c = fgetc( fp );
			};
		*p = ( char )c; p ++; len --;
		if ( !( isascii( c ) ) ) {
				isEn = 0;
			}	
		
		preC = c;
		c = fgetc( fp );
		};

	if ( isEn ) {
			*lang = CS_LANGTYPE_EN;
		}
	else {
			*lang = CS_LANGTYPE_GB;
		};		
//end frank
	if ( c != '\"' ) return -1;
	return p - buf;

}

 int  setupCFDicts(  QY_CF_STRUCT  *  pCS,  CF_DICT  *  pCFDict[]  )
{ 
	int											iErr			=		-1;
	int											dictFileInd;
	int											i;
	FILE									*	fp				=		NULL;
	int											n;
	CF_KEY										tmpCK;
	int											lang,	lTypeInfo,  level;
	char										buf[1024];
	char										tmpDictFile[QY_MAXPATHLEN + 1];
	 
	traceLogA(  "setupCFDicts ..  enters."  );
	
	InitKeyHash(  );
	if  (  initAsrZh(  (  void  *  )pCS->pDictDir  )  )  goto errLabel;

	for  (  dictFileInd  =  0;  dictFileInd  <  pCS->cfFileCnt;  dictFileInd  ++  ) {
	
		 if  (  qyStrCat( ( char * )pCS->pDictDir, pCS->pCfFiles[dictFileInd].fileName, tmpDictFile, sizeof( tmpDictFile ) ) ) {
			 debugLog( "tmpDictFile is too small to contain [%s] and [%s], so the dict is skipped", pCS->pDictDir, pCS->pCfFiles[dictFileInd].fileName );
			 continue;
		 }

		 traceLogA(  "Policy file is [%s]",  tmpDictFile  );

		 fp  =  fopen(  tmpDictFile,  "r"  );
		 if  (  !fp  )  {
			 debugLog( "File [%s] can't be open.", tmpDictFile );
			 goto errLabel;
		 }		

		 if  (  pCS->pCfFiles[dictFileInd].preSetupDict  )  {
			 if  (  pCS->pCfFiles[dictFileInd].preSetupDict(  &pCS->pCfFiles[dictFileInd],  fp,  pCFDict[0]->opInfos  )  )  goto  errLabel;
		 }

		 traceLogA(  "setupCFDicts .. here."  );

		 pCFDict[0]->type  =  CS_LANGUAGE;
		 for  (  i  =  0;  ;  i  ++  )  {
			  if  (  getCFDictAvailable( pCFDict[0] ) < MIN_DICT_AVAILABLE )
				  break;
			  if  (  pCS->pCfFiles[dictFileInd].getPhrase  )  {
				  n  =  pCS->pCfFiles[dictFileInd].getPhrase(  &pCS->pCfFiles[dictFileInd],  fp,  buf,  sizeof(  buf  )  -  1,  &lang,  &lTypeInfo,  &level  );
			  	  }
			  else  {
					lang  =  pCS->pCfFiles[dictFileInd].curLangMode;
					n  =  getPhrase(  fp,  buf,  sizeof(  buf  )  -  1,  &lTypeInfo,  &level  );
			  }
			  if  (  n  <=  0  )  break;
			  buf[n]  =  0;
			  _strlwr(  buf  );
			  memset(  &tmpCK,  0,  sizeof(  tmpCK  )  );
			
			  n  =  min(  n,  sizeof(  tmpCK.key  )  );
			  memcpy(  tmpCK.key,  buf,  n  );
						
			  tmpCK.language[0]  =  lang;
			  memcpy(  tmpCK.typeInfo,  &lTypeInfo,  4  );
			  *( short * )tmpCK.value  =  level;
			  cfInsertKey(  (  char  *  )&tmpCK  );
			  if  (  lang  ==  CS_LANGUAGE  &&  lTypeInfo  ==  CS_LANGTYPE_GB  )  {
	
				  traceLogA(  "CF It is %s",  tmpCK.key  );

				  g2bFunc( ( unsigned char * )&tmpCK.key, n );
				  lTypeInfo  =  CS_LANGTYPE_BIG5;
				  memcpy(  tmpCK.typeInfo,  &lTypeInfo,  4  );
				  cfInsertKey( ( char * )&tmpCK );
			  }

		 }	// end of a specified dict file.
		 fclose( fp ); fp = NULL;
	}	// end of processing all dict file.

	iErr = 0;

errLabel:

	if ( fp ) fclose( fp );	
	
	exitAsrZh( );

	traceLogA(  "setupCFDicts ..  leaves."  );
	
	return iErr;
	
}

 void  destroyCFDicts(  CF_DICT  *  pCFDict[]  )
{
	ClearKeyHash( );

}


