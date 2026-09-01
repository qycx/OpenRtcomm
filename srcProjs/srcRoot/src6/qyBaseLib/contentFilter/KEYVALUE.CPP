

#include <io.h>
#include <windows.h>

#include "vardefine.h"
#include "cfCommon.h"
#include "keyvalue.h"
#include "contentFilter.h"

#include "keyHash.h"	//Modified by wht 0315


/*Create a array of 65535 to install Hash value*/
void InitKeyHash()
{
	__u32 i = 0;
	/*initial hash table*/
	for(i=0;i<HASH_LEN;i++){
		KeyHash[i].dwLenIndex = 0;
		KeyHash[i].pstNextUnit = NULL;
		KeyIndex[i] = 0;
	}

	return;
}

void ClearKeyHash()
{
	__u32 i = 0;
	struct HashUnit *pstDelEmail;

	for(i=0;i<HASH_LEN;i++){
		pstDelEmail = KeyHash[i].pstNextUnit;
		while(pstDelEmail!=NULL){
			KeyHash[i].pstNextUnit = pstDelEmail->pstNextUnit;
			free(pstDelEmail);
			pstDelEmail = KeyHash[i].pstNextUnit;
		}
	}
	for(i=0;i<HASH_LEN;i++)
		KeyIndex[i] = 0;
	return;
}

void InitEmailHash()
{
	__u32 i = 0;

	for(i=0;i<HASH_LEN;i++){
		EmailHash[i].dwLenIndex = 0;
		EmailHash[i].pstNextUnit = NULL;
		EmailIndex[i] = 0;
	}
	return;
}


void ClearEmailHash()
{
	struct EmailUnit *pstDelEmail;
	__u32 i = 0;

	for(i=0;i<HASH_LEN;i++){
		pstDelEmail = EmailHash[i].pstNextUnit;
		while(pstDelEmail!=NULL){
			EmailHash[i].pstNextUnit = pstDelEmail->pstNextUnit;
			free(pstDelEmail);
			pstDelEmail = EmailHash[i].pstNextUnit;
		}
	}
	for(i=0;i<HASH_LEN;i++)
		EmailIndex[i] = 0;

	return;
}

//Insert the key of sentence to HashTable
//this pcSentence parameter string include key,direction,language,value
//this string length is 40+20+1+2
void InsertKey(char *pcSentence)
{
	__u16 HashKey = 0;
	__u64 Index = 0;
	char *pcStart = NULL;
	struct HashUnit *pstInsert = NULL;
	struct HashUnit *pstBefore = NULL;

	struct HashUnit *pstUnit = (HashUnit * )malloc(sizeof(HashUnit));
	memset(pstUnit,0,sizeof(HashUnit));
	//get key string
	memcpy(pstUnit->pcKey,pcSentence,SET_KEY_KEYLEN);
	pstUnit->pcKey[SET_KEY_KEYLEN] = 0;
	//get key dir string
	memcpy(pstUnit->pcDir,pcSentence+SET_KEY_KEYLEN,SET_KEY_DIRLEN);
	pstUnit->pcDir[SET_KEY_DIRLEN]=0;
	//get key length
	pstUnit->cKeyLen = strlen(pstUnit->pcKey);
	//get language
	pstUnit->cLanguage = *(__u8*)(pcSentence+SET_KEY_KEYLEN+SET_KEY_DIRLEN);
	//get value of keyword
	pstUnit->iKeyValue = *(__s16*)(pcSentence+SET_KEY_KEYLEN+SET_KEY_DIRLEN+SET_KEY_LANGLEN);


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
	else{
		while((pstInsert) != NULL){
			if(pstInsert->cKeyLen == pstUnit->cKeyLen &&
			   	pstInsert->cLanguage == pstUnit->cLanguage){
				if(strcmp(pstInsert->pcKey,pstUnit->pcKey)==0){
					free(pstUnit);
					return;
				}
			}
			pstBefore = pstInsert;
			pstInsert = pstInsert->pstNextUnit;
		}
		pstBefore->pstNextUnit = pstUnit;
	}
	//free( pstUnit );

	//frank modified here to test if we have mem leak.
	return;
}

