#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qyWmComm.h"

#include	"qyCusResTemp.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcDynBmp.h"
#include	"qmcVWall.h"
#include	"qyDynLib.h"
#include	"qmcCmdProc.h"
//
#include	"isCmdConst.h"
//
#include	"myDb.h"
#include	"qyMessengerHelpPublic.h"

#include	"myresource.h"
#include	"qyMcMainWndProc.h"
#include	"genericHash.h"
#include	"imObjHash.h"


int  getObjIndex_myDb(  QY_OBJ_DB  *  pObjDb,  int  iObjId,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	int  iErr  =  -1;
	BOOL	bNeedFree_elem_o  =  FALSE;
	BOOL  bNeedFree_elem_obj  =  FALSE;


	LP_hashTbl  pHashTbl_tree  =  (  LP_hashTbl  )pObjDb->pHashTbl_tree;
	if  (  !pHashTbl_tree  )  return  -1;

	//
	// curiObjId  =  m_TreeCtrl->GetItemData(  htItem  );
	int  curiObjId  =  iObjId;

	 //  if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  curiObjId,  &objIndex  )  )  goto  errLabel;
	 HashTblElementType  elem,  elem_o;
	 memset(  &elem,  0,  sizeof(  elem  )  );
	 elem.bKeyInt  =  TRUE;
	 elem.iKeyVal  =  curiObjId;
	 elem.iKeyType  =  CONST_hashKeyType_iObjId;
	 HashData_iObjId  data;
	 memset(  &data,  0,  sizeof(  data  )  );
	 elem.pData  =  &data;
	 elem.uiSize_pData  =  sizeof(  data  );
	 //
	 memset(  &elem_o,  0,  sizeof(  elem_o  )  );
	 //
	 if  (  hashTbl_find(  pHashTbl_tree,  &elem,  NULL,  &elem_o  )  )  {
		 goto  errLabel;
	 }
	 bNeedFree_elem_o  =  TRUE;

	 //
	 unsigned  int  uiHashIndex  =  0;
	 HashData_iObjId  *  pData  =  (  HashData_iObjId  *  )elem_o.pData;
	 if  (  !pData  )  goto  errLabel;
	 uiHashIndex  =  pData->uiHashIndex;

	 imObj_hash_free(  &elem_o  );
	 bNeedFree_elem_o  =  FALSE;

	 //	  
	 HashTblElementType  elem_obj;
	 memset(  &elem_obj,  0,  sizeof(  elem_obj  )  );
	 if  (  hashTbl_findEx(  pHashTbl_tree,  uiHashIndex,  &elem_o,  NULL,  &elem_obj  )  )  goto  errLabel;
	 bNeedFree_elem_obj  =  TRUE;

	 if  (  elem_obj.iKeyType  !=  CONST_hashKeyType_imObj  )  goto  errLabel;
	 HashData_imObj  *  pData_imObj  =  (  HashData_imObj  *  )elem_obj.pData;
	 pObjIndex->objType  =  pData_imObj->iObjType;

	 //
	 pObjIndex->id  =  iObjId;
	 switch  (  pObjIndex->objType  )  {
			 case  CONST_objType_messenger:
			 case  CONST_objType_imGrp:
				   myUtf82TChar(  elem_obj.pKeyStr,  pObjIndex->objIdStr0,  mycountof(  pObjIndex->objIdStr0  )  );
				   break;
			 default:
					break;
	 }

	 //
	 iErr  =  0;

errLabel:

	 if  (  bNeedFree_elem_o  )  imObj_hash_free(  &elem_o  );
	 if  (  bNeedFree_elem_obj  )  imObj_hash_free(  &elem_obj  );

	return  iErr;
}
