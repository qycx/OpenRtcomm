
#include	"stdAfx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"

 BOOL  bQnmCmdEnable_bhb(  int  cmdId  );
 BOOL  bQnmCmdEnable_netMc2(  int  cmdId  );
 BOOL  bQnmCmdEnable_nms(  int  cmdId  );
 //  BOOL  bQnmCmdEnable_secChk(  int  cmdId  );
 BOOL  bQnmCmdEnable_assetMgr(  int  cmdId  );
 //
 BOOL  bQnmCmdEnable_messenger(  int  cmdId  );


 BOOL  bQnmCmdEnable(  int  cmdId  )  
{
	 int  iSystemId  =  qyGetSystemId(  );
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	 #ifdef  __DEBUG__
			   //  traceLogA(  "为了调试方便,2005/11/13,在这里故意先放开权限管理,  请用完后立即关上"  );  return  TRUE;	
	 #endif

#if  10
	 if  (  pQyMc->bQnmLicenseTimeout  )  {
		 switch  (  cmdId  )  {
				 case  ID_qyExport:
					   break;
				 default:
					    return  FALSE;
						break;
		 }
	 }
#endif

 	 if  (  iSystemId  ==  CONST_qySystemId_bhb  )  return  bQnmCmdEnable_bhb(  cmdId  );
	 if  (  iSystemId  ==  CONST_qySystemId_netMc2  )  return  bQnmCmdEnable_netMc2(  cmdId  );
 	 if  (  iSystemId  ==  CONST_qySystemId_nms  )  return  bQnmCmdEnable_nms(  cmdId  );	 
	 if  (  iSystemId  ==  CONST_qySystemId_secChk  )  return  bQnmCmdEnable_netMc2(  cmdId  );
	 if  (  iSystemId  ==  CONST_qySystemId_assetMgr  )  return  bQnmCmdEnable_assetMgr(  cmdId  );
	 if  (  iSystemId  ==  CONST_qySystemId_messenger  )  return  bQnmCmdEnable_messenger(  cmdId  );


	 return  TRUE;
}
 BOOL  bQnmCmdEnable_nms(  int  cmdId  )
{
	 QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	 BOOL	bRet  =  TRUE;

	 if  (  pQyMc->curUsrInfo.scope.bRestricted  )	{
		 switch  (  cmdId  )  {
				 case		ID_qyMgrSystems:
				 case		ID_qyCfgSystems:
				 case		ID_qyImport:
				 case		ID_qyClearUp:
				 //
				 case		ID_qyNetworkView:				//	设备管理视图(&S)
				 case		ID_qyConnectionView:			//	用户管理视图(&J)
				 case		ID_qyNetworkSpeedView:			//	流量管理视图(&L)
				 case		ID_snmpObjRuleList:				//	设备管理策略列表(&C)
				 case		ID_conflictConnList:			//	MAC绑定列表(&D)
				 case		ID_directConnList:				//	端口信息列表(&J)
				 //
				 case		ID_qyStopMacScan:				//	停止扫描计算机(&S)
				 case		ID_qyStartMacScan:				//	启动扫描计算机(&U)
				 case		ID_qyStopWatchIp:				//	停止记录IP变更(&B)
				 case		ID_qyStartWatchIp:				//	启动记录IP变更(&G)
				 //
				 case		ID_qyStopSnmpScan:				//	停止扫描网络设备(&J)
				 case		ID_qyStartSnmpScan:				//	启动扫描网络设备(&R)
				 case		ID_qyStopDownPortIfMacChanged:	//	停止在联接MAC变更时阻断端口(&Z)
				 case		ID_qyStartDownPortIfMacChanged:	//	启用在联接MAC变更时阻断端口(&D)
				 case		ID_qyStopDownPortIfWarnSpeed:	//	停止在流量报警时阻断端口(&L)
				 case		ID_qyStartDownPortIfWarnSpeed:	//	启用在流量报警时阻断端口(&L)
				 //

				 case		ID_qyStopRegScan:				//  停止内网审核检查(&A)												
				 case		ID_qyStartRegScan:				//  启动内网审核检查(&H)												
				 case		ID_qyStartUpdate:				//  停用重新注册功能，启用升级功能(&J),2003/09/13.
				 case		ID_qyStopUpdate:				//  启用重新注册功能，停用升级功能(&C),2003/09/13.
				 //	
				 case		ID_qyCfgIpScan:					//  IP扫描网段配置
				 case		ID_qyMgrPcGrp:					//  注册管理配置
				 case		ID_qyCfgUnchk:					//  特许免注册检查配置
				 case		ID_qyCfgSkippedMacs:			//	要求忽略的虚拟网卡列表
				 case		ID_qyCfgSwitchPolicyGrps:		//	snmp组策略配置(&J)
				 case		ID_qyMgrSwitchPolicyGrps:		//	网络设备分组配置(&S)
				 //
				 case		ID_cfgSystemParams:				//	系统参数配置
				 //
				 case		ID_qyCfgBoard:					//	公告栏(&L)
				 case		ID_qyCfgSp:						//	补丁库配置(&B)
				 //
				 //
				 case		ID_qyCfgCustom:					//	定制配置(&D)
				 case		ID_qyCfgStandardNames:			//	规范名称配置(&G)
				 //
				 case		ID_cfgOptions:					//	选项(&X)
				 case		ID_cfgAdvancedOptions:			//	高级选项(&G)
				 case		ID_CFGWARN:						//	系统告警配置[&S]

				 //
				 //	case	ID_CFGUSR:						//	系统账号管理[&Z]
			 
					   return  FALSE;
					   break;
				 default:
						break;
		 }
	 }



     if  (  bQnmDemo(  )  )  {
	     switch  (  cmdId  )  {
				 //	case	ID_CFGUSR:
				 case	ID_cfgAdvancedOptions:

				 case	ID_qyPcUsrInTab1List:
				 //  case	ID_qyNetworkSpeedView:						//  2006/5/30,v032309版本开放流量功能

				 #ifndef  __DEBUG__
 						  case	ID_qyImport:							//  导入
				 #endif
				 //  case   ID_qyExport:							//  导出

				 case	ID_qyStopRegScan:
				 case	ID_qyStartRegScan:

				 case	ID_qyStopUpdate:
				 case	ID_qyStartUpdate:
						bRet  =  FALSE;
						break;
				 default:
					    break;
		 }
	 }

	 else  {
		   if  (  pQyMc->curUsrInfo.right.bAdmin  )  return  TRUE;
		   if  (  pQyMc->curUsrInfo.right.bXtpz  )  {
			   switch  (  cmdId  )  {
				   	   //  nms管理
				   	   //  计算机管理(&G)"														
				   	   //  case	ID_qyPcList:			//  计算机列表(&J)														
				   	   case		ID_qyPcSpList:			//  补丁列表(&B)														
				   	   //  用户管理"														
				   	   //  case	ID_qyPcUsrList:			//  用户列表(&Y)														
				   	   //  case	ID_qyPcUsrInTab1List:		//  已审核的重复注册用户列表(&C)														
				   	   //  网络管理(&K)"														
				   	   //  case		ID_qyNetworkView:		//  网络联接视图(&S)														
				   	   //  case		ID_qyConnectionView:		//  用户接入视图(&J)														
				   	   //  case		ID_qyNetworkSpeedView:		//  网络流量视图(&L)														
				   	   //  case		ID_snmpObjRuleList:		//  网络设备管理策略列表(&C)														
				   	   //  case		ID_conflictConnList:		//  联接绑定列表(&D)														
				   	   //  case	   	ID_directConnList:		//  接入列表(J)														
				   	   //  事件查看(&S)"														
				   	   case		ID_qyEventAll:			//  计算机事件(&S)														
				   	   case		ID_qyNetDevEventAll:		//  网络设备事件(&W)														
				   	   case  	ID_qyOpEventAll:		//  系统事件(&Y)														
				   	   //  查询(&C)"														
				   	   case		ID_qySearch_netDevEvent:	//  网络设备事件查询(&W)														
				   	   case		ID_qySearch_pcEvent:		//  计算机事件查询(&S)														
				   	   case		ID_qySearch_pcList:		//  计算机查询(&J)														
				   	   case		ID_qySearch_pcSpList:		//  补丁查询(B)														
				   	   case		ID_qySearch_mac:		//  MAC查询(&M)														
				   	   case		ID_qySearch_ip:			//  IP查询(&I)														
				   	   case		ID_qySearch_unusedConn:		//  无效联接查询(&W)														
				   	   case		ID_qySearch:			//  查询
				   	   case		ID_qyStat:			//  统计
				   	   //
				   	   //  case	ID_qyImport:			//  导入
				   	   //  case	ID_qyExport:			//  导出
				   	   case		ID_qyClearUp:			//  清空
				   	   //
				   	   //  case	ID_FILE_PRINT_SETUP:		//  打印设置
				   	   //  case	ID_FILE_PRINT:			//  打印
				   	   //
				   	   //  case	ID_APP_EXIT:			//  退出
								bRet  =  FALSE;  
								break;
					   default:
								break;
		 		   }
			   goto  errLabel;
		   }
		   //  剩下的是日志审计变灰MENU
		   switch  (  cmdId  )  {
				   //  nms配置
				   case		ID_qyMgrPcGrp:			//  网段配置(&F)									
				   case		ID_qyCfgSwitchPolicyGrps:	//  snmp组策略配置(&J)									
				   case		ID_qyMgrSwitchPolicyGrps:	//  网络设备分组配置(&S)									
				   //        									
				   case		ID_qyCfgBoard:			//  公告栏(&L)									
				   case		ID_qyCfgSp:			//  补丁库配置(&B)									
				   //        									
				   case		ID_qyCfgCustom:			//  定制配置(&D)									
				   //        									
				   case		ID_cfgOptions:			//  选项(&X)									
				   case		ID_cfgAdvancedOptions:		//  高级选项(&G)									
				   //        									
				   case		ID_CFGUSR:			//  系统账号管理(&Z)									
				   //  nms系统	
				   case		ID_qyStopSnmpScan:		//  停止扫描网络设备(&J)												
				   case		ID_qyStartSnmpScan:		//  启动扫描网络设备(&R)												
				   case		ID_qyStopMacScan:		//  停止扫描计算机(&S)												
				   case		ID_qyStartMacScan:		//  启动扫描计算机(&U)												
								//												
				   case		ID_qyStopWatchIp:		//  停止记录IP变更(&B)												
				   case		ID_qyStartWatchIp:		//  启动记录IP变更(G)												
								//												
				   case		ID_qyStopRegScan:		//  停止内网审核检查(&A)												
				   case		ID_qyStartRegScan:		//  启动内网审核检查(&H)												
								//												
				   case		ID_qyStopDownPortIfMacChanged:		//  停止在关联MAC变化时阻断端口(&Z)												
				   case		ID_qyStartDownPortIfMacChanged:		//  启用在关联MAC变化时阻断端口(&D)												
								//												
				   case		ID_qyStartUpdate:		//  停用重新注册功能，启用仅检查功能(&J)												
				   case		ID_qyStopUpdate:		//  启用重新注册功能，停用仅检查功能(&C)												
				   //  nms管理
				   //  计算机管理(&G)"														
				   case		ID_qyPcList:			//  计算机列表(&J)														
				   //  case	ID_qyPcSpList:			//  补丁列表(&B)														
				   //  用户管理"														
				   case		ID_qyPcUsrList:			//  用户列表(&Y)														
				   case		ID_qyPcUsrInTab1List:		//  已审核的重复注册用户列表(&C)														
				   //  网络管理(&K)"														
				   //  case		ID_qyNetworkView:		//  网络联接视图(&S)														
				   //  case		ID_qyConnectionView:		//  用户接入视图(&J)														
				   //  case		ID_qyNetworkSpeedView:		//  网络流量视图(&L)														
				   //  case		ID_snmpObjRuleList:		//  网络设备管理策略列表(&C)														
				   //  case		ID_conflictConnList:		//  联接绑定列表(&D)														
				   //  case	   	ID_directConnList:		//  接入列表(J)														
				   //  事件查看(&S)"														
				   //  case	ID_qyEventAll:			//  计算机事件(&S)														
				   //  case	ID_qyNetDevEventAll:		//  网络设备事件(&W)														
				   //  case  	ID_qyOpEventAll:		//  系统事件(&Y)														
				   //  查询(&C)"														
				   //  case	ID_qySearch_netDevEvent:	//  网络设备事件查询(&W)														
				   //  case	ID_qySearch_pcEvent:		//  计算机事件查询(&S)														
				   //  case	ID_qySearch_pcList:		//  计算机查询(&J)														
				   //  case	ID_qySearch_pcSpList:		//  补丁查询(B)														
				   //  case	ID_qySearch_mac:		//  MAC查询(&M)														
				   //  case	ID_qySearch_ip:			//  IP查询(&I)														
				   //  case	ID_qySearch_unusedConn:		//  无效联接查询(&W)														
			   	   //  case	ID_qySearch:			//  统计
				   //  case	ID_qyStat:			//  统计
				   //
				   case		ID_qyImport:			//  导入
				   //  case		ID_qyExport:			//  导出
				   //  case	ID_qyClearUp:			//  清空
				   //
				   //  case	ID_FILE_PRINT_SETUP:		//  打印设置
				   //  case	ID_FILE_PRINT:			//  打印
				   //
				   //  case	ID_APP_EXIT:			//  退出

							bRet  =  FALSE;  
							break;
				   default:
							break;
		   }
	 }



errLabel:

	 return  bRet;

}

 BOOL  bQnmCmdEnable_bhb(  int  cmdId  )
{
	 QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	 BOOL	bRet  =  TRUE;

	 switch  (  cmdId  )  {
			 case  ID_qySearch:
				   if  (  pQyMc->iAppType  !=  CONST_qyAppType_interMonOfBhb  )  return  FALSE;
				   break;
			 default:
					 break;
	 }

	 if  (  pQyMc->curUsrInfo.right.bAdmin  )  return  TRUE;

	 if  (  pQyMc->curUsrInfo.right.bXtpz  )  {
		 switch  (  cmdId  )  {
				 
				 //  case   ID_qyScannedIpList:			// 2003/9/13.
				 //  case	ID_qyEventAll:

				 //  case	ID_qyRas:
				 //  case   ID_qyProxyServer:			// 2003/09/13.
				 //  case	ID_qyOnInternet:
				 //  case	ID_qyIntraConn:
				 //  case	ID_qyDevChanged:
				 //  case	ID_qyQwmDel:
				 //  case	ID_qySearch:
				 case	ID_qyStat:
						
				 		bRet  =  FALSE;  
						break;

				 default:
						break;
		 }
		 goto  errLabel;
	 }

	 //  剩下的是日志审计
	 switch  (  cmdId  )  {
			 //  case  ID_cfgOptions:
			 //  case  ID_cfgRasOptions:
			 case  ID_cfgBhbSysOptions:				//  系统设置
			 case  ID_cfgBhbScannedNetSegs:			//	扫描网段设置
			 //  case  ID_qyMgrPcGrp:
			 //  case  ID_qyCfgUnchk:

			 case  ID_qyStopIntraMon:
			 case  ID_qyStartIntraMon:
			 
			 case  ID_qyImport:						//  导入
			 case  ID_qyExport:						//  导出
			 //  case  ID_qyClearUp:
			 //  case  ID_CFGWARN:
				 

				   bRet  =  FALSE;  
				   break;
			 default:
					break;
				   
	 }

errLabel:

	 return  bRet;

}
 

 BOOL  bQnmCmdEnable_netMc2(  int  cmdId  )
{
	 QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	 BOOL	bRet  =  TRUE;

	 if  (  pQyMc->curUsrInfo.scope.bRestricted  )  {
		 switch  (  cmdId  )  {
				 case		ID_qyPcView:
				 case		ID_qyMgrSystems:
				 case		ID_qyCfgSystems:
				 case		ID_qyImport:
				 case		ID_qyClearUp:
				 //
				 case		ID_qyStopIpScan:				//  停止IP扫描检测(&N)
				 case		ID_qyStartIpScan:				//  启动IP扫描检测(&I)
				 case		ID_qyStopRegScan:				//  停止注册检查(&A)
				 case		ID_qyStartRegScan:				//  启动注册检查(&H)
				 //
				 case		ID_stopFileMon:					//  停止文件监视		//  2006/3/23
				 case		ID_startFileMon:				//  启动文件监视		//  2006/3/23
				 case		ID_stopModuleMon:				//	停止上传进程调用模块信息,	2006/6/17
				 case		ID_startModuleMon:				//  启动上传进程调用模块信息,	2006/6/17
				 case		ID_stopPcRegistryMon:			//	停止注册表监视
				 case		ID_startPcRegistryMon:			//	启动注册表监视
				 //
				 case		ID_qyStartUpdate:				//  停用重新注册功能，启用升级功能(&J),2003/09/13.
				 case		ID_qyStopUpdate:				//  启用重新注册功能，停用升级功能(&C),2003/09/13.
				 //	
				 case		ID_qyCfgIpScan:					//  IP扫描网段配置
				 case		ID_qyMgrPcGrp:					//  注册管理配置
				 case		ID_qyCfgUnchk:					//  特许免注册检查配置
				 case		ID_qyCfgSkippedMacs:			//	要求忽略的虚拟网卡列表
				 //
				 case		ID_cfgSystemParams:				//	系统参数配置
				 //
				 case		ID_cfgPcMonOptions:				//	统一监控策略配置(&J)
				 case		ID_cfgRasOptions:				//	统一管理策略配置(&B)
				 case		ID_cfgPcNetworkOptions:			//	统一远程桌面策略配置(&W)
				 //
				 case		ID_qyCfgModuleInfo:				//	进程\\模块知识库(&M)
				 case		ID_qyCfgPcRegistryKnowledge:	//	注册表知识库(&R)
				 //
				 case		ID_qyCfgCustom:					//	定制配置(&D)
				 case		ID_qyCfgStandardNames:			//	规范名称配置(&G)
				 //
				 case		ID_cfgOptions:					//	选项(&X)
				 case		ID_cfgAdvancedOptions:			//	高级选项(&G)
				 case		ID_CFGWARN:						//	系统告警配置[&S]
				 //
				 //	case	ID_CFGUSR:						//	系统账号管理[&Z]

					 
					   return	FALSE;
					   break;
				 default:
						break;
		 }
	 }

     if  (  bQnmDemo(  )  )  {									//  2005/01/10,  开始出演示版
	     switch  (  cmdId  )  {	//  注释的则为开放的菜单

				 //  case	ID_qyCfgIpScan:							//  IP扫描网段配置
				 //  case	ID_qyMgrPcGrp:							//  注册管理配置
				 case	ID_qyCfgUnchk:								//  特许免注册检查配置
				 case	ID_CFGWARN:									//  系统告警配置
				 
				 //		  case	ID_CFGUSR:							//  系统账号管理

				 case	ID_cfgAdvancedOptions:						//  高级选项
				 
				 //  case	ID_qyStopIpScan:						//	停止IP扫描检测
				 //  case	ID_qyStartIpScan:						//	启动IP扫描检测
				 //  case	ID_qyStopRegScan:						//  停止注册检查
				 //  case	ID_qyStartRegScan:						//  启动注册检查
				 //  case	ID_stopFileMon:							//  停止文件监视	//  2006/3/23
				 //  case	ID_startFileMon:						//  启动文件监视	//  2006/3/23
				 //  case	ID_qyStartUpdate:						//  停用重新注册功能，启用升级功能(&J)
				 //  case	ID_qyStopUpdate:						//  启用重新注册功能，停用升级功能(&C)

				 //  case	ID_qyScannedIpList:						//  扫描检测IP列表
				 case	ID_qyPcUsrInTab1List:						//  已审核的重复注册用户列表
				 case	ID_qyRas:									//  拨号
				 case	ID_qyProxyServer:							//  代理设置检查
				 case	ID_qyOnInternet:							//  非法外联检测
				 case	ID_qyIntraConn:								//  陌生主机接入
				 case	ID_qyDevChanged:							//  网卡变更
				 case	ID_qyQwmDel:								//  客户端软件运行异常
				 //  case	ID_qyOpEventAll:						//  系统事件,  2006/2/16开放，要查看远程桌面的使用情况
				 #ifndef  __DEBUG__
						  case	ID_qyImport:						//  导入
				 #endif
				 //  case   ID_qyExport:						    //  导出
				 //  case	ID_qyClearUp:							//  清空

						bRet  =  FALSE;
						break;
				 default:
					    break;
		 }
	 }

	 else  {
		   if  (  pQyMc->curUsrInfo.right.bAdmin  )  return  TRUE;
		   if  (  pQyMc->curUsrInfo.right.bXtpz  )  
		   {
			   // 2010/01/17
			   switch  (  cmdId  )  {
					   //  管理	
				       //  case		ID_qyScannedIpList:			//  扫描检测IP列表(&I), 2003/9/13.
					   //
					   //  case		ID_qyPcList:				//  计算机列表(&J)
				       //  
					   //  case  	ID_qyPcUsrList:				//  用户管理
					   //  case  	ID_qyPcUsrInTab1List:			//  已审核的重复注册用户列表(&C)
					   //  case		ID_qwmSvrList:				//  客户端管理
				       //	
					   //  case		ID_pcSecChkEventList:				//  上网网址列表	变灰		,2006/3/10
					   //  case		ID_pcRegistryList:					//  注册表项列表
					   //  case		ID_pcRegistryRuleStatusList:		//  注册表规则检测状态列表
				   	   //  case		ID_pcEventLogList:					//  系统日志列表(&T)
				       //  case		ID_pcOsUsrList:						//  操作系统用户列表
				       //  case		ID_qyPcNetStatList:					//  NetStat列表
				       //  case		ID_pcPrinterPropList:				//  打印机列表

				   	   //  case		ID_pcNetworkPropList:			//  网络连接配置的状态列表(&W)
				   	   //  case		ID_pcNetworkRuleList:			//  网络连接配置的策略列表(&W)
				       //  case		ID_pcProxyCfgPropList:			//  代理服务器配置的状态列表(&W)
				   	   //  case		ID_pcProxyCfgRuleList:			//  代理服务器配置的策略列表(&W)
				   	   //  case		ID_pcComputerPropList:			//  计算机信息配置的状态列表(&M)
				   	   //  case		ID_pcComputerRuleList:			//  计算机信息配置的策略列表(&M)
				       //  case  	ID_pcRuleList:				//  单机管理策略列表(&D)
				   	   //
				   	   //
				       //  case		ID_pcProcessPropList:			//  进程列表
				       //  case		ID_qyPcSpList:				//  补丁列表
					   //
				       //  case		ID_qyEventAll:				//  所有事件
				       //  case		ID_qyRas:				//  拨号
				       //  case		ID_qyProxyServer:			//  代理设置检查(&D)
				       //  case		ID_qyOnInternet:			//  非法外联(&W)
				       //  case		ID_qyIntraConn:				//  陌生主机接入(&M)
				       //  case		ID_qyDevChanged:			//  网卡变更(&C)
				       //  case		ID_qyQwmDel:				//  客户端软件运行异常(&Y)
				       case		ID_qyOpEventAll:			//  系统事件(&Y)
					   //
				       //  case		ID_qySearch:				//  查询
				       //  case		ID_qyStat:				//  统计
				       //
				       //  case		ID_qyImport:				//  导入
				       //  case		ID_qyExport:				//  导出
					   //  case		ID_qyClearUp:				//  清空
				       //
				       //  case		ID_FILE_PRINT_SETUP:			//  打印设置
				       //  case		ID_FILE_PRINT:				//  打印
				       //
				       //  case		ID_APP_EXIT:				//  退出   
			   					bRet  =  FALSE;  
								break;
					   default:
						        break;
			   }
			   goto  errLabel;

		   }

		   //  剩下的是日志审计的变灰菜单
		   switch  (  cmdId  )  {
				   //  
				   case		ID_qyMakeClients:			// 生成客户端
				   //  netMc2配置
				   case		ID_qyCfgIpScan:			//  IP扫描网段配置
				   case		ID_qyMgrPcGrp:			//  注册管理配置
				   case		ID_qyCfgUnchk:			//  特许免注册检查配置
				   //
				   case		ID_qyCfgSkippedMacs:				//  忽略虚拟网卡,		,2010/01/17

				   //
				   case		ID_cfgSystemParams:		//  系统参数配置
				   case		ID_cfgPcMonOptions:		//  统一监控策略配置	变灰,2006/3/10
				   case		ID_cfgRasOptions:		//  终端安全策略配置
				   case		ID_cfgPcNetworkOptions:	//	远程桌面管理策略配置
				   //	
				   case		ID_qyCfgBoard:			//  公告栏
				   case		ID_qyCfgSp:				//  补丁库配置
				   //
				   case		ID_qyCfgModuleInfo:		//  进程\\模块知识库,  2006/6/17
				   case		ID_qyCfgPcRegistryKnowledge:		//  注册表知识库		,2010/01/17
				   //	
				   case		ID_qyCfgCustom:						//  定制配置
				   case		ID_qyCfgStandardNames:				//  规范名称配置		,2010/01/17

				   //
				   case		ID_cfgOptions:			//  选项
				   case		ID_cfgAdvancedOptions:	//  高级选项
				   case		ID_CFGWARN:				//  系统告警配置
				   //
				   //  case		ID_CFGUSR:				//  系统账号管理				   case  ID_cfgOptions:				//  [配置]/[选项]
				   //  netMc2系统
				   case		ID_qyStopMon:					//  卸载客户端软件并停止管理(&K)
				   case		ID_qyStartMon:					//  不卸载客户端软件并恢复管理(&B)
				   //
				   case		ID_qyStopIpScan:				//  停止IP扫描检测(&N)
				   case		ID_qyStartIpScan:				//  启动IP扫描检测(&I)
				   case		ID_qyStopRegScan:				//  停止注册检查(&A)
				   case		ID_qyStartRegScan:				//  启动注册检查(&H)
				   //
				   case		ID_stopFileMon:					//  停止文件监视		//  2006/3/23
				   case		ID_startFileMon:				//  启动文件监视		//  2006/3/23
				   case		ID_stopModuleMon:				//	停止上传进程调用模块信息,	2006/6/17
				   case		ID_startModuleMon:				//  启动上传进程调用模块信息,	2006/6/17
				   case		ID_stopPcRegistryMon:			//	停止注册表监视				,2010/01/17
				   case		ID_startPcRegistryMon:			//	启动注册表监视				,2010/01/17
				   //
				   case		ID_qyStartUpdate:				//  停用重新注册功能，启用升级功能(&J),2003/09/13.
				   case		ID_qyStopUpdate:				//  启用重新注册功能，停用升级功能(&C),2003/09/13.
				   //  secChk系统	
				   case		ID_qyStopSecChk:				//  MENUITEM "停止检查(&K)",  
				   case     ID_qyStartSecChk:				//  MENUITEM "启动检查(&B)", 

				   //  netMc2管理	
				   case		ID_qyScannedIpList:				//  扫描检测IP列表(&I), 2003/9/13.
				   //
				   case		ID_qyPcView:						//	计算机视图				,2010/01/17
				   case		ID_qyPcList:						//  计算机列表(&J)
				   //  
				   case  	ID_qyPcUsrList:						//  用户管理
				   case  	ID_qyPcUsrInTab1List:				//  已审核的重复注册用户列表(&C)
				   case		ID_qwmSvrList:					//  客户端管理
				   //	
				   case  	ID_pcRuleList0:						//  单机管理策略列表(&D)
				   case  	ID_pcRuleList1:						//  单机管理策略列表(&D)
				   //
				   case		ID_pcNetworkPropList:				//  网络连接配置的状态列表(&W)
				   case		ID_pcNetworkRuleList:				//  网络连接配置的策略列表(&W)
				   case		ID_pcProxyCfgPropList:				//  代理服务器配置的状态列表(&W)
				   case		ID_pcProxyCfgRuleList:				//  代理服务器配置的策略列表(&W)
				   case		ID_pcComputerPropList:				//  计算机信息配置的状态列表(&M)
				   case		ID_pcComputerRuleList:				//  计算机信息配置的策略列表(&M)
				   //
				   case		ID_qyPcSpList:						//  补丁列表				,2006/6/17
				   case		ID_pcWindowsUpdatePolicyPropList:	//  补丁分发配置的状态列表	,2006/6/17
				   case		ID_pcWindowsUpdatePolicyRuleList:	//  补丁分发配置的策略列表	,2006/6/17
				   //
				   case		ID_pcProcessPropList:				//  进程列表				,2006/3/10
				   case		ID_pcProcessModulePropList:			//  进程调用模块列表		,2006/6/17				
				   case		ID_pcProcessRuleList:				//  进程策略列表			,2006/3/10
				   case		ID_pcNetFlowPropList:				//  流量列表				,2010/01/17
				   case		ID_pcNetFlowPropList_ethernet:		//  以太网卡流量列表		,2010/01/17
				   case		ID_pcNetSharePropList:				//  网络共享列表			,2010/01/17	


				   //
				   case		ID_pcRegistryList:					//  注册表项列表			,2010/01/17
				   case		ID_pcRegistryRuleStatusList:		//  注册表项策略列表		,2010/01/17

				   case		ID_pcEventLogList:			//  系统日志列表(&T)
				   case		ID_pcOsUsrList:				//  操作系统用户列表
				   case		ID_qyPcNetStatList:			//  NetStat列表
				   case		ID_pcPrinterPropList:			//  打印机列表
				   //
				   case		ID_qyEventAll:				//  所有事件
				   case		ID_qyRas:				//  拨号
				   case		ID_qyProxyServer:			//  代理设置检查(&D)
				   case		ID_qyOnInternet:			//  非法外联(&W)
				   case		ID_qyIntraConn:				//  陌生主机接入(&M)
				   case		ID_qyDevChanged:			//  网卡变更(&C)
				   case		ID_qyQwmDel:				//  客户端软件运行异常(&Y)
				   //  case		ID_qyOpEventAll:			//  系统事件(&Y)
				   //

				   case		ID_qyMgrSystems:			//	打开数据源		,2010/01/17
				   case		ID_qyCfgSystems:			//	添加/删除数据源		,2010/01/17

				   case		ID_qySearch:				//  查询
				   case		ID_qyStat:				//  统计
				   //
				   case		ID_qyImport:				//  导入
				   //  case		ID_qyExport:				//  导出
				   case		ID_qyClearUp:				//  清空
				   //
				   //  case		ID_FILE_PRINT_SETUP:			//  打印设置
				   //  case		ID_FILE_PRINT:				//  打印
				   //
				   //  case		ID_APP_EXIT:				//  退出
 
						    bRet  =  FALSE;  
							break;
				   default:
							break;
		   }
	 }
errLabel:

	 return  bRet;

}



