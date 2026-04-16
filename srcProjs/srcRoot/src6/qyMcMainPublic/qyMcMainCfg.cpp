
#include	"stdafx.h"
#include	<tchar.h>
#include	"qyMcMainCommon.h"
#include	"myresource.h"

#include	"qyModuleCommProc.h"






 



  BOOL  bMenuIdSupported(  QY_MC  *  pQyMc,  int  id  )
{
	 BOOL			bRet	=	FALSE;
	 //QY_MC	*		pQyMc	=	QY_GET_GBUF(  );	

#if  0
	 #ifndef  __SUPPORT_AUTOLOGON__
			  if  (  id  ==  ID_autoLogonList  )  goto  errLabel;
			  if  (  id  ==  ID_qyCfgAutoLogon  )  goto  errLabel;
	 #endif
#endif

	 if  (  !pQyMc->cfg.ucbRemoteDesktopSupported  )  {
	 		 if  (  id  ==  ID_viewRemoteDesktop  )  goto  errLabel;
			 if  (  id  ==  ID_cancelRemoteDesktop  )  goto  errLabel;
			 //  if  (  id  ==  ID_monDesktop  )  goto  errLabel;			//  2006/03/08
			 //  if  (  id  ==  ID_cancelMonDesktop  )  goto  errLabel;
	 }

	 if  (  !pQyMc->cfg.ucbPcMonSupported  )  {
			 if  (  id  ==  ID_monDesktop  )  goto  errLabel;			//  2006/03/08
			 if  (  id  ==  ID_cancelMonDesktop  )  goto  errLabel;
			 if  (  id  ==  ID_doSecChk  )  goto  errLabel;
			 if  (  id  ==  ID_undoSecChk  )  goto  errLabel;
			 if  (  id  ==  ID_pcSecChkEventList  )  goto  errLabel;
	 }
	 if  (  !pQyMc->cfg.ucbPcMonSupported  &&  !pQyMc->cfg.ucbFileMonSupported  )  {
			 if  (  id  ==  ID_cfgPcMonOptions  )  goto  errLabel;
			 if  (  id  ==  ID_stopFileMon  )  goto  errLabel;
			 if  (  id  ==  ID_startFileMon  )  goto  errLabel;

	 }

	 //  2006/05/23
	 if  (  pQyMc->iSystemId  ==  CONST_qySystemId_netMc2  )  {
		 if  (  id  ==  ID_qyCfgBoard  )  goto  errLabel;
		 if  (  id  ==  ID_qyCfgSp  )  goto  errLabel;
		 //
		 //  2006/06/28, 因为注册表监控尚未完成，故暂将计算机管理视图隐去
		 //  if  (  id  ==  ID_qyPcView  )  goto  errLabel;

	 }
	 //  2006/05/24, 将统一卸载的菜单隐去
	 if  (  id  ==  ID_qyStopMon  )  goto  errLabel;
	 if  (  id  ==  ID_qyStartMon  )  goto  errLabel;
	 

	 bRet  =  TRUE;

errLabel:

	 return  bRet;
}


 int  getMenuStatus(  QY_MC  *  pQyMc,  void  *  p0,  void  *  p1,  void  *  piStatusParam  )
{
	 int						iErr		=	-1;
	 OBJ_STATUS_INFO	*		pU			=	(  OBJ_STATUS_INFO  *  )p0;
	 int						iMenuId		=	(  int  )p1;
	 int				*		piStatus	=	(  int  *  )piStatusParam;


	 if  (  !pQyMc  )  return  -1;
	 
	 if  (  !piStatus  )  return  -1;

	 if  (  !bMenuIdSupported(  pQyMc,  iMenuId  )  )  goto  errLabel;

	 if  (  p0  &&  pU->iObjType  ==  CONST_objType_procedObj  )  {		//  2007/01/02
		 if  (  !pU->u.procedObj.ucbLoaded  &&  iMenuId  !=  ID_loadProcedObj  )  *piStatus  =  -1;
		 if  (  pU->u.procedObj.ucbLoaded  )  {
			 switch  (  iMenuId  )  {
					 case  ID_loadProcedObj:	*piStatus  =  -1;	break;		//  对已装载的，一定要把装载菜单禁掉
					 //					 
					 case  ID_qyMessengerView:		//  2007/09/16
						   if  (  pU->pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  *piStatus  =  -1;	//  因为客户端的messengerView支持实时刷新，不方便在多数据源中引入。
						   break;
					 case  ID_qyNewImGrp:		*piStatus  =  -1;	break;
						   break;
					 default:
							break;
			 }
		 }
		 iErr  =  0;  goto  errLabel;
	 }		   

	 //  这里把非基本系统的写权限的菜单给禁掉
	 if  (  bObjDbAvail(  pU->pObjDb  )  &&  pU->pObjDb->iDsnIndex  !=  pQyMc->iDsnIndex_mainSys  )  {
		 switch  (  iMenuId  )  {
				 case  ID_qyCfgPcRule:
				 case  ID_qyDelPcRule:
				 case  ID_qyEdit:
				 case  ID_qyCfgStandardName:
				 case  ID_qyDel:
				 case  ID_viewRemoteDesktop:
				 case  ID_cancelRemoteDesktop:
				 case  ID_monDesktop:
				 case  ID_cancelMonDesktop:
				 case  ID_doSecChk:
				 case  ID_undoSecChk:
				 case  ID_qyDelPcUsr:
				 case  ID_qyEditPcUsrInTab1:
				 case  ID_qyDelPcUsrInTab1:
				 case  ID_qyEdit_pcNetwork:
				 case  ID_qyDel_pcNetwork:
				 case  ID_qyProhibit:
				 case  ID_qyProhibitAll:
				 case  ID_addPcProcessPermitRule:
				 case  ID_editPcModuleKnowlege:
				 //
				 case  ID_qyRefresh:
				 case  ID_qyEdit_switchInfo:
				 case  ID_qyEdit_switchAndAllConns:
				 case  ID_qyCancel_switchAndAllConns:
				 case  ID_qyCancel_allConns:
				 case  ID_qyCfgSnmpObjRule:
				 case  ID_qyDel_switch:
				 case  ID_qyWillAttack:
				 case  ID_qyStopWillAttack:
				 case  ID_beStaticAccessModeAndEnablePortSecurity:
				 case  ID_disablePortSecurity:
				 case  ID_setCpsIfMaxSecureMacAddr:
				 case  ID_qyCfgSnmpObjPortRule:
				 case  ID_qyDelSnmpObjRule:
				 case  ID_qyEdit_portUsrInfo:
				 case  ID_qyCancel_portUsrInfo:
				 case  ID_qyDel_connection:

					   *piStatus  =  -1;
				       break;
				 case  ID_qyTalk:
				 case  ID_qyAddTo:

					   *piStatus  =  -1;
					   break;
				 default:
						break;
		 }
	 }




	 switch  (  iMenuId  )  {
			 case  ID_viewRemoteDesktop:
				   if  (  p0  &&  pU->iObjType  ==  CONST_objType_syr  )  {
					   if  (  pU->u.pc.pcInfo.iPlatformId  ==  CONST_qyPlatform_win98
						   ||  pU->u.pc.pcInfo.iPlatformId  ==  CONST_qyPlatform_winme  )  
					   {
						   *piStatus  =  -1;
					   }
					   if  (  bMacLocal(  &pQyMc->env,  pU->u.pc.mac0  )  )  *piStatus  =  -1;
					   if  (  pU->u.pc.ucbOped  &&  pU->u.pc.ucbViewRemoteDesktop  )  *piStatus  =  -1;
					   if  (  pU->u.pc.ucbOped  &&  pU->u.pc.ucbMonDesktop  )  *piStatus  =  -1;					   					   
				   }
				   break;				   
			 case  ID_cancelRemoteDesktop:
				   if  (  p0  &&  pU->iObjType  ==  CONST_objType_syr  )  {
				   	   if  (  pU->u.pc.pcInfo.iPlatformId  ==  CONST_qyPlatform_win98
						   ||  pU->u.pc.pcInfo.iPlatformId  ==  CONST_qyPlatform_winme  )  
					   {
						   *piStatus  =  -1;
					   }
					   if  (  bMacLocal(  &pQyMc->env,  pU->u.pc.mac0  )  )  *piStatus  =  -1;					   
					   if  (  !pU->u.pc.ucbOped  ||  !pU->u.pc.ucbViewRemoteDesktop  )  *piStatus  =  -1;
				   }
				   break;
			 case  ID_monDesktop:
				   if  (  p0  &&  pU->iObjType  ==  CONST_objType_syr  )  {
					   if  (  pU->u.pc.pcInfo.iPlatformId  ==  CONST_qyPlatform_win98
						   ||  pU->u.pc.pcInfo.iPlatformId  ==  CONST_qyPlatform_winme  )  
					   {
						   *piStatus  =  -1;
					   }
					   if  (  pU->u.pc.pcInfo.lhQwmVer  <  334  )  {
                           if  (  bMacLocal(  &pQyMc->env,  pU->u.pc.mac0  )  )  *piStatus  =  -1;
					   }
					   if  (  pU->u.pc.ucbOped  &&  pU->u.pc.ucbViewRemoteDesktop  )  *piStatus  =  -1;
					   if  (  pU->u.pc.ucbOped  &&  pU->u.pc.ucbMonDesktop  )  *piStatus  =  -1;
					   						
				   }
				   break;
			 case  ID_cancelMonDesktop:
				   if  (  p0  &&  pU->iObjType  ==  CONST_objType_syr  )  {
				   	   if  (  pU->u.pc.pcInfo.iPlatformId  ==  CONST_qyPlatform_win98
						   ||  pU->u.pc.pcInfo.iPlatformId  ==  CONST_qyPlatform_winme  )  
					   {
						   *piStatus  =  -1;
					   }
					   if  (  pU->u.pc.pcInfo.lhQwmVer  <  334  )  {
                           if  (  bMacLocal(  &pQyMc->env,  pU->u.pc.mac0  )  )  *piStatus  =  -1;					   
					   }
					   if  (  !pU->u.pc.ucbOped  ||  !pU->u.pc.ucbMonDesktop  )  *piStatus  =  -1;
				   }
				   break;
			 default:
					break;
					
	 }

	 iErr  =  0;

errLabel:

	 return  iErr;
}






