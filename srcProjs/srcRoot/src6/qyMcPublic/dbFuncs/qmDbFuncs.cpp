
#include	"stdafx.h"
//  #include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>
#include	<tchar.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"
#include	"myDb.h"
#include	"qmDbFuncs.h"

//
bool  bObjGrp(  int  iObjType  )
{
	switch  (  iObjType  )  {
			case  CONST_objType_imGrp:
				  return  true;
				  break;
			default:
					break;
	}
	return  false;
}


//
 int  getTalkerDesc(  QM_dbFuncs  *  p_g_dbFuncs,  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  TCHAR  *  talkerDesc,  unsigned  int  talkerDescCnt,  TCHAR  *  shortName,  unsigned  int  shortNameCnt  )
 {
	 if  (  !p_g_dbFuncs  )  return  -1;
	 QM_dbFuncs  &g_dbFuncs  =  *p_g_dbFuncs;
	 	
	 QY_MESSENGER_INFO		msgrInfo;
	 QY_MESSENGER_REGINFO	regInfo;
	 IM_GRP_INFO			grpInfo;		 
	
	 //
	 if  (  talkerDesc  &&  talkerDescCnt  )  {
		 talkerDesc[0]  =  0;
	 }
	 if(  shortName  &&  shortNameCnt  )  {
		 shortName[0]  =  0;
	 }

	 //
	 if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  p_g_dbFuncs,  pDb,  iDbType,  CONST_fieldIdTable_en,  misServName,  pIdInfo,  0,  &msgrInfo,  NULL,  NULL,  NULL  )  )  memset(  &msgrInfo,  0,  sizeof(  msgrInfo  )  );

	 if  (  !msgrInfo.uiType  )  ;
	 else  if  (  bObjGrp(  msgrInfo.uiType  )  )  {
			   if  (  g_dbFuncs.pf_bGetImGrpInfoBySth(  pDb,  iDbType,  misServName,  pIdInfo,  &grpInfo  )  )  {
				   safeTcsnCpy(  grpInfo.name,  talkerDesc,  talkerDescCnt  );
				   safeTcsnCpy(  grpInfo.name,  shortName,  shortNameCnt  );
			   }
			   }
	 else  {
		   if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pDb,  iDbType,  CONST_fieldIdTable_en,  CONST_tabName_qyImObjRegInfoTab,  misServName,  pIdInfo,  0,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		   //
		    MY_REG_DESC				desc;	
	 
			regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  talkerDescCnt,  shortName,  shortNameCnt  );
	 } 			 
	
	 return  0;
 }