/*
BOOL  bQnmCmdEnable_secChk(  int  cmdId  )
{
	 QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	 BOOL	bRet  =  TRUE;

	 if  (  pQyMc->curUsrInfo.right.bAdmin  )  return  TRUE;

	 if  (  pQyMc->curUsrInfo.right.bXtpz  )  {
		 switch  (  cmdId  )  {
				 
				 case   ID_qyScannedIpList:			// 2003/9/13.
				 case	ID_qyEventAll:

				 case	ID_qyRas:
				 case   ID_qyProxyServer:			// 2003/09/13.
				 case	ID_qyOnInternet:
				 case	ID_qyIntraConn:
				 case	ID_qyDevChanged:
				 case	ID_qyQwmDel:

				 case	ID_qySearch:

				 case	ID_qyStat:
						
						bRet  =  FALSE;  
						break;

				 default:
						break;
		 }
		 goto  errLabel;
	 }

	 //  剩下的是日志审计
	 switch  (  cmdId  )  {
			 case  ID_cfgOptions:
			 case  ID_cfgRasOptions:
			 case  ID_qyCfgIpScan:
			 case  ID_qyMgrPcGrp:
			 case  ID_qyCfgUnchk:

			 case  ID_qyStopScripts:
			 case  ID_qyStartScripts:
			 case  ID_qyStopAutoReg:
			 case  ID_qyStartAutoReg:

			 case  ID_qyStopMon:
			 case  ID_qyStartMon:

			 case  ID_qyStopIpScan:
			 case  ID_qyStartIpScan:
			 case  ID_qyStopRegScan:
			 case  ID_qyStartRegScan:
			 case  ID_qyStopRespForUnreg:
			 case  ID_qyStartRespForUnreg:

			 case  ID_qyStopUpdate:					//  2003/09/13.
			 case  ID_qyStartUpdate:				//  2003/09/13.

			 case  ID_qyPcList:
			 case  ID_pcRuleList:
			 case  ID_qyPcUsrList:
			 case  ID_qyPcUsrInTab1List:

			 case  ID_qyImport:
			 case  ID_qyExport:
			 case  ID_qyClearUp:
			 case  ID_CFGWARN:

				   bRet  =  FALSE;  
				   break;
			 default:
					break;
				   
	 }

errLabel:

	 return  bRet;

}
*/

 //  2004/8/29
 BOOL  bQnmCmdEnable_assetMgr(  int  cmdId  )
{
	 QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	 BOOL	bRet  =  TRUE;

	 if  (  pQyMc->curUsrInfo.scope.bRestricted  )	{
		 switch  (  cmdId  )  {
				 case		ID_qyAssetsView:
				 case		ID_qyMgrSystems:
				 case		ID_qyCfgSystems:
				 case		ID_qyImport:
				 case		ID_qyClearUp:
				 //
				 case		ID_qyStopMacScan:				//	停止扫描计算机(&S)
				 case		ID_qyStartMacScan:				//	启动扫描计算机(&U)
				 case		ID_qyStopWatchIp:				//	停止记录IP变更(&B)
				 case		ID_qyStartWatchIp:				//	启动记录IP变更(&G)
				 //
				 case		ID_qyStartUpdate:				//  停用重新注册功能，启用升级功能(&J),2003/09/13.
				 case		ID_qyStopUpdate:				//  启用重新注册功能，停用升级功能(&C),2003/09/13.
				 //	
				 case		ID_qyCfgIpScan:					//  IP扫描网段配置
				 case		ID_qyMgrPcGrp:					//  注册管理配置
				 case		ID_qyCfgUnchk:					//  特许免注册检查配置
				 case		ID_qyCfgSkippedMacs:			//	要求忽略的虚拟网卡列表
				 //
				 case		ID_cfgSystemParams:				//	系统参数配置
				 //
				 case		ID_qyCfgBoard:					//	公告栏(&L)
				 case		ID_qyCfgSp:						//	补丁库配置(&B)
				 //
				 //
				 case		ID_qyCfgCustom:					//	定制配置(&D)
				 case		ID_qyCfgStandardNames:			//	规范名称配置(&G)
				 //
				 case		ID_cfgOptions:					//	选项(&X)
				 case		ID_cfgAdvancedOptions:			//	高级选项(&G)
				 case		ID_CFGWARN:						//	系统告警配置[&S]

				 //
				 //	case	ID_CFGUSR:						//	系统账号管理[&Z]
				 

					 
					   return	FALSE;
					   break;
				 default:
						break;
		 }
	 }




	 
	 
     if  (  bQnmDemo(  )  )  {
	     switch  (  cmdId  )  {
				 case	ID_qyMgrPcGrp:		 
				 case	ID_cfgAdvancedOptions:
					    if  (  cmdId  ==  ID_cfgAdvancedOptions  &&  pQyMc->cfg.ucbAdvancedOptionEnabled  )  break;
				 //	case	ID_CFGUSR:							//	系统账户管理，2008/09/06

				 case	ID_qyPcUsrInTab1List:
				 case	ID_qyNetworkSpeedView:

				 case	ID_qyStopRegScan:
				 case	ID_qyStartRegScan:

				 case	ID_qyStopMacScan:
				 case	ID_qyStartMacScan:
				 case	ID_qyStopWatchIp:						//  停止记录ip变更,2005/01/15
				 case	ID_qyStartWatchIp:						//  启动记录ip变更,2005/01/15

				 case	ID_qyStopUpdate:
				 case	ID_qyStartUpdate:

				 case	ID_qyImport:							//  导入
				 //  case   ID_qyExport:							//  导出
				 
					    bRet  =  FALSE;
						break;
				 default:
					    break;
		 }
	 }

	 else  {
		   if  (  pQyMc->curUsrInfo.right.bAdmin  )  return  TRUE;
		   if  (  pQyMc->curUsrInfo.right.bXtpz  )  {
			   switch  (  cmdId  )  {
				   	   //  assetMgr管理
				   	   //  计算机管理(&G)"														
				   	   //  case		ID_qyPcList:			//  计算机列表(&J)														
				   	   //  case	ID_qyPcSpList:			//  补丁列表(&B)														
				   	   //  用户管理"														
				   	   //  case		ID_qyPcUsrList:			//  用户列表(&Y)														
				   	   //  case		ID_qyPcUsrInTab1List:		//  已审核的重复注册用户列表(&C)														
				   	   //  客户端管理(&K)   
				   	   //  case		ID_qwmSvrList:				//  客户端管理
				   	   //  单机策略
				   	   //  case  	ID_pcRuleList:				//  单机管理策略列表(&D)
				   	   //  资产管理(&Z)"
			           	   //  case    ID_qyAssetsView:				//  "资产视图(&Z)
 				   	   //
				   	   //  case		ID_qyEventAll:				//  所有事件
				   	   case		ID_qyOpEventAll:			//  系统事件(&Y)
				   	   //
				   	   //  case		ID_qySearch:				//  查询
				   	   //  case		ID_qyStat:				//  统计
					   //  计算机硬件资产中文报表(&J)"
		               //  case		ID_qyReportAssetsInfo_byMac:	//  MENUITEM "按计算机(&J)
					   //  case		ID_qyReportAssetsInfo_byOs:		//	MENUITEM "按操作系统(&C)",                
					   //  计算机硬件资产英文报表(&Y)"
					   //  case		ID_qyReportAssetsInfo_en_byMac:	//  MENUITEM "按计算机(&J)",
					   //  case     ID_qyReportAssetsInfo_en_byOs:	//  MENUITEM "按操作系统(&C)",
				   	   //
				   	   //  case		ID_qyImport:			//  导入
				   	   //  case		ID_qyExport:			//  导出
				   	   //  case	ID_qyClearUp:			//  清空
				   	   //
				   	   //  case	ID_FILE_PRINT_SETUP:		//  打印设置
				   	   //  case	ID_FILE_PRINT:			//  打印
				   	   //
				   	   //  case	ID_APP_EXIT:			//  退出

								bRet  =  FALSE;  
								break;
					   default:
								break;
		 		   }
			   goto  errLabel;
		   }
		   //  剩下的是日志审计
		   switch  (  cmdId  )  {
				   case		ID_qyMakeClients:			// 生成客户端
				   //  assetMgr配置
				   case		ID_qyMgrPcGrp:			//  注册管理配置
				   //
				   case		ID_cfgSystemParams:		//  系统参数配置
				   //	
				   case		ID_qyCfgBoard:			//  公告栏
				   case		ID_qyCfgSp:				//  补丁库配置
				   //	
				   case		ID_qyCfgCustom:						//  定制配置
				   case		ID_qyCfgStandardNames:				//  规范名称配置		,2010/01/17
				   //
				   case		ID_cfgOptions:			//  选项
				   case		ID_cfgAdvancedOptions:	//  高级选项
				   //
				   case		ID_CFGUSR:				//  系统账号管理				   	   //  nms管理
				   //  assetMgr系统
				   case		ID_qyStopMon:					//  卸载客户端软件并停止管理(&K)
				   case		ID_qyStartMon:					//  不卸载客户端软件并恢复管理(&B)
				   //
				   case		ID_qyStopMacScan:		//  停止扫描计算机(&S)												
				   case		ID_qyStartMacScan:		//  启动扫描计算机(&U)												
				   //
				   case		ID_qyStopWatchIp:		//  停止记录IP变更(&B)												
				   case		ID_qyStartWatchIp:		//  启动记录IP变更(G)												
				   //
				   case		ID_qyStartUpdate:				//  停用重新注册功能，启用升级功能(&J),2003/09/13.
				   case		ID_qyStopUpdate:				//  启用重新注册功能，停用升级功能(&C),2003/09/13.
				   //  assetMgr管理
				   //  计算机管理(&G)"														
				   case		ID_qyPcList:			//  计算机列表(&J)														
				   case		ID_qyPcSpList:			//  补丁列表(&B)														
				   //  用户管理"														
				   case		ID_qyPcUsrList:			//  用户列表(&Y)														
				   case		ID_qyPcUsrInTab1List:		//  已审核的重复注册用户列表(&C)														
				   //  客户端管理(&K)   
				   case		ID_qwmSvrList:				//  客户端管理
				   //  单机策略
				   case  	ID_pcRuleList0:				//  单机管理策略列表(&D)
				   case		ID_pcRuleList1:
				   //  资产管理(&Z)"
			       case    ID_qyAssetsView:				//  "资产视图(&Z)
 				   //
				   case		ID_qyEventAll:				//  所有事件
				   //  case		ID_qyOpEventAll:			//  系统事件(&Y)
				   //  计算机硬件资产中文报表(&J)"
                   case		ID_qyReportAssetsInfo_byMac:	//  MENUITEM "按计算机(&J)
				   case		ID_qyReportAssetsInfo_byOs:		//	MENUITEM "按操作系统(&C)",                
				   //  计算机硬件资产英文报表(&Y)"
				   case		ID_qyReportAssetsInfo_en_byMac:	//  MENUITEM "按计算机(&J)",
				   case     ID_qyReportAssetsInfo_en_byOs:	//  MENUITEM "按操作系统(&C)",
				   //  
				   case		ID_qyMgrSystems:			//	打开数据源		,2010/01/17
				   case		ID_qyCfgSystems:			//	添加/删除数据源		,2010/01/17
				   //
				   case		ID_qySearch:				//  查询
				   case		ID_qyStat:				//  统计

				   case		ID_qyImport:			//  导入
				   //  case		ID_qyExport:			//  导出
				   case	ID_qyClearUp:			//  清空
				   //
				   //  case	ID_FILE_PRINT_SETUP:		//  打印设置
				   //  case	ID_FILE_PRINT:			//  打印
				   //
				   //  case	ID_APP_EXIT:			//  退出

							bRet  =  FALSE;  
							break;
				   default:
							break;
		   }
	 }

errLabel:

	 return  bRet;

}



 BOOL  bQnmCmdEnable_messenger(  int  cmdId  )
{
	 QY_MC	*	pQyMc	=  QY_GET_GBUF(  );
	 BOOL		bRet	=  TRUE;

	 
     if  (  bQnmDemo(  )  )  {
	     switch  (  cmdId  )  {
			     
				 case	ID_cfgAdvancedOptions:  
				 case	ID_CFGUSR:

						#ifdef  __DEBUG__
							    return  TRUE;					//  这是为了测试的方便, 2008/01/16
						#endif
				 
				 case	ID_qyMgrPcGrp:		 
				 
				 case	ID_qyNetworkSpeedView:

				 case	ID_qyStopRegScan:
				 case	ID_qyStartRegScan:

				 case	ID_qyStopMacScan:
				 case	ID_qyStartMacScan:
				 case	ID_qyStopWatchIp:						//  停止记录ip变更, 2005/01/15
				 case	ID_qyStartWatchIp:						//  启动记录ip变更, 2005/01/15

				 case	ID_qyStopUpdate:
				 case	ID_qyStartUpdate:

				 //  case	ID_qyImport:						//  导入
				 //  case   ID_qyExport:						//  导出

				 //  case	ID_qyNewMessenger:					//  2014/07/11. demo版允许新建账户了

				 //  case	ID_qyNewImGrp:						//  2014/07/27. demon允许建组
				 
						#ifndef  __DEBUG__
								 bRet  =  FALSE;
						#endif
						break;
				 default:
					    break;
		 }
	 }

	 else  {
		   if  (  pQyMc->curUsrInfo.right.bAdmin  )  return  TRUE;
		   if  (  pQyMc->curUsrInfo.right.bXtpz  )  {
			   switch  (  cmdId  )  {
				   	   //  assetMgr管理
				   	   //  计算机管理(&G)"														
				   	   //  case		ID_qyPcList:			//  计算机列表(&J)														
				   	   case	ID_qyPcSpList:			//  补丁列表(&B)														
				   	   //  用户管理"														
				   	   //  case		ID_qyPcUsrList:			//  用户列表(&Y)														
				   	   //  case		ID_qyPcUsrInTab1List:		//  已审核的重复注册用户列表(&C)														
				   	   //  客户端管理(&K)   
				   	   case		ID_qwmSvrList:				//  客户端管理
				   	   //  单机策略
				   	   //  case  	ID_pcRuleList:				//  单机管理策略列表(&D)
				   	   //  资产管理(&Z)"
			           	   //  case    ID_qyAssetsView:				//  "资产视图(&Z)
 				   	   //
				   	   //  case		ID_qyEventAll:				//  所有事件
				   	   //  case		ID_qyOpEventAll:			//  系统事件(&Y)
				   	   //
				   	   case		ID_qySearch:				//  查询
				   	   case		ID_qyStat:				//  统计
					   //  计算机硬件资产中文报表(&J)"
		               case		ID_qyReportAssetsInfo_byMac:	//  MENUITEM "按计算机(&J)
					   case		ID_qyReportAssetsInfo_byOs:		//	MENUITEM "按操作系统(&C)",                
					   //  计算机硬件资产英文报表(&Y)"
					   case		ID_qyReportAssetsInfo_en_byMac:	//  MENUITEM "按计算机(&J)",
					   case     ID_qyReportAssetsInfo_en_byOs:	//  MENUITEM "按操作系统(&C)",
				   	   //
				   	   //  case		ID_qyImport:			//  导入
				   	   //  case		ID_qyExport:			//  导出
				   	   case	ID_qyClearUp:			//  清空
				   	   //
				   	   //  case	ID_FILE_PRINT_SETUP:		//  打印设置
				   	   //  case	ID_FILE_PRINT:			//  打印
				   	   //
				   	   //  case	ID_APP_EXIT:			//  退出

								bRet  =  FALSE;  
								break;
					   default:
								break;
		 		   }
			   goto  errLabel;
		   }

		   //  剩下的是日志审计
		   switch  (  cmdId  )  {
				   //  assetMgr配置
				   case		ID_qyMgrPcGrp:			//  注册管理配置
				   //
				   case		ID_cfgSystemParams:		//  系统参数配置
				   //	
				   case		ID_qyCfgBoard:			//  公告栏
				   case		ID_qyCfgSp:				//  补丁库配置
				   //	
				   case		ID_qyCfgCustom:			//  定制配置
				   //
				   case		ID_cfgOptions:			//  选项
				   case		ID_cfgAdvancedOptions:	//  高级选项
				   //
				   case		ID_CFGUSR:				//  系统账号管理				   	   //  nms管理
				   //  assetMgr系统
				   case		ID_qyStopMon:					//  卸载客户端软件并停止管理(&K)
				   case		ID_qyStartMon:					//  不卸载客户端软件并恢复管理(&B)
				   //
				   case		ID_qyStopMacScan:		//  停止扫描计算机(&S)												
				   case		ID_qyStartMacScan:		//  启动扫描计算机(&U)												
				   //
				   case		ID_qyStopWatchIp:		//  停止记录IP变更(&B)												
				   case		ID_qyStartWatchIp:		//  启动记录IP变更(G)												
				   //
				   case		ID_qyStartUpdate:				//  停用重新注册功能，启用升级功能(&J),2003/09/13.
				   case		ID_qyStopUpdate:				//  启用重新注册功能，停用升级功能(&C),2003/09/13.
				   //  assetMgr管理
				   //  计算机管理(&G)"														
				   case		ID_qyPcList:			//  计算机列表(&J)														
				   //  case	ID_qyPcSpList:			//  补丁列表(&B)														
				   //  用户管理"														
				   case		ID_qyPcUsrList:			//  用户列表(&Y)														
				   case		ID_qyPcUsrInTab1List:		//  已审核的重复注册用户列表(&C)														
				   //  客户端管理(&K)   
				   //  case		ID_qwmSvrList:				//  客户端管理
				   //  单机策略
				   case  	ID_pcRuleList0:				//  单机管理策略列表(&D)
				   case  	ID_pcRuleList1:				//  单机管理策略列表(&D)

				   //  资产管理(&Z)"
			           //  case    ID_qyAssetsView:				//  "资产视图(&Z)
 				   //
				   //  case		ID_qyEventAll:				//  所有事件
				   //  case		ID_qyOpEventAll:			//  系统事件(&Y)
				   //
				   //  case		ID_qySearch:				//  查询
				   //  case		ID_qyStat:				//  统计
				   //  计算机硬件资产中文报表(&J)"
                   //  case		ID_qyReportAssetsInfo_byMac:	//  MENUITEM "按计算机(&J)
				   //  case		ID_qyReportAssetsInfo_byOs:		//	MENUITEM "按操作系统(&C)",                
				   //  计算机硬件资产英文报表(&Y)"
				   //  case		ID_qyReportAssetsInfo_en_byMac:	//  MENUITEM "按计算机(&J)",
				   //  case     ID_qyReportAssetsInfo_en_byOs:	//  MENUITEM "按操作系统(&C)",
				   //  
				   case		ID_qyImport:			//  导入
				   case		ID_qyExport:			//  导出
				   //  case	ID_qyClearUp:			//  清空
				   //
				   //  case	ID_FILE_PRINT_SETUP:		//  打印设置
				   //  case	ID_FILE_PRINT:			//  打印
				   //
				   //  case	ID_APP_EXIT:			//  退出

							bRet  =  FALSE;  
							break;
				   default:
							break;
		   }
	 }

errLabel:

	 return  bRet;

}



