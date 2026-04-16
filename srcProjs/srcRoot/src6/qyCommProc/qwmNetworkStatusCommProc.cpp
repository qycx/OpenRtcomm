
#include	"stdafx.h"
#include	"qyPrecomp.h"
#include	<assert.h>



#ifndef  __WINCE__

	#include	<windows.h>
	#include	<Winternl.h>
	#include	<lmshare.h>
	#include	<vfw.h>
#else
		
	#include	<winsock2.h>
	#include	<windows.h>

	#ifdef  __TEST__
		#include	<vfw.h>
	#endif

	#include	<mmreg.h>
	#include	<MSAcm.h>
	
#endif

#include	<tchar.h>
#include	<iphlpapi.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qySnmpCommProc.h"
#include	"qnmCommProc.h"
#include	"qmOpenCommon.h"
#include	"qnmCommProc_mis.h"
#include	"qnmPcComm.h"
#include	"qnmCustom.h"
#include	"qnmAssetsCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qwmDynFunc.h"
#include	"qytcharcommproc.h"

#include	"tmpCeLib.h"
#include	"pcCommType_defs.h"


//
 QY_DMITEM  CONST_adapterTypeTable[]  =  
{
	{	MIB_IF_TYPE_ETHERNET,	(TCHAR*)_T(  "Ethernet Adapter"  ),		},
	{	MIB_IF_TYPE_TOKENRING,	(TCHAR*)_T(  "Token-ring Adapter"  ),		},
	{	MIB_IF_TYPE_FDDI,		(TCHAR*)_T(  "FDDI Adapter"  ),		},
	{	MIB_IF_TYPE_PPP,		(TCHAR*)_T(  "PPP Adapter"  ),		},
	{	MIB_IF_TYPE_LOOPBACK,	(TCHAR*)_T(  "Loopback Adapter"  ),	},
	{	MIB_IF_TYPE_SLIP,		(TCHAR*)_T(  "Slip Adapter"  ),		},
	{	IF_TYPE_IEEE80211,		(TCHAR*)_T(  "Radio spread spectrum"  ),	},
	//							_T(  "Unknown Device Adapter"  )
	{	-1,						NULL,						},
};



 QY_DMITEM  CONST_qyCommTypeTable_en[]  =
{
#if  0
	{	CONST_pcNetworkPropType_adapter,					(TCHAR*)_T(  "network connection"  ),				},
	{	CONST_pcNetworkPropType_proxy,						(TCHAR*)_T(  "proxy"  ),			},
	{	CONST_pcNetworkPropType_computer,					(TCHAR*)_T(  "computer name"  ),				},
	{	CONST_pcCommType_cleanNetworkProp,					(TCHAR*)_T(  "clear network config information"  ),	},
	{	CONST_pcCommType_process,							(TCHAR*)_T(  "process"  ),					},
	{	CONST_pcCommType_eventLog,							(TCHAR*)_T(  "windows log"  ),				},
	{	CONST_pcCommType_usrInfo,							(TCHAR*)_T(  "user account"  ),			},
	{	CONST_pcCommType_tcpTable,							(TCHAR*)_T(  "TCP connection"  ),				},
	{	CONST_pcCommType_udpTable,							(TCHAR*)_T(  "UDP connection"  ),				},
	{	CONST_pcCommType_printers,							(TCHAR*)_T(  "printer"  ),				},
	{	CONST_pcCommType_processRule,						(TCHAR*)_T(  "process rule"  ),				},
	{	CONST_pcCommType_processModule,						(TCHAR*)_T(  "module"  ),					},
	{	CONST_pcCommType_windowsUpdatePolicy,				(TCHAR*)_T(  "windows update settings"  ),			},
	{	CONST_pcCommType_registryVal,						(TCHAR*)_T(  "registry"  ),			},
	{	CONST_pcCommType_netFlow,							(TCHAR*)_T(  "flow"  ),					},
	{	CONST_pcCommType_netShare,							(TCHAR*)_T(  "network share"  ),				},
	//
	{	CONST_pcCommType_switchRule,						(TCHAR*)_T(  "Device policy"  ),				},
	{	CONST_pcCommType_switchPortRule,					(TCHAR*)_T(  "Port policy"  ),				},
	//
	//  {	CONST_pcCommType_pcFileMonRules					2		//  2006/07/16, ?????????????
	{	CONST_pcCommType_registryRule,						(TCHAR*)_T(  "Registry rule"  ),			},
	{	CONST_pcCommType_registryRuleStatus,				(TCHAR*)_T(  "registry status acording to registry rule"  ),	},
	{	CONST_pcCommType_queryCfgs,							(TCHAR*)_T(  "Query configuration"  ),		},
	{	CONST_pcCommType_pcProcessKnowledge,				(TCHAR*)_T(  "Process knowledge base"  ),				},
	{	CONST_pcCommType_pcRegistryKnowledge,				(TCHAR*)_T(  "Registry knowledge base"  ),			},
#endif 
	//
	//  mis???????????2007/05/07
	{	CONST_imCommType_htmlContent,						(TCHAR*)_T(  "HTML content"  ),			},
	{	CONST_imCommType_simpleResp,						(TCHAR*)_T(  "simply response"  ),				},
	//  {	CONST_imCommType_streamContent,						_T(  "Stream content"  ),			},
	//  {	CONST_imCommType_msgRoute,							_T(  "message route"  ),				},
	//  {	CONST_imCommType_dataContent,						_T(  "raw data"  ),				},
	{	CONST_imCommType_lStream,							(TCHAR*)_T(  "long stream content"  ),				},
	//  
	{	CONST_imCommType_retrieveImGrpListReq,				(TCHAR*)_T(  "Request message of getting groups"  ),		},
	{	CONST_imCommType_retrieveImGrpListResp,				(TCHAR*)_T(  "Response message of getting groups"  ),		},
	{	CONST_imCommType_retrieveImGrpMemListReq,			(TCHAR*)_T(  "Request message of getting members "  ),		},
	{	CONST_imCommType_retrieveImGrpMemListResp,			(TCHAR*)_T(  "Response message of getting members"  ),		},
	{	CONST_imCommType_retrieveContactListReq,			(TCHAR*)_T(  "Request message of getting contacts"  ),		},
	{	CONST_imCommType_retrieveContactListResp,			(TCHAR*)_T(  "Response message of getting contacts"  ),		},
	{	CONST_imCommType_retrieveImObjListEndReq,			(TCHAR*)_T(  "Request message of ending to update contact list"  ),	},
	{	CONST_imCommType_retrieveImObjListEndResp,			(TCHAR*)_T(  "Response message of ending to update contact list"  ),	},
	//
	{	CONST_imCommType_messengerRegInfo,					(TCHAR*)_T(  "Request message of sending contact"  ),	},
	{	CONST_imCommType_messengerPcInfo,					(TCHAR*)_T(  "Request message of sending pc info"  ),		},
	//
	{	CONST_imCommType_refreshRecentFriendsReq,			(TCHAR*)_T(  "Request message of refreshing recent contact"  ),	},
	{	CONST_imCommType_refreshRecentFriendsResp,			(TCHAR*)_T(  "Response message of refreshing recent contact"  ),	},
	//
	{	CONST_imCommType_transferFileReq,					(TCHAR*)_T(  "Request of transfering file"  ),				},			//  _T(  "Request message of transfering file"  ),				},
	{	CONST_imCommType_transferFileReplyReq,				(TCHAR*)_T(  "Re: request of transfering file"  ),				},		//  _T(  "Re:request message of transfering file"  ),				},
	{	CONST_imCommType_transferFileDataReq,				(TCHAR*)_T(  "Request of transfering file data"  ),				},		//  _T(  "Request message of transfering file data"  ),				},
	{	CONST_imCommType_transferFileDataResp,				(TCHAR*)_T(  "Response of transfering file data"  ),				},	//  _T(  "Response message of transfering file data"  ),				},
	{	CONST_imCommType_transferFileEndReq,				(TCHAR*)_T(  "Request of ending to transfer file"  ),				},	//  _T(  "Request message of ending to transfer file"  ),				},
	{	CONST_imCommType_transferFileEndResp,				(TCHAR*)_T(  "Response of ending to transfer file"  ),				},	//  _T(  "Response message of ending to transfer file"  ),				},
	{	CONST_imCommType_taskProcReq,						(TCHAR*)_T(  "Request of task"  ),				},						//  _T(  "Request message of task"  ),				},
	{	CONST_imCommType_taskProcResp,						(TCHAR*)_T(  "Response of task"  ),				},						//  _T(  "Response message of task"  ),				},
	//
	{	CONST_imCommType_rtcCallReq,						(TCHAR*)_T(  "Rtc Call Req"  ),			},
	//
	{	CONST_imCommType_transferAvInfo,					(TCHAR*)_T(  "AV request"  ),				},
	{	CONST_imCommType_transferAvReplyInfo,				(TCHAR*)_T(  "AV response"  ),				},
	{	CONST_imCommType_transferVideoData,					(TCHAR*)_T(  "Video data"  ),			},
	{	CONST_imCommType_transferVideoDataResp,				(TCHAR*)_T(  "Video data response"  ),		},
	//
	{	CONST_imCommType_transferAudioData,					(TCHAR*)_T(  "Audio data"  ),			},
	{	CONST_imCommType_transferAudioDataResp,				(TCHAR*)_T(  "Audio data response"  ),		},
	//
	//  {	CONST_imCommType_transferFileStatus,				_T(  "Status of transfering file"  ),			},
	//
	{	CONST_imCommType_imGrp,								(TCHAR*)_T(  "Im group"  ),				},
	{	CONST_imCommType_refreshImGrp,						(TCHAR*)_T(  "Refresh group"  ),				},
	//
	{	CONST_imCommType_retrieveWebContactListReq,			(TCHAR*)_T(  "Request message of querying web messenger"  ),	},
	{	CONST_imCommType_retrieveWebContactListResp,		(TCHAR*)_T(  "Response message of querying web messenger"  ),	},
    //
	{	CONST_imCommType_refreshWebContactsInfo,			(TCHAR*)_T(  "Refresh web messenger"  ),		},
	{	CONST_imCommType_ipKnowledge,						(TCHAR*)_T(  "IP address knowledge base"  ),			},
	//
	{	CONST_imCommType_smPkt,								(TCHAR*)_T(  "Short Message Packet"  ),	},
	{	CONST_imCommType_phoneGuest,						(TCHAR*)_T(  "Phone Guest"  ),			},
	{	CONST_imCommType_vDevComs,							(TCHAR*)_T(  "VDev Coms"  ),			},
	{	CONST_imCommType_retrieveSmPolicy,					(TCHAR*)_T(  "Get SM policy"  ),			},
	//
	{	CONST_imCommType_vDevData,							(TCHAR*)_T(  "VDev Data"  ),			},
	//
	{	CONST_imCommType_qmdStatus,							(TCHAR*)_T(  "qmdStatus"  ),	},
	{	CONST_imCommType_qmdMcuStatusList,					(TCHAR*)_T(  "qmdMcuStatusList"  ),	},
	//
	{	-1,											NULL,				},
};



