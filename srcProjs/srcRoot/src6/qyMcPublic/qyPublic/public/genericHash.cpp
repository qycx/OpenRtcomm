
#include	"stdafx.h"

#include	"qyPrecomp.h"

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<assert.h>

#include	<windows.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"commondefs.h"
#include	"qyCommon\\commonfunc.h"
#include	<tchar.h>
#include	"qySyncCommProc.h"
#include	"genericHash.h"

#ifndef  __NOTSUPPORT_showInfo__
	#include	"qyCommon.h"
	#include	"qyCommProc.h"
#else
	#ifndef  CONST_qyShowType_warning
			 #define		qyShowInfo1(  )
			 #define		qyDisplayLastError(  )
			 #define		traceLog(  )
	#endif
#endif


//  hashsep.c
#define   MinTableSize	10

struct  ListNode
{
	HashTblElementType			element;
	LP_listNode					Next;
};

typedef  struct  __list_t				{			
				 LP_listNode			pFirst;
				 unsigned  int			cnt;
}										List;

struct  HashTbl							{
		int								TableSize;
		int								maxiTotal;		//  2014/05/27
		//
		PF_hash							pf_hash;
		//
		PF_hashTblElementType_bSame		pf_bSame;
		PF_hashTblElementType_copy		pf_copy;
		PF_hashTblElementType_free		pf_free;

		//
		List						*	TheLists;
		
		//  2014/05/27
		int								nTotal;
};
//  assume N  >=  10
static  int  NextPrime(  int  N  )
{
	int  i;
	if  (  N  %  2  ==  0  )
		N  ++;
	for  (  ;  ;  N  +=  2  )  
	{
		for  (  i  =  3;  i  *  i  <=  N;  i  +=  2  )  
			if  (  N  %  i  ==  0  )  
				goto    ContOuter;
		return  N;
ContOuter:
		;
	}
}

//  Hash function for ints
unsigned  int  tmpHash(  HashTbl  *  pHashTbl,  HashTblElementType  *  pKey  )	
{
	unsigned  int  uiHash  =  0;
	uiHash  =  pKey->iKeyVal;
	if  (  pHashTbl->pf_hash  )  {
		uiHash  =  pHashTbl->pf_hash(  pKey  );
	}

	return  uiHash  %  pHashTbl->TableSize;
}

__declspec(  dllexport  )  LP_hashTbl  newHashTbl(  int  TableSize,  int  maxiTotal,  PF_hash  pf_hash,  PF_hashTblElementType_bSame  pf_bSame,  PF_hashTblElementType_copy  pf_copy,  PF_hashTblElementType_free  pf_free  )
{
	int			iErr  =  -1;
	LP_hashTbl  H  =  NULL;
	int  size;
	int  i;

	if  (  TableSize  <  MinTableSize  )
	{		
		return  NULL;
	}
	size  =  sizeof(  struct  HashTbl  );
	H  =  (  LP_hashTbl  )mymalloc(  size  );
	if  (  H  ==  NULL  )  goto  errLabel;
	memset(  H,  0,  size  );
	
	H->TableSize  =  NextPrime(  TableSize  );
	H->maxiTotal  =  maxiTotal;
	//
	size  =  sizeof(  List  )  *  H->TableSize;
	H->TheLists  =  (  List  *  )mymalloc(  size  );
	if  (  !H->TheLists  )  goto  errLabel;
	memset(  H->TheLists,  0,  size  );

	//
	H->pf_hash  =  pf_hash;
	H->pf_bSame  =  pf_bSame;
	H->pf_copy  =  pf_copy;
	H->pf_free  =  pf_free;

	//
#if  0
	for  (  i  =  0;  i  <  H->TableSize;  i  ++  )  {
		 size  =  sizeof(  struct  ListNode  );
		 H->TheLists[i].pFirst  =  (  List  *  )mymalloc(  size  );
		 if  (  H->TheLists[i]  ==  NULL  )  goto  errLabel;
		 memset(  H->TheLists[i],  0,  size  );
	}
#endif

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		freeHashTbl(  (  void  **  )&H  );
	}
	return  iErr  ?  NULL  :  H;
}




