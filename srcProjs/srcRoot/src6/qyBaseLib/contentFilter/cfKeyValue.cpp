
// #include "stdafx.h"

#include <windows.h>
#include <ctype.h>
#include "cfCommon.h"
#include "cfComm.h"
#include "keyvalue.h"
#include "contentFilter.h"

// #include "awmNhCommon.h"
#include "asrCommon.h"
// #include "awmNhFunc2.h"
#include "cfTemp.h"


int giShmDiff = 0;

int  cfSearchKey(  __u8  cLangMode,  __s32  lTypeInfo,  char  *  pcDest,  int  iStrLen,  __s16  *  iValue,  char  *  pcDirection  );
char  *  getLangStr(  __u8  type  );


// uCfDealArticle( ) 为扫描内容而写。
// 返回值：匹配的词组数。
 extern "C" unsigned int uCfDealArticle( char *pcFileBuf, unsigned int dwFileLen , CF_INFO *pCI , void *pDb )
{
	//  --- Read variable
	__u8	cArtType	=	0,  cArtLangMode  =  0;
	__s32	lTypeInfo	=	0;
	//  --- Write variable
	char	pcDirection[LEN_ART_DIRECTION+1];
	__u32	dwReadLen	=	0;
	int		i			=	0;
	
	// search hash table variable
	char cIsFind =0;
	char *pcBlock=NULL;
	char *pcFind;
	__u64 Index = 1;
	__u64 Shield = 1;
	__s16 iKeyValue = 0;
	unsigned int dwKeyNum = 0;		// 匹配关键字数, 返回值。
	

	debugLog( "uCfDealArticle( ) enters." );
	debuglog( "uCfDealArticle: lang is %s", getLangStr( pCI->cArtLangMode ) );
	//  debuglog( "uCfDealArticle: lang is %s, pcFileBuf is [%s], dwFileLen is %d", getLangStr( pCI->cArtLangMode ), pcFileBuf, dwFileLen );

	if  (  dwFileLen <= 1  )  goto  errLabel;

	cArtType		= pCI->cArtType;
	cArtLangMode	= pCI->cArtLangMode;
	lTypeInfo		= *(  short  *  )pCI->serviceType; 
	dwReadLen		= dwFileLen;

	//if article is HTTP
	if ( cArtType == ART_TYPE_HTTP ) {
		////////////////////////////////////////////////////
		//deal with the string
		///////////////////////////////////////////////////
		// if ( cArtLangMode == 0 ) return dwKeyNum;	// Modified by wxr on 2002/08/11
		if ( cArtLangMode == 0 ) goto errLabel;
		// pcBlock = pcFileBuf+LEN_HEAD;		// Modified by asr.
		pcBlock = pcFileBuf;					// Modified by asr.
		pcFind = pcBlock;
		while ( ( pcFind + 1 ) <= pcBlock + dwReadLen ) { // search len of owning same first word
			if ( ( Index = KeyIndex[*( __u16* )pcFind] ) == 0 ) {//no key include the first word
				pcFind ++;
				continue;
			}
			for ( i = ( INDEX_KEY_LEN - 1 ); i >= 0; i -- ) {
				Shield = 1;
				Shield <<= i;
				if ( ( Index & Shield ) > 0 ) {
					//search the keyword length in index first
					if ( ( pcFind + i + 1 ) > ( pcBlock + dwReadLen ) ) //include the first keyword overstep block limit
						break;
					if ( cfSearchKey( cArtLangMode, lTypeInfo, pcFind, i + 1, &iKeyValue, pcDirection ) == 0 ) {
						//the key is in hash table
						// dwValueAdd+=iKeyValue;
						dwKeyNum ++;
						pCI->pKey = pcFind; 
						pCI->keyLen = i + 1;
						pcFind = pcFind + i + 1;
						pCI->value = ( short )iKeyValue;

						cIsFind = 1;

						{ 
							char		buf777[256];
							char  *		tmppContext		=	pCI->pKey;
							int			n				=	CONTEXT_N_LEFT;
							
							while  (  tmppContext  >  pcFileBuf  )  {
								   tmppContext  --  ;
								   if  (  !__isascii(  *tmppContext  )  )
									   tmppContext --;
							}
							if  (  tmppContext  <  pcFileBuf  )  tmppContext  =  pcFileBuf;
							
							pCI->pContext  =  tmppContext;
							pCI->contextLen  =  min( QY_CF_MAX_CONTEXT_LEN, pcFileBuf + dwFileLen - pCI->pContext );
							pCI->pOpInfo  =  &gpCFDict[0]->opInfos[iKeyValue];

							memcpy( buf777, pCI->pKey, pCI->keyLen );
							buf777[pCI->keyLen] = 0;
							traceLogA( "matched: pcKey is [%s], op is [%c].", buf777, ( char )iKeyValue );


						}

						break;
					}
				}
			}
			if ( !cIsFind ) {
				//if no  key  that start two byte in hash table
				pcFind ++;
				continue;
			}
			if ( pCI->pfCallback && pCI->pfCallback( pCI, 0 ) ) break;

			cIsFind = 0;
			continue;
			
		} /*while end*/

		// return dwKeyNum;		// Modified by wxr on 2002/08/11
		goto errLabel;

	}

errLabel:

	debugLog( "uCfDealArticle( ) leaves." );

	return dwKeyNum;

}