//
//

 QY_DMITEM  CONST_qyStatusTable_en[]  =
{
	{	CONST_qyStatus_ok,										(TCHAR*)_T(  "OK"  ),				},
	//	
	{	CONST_qyStatus_del,										(TCHAR*)_T(  "Del"  ),				},
	{	CONST_qyStatus_update,									(TCHAR*)_T(  "Update"  ),			},
	//
	{	CONST_qyStatus_err,										(TCHAR*)_T(  "Error"  ),			},		//  ???-1???Error?????
	//
	{	CONST_imTaskStatus_req,									(TCHAR*)_T(  "Req"  ),				},		//  2007/10/07
	{	CONST_imTaskStatus_resp,								(TCHAR*)_T(  "Resp"  ),				},
	//
	{	CONST_imTaskStatus_applyToSend,							(TCHAR*)_T(  "applyToSend"  ),						},
	{	CONST_imTaskStatus_waitToSend,							(TCHAR*)_T(  "waitToSend"  ),						},
	{	CONST_imTaskStatus_applyToRecv,							(TCHAR*)_T(  "applyToRecv"  ),						},
	{	CONST_imTaskStatus_waitToRecv,							(TCHAR*)_T(  "waitToRecv"  ),						},
    //
	{	CONST_imTaskStatus_sending,								(TCHAR*)_T(  "sending"  ),						},
	{	CONST_imTaskStatus_receiving,							(TCHAR*)_T(  "receiving"  ),						},
	//
	{	CONST_imTaskStatus_sendBreak,							(TCHAR*)_T(  "sendBreak"  ),						},
	{	CONST_imTaskStatus_recvBreak,							(TCHAR*)_T(  "recvBreak"  ),						},
	//
	{	CONST_imTaskStatus_recvFinished,						(TCHAR*)_T(  "recvFinished"  ),							},
	{	CONST_imTaskStatus_sendFinished,						(TCHAR*)_T(  "sendFinished"  ),							},
	//
	{	CONST_imTaskStatus_err_missingOrgReq,					(TCHAR*)_T(  "err_missingOrgReq"  ),					},
    //
	{	CONST_imTaskStatus_canceledBySender,					(TCHAR*)_T(  "canceledBySender"  ),						},
	{	CONST_imTaskStatus_canceledByReceiver,					(TCHAR*)_T(  "canceledByReceiver"  ),						},
	{	CONST_imTaskStatus_deniedByReceiver,					(TCHAR*)_T(  "deniedByReceiver"  ),						},
	{	CONST_imTaskStatus_autoCanceledByReceiver,				(TCHAR*)_T(  "autoCanceledByReceiver"  ),				},		//  2014/07/30
	//
	//
	{	-1,																		},
};

 /*
 QY_DMITEM  CONST_pcAdapterStatusTable[]  =  
{
	{	CONST_pcAdapterStatus_null,								(TCHAR*)_T(  ""  ),				},
	{	CONST_pcAdapterStatus_willBeLocked,						(TCHAR*)_T(  "Locking"  ),		},
	{	CONST_pcAdapterStatus_locked,							(TCHAR*)_T(  "Locked"  ),		},
	{	CONST_pcAdapterStatus_cantBeLocked,						(TCHAR*)_T(  "Cannot be locked"  ),		},
	{	-1,														NULL,			},
};
*/

 
	
 static  int  tmpAddIp2Buf(  char  *  ip,  char  *  cBuf,  char  *  buf,  unsigned  int  size  )
{
	 char	tmpBuf[256];

	 if  (  !buf[0]  )  _snprintf(  buf,  size,  "%s",  ip  );
	 else  {
		   _snprintf(  tmpBuf,  sizeof(  tmpBuf  ),  "%s",  buf  );
		   _snprintf(  buf,  size,  "%s%s%s",  ip,  (  cBuf  ?  cBuf  :  " "  ),  tmpBuf  );
	 }
	 return  0;
}


 int  getAdapterDnsInfo(  QWM_DYN_LIB  *  pDynLib,  PIP_ADAPTER_INFO  pAdapterInfo0,  QY_PCADAPTER_PROP  *  pAdapterProp  )
{
	 int						iErr				=	-1;
	 IP_PER_ADAPTER_INFO	*	pPerAdapterInfo		=	NULL;
	 ULONG						ulOutBufLen			=	0;
	 IP_ADDR_STRING			*	pIpAddr				=	NULL;

	 
	 if  (  !pDynLib->pGetPerAdapterInfo  )  return  0;	//  ?2000?????
	 if  (  !pAdapterInfo0  )  return  -1;

	 ulOutBufLen  =  sizeof(  IP_PER_ADAPTER_INFO  );
	 if  (  !(  pPerAdapterInfo  =  (  IP_PER_ADAPTER_INFO  *  )mymalloc(  ulOutBufLen  )  )  )  goto  errLabel;
	 // Make an initial call to GetAdaptersInfo to get
	 // the necessary size into the ulOutBufLen variable
	 if  (  pDynLib->pGetPerAdapterInfo(  pAdapterInfo0->Index,  pPerAdapterInfo,  &ulOutBufLen  )  ==  ERROR_BUFFER_OVERFLOW  ) {
		 free(  pPerAdapterInfo  );  pPerAdapterInfo  =  NULL;
		 if  (  !(  pPerAdapterInfo  =  (  IP_PER_ADAPTER_INFO  *  )mymalloc(  ulOutBufLen  )  )  )  goto  errLabel; 
	 }
	 if  (  pDynLib->pGetPerAdapterInfo(  pAdapterInfo0->Index,  pPerAdapterInfo,  &ulOutBufLen  )  !=  ERROR_SUCCESS  )  goto  errLabel;

	 pAdapterProp->dnsBuf[0]  =  0;
	 for  (  pIpAddr  =  &pPerAdapterInfo->DnsServerList;  pIpAddr;  pIpAddr  =  pIpAddr->Next  )  {
		  if  (  !pAdapterProp->dnsBuf[0]  )  _snprintf(  pAdapterProp->dnsBuf,  sizeof(  pAdapterProp->dnsBuf  ),  "%s",  pIpAddr->IpAddress.String  );
		  else  _snprintf(  pAdapterProp->dnsBuf,  sizeof(  pAdapterProp->dnsBuf  ),  "%s,%s",  pAdapterProp->dnsBuf,  pIpAddr->IpAddress.String  );
	 }

	 iErr  =  0;

errLabel:

	if  (  pPerAdapterInfo  )  free(  pPerAdapterInfo  );

	 return  iErr;
}



 int  enumPcAdaptersByIpHlp(  void  *  pReserved,  QY_ENV  *  pEnv,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  )
{
	//  QNM_DEV_INFO		*	pQnmDevInfo				=	(  QNM_DEV_INFO  *  )p1;
	PIP_ADAPTER_INFO		pAdapterInfo			=	NULL;
	PIP_ADAPTER_INFO		pAdapter				=	NULL;
	DWORD					dwRetVal				=	0;
	int						cnt						=	0;
	int						iErr					=	-1;
	//  BOOL					bKeyOpen				=	FALSE;
	TCHAR					tmpBuf[256]				=	_T(  ""  );
	long					size					=	0;
	TCHAR					pnpInstanceIDCfg[32]	=	_T(  "PnpInstanceID"  );
	TCHAR					nameCfg[16]				=	_T(  "Name"  );
	TCHAR					mediaSubType[16]		=	_T(  "MediaSubType"  );	
	char					data[20]; data[0] = 0;// = (char*)"192.168.103.3";
	IP_ADDR_STRING	*		pIpAddr					=	NULL;
	ULONG					ulOutBufLen				=	sizeof(  IP_ADAPTER_INFO  );
	char					mac[CONST_qyMacLen  +  1];
	int						i;
	QY_PCADAPTER_INFO		pcAdapter;
	QWM_DYN_LIB			*	pDynLib					=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;
	TCHAR					tBuf[512]				=	_T(  ""  );
	

	if  (  !bIpHlpApiOk(  pDynLib  )  )  return  -1;
	//  if  (  !pQnmDevInfo  )  return  -1;

	if  (  !(  pAdapterInfo  =  (  IP_ADAPTER_INFO  *  )mymalloc(  sizeof(  IP_ADAPTER_INFO  )  )  )  )  goto  errLabel;
	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into the ulOutBufLen variable
	ulOutBufLen  =  sizeof(  IP_ADAPTER_INFO  );
	if  (  pDynLib->pGetAdaptersInfo(  pAdapterInfo,  &ulOutBufLen  )  ==  ERROR_BUFFER_OVERFLOW  ) {
		free(  pAdapterInfo  );  pAdapterInfo  =  NULL;
		if  (  !(  pAdapterInfo  =  (  IP_ADAPTER_INFO  *  )mymalloc(  ulOutBufLen  )  )  )  goto  errLabel; 
	}

	if  (  (  dwRetVal  =  pDynLib->pGetAdaptersInfo(  pAdapterInfo,  &ulOutBufLen  )  )  !=  NO_ERROR  )  {
		traceLogA(  (char*)"GetAdaptersInfo failed"  );  goto  errLabel;
	}
	
	for  (  pAdapter = pAdapterInfo;  pAdapter;  pAdapter = pAdapter->Next,  cnt  ++  )  {

		 memset(  &pcAdapter,  0,  sizeof(  pcAdapter  )  );
		 pcAdapter.uiType  =  CONST_pcNetworkPropType_adapter;
		 pcAdapter.uiSize  =  sizeof(  pcAdapter  );

	#if  0
		 traceLogA(  "\tindex %d",  cnt  );  
		 traceLogA(  "\tAdapter Name: \t%s",  pAdapter->AdapterName  );
	#endif
		 safeStrnCpy(  pAdapter->AdapterName,  pcAdapter.adapterName,  sizeof(  pcAdapter.adapterName  )  );
		 
		 _sntprintf(  tmpBuf,  mycountof(  tmpBuf  ),  _T(  "%s%S%s"  ),  _T(  "SYSTEM\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}\\"  ),  pAdapter->AdapterName,  _T(  "\\Connection"  )  );

		 if  (  qyGetRegCfg(  tmpBuf,  pnpInstanceIDCfg,  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
		 myTChar2Utf8(  tBuf,  pcAdapter.devIdStr,  sizeof(  pcAdapter.devIdStr  )  );
	#if  0
		 traceLogA(  "\tAdapter  devId: \t%s",  pcAdapter.devIdStr  );
	#endif

		 //  if  (  strcmpi(  pcAdapter.devIdStr,  pQnmDevInfo->devIdStr  )  )  continue;
		 safeStrnCpy(  pAdapter->Description,  pcAdapter.devDesc,  sizeof(  pcAdapter.devDesc  )  );

		 if  (  qyGetRegCfg(  tmpBuf,  nameCfg,  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
		 myTChar2Utf8(  tBuf,  pcAdapter.connectionName,  sizeof(  pcAdapter.connectionName  )  );
	#if  0
		 traceLogA(  "\tAdapter Connection: \t%s",  pcAdapter.connectionName  );
	#endif

		 if  (  qyGetRegCfg(  tmpBuf,  mediaSubType,  (  char  *  )&pcAdapter.mediaSubType,  sizeof(  pcAdapter.mediaSubType  )  )  ){
			 pcAdapter.mediaSubType  =  0;
		 }    

		 //  traceLogA(  "\tAdapter Desc: \t%s",  pAdapter->Description  );
		 for  (  mac[0]  =  0,  i  =  0;  i  <  6;  i  ++  )  _snprintf(  mac,  sizeof(  mac  ),  "%s%02x",  mac,  (  unsigned  char  )pAdapter->Address[i]  );
		 _snprintf(  pcAdapter.mac,  sizeof(  pcAdapter.mac  ),  "%s",  mac  );

		 pcAdapter.uiAdapterIndex  =  pAdapter->Index;	//  2007/02/19
		 pcAdapter.uiAdapterType  =  pAdapter->Type;
		 //  traceLogA(  "\tAdapter Type:\t%s",  qyGetDesByType1(  CONST_adapterTypeTable,  pAdapter->Type  )  );
		 
		 for  (  pIpAddr  =  &pAdapter->IpAddressList;  pIpAddr;  pIpAddr  =  pIpAddr->Next  )  {
			#if  0
			  traceLogA(  "\tIP Address: \t%s",  pIpAddr->IpAddress.String  );
			  traceLogA(  "\tIP Mask: \t%s",  pIpAddr->IpMask.String  );
			#endif

			  tmpAddIp2Buf(  pIpAddr->IpAddress.String,  NULL,  pcAdapter.ipBuf,  sizeof(  pcAdapter.ipBuf  )  );
			  tmpAddIp2Buf(  pIpAddr->IpMask.String,  NULL,  pcAdapter.ipMaskBuf,  sizeof(  pcAdapter.ipMaskBuf  )  );
		 }

		 for  (  pIpAddr  =  &pAdapter->GatewayList;  pIpAddr;  pIpAddr  =  pIpAddr->Next  )  {
			#if  0
			  traceLogA(  "\tGateway: \t%s",  pAdapter->GatewayList.IpAddress.String  );
			#endif

			  tmpAddIp2Buf(  pIpAddr->IpAddress.String,  NULL,  pcAdapter.gatewayBuf,  sizeof(  pcAdapter.gatewayBuf  )  );
		 }
		#if  0
		 traceLogA(  "\t***"  );
		#endif
		 
		 pcAdapter.ucbDhcpEnabled  =  pAdapter->DhcpEnabled;
		 if  (  !pAdapter->DhcpEnabled  )  {
			#if  0
			 traceLogA(  "\tDHCP Enabled: No"  );
			#endif
			 }
		 else  {
			#if  0
			   traceLogA(  "\tDHCP Enabled: Yes"  );
			   traceLogA(  "\t\tDHCP Server: \t%s",  pAdapter->DhcpServer.IpAddress.String  );
			   traceLogA(  "\tLease Obtained: %ld",  pAdapter->LeaseObtained  );
			#endif

			   tmpAddIp2Buf(  pAdapter->DhcpServer.IpAddress.String,  NULL,  pcAdapter.dhcpServerIp,  sizeof(  pcAdapter.dhcpServerIp  )  );
			   pcAdapter.lLeaseObtained  =  pAdapter->LeaseObtained;			   
		 }

		 pcAdapter.ucbHaveWins  =  pAdapter->HaveWins;
		 if  (  !pAdapter->HaveWins)  {
			#if  0
			 traceLogA(  "\tHave Wins: No"  );
			#endif
			}
		 else  {
			#if  0
			   traceLogA(  "\tHave Wins: Yes"  );
			   traceLogA(  "\t\tPrimary Wins Server: \t%s",  pAdapter->PrimaryWinsServer.IpAddress.String  );
			   traceLogA(  "\t\tSecondary Wins Server: \t%s\n",  pAdapter->SecondaryWinsServer.IpAddress.String  );
			#endif

			   tmpAddIp2Buf(  pAdapter->PrimaryWinsServer.IpAddress.String,  NULL,  pcAdapter.primaryWinsServerIp,  sizeof(  pcAdapter.primaryWinsServerIp  )  );
			   tmpAddIp2Buf(  pAdapter->SecondaryWinsServer.IpAddress.String,  NULL,  pcAdapter.secondaryWinsServerIp,  sizeof(  pcAdapter.secondaryWinsServerIp  )  );
		 }

		 //  ?DNS
		 _sntprintf(  tmpBuf,  mycountof(  tmpBuf  ),  _T(  "%s%S"  ),  _T(  CONST_qyRootKey_tcpIpInterfaces  ),  pAdapter->AdapterName  );
		 if  (  qyGetRegCfg(  tmpBuf,  _T(  CONST_regValName_dns  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
		 myTChar2Utf8(  tBuf,  pcAdapter.dnsBuf,  sizeof(  pcAdapter.dnsBuf  )  );
		 trim(  pcAdapter.dnsBuf  );
		 if  (  pAdapter->DhcpEnabled  &&  !pcAdapter.dnsBuf[0]  )  pcAdapter.ucbAutoDns  =  TRUE;
		 getAdapterDnsInfo(  pDynLib,  pAdapter,  (  QY_PCADAPTER_PROP  *  )&pcAdapter  );

				  
		 /*		 
		   char					curUsrName[64  +  1];	
		   char					proxyBuf[128  +  1];
		   */
		 #ifdef		__DEBUG__
					//  printPcAdapterProp(  (  QY_PCADAPTER_PROP  *  )&pcAdapter  );
		 #endif

		 if  (  pf  )  {
			 int  tmpiRet  =  pf(  p0,  p1,  &pcAdapter  );
			 if  (  tmpiRet  )  {
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
		 }

	}
	

	iErr  =  0;		
	
errLabel:

	if  (  pAdapterInfo  )  free(  pAdapterInfo  );

	return  iErr;
}





#ifdef  __DEBUG__
  extern  "C"  int  printPcAdapterProp(  QY_PCADAPTER_PROP  *  p  )
{
	 traceLogA(  (char*)"printPcAdapterProp enters:"  );

	 //  traceLogA(  "\tpnpInstanceIDBuf is %s",  p->pnpInstanceIDBuf  );
	 traceLogA((char*)"\tdevId is %s",  p->devIdStr  );
	 traceLogA((char*)"\tdevDesc is %s",  p->devDesc  );
	 traceLogA((char*)"\tdevIndex is %d",  p->devIndex  );
	 //
	 traceLogA((char*)"\tconnection is %s",  p->connectionName  );
	 traceLogA((char*)"\tuiAdapterType is %s",  qyGetDesByType1(  CONST_adapterTypeTable,  p->uiAdapterType  )  );
	 traceLogA((char*)"\tmac is %s",  p->mac  );
	 traceLogA((char*)"\tipBuf is %s",  p->ipBuf  );
	 traceLogA((char*)"\tipMaskBuf is %s",  p->ipMaskBuf  );
	 traceLogA((char*)"\tgatewayBuf is %s",  p->gatewayBuf  );
	 //
	 traceLogA((char*)"\tucbDhcpEnabled is %s",  p->ucbDhcpEnabled  ?  "TRUE"  :  "FALSE"  );
	 if  (  p->ucbDhcpEnabled  )  {
		 traceLogA((char*)"\tdhcpServerIp is %s",  p->dhcpServerIp  );
		 traceLogA((char*)"\tlLeaseObtained is %d",  p->lLeaseObtained  );
	 }
	 //
	 traceLogA((char*)"\tucbHaveWins is %s",  p->ucbHaveWins  ?  "TRUE"  :  "FALSE"  );
	 if  (  p->ucbHaveWins  )  {
		 traceLogA((char*)"\tprimaryWinsServerIp is %s",  p->primaryWinsServerIp  );
		 traceLogA((char*)"\tsecondaryWinsServerIp is %s",  p->secondaryWinsServerIp  );
	 }
	 //
	 traceLogA((char*)"\tdnsBuf is %s",  p->dnsBuf  );
	 traceLogA((char*)"\tcurUsrName is %s",  p->curUsrName  );
	 traceLogA((char*)"\tproxyBuf is %s",  p->proxyBuf  );

	 traceLogA((char*)"printPcAdapterProp leases:"  );

	 return  0;

}



 extern  "C"  int  printQwmUsrInfo(  QWM_USR_INFO  *  pUsrInfo  )
{
#if  0
	 traceLogA(  "szSubKey is %s",  pUsrInfo->szSubKey  );					//  ?????
	 traceLogA(  "name is %s",  pUsrInfo->name  );							//  ????????2003/09/12??
	 traceLogA(  "proxyServer is %s",  pUsrInfo->proxyServer  );				//  IE??????2003/09/12??
		
	 //  ??????????????, 2005/06/17
	 traceLogA(  "dwEnableAutodial is %d",  pUsrInfo->ucbEnableAutodial  );
	 traceLogA(  "dwNoNetAutodial is %d",  pUsrInfo->ucbNoNetAutodial  );
	 traceLogA(  "ucbAutoDetectSettings is %d",  pUsrInfo->ucbAutoDetectSettings  );			//  ????????
	 //  unsigned  char						reserved[3];									//
	 traceLogA(  "dwProxyEnable is %d",  pUsrInfo->ucbProxyEnable  );							//		2005/06/16
	 traceLogA(  "proxyOverride is %s",  pUsrInfo->proxyOverride  );							//		???<local>?????????????????
	 traceLogA(  "AutoConfigURL is %s",  pUsrInfo->autoConfigUrl  );
#endif

	 return  0;
}


 extern  "C"  int  printPcNetworkProp(  QY_PCNETWORK_PROPU  *  p  )
{
#if  0
	 switch  (  p->uiType  )  {
			 case  CONST_pcNetworkPropType_adapter:
			   	   #ifdef		__DEBUG__
								printPcAdapterProp(  &p->adapter  );
				   #endif
				   break;
			 case  CONST_pcNetworkPropType_proxy:
			   	   #ifdef		__DEBUG__
								printQwmUsrInfo(  &p->usrInfo  );
				   #endif
				   break;
			 case  CONST_pcNetworkPropType_computer:
				   traceLogA((char*)"winDir is %s",  p->computer.winDir  );
				   traceLogA((char*)"activeComputerName is %s",  p->computer.activeComputerName  );
				   traceLogA((char*)"computerName is %s",  p->computer.computerName  );
				   break;
			 case  CONST_pcCommType_windowsUpdatePolicy:
				   traceLogA((char*)"auOptions is %d",  p->windowsUpdatePolicy.AUOptions  );
				   break;
			 default:
					break;
					
	 }
#endif 

	 return  0;
}




#endif


 QY_DMITEM  CONST_netShareTypeTable[]  =
{
#ifndef  __WINCE__
	{	STYPE_DISKTREE,			(TCHAR*)_T(  "Disk Drive"  ),		},
	{	STYPE_PRINTQ,			(TCHAR*)_T(  "Print Queue"  ),		},
	{	STYPE_DEVICE,			(TCHAR*)_T(  "Communication device"  ),	},
	{	STYPE_IPC,				(TCHAR*)_T(  "IPC"  ),					},
	//  {	STYPE_TEMPORARY,		(TCHAR*)_T(  "Temporary"  ),			},
	{	STYPE_SPECIAL,			(TCHAR*)_T(  "Special"  ),				},
#endif
	{	-1,														},
};




 extern  "C"  int  printPcCommU(  QY_PC_COMMU  *  pPcCommU  )
{
#ifndef  __DEBUG__
	     return  0;
#else
		 int	i;

		 //  traceLogA(  "uiType is %S, ?%d?",  qyGetDesByType1(  CONST_pcCommTypeTable,  pPcCommU->uiType  ),  pPcCommU->head.cnt  );
#if  0
		 switch  (  pPcCommU->uiType  )  {
			     case  CONST_pcCommType_process:  {
					   QY_PROCESS_PROP  *  pProcess  =  NULL;
					   traceLogA(  (char*)"??: %d, OS: %s, winDir is %s",  pPcCommU->head.uiLangId,  qyGetDesByType1(  CONST_qyPlatformTable,  pPcCommU->head.iPlatformId  ),  pPcCommU->head.winDir   );
					   traceLogA((char*)"?%d???",  pPcCommU->processesInfo.cnt  );
					   for  (  i  =  0;  i  <  (  int  )pPcCommU->processesInfo.cnt;  i  ++  )  {
						    pProcess  =  &pPcCommU->processesInfo.mems[i];
						    traceLogA((char*)"??%d: %s %s",  pProcess->dwPid,  pProcess->appPath,  pProcess->cmdLine  );
					   }
					   }
					   break;
				 case  CONST_pcCommType_eventLog:  {
					   QY_EVENTLOG_PROP	*	pEventLog  =  NULL;
					   for  (  i  =  0;  i  <  (  int  )pPcCommU->eventLogsInfo.cnt;  i  ++  )  {
						     pEventLog  =  &pPcCommU->eventLogsInfo.mems[i];
							 //printEventLogProp(  pEventLog  );
					   }
					   }
					   break;
				 case  CONST_pcCommType_usrInfo:  {
					   QY_PCUSR_PROP	*	pUsrProp  =  NULL;
					   for  (  i  =  0;  i  <  (  int  )pPcCommU->head.cnt;  i  ++  )  {
						    pUsrProp  =  &pPcCommU->usrInfos.mems[i];
							traceLogA((char*)"usrName is %s, %s",  pUsrProp->usrName,  pUsrProp->ucbDisabled  ?  "????"  :  ""  );
					   }
						}
					   break;
				 case  CONST_pcCommType_registryVal:  {
					   QY_PC_REGISTRYVAL  *  pVal;
					   for  (  i  =  0;  (  unsigned  int  )i  <  pPcCommU->head.cnt;  i  ++  )  {
						    pVal  =  &pPcCommU->registryVals.mems[i];
							traceLogA((char*)"registryVal[%d]: ruleId is [%d], szSidKey is [%s], usrName is [%S],  ucFlg is %d, cfgName is [%S]",  i,  pVal->iRuleId,  pPcCommU->registryVals.szSidKey,  pPcCommU->registryVals.wUsrName,  pVal->ucFlg,  pVal->wCfgName  );
					   }
						}
					   break;
				 case  CONST_pcCommType_netFlow:  {
					   QY_PCNETFLOW_PROP  *  pProp;
					   for  (  i  =  0;  (  unsigned  int  )i  <  pPcCommU->head.cnt;  i  ++  )  {
						    pProp  =  &pPcCommU->netFlows.mems[i];
							traceLogA((char*)"dwIndex is %d,  dwType is %d, dwSpeed is %d, dwInSpeed is %d, dwOutSpeed  is %d, dwPhysAddrLen is %d, bPhysAddr is %s",
								pProp->dwIndex,  pProp->dwType,  pProp->dwSpeed,  pProp->dwInSpeed,  pProp->dwOutSpeed,  pProp->dwPhysAddrLen,  pProp->bPhysAddr  );

					   }					   
						}
					   break;
				 case  CONST_pcCommType_netShare:  {
					   QY_PCNETSHARE_PROP  *	pProp;
					   for  (  i  =  0;  (  unsigned  int  )i  <  pPcCommU->head.cnt;  i  ++  )  {
						    pProp  =  &pPcCommU->netShares.mems[i];
							traceLogA((char*)"netname is %S,  type is %S,  path is %S",  pProp->shi502_netname,  qyGetDesByType1(  CONST_netShareTypeTable,  pProp->shi502_type  ),  pProp->shi502_path  );
					   }
						}
					   break;
				 default:
						break;
		 }
#endif 

		 return  0;
#endif

}



#if  0  //  2011/09/22
  static  int  tmpHandler_getQwmMacsByIpHlp(  void  *  p0,  void  *  p1,  QY_PCADAPTER_INFO  *  pPcAdapterInfo  )
{
	QWM_MACS_INFO  *  pMacsInfo	=	(  QWM_MACS_INFO  *  )p1;

	//  printPcAdapterProp(  (  QY_PCADAPTER_PROP  *  )pPcAdapterInfo  );

	if  (  pPcAdapterInfo->uiAdapterType  ==  MIB_IF_TYPE_ETHERNET  )  {
		if  (  bMacValid(  pPcAdapterInfo->mac  )  )  {
			if  (  pMacsInfo->nMacs  <  mycountof(  pMacsInfo->macs  )  )  {
				safeStrnCpy(  pPcAdapterInfo->mac,  (  char  *  )pMacsInfo->macs[pMacsInfo->nMacs],  sizeof(  pMacsInfo->macs[pMacsInfo->nMacs]  )  );
				pMacsInfo->nMacs  ++  ;		 
			}
		}
	}

	 return  0;
}

 extern  "C"  int  getQwmMacsByIpHlp(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  )
{
	 int	iErr	=	-1;

	 if  (  !pMacsInfo  )  goto  errLabel;

	 memset(  pMacsInfo,  0,  sizeof(  pMacsInfo[0]  )  );
	 if  (  enumPcAdaptersByIpHlp(  0,  pEnv,  (  PF_commonHandler  )tmpHandler_getQwmMacsByIpHlp,  0,  pMacsInfo  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
}
#endif

 BOOL  bUsbNetworkCard(  char  *  devIdStr  )
{
	//  BOOL				bRet					=	FALSE;

	char			*	CONST_usbStorPrefix		= (char*)"usb";
	char			*   p						=   NULL;
	int					i;

#ifdef  __DEBUG__	//  for  test
		//  CONST_usbStorPrefix  =  "pci";
#endif

	 if  (  _strnicmp(  devIdStr,  CONST_usbStorPrefix,  strlen(  CONST_usbStorPrefix  )  )  )  return  FALSE;
	 
	 return  TRUE;
}


  //  2011/09/22. 增加了对usb网卡的过滤。但是如果没有其他的网卡，则有usb网卡也是要取的
  //
  static  int  tmpHandler_getQwmMacsByIpHlp(  void  *  p0,  void  *  p1,  QY_PCADAPTER_INFO  *  pPcAdapterInfo  )
{
	COMMON_PARAM	*	pCommonParam0  =  (  COMMON_PARAM  *  )p0;
	QWM_MACS_INFO	*	pMacsInfo	=	(  QWM_MACS_INFO  *  )p1;

	BOOL			&	bUseUsb  =  *(  BOOL  *  )pCommonParam0->p0;
	BOOL			&	bUseRadio  =  *(  BOOL  *  )pCommonParam0->p1;
	//

	//  printPcAdapterProp(  (  QY_PCADAPTER_PROP  *  )pPcAdapterInfo  );

	if  (  !bUseUsb  )  {
		if  (  bUsbNetworkCard(  pPcAdapterInfo->devIdStr  )  )  return  0;
	}

	if  (  pPcAdapterInfo->uiAdapterType  !=  MIB_IF_TYPE_ETHERNET  )  {
		if  (  pPcAdapterInfo->uiAdapterType  !=  IF_TYPE_IEEE80211  )  return  0;

		if  (  !bUseRadio  )  return  0;		
	}

	{
		if  (  bMacValid(  pPcAdapterInfo->mac  )  )  {
			if  (  pMacsInfo->nMacs  <  mycountof(  pMacsInfo->macs  )  )  {
				safeStrnCpy(  pPcAdapterInfo->mac,  (  char  *  )pMacsInfo->macs[pMacsInfo->nMacs],  sizeof(  pMacsInfo->macs[pMacsInfo->nMacs]  )  );
				pMacsInfo->nMacs  ++  ;		 
			}
		}
	}

	 return  0;
}

 extern  "C"  int  getQwmMacsByIpHlp(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  )
{
	 int	iErr	=	-1;

	 if  (  !pMacsInfo  )  goto  errLabel;

	 memset(  pMacsInfo,  0,  sizeof(  pMacsInfo[0]  )  );

	 BOOL			bUseUsb;bUseUsb = FALSE;
	 BOOL			bUseRadio;bUseRadio = FALSE;
	 COMMON_PARAM	commonParam0;
	 MACRO_makeCommonParam3(  &bUseUsb,  &bUseRadio,  0,  commonParam0  );

	 if  (  enumPcAdaptersByIpHlp(  0,  pEnv,  (  PF_commonHandler  )tmpHandler_getQwmMacsByIpHlp,  &commonParam0,  pMacsInfo  )  )  goto  errLabel;

	 if  (  !pMacsInfo->nMacs  )  {
		 bUseUsb  =  TRUE;
		 if  (  enumPcAdaptersByIpHlp(  0,  pEnv,  (  PF_commonHandler  )tmpHandler_getQwmMacsByIpHlp,  &commonParam0,  pMacsInfo  )  )  goto  errLabel;
	 }

	 if  (  !pMacsInfo->nMacs  )  {
		 bUseUsb  =  FALSE;
		 bUseRadio  =  TRUE;
		 if  (  enumPcAdaptersByIpHlp(  0,  pEnv,  (  PF_commonHandler  )tmpHandler_getQwmMacsByIpHlp,  &commonParam0,  pMacsInfo  )  )  goto  errLabel;
	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}


 extern  "C"  void  getQwmMacs(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  )	//  ???????g_bIsWinNT?????????????????qwmPublic??
{
	 int	iErr	=	-1;

	 if  (  !pEnv  )  return;
	 if  (  !pMacsInfo  )  return;


	 switch  (  pEnv->iPlatformId  )  {
			 case  CONST_qyPlatform_win32:
			 case  CONST_qyPlatform_win95:
				   goto  errLabel;
			 case  CONST_qyPlatform_win98:
			 case  CONST_qyPlatform_winme:
				 {	
					 static  BOOL				bMacsGot	=	FALSE;
					 static  QWM_MACS_INFO		macsInfo;
		
					 if  (  !bMacsGot  )  {
						 memset(  pMacsInfo,  0,  sizeof(  QWM_MACS_INFO  )  );
						 getQwmMacsBySnmp(  pMacsInfo  );
						 if  (  pMacsInfo->nMacs  )  {
							 bMacsGot  =  TRUE;
							 memcpy(  &macsInfo,  pMacsInfo,  sizeof(  QWM_MACS_INFO  )  );
						 }
						 }
					 else  {
						   memcpy(  pMacsInfo,  &macsInfo,  sizeof(  QWM_MACS_INFO  )  );
					 }
	 			 }
				   break;
			 case  CONST_qyPlatform_winnt:
			 case  CONST_qyPlatform_win2k:
				   getQwmMacsBySnmp(  pMacsInfo  );					 
				   break;
			 case  CONST_qyPlatform_winxp:
			 case  CONST_qyPlatform_win2003:
			 case  CONST_qyPlatform_winVista:
			 default:
				     if  (  getQwmMacsByIpHlp(  pEnv,  pMacsInfo  )  )  goto  errLabel;
				     break;
	 }
	 iErr  =  0;
errLabel:

	 if  (  iErr  )  {
		 if  (  pMacsInfo  )  memset(  pMacsInfo,  0,  sizeof(  pMacsInfo[0]  )  );
		 traceLogA((char*)"getQwmMacs(  ) failed"  );
	 }

	 //  2011/09/22. 如果网卡被禁用，那么就很难修复了，所以这里伪造一个mac,以方便客户端运行下去
	 //  因此如果服务器装在本机的话，就可以利用127.0.0.1来卸载客户端
	 if  (  pMacsInfo  &&  !pMacsInfo->nMacs  )  {
		 safeStrnCpy((char*)"ba9876543210",  (  char  *  )pMacsInfo->macs[0],  mycountof(  pMacsInfo->macs[0]  )  );
		 pMacsInfo->nMacs  =  1;
	 }
	 
	 return;
}

 extern  "C"  void  getQwmSortedMacs(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  )
{

	 if  (  !pMacsInfo  )  return;

	 getQwmMacs(  pEnv,  pMacsInfo  );
	 sortQwmMacs(  pMacsInfo  );  

	 return;

}

 int mystricmp(  const char *string1,  const TCHAR *t_string2  )
{
	TCHAR	tBuf[2048]	=	_T(  ""  );

	if  (  !myUtf82TChar(  (  char  *  )string1,  tBuf,  mycountof(  tBuf  )  )  )  return  -1;

	return  _tcsicmp(  tBuf,  t_string2  );
}


  extern  "C"  QY_DMITEM  CONST_qyGrpTable[]  =
{
	{	CONST_qyGrpBit_administrators,		(TCHAR*)_T(  "Administrators"  ),	},
	{	CONST_qyGrpBit_system,				(TCHAR*)_T(  "System"  ),			},
	{	-1,									NULL,				},
};

 extern  "C"  int  qyGetProcessGrps(  int  *  pFlg  )
{
	 int							iErr				=	-1;
	 DWORD							dwSize				=	0;
	 TOKEN_GROUPS				*	pSidInfo			=	NULL;
	 DWORD							i;
	 HANDLE							hToken				=	NULL;
	 unsigned  char					ucbTokenOpen		=	FALSE;
	 TOKEN_INFORMATION_CLASS		tic					=	TokenGroups;  
	 int							iType;
	 int							flg					=	0;				//  ÏÈ½«±êÖ¾Î»Çå¿Õ
	 
	 if  (  !myOpenProcessToken(  GetCurrentProcess(  ),  TOKEN_QUERY,  &hToken  )  )  goto  errLabel;
	 ucbTokenOpen  =  TRUE;

	 dwSize  =  0;
	 myGetTokenInformation(  hToken,  tic,  NULL,  dwSize,  &dwSize  );
	 //  pSidInfo  =  (  PTOKEN_GROUPS  )new  BYTE[dwSize];
	 pSidInfo  =  (  PTOKEN_GROUPS  )mymalloc(  dwSize  );
	 if  (  !pSidInfo  )  goto  errLabel;
	 if  (  !myGetTokenInformation(  hToken,  tic,  pSidInfo,  dwSize,  &dwSize  )  )  {
		 traceLogA((char*)"GetTokenInfomation Error %u\n",  GetLastError(  )  );
		 goto  errLabel;
	 }
	 if  (  !pSidInfo->GroupCount  )  {
		 traceLogA((char*)"\tNone!\n"  );
		 iErr  =  0;
		 goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  pSidInfo->GroupCount;  i  ++  )  {
		  SID_NAME_USE	sidType;
		  TCHAR			nameBuf[256];
		  TCHAR			domainBuf[256];
		  DWORD			dwNameSize			=  sizeof(  nameBuf  )  /  sizeof(  nameBuf[0]  );
		  DWORD			dwDomainSize		=  sizeof(  domainBuf  )  /  sizeof(  domainBuf[0]  );
		  DWORD			dwAttr  =  0;

		  if  (  !myLookupAccountSid(  NULL,  pSidInfo->Groups[i].Sid,	nameBuf,  &dwNameSize,  domainBuf,  &dwDomainSize,  &sidType  )  )  {
			  if  (  GetLastError(  )  ==  ERROR_NONE_MAPPED  )  lstrcpyn(  nameBuf,  _T(  "NONE_MAPPED"  ),  sizeof(  nameBuf  )  /  sizeof(  nameBuf[0]  )  );
			  else  traceLogA((char*)"LoopupAccountSid Error %u\n",  GetLastError(  )  );
			  continue;
		  }
		
		  dwAttr  =  pSidInfo->Groups[i].Attributes;

		  //  traceLogA(  "\t%12s \\%-20s \t%s\n",  domainBuf,  nameBuf,  (  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  ?  "[DENY]"  :  ""  );
		  
		  if  (  !(  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  )  {
			  iType  =  qyGetTypeByDes(  CONST_qyGrpTable,  nameBuf  );
			  if  (  iType  !=  -1  )  flg  |=  1  <<  iType;
		  }
	 }

	 for  (  i  =  0;  CONST_qyGrpTable[i].type  !=  -1;  i  ++  )  {
		  if  (  flg  &  (  1  <<  CONST_qyGrpTable[i].type  )  )
			  traceLogA((char*)"\tbelongs to %s",  CONST_qyGrpTable[i].des  );
	 }

	 *pFlg  =  flg;
	 iErr  =  0;

errLabel:

	 //  if  (  pSidInfo  )  delete  []  (  LPBYTE  )pSidInfo;
	 if  (  pSidInfo  )  free(  pSidInfo  );
	 if  (  ucbTokenOpen  &&  hToken  )  CloseHandle(  hToken  );

	 return  iErr;

}