__declspec(  dllexport  )   void  freeHashTbl  (  void  **  ppHashTable  )
{
	int  i;

	if  (  !ppHashTable  )  return;
	LP_hashTbl  H  =  (  LP_hashTbl  )*ppHashTable;
	if  (  !H  )  return;

	if  (  H->TheLists  )  {
		for  (  i  =  0;  i  <  H->TableSize;  i   ++  )  {
			LP_listNode  P  =  H->TheLists[i].pFirst;
			LP_listNode  Tmp;
			while  (  P  !=  NULL  )  {
					Tmp  =  P->Next;
					//
					if  (  H->pf_free  )  {
						H->pf_free(  &P->element  );						
					}
					free(  P  );
					//
					P  =  Tmp;
			}
		}
		free(  H->TheLists  );
	}
	free(  H  );

}



//  uiHashIndex_i为-1时，用pKey来决定hashIndex
__declspec(  dllexport  )  int  hashTbl_findEx(  LP_hashTbl  H,  unsigned  int  uiHashIndex_i,  HashTblElementType  *  pKey,  unsigned  int  *  puiHashIndex,  HashTblElementType  *  pElem_o  )
{
	int			iErr	=	-1;

	if  (  !H  ||  !pKey  )  return  -1;

	unsigned  int  uiHashIndex  =  0;
	
	if  (  uiHashIndex_i  ==  -1  )  {
		uiHashIndex  =  tmpHash(  H,  pKey  );
		}
	else  {
		  uiHashIndex  =  uiHashIndex_i;
	}
	if  (  uiHashIndex  >=  H->TableSize  )  goto  errLabel;


	//
	LP_listNode		P	=	NULL;
	List		*  pL  =  NULL;
	pL  =  &H->TheLists[uiHashIndex];
	P  =  pL->pFirst;

	while  (  P  !=  NULL  )  {
		   if  (  H->pf_bSame  )  {
			   if  (  H->pf_bSame(  pKey,  &P->element  )  )  break;
			   }
		   else  {  
			     if  (  P->element.iKeyVal  ==  pKey->iKeyVal  )  break;
		   }
		   P  =  P->Next;
	}
	if  (  !P  )  goto  errLabel;

	//
	if  (  puiHashIndex  )  *puiHashIndex  =  uiHashIndex;
	//	
	if  (  pElem_o  )  {
			if  (  H->pf_copy  )  {
				if  (  H->pf_copy(  &P->element,  pElem_o  )  )  {
					#ifdef  __DEBUG__
							traceLog(  _T(  "hashTbl_find failed: pf_copy failed"  )  );
					#endif
					goto  errLabel;
				}
				}
			else  {
				  pElem_o->iKeyVal  =  P->element.iKeyVal;
			}	
	}
	

	iErr  =  0;

errLabel:

	//
	return  iErr;
}


 __declspec(  dllexport  )  int  hashTbl_find(  LP_hashTbl  H,  HashTblElementType  *  pKey,  unsigned  int  *  puiHashIndex,  HashTblElementType  *  pElem_o  )
{
	return  hashTbl_findEx(  H,  -1,  pKey,  puiHashIndex,  pElem_o  );
}


