

#ifndef  HASHSEP_H_INCLUDE
#define  HASHSEP_H_INCLUDE

typedef  struct						{
				 BOOL				bKeyInt;
				 int				iKeyVal;
				 char			*	pKeyStr;
				 //
				 int				iKeyType;
				 void			*	pData;
				 unsigned  int		uiSize_pData;
}									HashTblElementType;

//typedef  unsigned  int  Index;
struct	ListNode;
typedef  struct  ListNode  *  LP_listNode;	//  Position;
struct  HashTbl;
typedef  struct  HashTbl  *  LP_hashTbl;

//
typedef  unsigned  int  (  *PF_hash  )(  HashTblElementType  *  pKey  );
typedef  BOOL  (  *  PF_hashTblElementType_bSame  )(  HashTblElementType  *  p0,  HashTblElementType  *  p1  );
typedef  int  (  *  PF_hashTblElementType_copy  )(  HashTblElementType  *  pSrc,  HashTblElementType  *  pDst  );
typedef  int  (  *  PF_hashTblElementType_free  )(  HashTblElementType  *  p  );


//
__declspec(  dllexport  )  LP_hashTbl  newHashTbl(  int  TableSize,  int  maxiTotal,  PF_hash  pf_hash,  PF_hashTblElementType_bSame  pf_bSame,  PF_hashTblElementType_copy  pf_copy,  PF_hashTblElementType_free  pf_free  );
__declspec(  dllexport  )  void  freeHashTbl(  void  **  ppHashTable  );

//
__declspec(  dllexport  )  int  hashTbl_findEx(  LP_hashTbl  H,  unsigned  int  uiHashIndex_i,  HashTblElementType  *  pKey,  unsigned  int  *  puiHashIndex,  HashTblElementType  *  pElem_o  );
__declspec(  dllexport  )  int  hashTbl_find(  LP_hashTbl  H,  HashTblElementType  *  pKey,  unsigned  int  *  puiHashIndex,  HashTblElementType  *  pElem_o  );
__declspec(  dllexport  )  int  hashTbl_insert(  HashTblElementType  *  pKey,  unsigned  int  *  puiHashIndex,  LP_hashTbl  H  );
__declspec(  dllexport  )  int  hashTbl_traverse(  LP_hashTbl  H,  PF_commonHandler pf_visit,  void  *  p0,  void  *  p1  );

//
__declspec(  dllexport  )  int  hashTbl_getInfo(  LP_hashTbl  H,  int  *  pMaxiTotal,  int  *  piTotal  );


//
__declspec(  dllexport  )  unsigned  int  BKDRHash(  unsigned  char  *  str  );

//
#ifdef  __DEBUG__
__declspec(  dllexport  )  int testHashMain(  );
#endif






#endif  //  HASHSEP_H_INCLUDED

