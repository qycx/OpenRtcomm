
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#if  0
#include <sys/types.h>
#endif
#include <windows.h>


#include "vardefine.h"
#include "cfCommon.h"
#include "keyvalue.h"
#include "cfCfg.h"
#include "contentfilter.h"
#include "contentfilterFunc.h"


// SESSION_INFO sI;
QY_CF_GBUF_STRUCT	gBuf;
// int pResultCF;
	
int filterContent( CF_DICT *pCFDict, char *pContent, int len, int param1, int *pResultCF );
extern int cfCfgServRun( QY_CF_STRUCT *pCF, QY_CF_GBUF_STRUCT *pGBuf );
// extern void exitDoCF( SESSION_INFO *p );

 extern  "C"  void  cfIncIeCnt(  )
{
	 gBuf.pShmCfgSpace->iIeCnt  ++  ;
}

 extern  "C"  int  cfGetIeCnt(  )
{
	 return  gBuf.pShmCfgSpace->iIeCnt;
}


int setDefaultShmCfg( SHM_CFG_SPACE *p )
{
	p->bCFOn = TRUE;
	p->bDictChanged = FALSE;
    p->bCFLogOn = TRUE;

	return 0;

}



 int getCFDicts( QY_CF_GBUF_STRUCT *pGBuf )
{
	return setCFDicts( pGBuf );
}


 void showCFDicts( CF_DICT *p[], int dictCnt )
{
	showDict( );
}



// Why we malloc additional 256 bytes for big and small buffers?
// For we shall compare the dictionary item with buffer, the 256 bytes 
// will prevent content in buffer overflow.