__declspec(  dllexport  )  int  hashTbl_insert(  HashTblElementType  *  pKey,  unsigned  int  *  puiHashIndex,  LP_hashTbl  H  )
{
	int					iErr  =  -1;
	LP_listNode			NewCell  =  NULL;
	List			*	pL;
	int					size;
	unsigned  int		uiHashIndex  =  0;

	//  2015/01/14
	if  (  !H  )  return  -1;

	//
	if  (  hashTbl_find(  H,  pKey,  &uiHashIndex,  NULL  )  )  {
		
		//  2014/05/27
		if  (  H->nTotal  >=  H->maxiTotal  )  {
			qyShowInfo_internal(  NULL,  CONST_qyShowType_warning,  0,  "",  _T(  ""  ),  NULL,  NULL,  _T(  ""  ),  _T(  "hashTbl_insert failed: tbl is full"  )  );
			goto  errLabel;
		}

		//
		size  =  sizeof(  struct  ListNode  );
		NewCell  =  (  LP_listNode  )mymalloc(  size  );
		if  (  NewCell  ==  NULL  )  goto  errLabel;
		memset(  NewCell,  0,  size  );
					
		uiHashIndex  =  tmpHash(  H,  pKey  );
		pL  =  &H->TheLists[uiHashIndex];		
		NewCell->Next  =  pL->pFirst;
		if  (  H->pf_copy  )  {
			if  (  H->pf_copy(  pKey,  &NewCell->element  )  )  {
				#ifdef  __DEBUG__
						traceLog(  _T(  "hashTbl_insert failed: pf_copy failed"  )  );
				#endif
				goto  errLabel;
			}
			}
		else  {
			  NewCell->element  =  *pKey;
		}
		pL->pFirst  =  NewCell;
		pL->cnt  ++  ;
		//  2014/05/27
		H->nTotal  ++  ;
	}

	//
	if  (  puiHashIndex  )  *puiHashIndex  =  uiHashIndex;

	//
	iErr  =  0;
errLabel:
	if  (  iErr   )  {
		if  (  NewCell  )  free(  NewCell  );
	}
	return  iErr;
}


 __declspec(  dllexport  )  int  hashTbl_traverse(  LP_hashTbl  H,  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  )
{
	int					iErr		=	-1;
	int					i;
	int					tmpiRet		=	-1;

	if  (  !pf_visit  )  return  -1;

	if  (  H->TheLists  )  {
		for  (  i  =  0;  i  <  H->TableSize;  i   ++  )  {
			LP_listNode  P  =  H->TheLists[i].pFirst;
			LP_listNode  Tmp;
			while  (  P  !=  NULL  )  {
					Tmp  =  P->Next;
					//
					tmpiRet  =  pf_visit(  p0,  p1,  &P->element  );
					if  (  tmpiRet  )  {
						iErr  =  tmpiRet;  goto  errLabel;
					}
					//
					P  =  Tmp;
			}
		}
	}

	iErr  =  0;
errLabel:
	return  iErr;

}

 //  2014/05/27
 __declspec(  dllexport  )  int  hashTbl_getInfo(  LP_hashTbl  H,  int  *  pMaxiTotal,  int  *  piTotal  )
{
	 if  (  !H  )  return  -1;
	 if  (  !H->TheLists  )  return  -1;
	 
	 if  (  pMaxiTotal  )  *pMaxiTotal  =  H->maxiTotal;
	 if  (  piTotal  ) *piTotal  =  H->nTotal;

	 return  0;
 }


//Note:把单位部门个人，变成 key 存入. 同时要记录老的itemId. 如果修改时，需要将原来的ite修改或者移除。


// 对unicode,可以先转成utf8。然后调用this func
__declspec(  dllexport  )  unsigned  int  BKDRHash(  unsigned  char  *  str  )
{
	unsigned  int  seed  =  131;
	unsigned  int  hash  =  0;
	while  (  *str  )  {
		   hash  =  hash  *  seed  +  (  *str  ++  );
	}
	return  (  hash  &  0x7fffffff  );
}


#ifdef  __DEBUG__
//
int  test1(  )
{
	unsigned  int  ui  =  0;
	char  buf[128];
	unsigned  char  *  s  =  (  unsigned  char  *  )buf;
	*s  =  -1;
	ui  =  ui  +  (  *s  );

	return 0 ;
}

int  tmpHandler_printHashElem(  void  *  p0,  void  *  p1,  HashTblElementType  *  p  )
{
	traceLog(  _T(  "iKeyVal %d"  ),  p->iKeyVal  );
	return  0;
}

__declspec(  dllexport  )  int testHashMain(  )
{
	test1(  );

	LP_hashTbl  h  =  NULL;
	h  =  newHashTbl(  100,  100  *  10,  NULL,  NULL,  NULL,  NULL  );
	if  (  !h  )  goto  errLabel;
	
	//malloc(  1  );

	HashTblElementType  e;
	e.iKeyVal  =  123;
	hashTbl_insert(  &e,  NULL,  h  );
	e.iKeyVal  =  223;
	hashTbl_insert(  &e,  NULL,  h  );
	e.iKeyVal  =  323;
	hashTbl_insert(  &e,  NULL,  h  );
e.iKeyVal  =  1123;
	hashTbl_insert(  &e,  NULL,  h  );
e.iKeyVal  =  13;
	hashTbl_insert(  &e,  NULL,  h  );

	e.iKeyVal  =  1123;
	int			tmpiRet;
	tmpiRet    =  hashTbl_find(  h,  &e,  NULL,  NULL  );

	tmpiRet  =  hashTbl_traverse(  h,  (  PF_commonHandler  )tmpHandler_printHashElem,  0,  0  );


errLabel:
		if  ( h   )  freeHashTbl(  (  void  **  )&h  );
	return 0;
}

#endif