//  uCfDealAddr( ) 为扫描地址而写。
//				   servieType两位				
//  返回值：匹配的词组数。

 extern "C" unsigned int uCfDealAddr( char * serviceType, char *pcAddrBuf, unsigned int dwAddrLen, CF_INFO *pCI , void *pDb )
{
	//  Read variable
	__u8			cArtType									=		0;
	__u8			cArtLangMode								=		0;
	//  Write variable
	char			pcDirection[LEN_ART_DIRECTION  +  1];
	__u32			dwReadLen									=		0;
	int				i											=		0;
	//  search hash table variable
	char			cIsFind										=		0;
	char		*	pcBlock										=		NULL;
	char		*	pcFind;
	__u64			Index										=		1;
	__u64			Shield										=		1;
	__s16			iKeyValue									=		0;
	unsigned  int	dwKeyNum									=		0;
	//  dwKeyNum is 匹配的词组数，本函数返回值
	
	traceLogA(  "uCfDealAddr: lang is [%s]",  getLangStr(  pCI->cArtLangMode  )  );
	if  (  dwAddrLen  <=  1  )  goto  errLabel;

	cArtType			=			pCI->cArtType;
	cArtLangMode		=			pCI->cArtLangMode;
	dwReadLen			=			dwAddrLen;

	//  if article is HTTP
	if  (  cArtType  ==  ART_TYPE_HTTP  )  {
		////////////////////////////////////////////////////
		//  deal with the string
		///////////////////////////////////////////////////
		if  ( cArtLangMode  ==  0  )  goto  errLabel;
		//  pcBlock  =  pcFileBuf + LEN_HEAD;	// Modified by asr.
		pcBlock		=	pcAddrBuf;				// Modified by asr.
		pcFind		=	pcBlock;
		while ( ( pcFind + 1 ) <= pcBlock + dwReadLen ) { // search len of owning same first word
			if ( ( Index = KeyIndex[*( __u16 * )pcFind] ) == 0 ) { // no key include the first word
				// pcFind ++;
				// continue;
				break;	// Modified on 2002/08/04, 
			}
			for ( i = ( INDEX_KEY_LEN - 1 ); i >= 0; i -- ) {
				Shield = 1;
				Shield <<= i;
				if ( ( Index & Shield ) > 0 ){
					// search the keyword length in index first
					if ( ( pcFind + i + 1 ) > ( pcBlock + dwReadLen ) )	//include the first keyword overstep block limit
						break;
					if ( cfSearchKey( cArtLangMode, *(__s16  *  )serviceType,  pcFind, i + 1, &iKeyValue, pcDirection ) == 0 ) {
						// the key is in hash table
						// dwValueAdd += iKeyValue;
						dwKeyNum ++;
						pCI->pKey = pcFind; 
						pCI->keyLen = i + 1;
						pcFind = pcFind + i + 1;
						pCI->value = ( short )iKeyValue;
						
						cIsFind = 1;
						{ 	
							char buf777[256];
						
							pCI->pOpInfo  =  &gpCFDict[0]->opInfos[iKeyValue];

							memcpy( buf777, pCI->pKey, pCI->keyLen );
							buf777[pCI->keyLen] = 0;
							debuglog( "matched: iKeyValue is [%d] pcKey is [%s], op is [%c].", iKeyValue, buf777, ( char )iKeyValue );
						}
						
						break;
					}
				}
			}	// end of for( ; ; )
		
			break;

		} /*while end*/
		
		goto  errLabel;

	}

	// 其他类型的一律认为未匹配。


errLabel:

	traceLogA(  "uCfDealAddr ..  leaves."  );
	
	return dwKeyNum;

}


 void  showDict( )
{
	int  i;

	traceLogA(  "CF showDict Starts ---"  );
	traceLogA(  "CF space available is %d",  getCFDictAvailable(  gpCFDict[0]  )  );
	traceLogA(  "CF Dict count is:  %d",  HASH_LEN  );
	for  (  i  =  0;  i  <  HASH_LEN;  i  ++  )  showKeyHashHead(  &KeyHash[i]  );
	traceLogA(  "CF showDict ends ---"  );
	
}

 void showKeyHashHead( KeyHashHead *p )
{
	HashUnit  *  pHU;
	
	//	pHU = ( char * )p->pstNextUnit; 
	pHU  =  (  HashUnit  *  )p->pstNextUnit; 

	while  (  pHU  )  {
		   pHU = ( HashUnit * )( ( char * )pHU + giShmDiff );
		   showHashUnit(  pHU  );
		   pHU = ( HashUnit * )pHU->pstNextUnit;
	}
	
}

 //  显示langMode
 char  *  getLangStr(  __u8  type  )
{
	 switch  (  type  )  {
			 case  CS_LANGUAGE:
				   return  "Language";
			 case  CS_URL:
				   return  "Url";
			 default:
				 break;
	 }

	 return  "\"Unknown or error langMode type!\"";

}

 //  显示language
 char  *  getLangTypeStr(  long  type  )
{
	 switch  (  type  )  {
			 case  CS_LANGTYPE_GB:
				   return  "GB";
			 case  CS_LANGTYPE_BIG5:
				   return  "BIG5";
			 case  CS_LANGTYPE_EN:
				   return "EN";
			 case CS_LANGTYPE_UNKNOWN:
			 default:
					break;
	 }

	 return  "\"Unknown or error language type!\"";
}
 

 void  showHashUnit(  HashUnit  *  p  )
{
	char	*	qimServiceTypeStr(  char  *  );
	char		serviceType[3];
	char		keyTypeName[CONST_qyCfKeyTypeNameLen  +  1];
			
	memcpy(  serviceType,  &p->lTypeInfo,  2  );
	serviceType[2]  =  0;
	safeStrnCpy(  gpCFDict[0]->opInfos[p->iKeyValue].keyTypeName,  keyTypeName,  sizeof(  keyTypeName  )  );
	traceLogA(  "keyTypeCode [%02x]. keyTypeName [%8s]. serviceType [%s]. langMode [%s]. CF pcKey [%s].",  
					(  unsigned  char  )p->iKeyValue,  
						keyTypeName,
							qimServiceTypeStr(  serviceType  ),  
								getLangStr(  p->cLanguage  ),
									p->pcKey  );

	return;

}


 void *  cfMalloc(  size_t  size  )
{
	char *  p;

	if  (  getCFDictAvailable(  gpCFDict[0]  )  <  ( int )size  +  MIN_DICT_AVAILABLE  ) 
		return NULL;

	p  =  gpCFDict[0]->pEnd;
	gpCFDict[0]->pEnd  +=  size;

	return  p;

}

 void cfFree(  void  *  p  )
{
	gpCFDict[0]->pEnd  =  (  char  *  )p;
}