void InsertEmail(char *pcSentence)
{
	__u16 HashKey = 0;
	__u64 Index = 1;
	char *pcStart = NULL;
	struct EmailUnit *pstInsert = NULL;
	struct EmailUnit *pstBefore = NULL;

	struct EmailUnit *pstUnit =(EmailUnit *) malloc(sizeof(EmailUnit));
	memset(pstUnit,0,sizeof(HashUnit));
	//get key string
	memcpy(pstUnit->pcEmail,pcSentence,SET_KEY_EMAILLEN);
	pstUnit->pcEmail[SET_KEY_EMAILLEN] = 0;
	//get key dir string
	memcpy(pstUnit->pcDir,pcSentence+SET_KEY_EMAILLEN,SET_KEY_USRLEN);
	pstUnit->pcDir[SET_KEY_USRLEN]=0;
	//get key length
	pstUnit->cEmailLen = strlen(pstUnit->pcEmail);
	//get value of keyword
	pstUnit->iEmailValue = *(__s16*)(pcSentence+SET_KEY_EMAILLEN+SET_KEY_USRLEN);


	//Insert the first word of Key sentence to Index
	Index = 1;
	Index <<= (pstUnit->cEmailLen-1);
	EmailIndex[*(__u16*)(pstUnit->pcEmail)] |=  Index;
	//get Hash key
	pcStart = pstUnit->pcEmail;
	while(*pcStart!=0)
		HashKey  = (HashKey<<3) + HashKey + *pcStart++;

	//get inserted unit of keyword
	EmailHash[HashKey].dwLenIndex |=Index;
	pstInsert = EmailHash[HashKey].pstNextUnit;
	if(pstInsert == NULL)
		EmailHash[HashKey].pstNextUnit = pstUnit;
	else{
		while((pstInsert) != NULL){
			if(pstInsert->cEmailLen == pstUnit->cEmailLen){
				if(strcmp(pstInsert->pcEmail,pstUnit->pcEmail)==0){
					free(pstUnit);
					return;
				}
			}
			pstBefore = pstInsert;
			pstInsert = pstInsert->pstNextUnit;
		}
		pstBefore->pstNextUnit = pstUnit;
	}

	return;
}

/*get Hash value of key string,return -1no,0right*/
int SearchKey(__u8 cLangMode,char *pcDest,int iStrLen,__s16 *iValue,char *pcDirection)
{
	char *pcStart = pcDest;
	HashUnit* pstNowUnit = NULL;
	__u16 Key = 0;
	__u64 Shield = 1;

	while(pcStart != (pcDest+iStrLen))
		Key  = (Key << 3) + Key + *pcStart++;

	if( KeyHash[Key].dwLenIndex == 0)/*not in index table*/
		return -1;

	Shield <<= (iStrLen-1);
	if((KeyHash[Key].dwLenIndex & Shield) == 0)
		return -1;

	pstNowUnit = KeyHash[Key].pstNextUnit;
	while(pstNowUnit!=NULL){
		showHashUnit( pstNowUnit );
		if((pstNowUnit->cKeyLen == iStrLen) && (pstNowUnit->cLanguage == cLangMode)){
			if (strncmp(pcDest,pstNowUnit->pcKey,iStrLen) == 0){
				*iValue=pstNowUnit->iKeyValue;
				memset(pcDirection,0,LEN_ART_DIRECTION);
				memcpy(pcDirection,pstNowUnit->pcDir,LEN_ART_DIRECTION);
				return 0;
			}
		}
		pstNowUnit=pstNowUnit->pstNextUnit;
	}

	return -1;
}

