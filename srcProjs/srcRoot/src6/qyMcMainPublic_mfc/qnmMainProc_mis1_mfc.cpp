

#include	"stdafx.h"
#include	<stdio.h>
#include	"qyMcMainCommon.h"

#include	"QyRcdset.h"

#include	"qycusrescommon.h"

 //  2013/02/16
  QY_DMITEM  CONST_qwmDevTypeTable[]  =
{
	{	CONST_qwmDevType_wpd,				_T(  "Portable device"  ),  },
	{	CONST_qwmDevType_mobileDevice,		_T(  "Mobile device"  ),  },
	{	CONST_qwmDevType_usbNetworkCard,	_T(  "Usb network card"  ),  },
	{	-1,										},
};

 __declspec(  dllexport  )  BOOL  bPcOnline(  char  *  lastCommTime  )
{
	char	tmpBuf[CONST_qyTimeLen  +  1];

	getCurTime(  tmpBuf  );
	return  b2TimeNear(  tmpBuf,  lastCommTime,  CONST_qnmMaxLastCommTime  );		//  注意这里,用15分钟来判断是否离线

}						 


 //  2013/02/16
 __declspec(  dllexport  )  void  *  displayQnmElement(  void * pVoid,  void  *  pQueryParam,  void  *  pQyRcdset,  int  nSubItem,  TCHAR * output,  unsigned  int  size  )
{
	 int				iErr		=	-1;
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 QY_MC_QUERY	*	pQuery		=	(  QY_MC_QUERY  *  )pQueryParam;
	 CQyRcdset		*	pRecordset  =	(  CQyRcdset  *  )pQyRcdset;
	 CString			tmpStr;
	 int				iType;
	 TCHAR			*	pStopString;
	 char				buf[1024];
	 char				tmpBuf[1024];
	 QY_DMITEM		*	pTable;

	 
	 //  traceLogA(  "displayQnmElement: 第%d个单元",  nSubItem  );
	 //  2004/04/17增加对Null值的判断
	 if  (  pRecordset->IsFieldNull(  pRecordset->m_arrayValue[nSubItem]  )  )  {
		 _sntprintf(  output,  size,  _T(  ""  )  );
		 iErr  =  0;  goto  errLabel;
	 }

	 switch  (  pQuery->columns[nSubItem].type  )  {
			 case  CONST_qyColumnDisplayType_long:  
				   _sntprintf(  output,  size,  _T(  "%d"  ),  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  );
				   break;
			 case  CONST_qyColumnDisplayType_uLong:		//  2005/10/04
				   _sntprintf(  output,  size,  _T(  "%u"  ),  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  );
				   break;
			 case  CONST_qyColumnDisplayType_bool:  
				   tmpStr  =  *(  CString  *  )pRecordset->m_arrayValue[nSubItem];
				   
				   MACRO_CStringTrim(  tmpStr  );
				   if  (  !tmpStr.GetLength(  )  )  _sntprintf(  output,  size,  _T(  ""  )  );						
				   else  _sntprintf(  output, size,  _T(  "%s"  ),  _tcstol(  tmpStr.GetBuffer(  0  ),  &pStopString,  10  )  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_n  )  );
				   
				   break;
			 case  CONST_qyColumnDisplayType_iBool:  {
				   int		iBool  =	*(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  ); 
				   _sntprintf(  output,  size,  _T(  "%s"  ),  iBool  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_y  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_n  )  );
				   }
				   break;
			 case  CONST_qyColumnDisplayType_dwRegVal:  {
				   DWORD		dwVal  =	*(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  ); 
				   if  (  dwVal  ==  CONST_dwRegVal_invalid  )  _sntprintf(  output,  size,  _T(  ""  )  );
				   else  _sntprintf(  output,  size,  _T(  "%d"  ),  dwVal  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_eventType:  {
	 	 		   long		eventType	=  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  ); 
		 		   TCHAR  *  ptr			=  _T(  ""  );

		 		   ptr  =  qyGetDesByType1(  pQyMc->pQnmEventTypeTable0,  eventType  );
		 		   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  ptr  )  );					
		 			 }
					break;
			 case  CONST_qyColumnDisplayType_time:  {
				   CString  eventTime;
				
				   eventTime  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   if  (  eventTime  ==  CString(  CONST_qyNullTime  )  )  eventTime  =  CString(  ""  );
				   myTChar2Str(  eventTime.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
				   if  (  !qyDisplayTime(  buf,  tmpBuf,  sizeof(  tmpBuf  )  )  )  tmpBuf[0]  =  0;
				   myStr2TChar(  tmpBuf,  output,  size  ); 
					}
				   break;
			 case  CONST_qyColumnDisplayType_lTime:  {
				   CString  eventTime;
				
				   eventTime  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   if  (  eventTime  ==  CString(  CONST_qyNullTime  )  )  eventTime  =  CString(  ""  );
				   myTChar2Str(  eventTime.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
				   if  (  !qyDisplaylTime(  buf,  tmpBuf,  sizeof(  tmpBuf  )  )  )  tmpBuf[0]  =  0;
				   myStr2TChar(  tmpBuf,  output,  size  ); 
				   }
				   break;
			 case  CONST_qyColumnDisplayType_bOnLine:  {
				   CString  eventTime;
				   //
				   eventTime  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   //
				   if  (  eventTime.GetLength(  )  !=  CONST_qyTimeLen  ||  eventTime  ==  CString(  CONST_qyNullTime  )  )  _sntprintf(  output,  size,  _T(  ""  )  );
				   else  {
					     myTChar2Str(  eventTime.GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
						 _sntprintf(  output,  size,  bPcOnline(  buf  )  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_online  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_offline  )  );
				   }				   
				    }				   
				   break;
			 case  CONST_qyColumnDisplayType_ip12:  {
				   char  ipBuf[CONST_qyMaxIpLen  +  1];

				   myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyIp12ToStd(  buf,  ipBuf  )  ?  ipBuf  :  ""  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_mac:  
				   //  myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ), tmpBuf,  sizeof(  tmpBuf  )  );
				   //  _strlwr(  tmpBuf  );
				   //  myStr2TChar(  tmpBuf,  output,  size  );
				   tmpStr  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   tmpStr.MakeLower(  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
				   //  if  (  !strcmpi(  output,  CONST_qyNullMac  )  )  output[0]  =  0;	//  2005/10/10, 将qyNullMac的显示赋为空
				   break;
			 case  CONST_qyColumnDisplayType_lwrStr:
				   //  lstrcpyn(  output,  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  ),  size  );
				   //  myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ), output,  size  );
				   //  _strlwr(  output  );
				   tmpStr  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   tmpStr.MakeLower(  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
				   break;
			 case  CONST_qyColumnDisplayType_uprStr:
				   //  lstrcpyn(  output,  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  ),  size  );
				   //  myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ), output,  size  );
				   //  _strupr(  output  );
				   tmpStr  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   tmpStr.MakeUpper(  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
				   break;
			 case  CONST_qyColumnDisplayType_pcSp:
				   //  lstrcpyn(  output,  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  ),  size  );
				   //  myTChar2Str(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ), output,  size  );
				   //  _strupr(  output  );
				   //  if  (  !strcmp(  output,  CONST_qnmNullPcSp  )  )  _snprintf(  output,  size,  ""  );
				   tmpStr  =  *(  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  );
				   tmpStr.MakeUpper(  );
				   if  (  tmpStr  ==  CString(  CONST_qnmNullPcSp  )  )  tmpStr  =  CString(  ""  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  tmpStr  );			   
				   break;
			 case  CONST_qyColumnDisplayType_rasCmd:  {
				   unsigned  char  ucRasCmd;
		 		   TCHAR  *  ptr  =  _T(  ""  );

				   if  (  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetLength(  )  )  {
					   myTChar2Str( (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  buf,  sizeof(  buf  )  ); 
				   	   ucRasCmd  =  buf[0];
		 		   	   ptr  =  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmRasCmdTable  ),  ucRasCmd  );
		 		   }
		 		   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  ptr  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_devCmd:  {
				   unsigned  char  ucCmd;
				   TCHAR  *  ptr  =  _T(  ""  ); 
				   
				   if  (  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetLength(  )  )  {
				   	   myTChar2Str( (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  buf,  sizeof(  buf  )  ); 
				   	   ucCmd  =  buf[0];
		 		   	   ptr  =  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmDevCmdTable0  ),  ucCmd  );
		 		   }
		 		   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  ptr  )  );				
					}
				   break;	
			 case  CONST_qyColumnDisplayType_netFlowRule:  {	//  未完成
				   unsigned  char		ucCmd;
				   TCHAR			*	ptr				=	_T(  ""  ); 
				   unsigned  int		uiWarnPercent	=	0;
				   
				   if  (  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetLength(  )  >=  5  )  {
				   	   myTChar2Str( (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  buf,  sizeof(  buf  )  ); 
					   ucCmd  =  buf[5];
					   buf[5]  =  0;
		 		   	   ptr  =  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qnmDevCmdTable0  ),  ucCmd  );
					   uiWarnPercent  =  atol(  buf  );
					   _sntprintf(  output,  size,  _T(  "%.3f%% | %s"  ),  uiWarnPercent  /  (  float  )CONST_fakedFactor_percentOfBand,  ptr  );
		 				}
				   else  
					   _sntprintf(  output,  size,  _T(  ""  )  );				
					}
				   break;
			 case  CONST_qyColumnDisplayType_platformId:  {
				   pTable  =  CONST_qyPlatformTable;
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_assetType:  {
				   pTable  =  CONST_assetTypeTable;
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString  (  qyGetDesByType1(  pTable,  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_langId:  {
				   pTable  =  CONST_qyLangTable;
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  )  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_jqlx:  {
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_jqlxTable  );
				   iType  =  _tcstol(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  &pStopString,  10  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_ruleCmd:  {
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
					}
				   break;
			 case  CONST_qyColumnDisplayType_adapterType:  
				   pTable  =  CONST_adapterTypeTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%d %s"  ),  iType,  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_pcNetworkPropType:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_snmpBool:  {
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_snmpBoolTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   	}
				    break;
			 case  CONST_qyColumnDisplayType_pcAdapterStatus:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcAdapterStatusTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_iRootKey:
				   pTable  =  CONST_iRootKeyTable_abbr;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_regType:
				   pTable  =  CONST_regTypeTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_pcEventLogType:
				   pTable  =  CONST_pcEventLogTypeTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_pcEventId:
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%d"  ),  iType  &  0xffff  );
				   break;
			 case  CONST_qyColumnDisplayType_pcCommType:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcCommTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_tcpState:
				   pTable  =  CONST_tcpStateTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 //case  CONST_qyColumnDisplayType_pcProcessRuleType:
			//	   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_pcProcessRuleTypeTable  );
			//	   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
			//	   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
			//	   break;
			 case  CONST_qyColumnDisplayType_qyStatus:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyStatusTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_withFactor:						//  2006/05/30
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%.3f"  ),  (  float  )iType  /  CONST_fakedFactor_percentOfBand  );
				   break;
			 case  CONST_qyColumnDisplayType_netShareType:
				   pTable  =  CONST_netShareTypeTable;
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_qwmDevType:  //  2011/09/21
				   pTable  =  CONST_qwmDevTypeTable;	//  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_jqlxTable  );
				   iType  =  _tcstol(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  &pStopString,  10  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_idStr: {
				   CString str  =  *(  CString  *  )pRecordset->m_arrayValue[nSubItem];
				   char idStr[CONST_qyMessengerIdStrLen  +  1]  =  "";
				   myTChar2Utf8(str.GetBuffer(0),  idStr,  mycountof(  idStr  )  );
				   QY_MESSENGER_ID idInfo={0};
				   idStr2Info(idStr,&idInfo);
				   //
				   //_sntprintf(  output,  size,  _T(  "%u"  ),  _tcstol(  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  ),  &pStopString,  10  )  );
				   _sntprintf(  output,  size,  _T(  "%I64u"  ),  idInfo.ui64Id  );
													}
				   break;
			 case  CONST_qyColumnDisplayType_objType:				 				   
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_imTaskType:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_usRunningStatus:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_usRunningStatusTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_ruleType:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleTypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_imGrpSubtype:
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imGrpSubtypeTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
			 case  CONST_qyColumnDisplayType_imGrpMemRole:  //  2015/07/28
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imGrpMemRoleTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;
				   //
			 case  CONST_qyColumnDisplayType_imObjRole:  //  2015/07/28
				   pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imObjRoleTable  );
				   iType  =  *(  (  long  *  )pRecordset->m_arrayValue[nSubItem]  );
				   _sntprintf(  output,  size,  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  iType  )  )  );
				   break;

			 default:
				 	 _sntprintf(  output,  size,  _T(  "%s"  ),  (  (  CString  *  )pRecordset->m_arrayValue[nSubItem]  )->GetBuffer(  0  )  );
					 unescapeTStr(  output,  size  );
					 break;
	 }
		
	 iErr  =  0;

errLabel:

	
	 return  !iErr  ?  output  :  NULL;

}
