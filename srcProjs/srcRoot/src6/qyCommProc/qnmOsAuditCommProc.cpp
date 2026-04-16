
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<iprtrmib.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"qySnmpCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmPcComm.h"
#include	"qnmCustom.h"
#include	"qnmAssetsCommProc.h"

 QY_DMITEM  CONST_iRootKeyTable[]  =
{
	{	(  long  )HKEY_LOCAL_MACHINE,	(TCHAR*)_T(  "HKEY_LOCAL_MACHINE(  HKLM  )"  ),	},
	{	(  long  )HKEY_USERS,			(TCHAR*)_T(  "HKEY_USERS(  HKU  )\\*"  ),		},
	{	(  long  )HKEY_CLASSES_ROOT,	(TCHAR*)_T(  "HKEY_CLASSES_ROOT(  HKCR  )"  ),	},
	{	-1,					NULL,										},
};

 QY_DMITEM  CONST_iRootKeyTable_abbr[]  =
{
	{	(  long  )HKEY_LOCAL_MACHINE,	(TCHAR*)_T(  "HKLM"  ),	},
	{	(  long  )HKEY_USERS,			(TCHAR*)_T(  "HKU\\*"  ),		},
	{	(  long  )HKEY_CLASSES_ROOT,	(TCHAR*)_T(  "HKCR"  ),	},
	{	-1,					NULL,										},
};

 QY_DMITEM  CONST_iRootKeyTable_full[]  =
{
	{	(  long  )HKEY_LOCAL_MACHINE,	(TCHAR*)_T(  "HKEY_LOCAL_MACHINE"  ),	},
	{	(  long  )HKEY_USERS,			(TCHAR*)_T(  "HKEY_USERS"  ),		},
	{	(  long  )HKEY_CLASSES_ROOT,	(TCHAR*)_T(  "HKEY_CLASSES_ROOT"  ),	},
	{	(  long  )HKEY_CURRENT_USER,	(TCHAR*)_T(  "HKEY_CURRENT_USER"  ),	},
	{	-1,				},
};


  QY_DMITEM  CONST_regTypeTable[]  =
{
	{	REG_NONE,						(TCHAR*)_T(  ""  ),	/*(TCHAR*)_T(  "REG_NONE"  ),*/			},		//               ( 0 )   // No value type
	{	REG_SZ,							(TCHAR*)_T(  "REG_SZ"  ),							},		//               ( 1 )   // Unicode nul terminated string
	{	REG_EXPAND_SZ,					(TCHAR*)_T(  "REG_EXPAND_SZ"  ),					},		//               ( 2 )   // Unicode nul terminated string
																							// (with environment variable references)
	{	REG_BINARY,						(TCHAR*)_T(  "REG_BINARY"  ),						},		//               ( 3 )   // Free form binary
	{	REG_DWORD,						(TCHAR*)_T(  "REG_DWORD"  ),						},		//               ( 4 )   // 32-bit number
	//	REG_DWORD_LITTLE_ENDIAN																//				 ( 4 )   // 32-bit number (same as REG_DWORD)
	{	REG_DWORD_BIG_ENDIAN,			(TCHAR*)_T(  "REG_DWORD_BIG_ENDIAN"  ),				},		//		         ( 5 )   // 32-bit number
	{	REG_LINK,						(TCHAR*)_T(  "REG_LINK"  ),							},      //               ( 6 )   // Symbolic Link (unicode)
	{	REG_MULTI_SZ,					(TCHAR*)_T(  "REG_MULTI_SZ"  ),						},		//               ( 7 )   // Multiple Unicode strings
	{	REG_RESOURCE_LIST,				(TCHAR*)_T(  "REG_RESOURCE_LIST"  ),				},		//               ( 8 )   // Resource list in the resource map
	{	REG_FULL_RESOURCE_DESCRIPTOR,	(TCHAR*)_T(  "REG_FULL_RESOURCE_DESCRIPTOR"  ),		},		//				 ( 9 )  // Resource list in the hardware description
	{	REG_RESOURCE_REQUIREMENTS_LIST,	(TCHAR*)_T(  "REG_RESOURCE_REQUIREMENTS_LIST"  ),	},		//				 ( 10 )
	{	-1,								},
};


 QY_DMITEM	CONST_pcEventLogTypeTable[]  =  
{
	{	EVENTLOG_SUCCESS,				(TCHAR*)_T(  "成功"  ),		},
	{	EVENTLOG_ERROR_TYPE,			(TCHAR*)_T(  "错误"  ),		},
	{	EVENTLOG_WARNING_TYPE,			(TCHAR*)_T(  "警告"  ),		},
	{	EVENTLOG_INFORMATION_TYPE,		(TCHAR*)_T(  "信息"  ),		},
	{	EVENTLOG_AUDIT_SUCCESS,			(TCHAR*)_T(  "审计成功"  ),	},
	{	EVENTLOG_AUDIT_FAILURE,			(TCHAR*)_T(  "审计失败"  ),	},
	{	-1,								NULL,		},
};



 QY_DMITEM  CONST_tcpStateTable[]  =
{
	{	MIB_TCP_STATE_CLOSED,		(TCHAR*)_T(  "CLOSED"  ),		},
	{	MIB_TCP_STATE_LISTEN,		(TCHAR*)_T(  "LISTENING"  ),	},
	{	MIB_TCP_STATE_SYN_SENT,		(TCHAR*)_T(  "SYN_SENT"  ),		},
	{	MIB_TCP_STATE_SYN_RCVD,		(TCHAR*)_T(  "SYN_RCVD"  ),		},
	{	MIB_TCP_STATE_ESTAB,		(TCHAR*)_T(  "ESTABLISHED"  ),	},
	{	MIB_TCP_STATE_FIN_WAIT1,	(TCHAR*)_T(  "FIN_WAIT1"  ),	},
	{	MIB_TCP_STATE_FIN_WAIT2,	(TCHAR*)_T(  "FIN_WAIT2"  ),	},
	{	MIB_TCP_STATE_CLOSE_WAIT,	(TCHAR*)_T(  "CLOSE WAIT"  ),	},
	{	MIB_TCP_STATE_CLOSING,		(TCHAR*)_T(  "CLOSING"  ),		},
	{	MIB_TCP_STATE_LAST_ACK,		(TCHAR*)_T(  "LAST ACK"  ),		},
	{	MIB_TCP_STATE_TIME_WAIT,	(TCHAR*)_T(  "TIME WAIT"  ),	},
	{	MIB_TCP_STATE_DELETE_TCB,	(TCHAR*)_T(  "DELETE TCB"  ),	},
	//  {		  default:			(TCHAR*)_T(  "<ERR>"  ),		},
	{	-1,  },
};

  extern  "C"  int  printEventLogProp(  QY_EVENTLOG_PROP  *  pEventLog  )
{

	 traceLogA(  (char*)  "RecordNumber is %d",  pEventLog->dwRecordNumber  );
	 traceLogA(  (char*)  "TimeGenerated: %s",  pEventLog->timeGeneratedBuf  );
	 traceLogA(  (char*)  "EventID: %d\n",  pEventLog->dwEventID  &  0xffff  );
	 traceLogA(  (char*)  "EventLogType: %s",  qyGetDesByType1(  CONST_pcEventLogTypeTable,  pEventLog->wEventType  )  );
	 traceLogA(  (char*)  "SourceName: %s\n",  pEventLog->sourceName  );
	 traceLogA(  (char*)  "ComputerName: %s\n",  pEventLog->computerName  );
	 traceLogA(  (char*)  "EventCategory: %d",  pEventLog->wEventCategory  );
	 traceLogA(  (char*)  "EventLogDesc: %s",  pEventLog->eventLogDesc  );

	 return  0;
}