//search email_box
int SearchEmail(char *pcDest,int iStrLen,__s16 *iValue,char *pcDirection)
{
	char *pcStart = pcDest;
	EmailUnit* pstNowUnit = NULL;
	__u16 Key = 0;
	__u64 Shield = 1;

	while(pcStart != (pcDest+iStrLen))
		Key  = (Key << 3) + Key + *pcStart++;

	if(EmailHash[Key].dwLenIndex == 0)/*not in index table*/
		return -1;

	Shield <<= (iStrLen-1);
	if((EmailHash[Key].dwLenIndex & Shield) ==0)
		return -1;

	pstNowUnit  = EmailHash[Key].pstNextUnit;
	while(pstNowUnit!=NULL){
		if(pstNowUnit->cEmailLen == iStrLen){
			if (strncmp(pcDest,pstNowUnit->pcEmail,iStrLen) == 0){
				*iValue=pstNowUnit->iEmailValue;
				memset(pcDirection,0,LEN_ART_DIRECTION);
				memcpy(pcDirection,pstNowUnit->pcDir,LEN_ART_DIRECTION);
				return 0;
			}
		}
		pstNowUnit=pstNowUnit->pstNextUnit;
	}
	return -1;
}

//read the formatted files to deal
__u32 DealArticl(int ifd,char *pcFileBuf,__u32 dwFileLen)
{
	//Read variable
	__u8 cArtType=0,cArtLangMode=0;
	__u16 wFromAddr=0,wFromLen=0,wToAddr=0,wToLen=0;

	__u32 dwBlockNum=0,dwOffFirstBlock=0;
	__u16 wBlockAvail=0;
	__u32 dwStrOffBlock=0,dwBlockLen=0;

	//Write variable
	__u8 cStrictType = 0;
	char pcDirection[LEN_ART_DIRECTION+1];
	char pcTail[LEN_KEY_STRUCT+1];
	__u32 dwArtValue=0;
	__u32 dwReadLen=0;

	int i = 0;
	char *pcFrom=NULL,*pcTo=NULL;

	//search hash table variable
	char cIsFind =0;
	char *pcBlock=NULL;
	char *pcFind;
	__u64 Index = 1;
	__u64 Shield = 1;
	__s16 iKeyValue = 0;
	__s32 dwValueAdd = 0,dwKeyNum = 0;

	int j;



	cStrictType = *(__u8*)(pcFileBuf+OFF_ART_STRICT);
	cArtType = *(__u8*)(pcFileBuf+OFF_ART_TYPE);
	cArtLangMode = *(__u8*)(pcFileBuf+OFF_ART_LANGMODE);

	lseek(ifd,0,SEEK_END);
	lseek(ifd,OFF_KEY_STRUCT,SEEK_SET);
	write(ifd,(char*)&dwFileLen,sizeof(__u32));

	//if article is HTTP
	if(cArtType == ART_TYPE_HTTP){
		////////////////////////////////////////////////////
		//deal with the string
		///////////////////////////////////////////////////
		if(cArtLangMode == 0)
			return dwKeyNum;
		pcBlock = pcFileBuf+LEN_HEAD;
		pcFind = pcBlock;
		while((pcFind+1) <= pcBlock+dwReadLen){// search len of owning same first word
			if((Index = KeyIndex[*(__u16*)pcFind]) == 0){//no key include the first word
				pcFind++;
				continue;
			}
			for(i=(INDEX_KEY_LEN-1);i>=0;i--){
				Shield = 1;
				Shield <<= i;
				if((Index & Shield) > 0){//search the keyword length in index first
					if((pcFind+i+1)>(pcBlock+dwReadLen))//include the first keyword overstep block limit
						break;
					if(SearchKey(cArtLangMode,pcFind,i+1,&iKeyValue,pcDirection)==0){//the key is in hash table
						dwValueAdd+=iKeyValue;
						dwKeyNum++;
						pcFind = pcFind+i+1;
						cIsFind =1;

						//write to file tail
						memset(pcTail,0,LEN_KEY_STRUCT);
						*(__u32*)(pcTail+OFF_KEY_ADDR) = pcFind-pcBlock;
						*(__u32*)(pcTail+OFF_KEY_LEN) = i+1;
						memcpy(pcTail+OFF_KEY_NOTE,pcDirection,SET_KEY_DIRLEN);
						lseek(ifd,0,SEEK_END);
						write(ifd,pcTail,OFF_KEY_LEN);
						break;
					}
				}
			}
			if(!cIsFind)//if no  key  that start two byte in hash table
				pcFind++;
			cIsFind = 0;
		}
/*while end*/
		if(dwKeyNum){
			lseek(ifd,OFF_KEY_NUM,SEEK_SET);//key number
			write(ifd,&dwKeyNum,LEN_KEY_NUM);
			lseek(ifd,OFF_ART_DIRECTION,SEEK_SET);//articl direction
			write(ifd,pcDirection,LEN_ART_DIRECTION);
			dwArtValue = dwValueAdd/dwKeyNum;
			lseek(ifd,OFF_ART_VALUE,SEEK_SET);//articl value
			write(ifd,(char*)&dwArtValue,LEN_ART_VALUE);
			lseek(ifd,OFF_ART_STRICT,SEEK_SET);//articl strict attribute
			cStrictType |= ART_STRICT_KEY;
			write(ifd,(char*)&cStrictType,sizeof(__u8));
		}

		return dwKeyNum;
	}

	//if article is SMTP or POP3
	else if(cArtType == ART_TYPE_SMTP||cArtType == ART_TYPE_POP3){
		//////////////////////////////////////////////////////
		//deal with the from email string
		////////////////////////////////////////////////////
		wFromLen = *(__u16*)(pcFileBuf+OFF_FROM_LEN);//from email_box
		if(wFromLen){
			wFromAddr = *(__u16*)(pcFileBuf+OFF_FROM_ADDR);//OFF_FROM_ADDR
			pcFrom = pcFileBuf+LEN_HEAD+wFromAddr;

			if((Index = EmailIndex[*(__u16*)pcFrom]) != 0){//no key include the first word
				Shield = 1;
				Shield <<= (wFromLen-1);
				if((Index & Shield) != 0){//search the keyword length in index first
					if(SearchEmail(pcFrom,wFromLen,&iKeyValue,pcDirection)==0){//the key is in hash table

						//write to file
						lseek(ifd,OFF_ART_DIRECTION,SEEK_SET);
						write(ifd,pcDirection,LEN_ART_DIRECTION);
						lseek(ifd,OFF_ART_VALUE,SEEK_SET);
						write(ifd,(char*)&iKeyValue,sizeof(__u16));
						lseek(ifd,OFF_ART_STRICT,SEEK_SET);
						cStrictType |= ART_STRICT_EMAIL;
						write(ifd,(char*)&cStrictType,sizeof(__u8));
						dwKeyNum++;

						return dwKeyNum;
					}
				}
			}
		}

		///////////////////////////////////////////////////////
		//deal with the to email string
		////////////////////////////////////////////////////////
		wToLen = *(__u16*)(pcFileBuf+OFF_TO_LEN);//length
		if(wToLen){
			wToAddr = *(__u16*)(pcFileBuf+OFF_TO_ADDR);
			pcTo = pcFileBuf+LEN_HEAD+wToAddr;//to pointer

			pcFind = pcTo;
			cIsFind = 0;
			while((pcFind+1) <= pcTo+wToLen){// search len of owning same first word
				if((Index = EmailIndex[*(__u16*)pcFind]) == 0){//no key include the first word
					pcFind++;
					continue;
				}
				for(i=0;i<INDEX_UNIT_LEN;i++){
					Shield = 1;
					Shield <<= i;
					if((Index & Shield) > 0){//search the keyword length in index first
						if((pcFind+i+1)>(pcTo+wToLen))// keyword length overstep block limit
							break;
						if(SearchEmail(pcFind,i+1,&iKeyValue,pcDirection)==0){//the key is in hash table
							cIsFind = 1;
							dwValueAdd+=iKeyValue;
							dwKeyNum++;
							pcFind = pcFind+i+1;

							//write to file
							lseek(ifd,OFF_ART_DIRECTION,SEEK_SET);
							write(ifd,pcDirection,LEN_ART_DIRECTION);
							lseek(ifd,OFF_ART_VALUE,SEEK_SET);
							write(ifd,(char*)&iKeyValue,sizeof(__u16));
							lseek(ifd,OFF_ART_STRICT,SEEK_SET);
							cStrictType |= ART_STRICT_EMAIL;
							write(ifd,(char*)&cStrictType,sizeof(__u8));

							return dwKeyNum;
						}
					}
				}
				if(!cIsFind)//if no  key  that start two byte in hash table
					pcFind++;
				cIsFind = 0;
			}

		}

		dwBlockNum = *(__u32*)(pcFileBuf+OFF_BLOCK_NUM);//get text block number dwOffFirstBlock
		dwOffFirstBlock = *(__u32*)(pcFileBuf+OFF_BLOCK_STRUCT);//the first block tail struct offset
		for(i=0; ( __u32 )i< dwBlockNum; i++){
			cArtLangMode = *(__u8*)(pcFileBuf+dwOffFirstBlock+i*LEN_TAIL_STRUCT+OFF_LANGUAGE);
			if(cArtLangMode==0)
				continue;
			wBlockAvail = *(__u16*)(pcFileBuf+dwOffFirstBlock+i*LEN_TAIL_STRUCT+OFF_STRING_AVAIL);
			if(!wBlockAvail){//wBlockAvail==0,can be searched
				dwStrOffBlock = *(__u32*)(pcFileBuf+dwOffFirstBlock+i*LEN_TAIL_STRUCT+OFF_STRING_OFFSET);
				dwBlockLen =	*(__u32*)(pcFileBuf+dwOffFirstBlock+i*LEN_TAIL_STRUCT+OFF_STRING_LEN);

				//////////////////////////////////////////////////
				//deal with the text block
				///////////////////////////////////////////////////
				pcBlock = pcFileBuf+dwStrOffBlock;
				pcFind = pcBlock;
				while((pcFind+1) <= (pcBlock+dwBlockLen)){// search len of owning same first word
					if((Index = KeyIndex[*(__u16*)pcFind]) == 0){//no key include the first word
						pcFind++;
						continue;
					}
					for(j=(INDEX_KEY_LEN-1);j>=0;j--){
						Shield = 1;
						Shield <<= j;
						if((Index & Shield) > 0){//search the keyword length in index first
							if((pcFind+j+1)>(pcBlock+dwBlockLen))//include the first keyword overstep block limit
								break;
							if(SearchKey(cArtLangMode,pcFind,j+1,&iKeyValue,pcDirection)==0){//the key is in hash table
								cIsFind = 1;
								dwValueAdd+=iKeyValue;
								dwKeyNum++;
								pcFind = pcFind+j+1;

								//write to file tail
								memset(pcTail,0,LEN_KEY_STRUCT);
								*(__u32*)(pcTail+OFF_KEY_ADDR) = pcFind-pcBlock;
								*(__u32*)(pcTail+OFF_KEY_LEN) = j+1;
								memcpy(pcTail+OFF_KEY_NOTE,pcDirection,SET_KEY_DIRLEN);
								lseek(ifd,0,SEEK_END);
								write(ifd,pcTail,OFF_KEY_LEN);
								break;
							}
						}
					}
					if(!cIsFind)//if no  key  that start two byte in hash table
						pcFind++;
					cIsFind = 0;
				}
			}
		}
		if(dwKeyNum){
			lseek(ifd,OFF_KEY_NUM,SEEK_SET);//key number
			write(ifd,&dwKeyNum,LEN_KEY_NUM);
			lseek(ifd,OFF_ART_DIRECTION,SEEK_SET);//article direction
			write(ifd,pcDirection,LEN_ART_DIRECTION);
			dwArtValue = dwValueAdd/dwKeyNum;
			lseek(ifd,OFF_ART_VALUE,SEEK_SET);//articl value
			write(ifd,(char*)&dwArtValue,LEN_ART_VALUE);
			lseek(ifd,OFF_ART_STRICT,SEEK_SET);//articl strict attribute
			cStrictType |= ART_STRICT_KEY;
			write(ifd,(char*)&cStrictType,sizeof(__u8));
		}
		return dwKeyNum;
	}

	return 0;
}
