
#ifndef __CONTENTFILTERFUNC_H__
#define __CONTENTFILTERFUNC_H__	/* { */
	
extern int getCFDicts( QY_CF_GBUF_STRUCT *pGBuf );
extern void showCFDict( CF_DICT *pCFDict );
extern void showCFDicts( CF_DICT *pCFDict[], int cfDictCnt );
extern int getCharsetType( char *p );
int getPhrase( FILE *fp, char *buf, unsigned int len ,int *lang , int *level);
#ifndef __WITH_9C__
 int setupCFDicts( char *dictCfgFile, CF_DICT *pCFDict[] );
#else 
 int setupCFDicts( QY_CF_STRUCT *pCS, CF_DICT *pCFDict[] );
#endif


int setCFDicts( QY_CF_GBUF_STRUCT *p );



void cfZeroMemory( void *dst, unsigned long len );
int memCp( SESSION_INFO *pSessionInfo , char *ptr , int count);
extern int getContentType ( char *p );

//  int  intFromHex(  char  *  pChars1  );

extern int urlDecode( unsigned char *pEncoded , int countEncoded , 
			unsigned char *pDecoded , int *countDecoded);
#ifdef __DEBUG__
 extern void testCF( );
#endif



#endif /* } */