//  Insert the key of sentence to HashTable
//  this pcSentence parameter string include key,direction,language,value
//  this string length is SET_KEY_LENGTH
//  #define		SET_KEY_LENGTH	(  SET_KEY_KEYLEN  +  SET_KEY_DIRLEN  +  SET_KEY_LANGLEN  +  SET_KEY_VALLEN  +  SET_KEY_TYPEINFOLEN  )

 void  cfInsertKey(  char  *  pcSentence  )
{
	__u16 HashKey = 0;
	__u64 Index = 0;
	char *pcStart = NULL;
	struct HashUnit *pstInsert = NULL;
	struct HashUnit *pstBefore = NULL;

	struct HashUnit *pstUnit =(HashUnit *) cfMalloc(sizeof(HashUnit));
	memset(pstUnit,0,sizeof(HashUnit));
	//  get key string
	memcpy(pstUnit->pcKey,pcSentence,SET_KEY_KEYLEN);
	pstUnit->pcKey[SET_KEY_KEYLEN] = 0;
	//  get key dir string
	memcpy(pstUnit->pcDir,pcSentence+SET_KEY_KEYLEN,SET_KEY_DIRLEN);
	pstUnit->pcDir[SET_KEY_DIRLEN]=0;
	//  get key length
	pstUnit->cKeyLen = strlen(pstUnit->pcKey);
	//  get language
	pstUnit->cLanguage = *(__u8*)(pcSentence+SET_KEY_KEYLEN+SET_KEY_DIRLEN);
	//  get value of keyword
	pstUnit->iKeyValue = *(__s16*)(pcSentence+SET_KEY_KEYLEN+SET_KEY_DIRLEN+SET_KEY_LANGLEN);
	//  get type info of keyword
	pstUnit->lTypeInfo = *(  __s32  *  )( pcSentence +  SET_KEY_KEYLEN  +  SET_KEY_DIRLEN  +  SET_KEY_LANGLEN  +  SET_KEY_VALLEN  );

	/*Insert the first word of Key sentence to Index*/
	Index = 1;
	Index <<= (pstUnit->cKeyLen-1);
	KeyIndex[*(__u16*)(pstUnit->pcKey)] |= Index;
	//get Hash key
	pcStart = pstUnit->pcKey;
	while(*pcStart!=0)
		HashKey  = (HashKey<<3) + HashKey + *pcStart++;

	//get inserted unit of keyword
	KeyHash[HashKey].dwLenIndex |= Index;
	pstInsert = KeyHash[HashKey].pstNextUnit;
	if(pstInsert == NULL)
		KeyHash[HashKey].pstNextUnit = pstUnit;
	else  {
		   while  (  (  pstInsert  )  !=  NULL  )  {
				  if  (  pstInsert->cKeyLen  ==  pstUnit->cKeyLen 
					  &&  pstInsert->cLanguage   ==  pstUnit->cLanguage
						&&  pstInsert->lTypeInfo  ==  pstUnit->lTypeInfo  )
				  {
					  if  (  strcmp(  pstInsert->pcKey,  pstUnit->pcKey  )  ==  0  )  {
						  cfFree(  pstUnit  );
						  return;
					  }
				  }
				  pstBefore  =  pstInsert;
				  pstInsert  =  pstInsert->pstNextUnit;
		   }
		   pstBefore->pstNextUnit  =  pstUnit;
	}

	return;

}


 //  get Hash value of key string,return -1 no, 0 right
 //  cLangMode作为大类别用，不表示语言
 int  cfSearchKey(  __u8  cLangMode,  __s32  lTypeInfo,  char  *  pcDest,  int  iStrLen,  __s16  *  iValue,  char  *  pcDirection  )
{
	char  *  pcStart  =  pcDest;
	HashUnit  *  pstNowUnit  =  NULL;
	__u16  Key  =  0;
	__u64  Shield  =  1;

	debugLog(  "cfSearchKey( ) enters."  );

	while  (  pcStart  !=  (  pcDest  +  iStrLen  )  )
		   Key  = (  Key  <<  3  )  +  Key  +  *pcStart++  ;

	if  (  KeyHash[Key].dwLenIndex  ==  0 )	 //  not in index table
		return  -1;

	Shield  <<=  (  iStrLen  -  1  );
	if  (  (  KeyHash[Key].dwLenIndex  &  Shield  )  ==  0  )
		return  -1;

	for  (  pstNowUnit  =  KeyHash[Key].pstNextUnit;  pstNowUnit;  	pstNowUnit  =  pstNowUnit->pstNextUnit  )  {
	
		 pstNowUnit  =  (  HashUnit  *  )(  (  char  *  )pstNowUnit  +  giShmDiff  );
		 //  pstNowUnit = ( HashUnit * )pstNowUnit + giShmDiff;

		 showHashUnit( pstNowUnit );
		 traceLogA( "CF cLangMode is [%s]. iStrLen is %d.", getLangStr( cLangMode ), iStrLen );
		 traceLogA( "CF pstNowUnit->cLanguage is [%s]. pstNowUnit->cKeyLen is %d.", getLangStr( pstNowUnit->cLanguage ), pstNowUnit->cKeyLen );
		 
		 if  (  cLangMode  ==  CS_LANGUAGE  )  {
			 if  (  (  pstNowUnit->cKeyLen  ==  iStrLen  )  )  {
				 if  (  strncmp(  pcDest,  pstNowUnit->pcKey,  iStrLen  )  ==  0  )  {
					 *iValue  =  pstNowUnit->iKeyValue;
					 //  memset(  pcDirection,  0,  LEN_ART_DIRECTION  );
					 memcpy(  pcDirection,  pstNowUnit->pcDir,  LEN_ART_DIRECTION  );
					 return  0;
				 }
			 }
			 continue;
		 }
		 
		 if  (  cLangMode  ==  pstNowUnit->cLanguage  
			 &&   lTypeInfo  ==  pstNowUnit->lTypeInfo  )
		 {
		 	if  (  (  pstNowUnit->cKeyLen  ==  iStrLen  )  )  {
				if  (  strncmp(  pcDest,  pstNowUnit->pcKey,  iStrLen  )  ==  0  )  {
					*iValue  =  pstNowUnit->iKeyValue;
					//  memset(  pcDirection,  0,  LEN_ART_DIRECTION  );
					memcpy(  pcDirection,  pstNowUnit->pcDir,  LEN_ART_DIRECTION  );
					return  0;
				}
			}
		}
		
	}

	return -1;
}

