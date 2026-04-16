
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myDb.h"

#include	"qyDynLib.h"
#include	"qyCusResTemp.h"
#include	"qmcSharePublic.h"
#include	"funcsForIsCliHelp.h"
#include	"isCliD3dPublic.h"
#include	"imgProcessPublic.h"
#include	"genericHash.h"
#include	"imObjHash.h"




 ///
 unsigned  int  imObj_hash(  HashTblElementType  *  pKey  )
 {
	 if  (  pKey->bKeyInt  )  return  pKey->iKeyVal;
	 //
	 return  BKDRHash(  (  unsigned  char  *  )pKey->pKeyStr  );
 }


BOOL  imObj_hash_bSame(  HashTblElementType  *  p0,  HashTblElementType  *  p1  )
{
	BOOL				bRet	=	FALSE;

	//
	MACRO_qyAssert(  p0->iKeyType,  _T(  "imObj_hash_bSame: keyType can't be 0"  )  );
	MACRO_qyAssert(  p1->iKeyType,  _T(  "imObj_hash_bSame: keyType can't be 0"  )  );

	if  (  p0->iKeyType  ==  p1->iKeyType  )  {
		//
		if  (  p0->bKeyInt  !=  p1->bKeyInt  )  return  FALSE;

		if  (  p0->bKeyInt  )  {
			if  (  p0->iKeyVal  !=  p1->iKeyVal  )  return  FALSE;
			//
			}
		else  {
			  //
			  if  (  strcmp(  p0->pKeyStr,  p1->pKeyStr  )  )  return  FALSE;	
		}
	
		//
		switch  (  p0->iKeyType  )  {		
				case  CONST_hashKeyType_imObj:  {
					  HashData_imObj  *  pData0  =  (  HashData_imObj  *  )p0->pData;
					  HashData_imObj  *  pData1  =  (  HashData_imObj  *  )p1->pData;

					  if  (  pData0->iObjType  !=  pData1->iObjType  )  return  FALSE;
					  }
					  break;			
				default:
					   break;			  
		}
	
		//
		bRet  =  TRUE;  goto  errLabel;		
	}

	switch  (  p0->iKeyType  )  {	
			case  CONST_hashKeyType_iObjId:
				  switch  (  p1->iKeyType  )  {
						  case  CONST_hashKeyType_imObj:  {
							    HashData_imObj  *  pData  =  (  HashData_imObj  *  )p1->pData;
								if  (  pData->iObjId  ==  p0->iKeyVal  )  {
									bRet  =  TRUE;  goto  errLabel;
								}
								}
							    break;
						  default:
								 break;
				  }
				  break;
			default:
					break;		  
	}
	
	
errLabel:

	//
	return  bRet;
}


 int  imObj_hash_copy(  HashTblElementType  *  pSrc,  HashTblElementType  *  pDst  )
 {
	 int				iErr	=	-1;
	 int				size;

	 if  (  !pSrc->bKeyInt  )  {
		 if  (  !pSrc->pKeyStr  )  {
			 return  -1;		
		 }
		 if  (  pDst->pKeyStr  )  {
			 return  -1;	 
		 }
	 }
	 if  (  pDst->pData  )  return  -1;


	 pDst->bKeyInt  =  pSrc->bKeyInt;
	 if  (  pSrc->bKeyInt  )  {
		 pDst->iKeyVal  =  pSrc->iKeyVal;
		 }
	 else  {
		   size  =  strlen(  pSrc->pKeyStr  )  +  1;
		   pDst->pKeyStr  =  (  char  *  )mymalloc(  size  );
		   if  (  !pDst->pKeyStr  )  goto  errLabel;
		   safeStrnCpy(  pSrc->pKeyStr,  pDst->pKeyStr,  size  );
	 }
	 
	 //
	 pDst->iKeyType  =  pSrc->iKeyType;
	 //
	 if  (  pSrc->pData  )  {
		 size  =  pSrc->uiSize_pData;
		 //
		 if  (  !size  )  {
			 MACRO_qyAssert(  size,  _T(  "imObj_hash_copy failed, size is 0"  )  );
		 }
		 //
		 pDst->uiSize_pData  =  size;
		 pDst->pData  =  mymalloc(  size  );
		 if  (  !pDst->pData  )  goto  errLabel;
		 memcpy(  pDst->pData,  pSrc->pData,  size  );
	 }

	 iErr  =  0;
errLabel:

	 if  (  iErr  )  {
		 imObj_hash_free(  pDst  );
	 }
	 return  iErr;
 }

 int  imObj_hash_free(  HashTblElementType  *  p  )
 {
	 MACRO_safeFree(  p->pKeyStr  );
	 MACRO_safeFree(  p->pData  );

	 return  0;
 }


