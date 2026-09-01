#ifndef _KEYVALUE_H
#define _KEYVALUE_H

#include <stdlib.h>

#if  0
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

//#include <strings.h>
#include <stdio.h>
//#include </usr/include/linux/types.h>
//#include <dirent.h>
#include "vardefine.h"
//#include "cfCommon.h"


#define MAX_COMMAND_LEN 1024
/*program application*/

#define HASH_LEN	65535+1
#define INDEX_LEN	65535+1
#define INDEX_UNIT_LEN 64//__64
#define INDEX_KEY_LEN	40


//read from head struct
#define HEAD_ONE_LEN 73
#define HEAD_TWO_LEN 116
#define LEN_HEAD	(HEAD_ONE_LEN+HEAD_TWO_LEN)

// 以下移至qyCfPubli.h中
//		#define OFF_ART_TYPE 		55//protocol type 1byte
//		// #define ART_TYPE_HTTP	0
//		#define ART_TYPE_UNKNOWN	99	// Modified by ywm on 2002/08/04
//		#define ART_TYPE_SMTP		1
//		#define ART_TYPE_POP3		2
//		#define ART_TYPE_FTP		3
//		#define ART_TYPE_HTTP		4	// Modified by ywm on 2002/08/04

#define OFF_ART_STRICT		56//whether strict 1byte
#define ART_STRICT_EMAIL	2//email strict
#define ART_STRICT_KEY		4//keyword strict
#define OFF_ART_LANGMODE 	68/*language mode 1byte*/

#define OFF_USER_ID		(HEAD_ONE_LEN+35)//email user account 16byte
#define OFF_USER_PASSWD (HEAD_ONE_LEN+53)//email user passwd 16byte
#define OFF_FROM_ADDR 	(HEAD_ONE_LEN+77)//email from 2byte
#define OFF_FROM_LEN 	(HEAD_ONE_LEN+79)//email from  length 2byte
#define OFF_TO_ADDR		(HEAD_ONE_LEN+81)//email to 2byte
#define OFF_TO_LEN		(HEAD_ONE_LEN+83)//email to length 2byte


//read from tail
#define OFF_BLOCK_NUM		(HEAD_ONE_LEN+90)//string finded number 4byte
#define OFF_BLOCK_STRUCT	(HEAD_ONE_LEN+94)//string finded struct one 4byte
#define LEN_TAIL_STRUCT		60//length of string fined struct
#define OFF_STRING_AVAIL	2//wether the string can be finded 2byte
#define OFF_STRING_OFFSET	40//string finded offset in block 4byte
#define OFF_STRING_LEN		44//length of string finded in block 4byte
#define OFF_LANGUAGE		48//block language mode 1byte

//write to articl head struct
#define OFF_ART_DIRECTION 	58//offset article direction 10byte
#define LEN_ART_DIRECTION	10
#define OFF_ART_VALUE 		69//offset article value 4byte
#define LEN_ART_VALUE		4
#define OFF_KEY_NUM			(HEAD_ONE_LEN+98)//key word number 4byte
#define LEN_KEY_NUM			4
#define OFF_KEY_STRUCT		(HEAD_ONE_LEN+102)//key tail start offset 4byte

//write to tail
#define LEN_KEY_STRUCT		113
#define OFF_RESIDE_BLOCK	0//the articl block number include this key 4byte
#define OFF_KEY_ADDR		4//offset key address at articl block 4byte
#define OFF_KEY_LEN			8//offset key len  (4byte)
#define OFF_KEY_NOTE		12//offset key note
#define LEN_OFF_KEY_STRUCT	4


//KEY Hash
typedef  struct  HashUnit	{
				 char					pcKey[SET_KEY_KEYLEN  +  1];		//  输入
				 char					pcDir[SET_KEY_DIRLEN  +  1];		//  不用
				 __u8					cLanguage;							//  输入
				 __u8					cKeyLen;							//  输入
				 __s16					iKeyValue;							//  输出
				 __s32					lTypeInfo;							//  输入
				 struct HashUnit *		pstNextUnit;
}		 HashUnit;

//EMAIL HASH
typedef struct EmailUnit{
	char pcEmail[SET_KEY_EMAILLEN+1];
	char pcDir[SET_KEY_USRLEN+1];
	__u8 cEmailLen;
	__s16 iEmailValue;
	struct EmailUnit *pstNextUnit;
}EmailUnit;

typedef struct KeyHashHead{
	__u64 dwLenIndex;
	struct HashUnit *pstNextUnit;
}KeyHashHead;

typedef struct EmailHashHead{
	__u64 dwLenIndex;
	struct EmailUnit *pstNextUnit;
}EmailHashHead;

void InitKeyHash();
void ClearKeyHash();
void InitEmailHash();
void ClearEmailHash();

void InsertKey(char* pcSentence);		/*insert key to hashtable*/
void InsertEmail(char* pcSentence);		/*insert Email to hashtable*/

int SearchKey( __u8 cLangMode,char *pcDest,int iStrLen,__s16 *iValue,char *pcDirection);
int SearchEmail(char *pcDest,int iStrLen,__s16 *iValue,char *pcDirection);

__s16 EvalBlock(__u8 cLangMode,char *pcBlock,__u32 dwBlockLen);
__u32 DealArticl(int ifd,char *pcFileBuf,__u32 dwFileLen);


/*
struct KeyHashHead KeyHash[HASH_LEN];
__u64 KeyIndex[INDEX_LEN];
*/
//struct EmailHashHead EmailHash[HASH_LEN];
//__u64 EmailIndex[INDEX_LEN];

#endif