/*
 int initDoCF( SESSION_INFO *p )
{
	int iErr = -1;

	debugLog( "initDoCF( ) enters." );

	if ( p->bSize || p->sSize || p->pTmpB || p->pTmpS ) {
		debugLog( "Invalid input, so returns." );
		return -1;
	}
	
	p->pTmpB = (char *) malloc( TMP_B_BUF_SIZE + 256 );
	p->pTmpS = (char *) malloc( TMP_S_BUF_SIZE + 256 );
	if ( !p->pTmpB || !p->pTmpS ) {
		goto errLabel;
	}
	memset( p->pTmpB + TMP_B_BUF_SIZE, ' ', 256 );
	memset( p->pTmpS + TMP_S_BUF_SIZE, ' ', 256 );
	p->bSize = TMP_B_BUF_SIZE;
	p->sSize = TMP_S_BUF_SIZE;
	p->bLen = 0;
	p->sLen = 0;

	p->charsetType = CS_GB;
	
	iErr = 0;

errLabel:

	if ( iErr ) {
		if ( p->pTmpB ) { free( p->pTmpB ); p->pTmpB = NULL; }
		if ( p->pTmpS ) { free( p->pTmpS ); p->pTmpS = NULL; }
	}

	debugLog( "initDoCF( ) leaves." );

	return iErr;

}

  */

 /*
 void exitDoCF( SESSION_INFO *p )
{

	if ( p->pTmpB ) {
		free( p->pTmpB ); p->pTmpB = NULL;
		p->bSize = 0;
	};
	if ( p->pTmpS ) {
		free( p->pTmpS ); p->pTmpS = NULL;
		p->sSize = 0;
	};

	return;

}

  */

 int getCharsetType( char *p )
{
	int iType = CS_LANGTYPE_GB;
	return iType;

}


 int doCF( QY_CF_GBUF_STRUCT *pGBuf, SESSION_INFO *pSessionInfo, char *ptr, int count,
	   CF_INFO *ci, int param2, BOOL bForce, int *pResultCF , void *pDb )
{
	int iErr = -1;
	int len;
	int True_Memcp;

	if ( ( !ptr || count == 0 ) && !bForce ) return 0;
	if ( ptr && count ) {
		debuglog("CF the count is:%d",count);
		len = min( count, pSessionInfo->bSize - pSessionInfo->bLen );
		
		debuglog("CF The Len is:%d",len);
		True_Memcp = memCp( pSessionInfo,ptr,len);

	}

	ci->cArtType = ART_TYPE_HTTP;
	ci->cArtLangMode = pSessionInfo->charsetType;
	debuglog("CF cArtLangMode is %d", ci->cArtLangMode);
	if( uCfDealArticle( pSessionInfo->pTmpB, pSessionInfo->bLen, ci , pDb) ) {
		*pResultCF = ci->value;
	}
	else *pResultCF = CF_OK; 

	if ( *pResultCF != CF_WAIT ) { 
		if ( pSessionInfo->bLen > CF_SAVE_WORDS ) {
			int iTmp;

			for ( iTmp = 0 ; iTmp < CF_SAVE_WORDS ; iTmp ++ ) {
				*(pSessionInfo->pTmpB + iTmp) = 
					*(pSessionInfo->pTmpB +
					pSessionInfo->bLen - CF_SAVE_WORDS + 
					iTmp + 1);
				}
			
			pSessionInfo->bLen = CF_SAVE_WORDS - 1; 
			}
		};

	iErr = 0;
	return iErr;
}


 void cfZeroMemory( void *Destination, unsigned long Length)
	 // the first paramter is address of block to fill with zeros   
	 // the second is size, in bytes, 
{
	memset( Destination, '\0', Length );
}



 static void sTrim( char *buf )
{
	char *p = buf;
	int len;

	if ( !buf ) return;
	while ( ( len = strlen( p ) ) ) {
		if ( !isspace( p[len - 1] ) ) break;
		p[len - 1] = 0;
	}
	while ( strlen( p ) ) {
		if ( !isspace( *p ) ) break;
		p ++;
	}
	strcpy( buf, p );
	return;
}

 extern  "C"  int  initCF(  QY_CF_STRUCT  *  pCS  )
{
	int  iErr  =  -1;

	debugLog(  "initCF( ) enters."  );
	
	memset( &gBuf, 0, sizeof( gBuf ) );
	//init CF_CFG_STRUCT
	if  (  sizeof(  gBuf.cfg.var.cCS.cfDictDir  )  <=  strlen(  pCS->pDictDir  )  )  {
		debugLog(  "cfDictDir is too small."  );
		goto  errLabel;
	}
	strcpy( gBuf.cfg.var.cCS.cfDictDir, pCS->pDictDir );
 	
	//init gBuf
	gBuf.cfg.sysLogFlg = 1;
	gBuf.cfDictCnt = 1;
	gBuf.shmAddr = ( char * )pCS->pSharedDataBuf->data;
	gBuf.shmSize = pCS->pSharedDataBuf->len;

	// memset( &sI, 0, sizeof( sI ) );
	// if ( initDoCF( &sI ) ) {
	// 	debuglog( "initDoCF( ) error!" );
	// 	goto errLabel;
	// }

	if ( cfCfgServRun( pCS, &gBuf ) ) {
		debuglog( "cfCfgServRun( ) error!");
		goto errLabel;
	}

	iErr = 0;

errLabel:

	debugLog( "initCF( ) leaves." );
  
	return iErr;

}

  extern "C" void exitCF()
{
	// exitDoCF( &sI );
}

/*
 int awmNHDoCF( char *ptr , int count , void *p )
{
	return doCF( &gBuf , &sI , ptr , count , &ci , 0 , 0 , &pResultCF , p);
}
*/

 /*
 int awmNHDoCFWithFile(	char *pFileName , void *p )
{
	FILE *fp = NULL;
	char buf[2048];
	int	 i = 0;

	ptr = buf;
	cfZeroMemory( ptr, 2048);
	debuglog( "File name is %s" , pFileName );
	fp = fopen( pFileName , "r");
	if (!fp ) {
		debuglog("CF cant find dest file ");
		return -1;
	}
	while ( !feof( fp ) ){

		count = fread( ptr , 1, sizeof(buf) , fp );
		
		if ( ferror( fp ) ) {
			debuglog("CF read file content error");
			fclose( fp );
			return -1;
		};
		debuglog("ptr is %s count is %d" , ptr , count);
		if ( awmNHDoCF(ptr , count , p) ){
			debuglog( "awmNHDoCF error" );
			fclose(fp);
			return -1;
		}
	}
	fclose(fp);

	return 0;

}
*/

