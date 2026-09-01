
/* 
Winsock Programmer's FAQ: Get MAC Address, SNMP Method Winsock 
      Programmer's FAQ
      Example: How to Get the Ethernet MAC Address, SNMP Method  
      James Marsh writes:
      In my search for an ironclad method of finding the MAC address of the 
      ethernet card of a system, I attempted the NetBIOS method as described in 
      the FAQ, but found this to be unacceptable as some of our customers 
      reportedly didn't use [NetBIOS]. I passed over the RPC method, and found a 
      solution in a page maintained by Stas Khirman and Raz Galili.... They 
      describe a method of using the internal SNMP calls in Windows (NT, 95, and 
      2000 have worked for me) that are used by netstat and other windows 
      utilities, but unfortunately provide no code example for finding the MAC 
      code.
      [Below is] a small program I've written up, so that hopefully other people 
      won't have to go through the same learning curve I did with SNMP. I will 
      also attach a file, snmpapi.cpp, that was written by Stas Khirman and 
      distributed on his web page.
      A great resource for those interested in retrieving system info through 
      this method is http://www.alvestrand.no/objectid/top.html.
*/
//      snmpmac.cpp

#include	"qyPrecomp.h"

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include	<windows.h>
#include	<stdio.h>
#include	"qyCommon.h"
//#include	"qyCommProc.h"

#include	<tchar.h>


#ifndef  __WINCE__
		 #include	<snmp.h>
		 #include	<conio.h>


typedef  BOOL  (  WINAPI  *  pSnmpExtensionInit  )(  IN  DWORD  dwTimeZeroReference,
        										     OUT  HANDLE  *  hPollForTrapEvent,
        										     OUT  AsnObjectIdentifier  *  supportedView  );
typedef  BOOL  (  WINAPI  *  pSnmpExtensionTrap  )(  OUT  AsnObjectIdentifier  *  enterprise,
        										     OUT  AsnInteger  *  genericTrap,
        											 OUT  AsnInteger  *  specificTrap,
        											 OUT  AsnTimeticks  *  timeStamp,
        											 OUT  RFC1157VarBindList  *  variableBindings  );
typedef  BOOL  (  WINAPI  *  pSnmpExtensionQuery  )(  IN  BYTE  requestType,
        											  IN  OUT  RFC1157VarBindList  *  variableBindings,
        											  OUT  AsnInteger  *  errorStatus,
        											  OUT  AsnInteger  *  errorIndex  );
typedef  BOOL  (  WINAPI  *  pSnmpExtensionInitEx  )(  OUT  AsnObjectIdentifier  *  supportedView  );
typedef  VOID  (  WINAPI  *  pSnmpExtensionClose  )(  );

typedef  struct  __asrAdapter_t  {
				 char			mac[12 + 1];
				 unsigned  int  ifInUcastPkts;
				 unsigned  int  ifInNUcastPkts;
}		 ASR_ADAPTER;

#define		MAX_AWM_ADAPTERS			4

typedef  struct  __awm_adapters  {
				 ASR_ADAPTER	Adapter[MAX_AWM_ADAPTERS];
				 int			cnt;
}		 AWM_ADAPTERS;

AWM_ADAPTERS  gAwmAdapters;
 
HINSTANCE		ghDll_InetMib1		=	NULL;
unsigned  char  ucbInetMib1Inited	=	FALSE;		//  inetmib1库是否初始化的标志变量


pSnmpExtensionInit m_Init;
pSnmpExtensionInitEx m_InitEx;
pSnmpExtensionQuery m_Query;
pSnmpExtensionTrap m_Trap;
pSnmpExtensionClose m_Close;
HANDLE PollForTrapEvent;
AsnObjectIdentifier SupportedView;

 extern  "C"  int  qyInitSnmp(  HINSTANCE  *  pInst  )
{
	int	iErr  =  -1;
	
	if  (  !pInst  )  return  -1;

	if  (  !*pInst  )  {
		TCHAR	svLibName[MAX_PATH  +  1];

		if  (  isWinNt(  )  )  {
			if  (  qyFullLibName(  _T(  "inetmib1.dll"  ),  svLibName,  mycountof(  svLibName  )  )  )  return  -1;
			}
		else  if  (  qyFullWinLibName(  _T(  "inetmib1.dll"  ),  svLibName,  mycountof( svLibName  )  )  )  return  -1;

		if  (  !(  ghDll_InetMib1  =  LoadLibrary(  svLibName  )  )  )  return  -1;
		
		*pInst  =  ghDll_InetMib1;
	}

	m_Init		=  NULL;
    m_InitEx	=  NULL;
    m_Query		=  NULL;
    m_Trap		=  NULL;
	m_Close		=  NULL;

    m_Init  =  (pSnmpExtensionInit) GetProcAddress( *pInst, "SnmpExtensionInit");
    m_InitEx  =  (pSnmpExtensionInitEx) GetProcAddress( *pInst,  "SnmpExtensionInitEx");
    m_Query  =  (pSnmpExtensionQuery) GetProcAddress( *pInst,  "SnmpExtensionQuery");
    m_Trap  =  (pSnmpExtensionTrap) GetProcAddress( *pInst, "SnmpExtensionTrap");
	m_Close  =  (pSnmpExtensionClose) GetProcAddress( *pInst, "SnmpExtensionClose");

    if  (  !m_Init(  GetTickCount(  ),  &PollForTrapEvent,  &SupportedView  )  )  goto  errLabel;
	ucbInetMib1Inited  =  TRUE;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		qyExitSnmp(  pInst  );
	}

	return  iErr;

}

 extern  "C"  void qyExitSnmp(  HINSTANCE  *  pInst  )
{
	if  (  m_Close  &&  ucbInetMib1Inited  )  {
		m_Close( );  ucbInetMib1Inited  =  FALSE;
	}
	if  (  ghDll_InetMib1  )  {
		FreeLibrary( ghDll_InetMib1 ); ghDll_InetMib1 = NULL;
	}
	*pInst  =  NULL;

	return;
}


 int initAsrAdapter( ASR_ADAPTER *p )
{
	memset( p, 0, sizeof( ASR_ADAPTER ) );
	return 0;
}

 void exitAsrAdapter( ASR_ADAPTER *p )
{
	memset( p, 0, sizeof( ASR_ADAPTER ) );
	return;
}

 int resetAsrAdapter( ASR_ADAPTER *p )
{
	p->ifInUcastPkts = 0;
	p->ifInNUcastPkts = 0;
	return 0;
}

 int resetAwmAdapters( AWM_ADAPTERS *p )
{
	memset( p, 0, sizeof( AWM_ADAPTERS ) );
	return 0;
}
 

//      snmpapi.cpp
/******************************************************************
*
*      Copyright (C) Stas Khirman 1998.  All rights reserved.         
*                                                                     
*       This program is distributed WITHOUT ANY WARRANTY
*
*******************************************************************/

/*************************************************
*     
*       Reproduction of SNMP.LIB and SNMPAPI.LIB base
*           functions
*
* Author: Stas Khirman (staskh@rocketmail.com)
*
*
* Free software: no warranty; use anywhere is ok; spread the      
* sources; note any modifications; share variations and           
* derivatives (including sending to staskh@rocketmail.com).       
*                                                                     
*
*************************************************/
#include	<snmp.h>

 SNMPAPI  SNMP_FUNC_TYPE  SnmpUtilOidCpy(  OUT  AsnObjectIdentifier  *  DstObjId,
										   IN  AsnObjectIdentifier  *  SrcObjId  )
{
	DstObjId->ids  =  (  UINT  *  )GlobalAlloc(  GMEM_ZEROINIT,  SrcObjId->idLength  *  sizeof(  UINT  )  );
  	if  (  !DstObjId->ids  )  {
    	SetLastError(  1  );
    	return  0;
  	}

  	memcpy(DstObjId->ids,SrcObjId->ids,SrcObjId->idLength*sizeof(UINT));
  	DstObjId->idLength = SrcObjId->idLength;
  
	return  1;

}


 VOID  SNMP_FUNC_TYPE  SnmpUtilOidFree(  IN  OUT  AsnObjectIdentifier  *  ObjId  )
{
	GlobalFree(  ObjId->ids  );
  	ObjId->ids  =  0;
  	ObjId->idLength  =  0;
}

 SNMPAPI  SNMP_FUNC_TYPE  SnmpUtilOidNCmp(  IN  AsnObjectIdentifier  *  ObjIdA,
											IN  AsnObjectIdentifier  *  ObjIdB,
    										IN  UINT  Len  )
{
  UINT CmpLen;
  UINT i;
  int  res;

  CmpLen = Len;
  if(ObjIdA->idLength < CmpLen)
    CmpLen = ObjIdA->idLength;
  if(ObjIdB->idLength < CmpLen)
    CmpLen = ObjIdB->idLength;

  for(i=0;i<CmpLen;i++){
    res = ObjIdA->ids[i] - ObjIdB->ids[i];
    if(res!=0)
      return res;
  }
  return 0;
}

 VOID  SNMP_FUNC_TYPE  SnmpUtilVarBindFree(  IN  OUT  RFC1157VarBind  *  VarBind  )
{
  BYTE asnType;
  // free object name
  SnmpUtilOidFree(&VarBind->name);

  asnType = VarBind->value.asnType;

  if(asnType==ASN_OBJECTIDENTIFIER){
    SnmpUtilOidFree(&VarBind->value.asnValue.object);
  }
  else if(
        (asnType==ASN_OCTETSTRING) ||
        (asnType==ASN_RFC1155_IPADDRESS) ||
        (asnType==ASN_RFC1155_OPAQUE) ||
        (asnType==ASN_SEQUENCE)){
    if(VarBind->value.asnValue.string.dynamic){
      GlobalFree(VarBind->value.asnValue.string.stream);
    }
  }

  VarBind->value.asnType = ASN_NULL;

}


 //  macAddr须提供>12字节的buf, 返回时将macAddr[12]置为0
 int  asrGetMacAddr(  unsigned  char  *  macAddr  )
{
  int iErr = -1;

  UINT					OID_ifEntryType[]	=  {  1, 3, 6, 1, 2, 1, 2, 2, 1, 3  }; 
  UINT					OID_ifEntryNum[]	=  {  1, 3, 6, 1, 2, 1, 2, 1  }; 
  UINT					OID_ipMACEntAddr[]	=  {  1, 3, 6, 1, 2, 1, 2, 2, 1, 6  }; 
  AsnObjectIdentifier	MIB_ifMACEntAddr	=  {  sizeof(OID_ipMACEntAddr) / sizeof(UINT),  OID_ipMACEntAddr  }; 
  AsnObjectIdentifier	MIB_ifEntryType		=  {  sizeof(OID_ifEntryType) / sizeof(UINT),  OID_ifEntryType  }; 
  AsnObjectIdentifier	MIB_ifEntryNum		=  {  sizeof(OID_ifEntryNum) / sizeof(UINT), OID_ifEntryNum  }; 
  RFC1157VarBindList	varBindList; 
  RFC1157VarBind		varBind[2]; 
  AsnInteger			errorStatus; 
  AsnInteger			errorIndex; 
  AsnObjectIdentifier	MIB_NULL			=  {  0, 0  }; 
  int					ret; 
  int					dtmp; 
  int					i					=  0;
  int					j					=  0; 
  bool					found				=  false; 
  char					TempEthernet[13]; 


  /* 初始化用来接收m_Query查询结果的变量列表 */ 
  varBindList.list = varBind; 
  varBind[0].name = MIB_NULL; 
  varBind[1].name = MIB_NULL; 

  /* 在OID中拷贝并查找接口表中的入口数量 */ 
  varBindList.len  =  1;        /* Only retrieving one item */ 
  SNMP_oidcpy(  &varBind[0].name,  &MIB_ifEntryNum  ); 
  ret  =  m_Query(  ASN_RFC1157_GETNEXTREQUEST,  &varBindList,  &errorStatus,  &errorIndex  ); 

  SNMP_FreeVarBind(  &varBind[0]  ); 
  
  varBindList.len = 2; 

  /* 拷贝OID的ifType－接口类型 */ 
  SNMP_oidcpy(  &varBind[0].name,  &MIB_ifEntryType  ); 

  /* 拷贝OID的ifPhysAddress－物理地址 */ 
  SNMP_oidcpy(  &varBind[1].name,  &MIB_ifMACEntAddr  ); 

  do  { 

    /* 提交查询，结果将载入 varBindList。 
       可以预料这个循环调用的次数和系统中的接口卡数量相等 */ 
    ret  =  m_Query(  ASN_RFC1157_GETNEXTREQUEST,  &varBindList,  &errorStatus,  &errorIndex  ); 
    if  (  !ret  )  ret  =  1; 
    else  /* 确认正确的返回类型 */ 
        ret  =  SNMP_oidncmp(  &varBind[0].name,  &MIB_ifEntryType,  MIB_ifEntryType.idLength  ); 
	if  (  !ret  )  { 
    	j  ++  ; 
    	dtmp  =  varBind[0].value.asnValue.number; 
    
		/* Type 6 describes ethernet interfaces */ 
    	if  (  dtmp  ==  6  )  { 

			/* 确认我们已经在此取得地址 */ 
    		ret  =  SNMP_oidncmp(  &varBind[1].name,  &MIB_ifMACEntAddr,  MIB_ifMACEntAddr.idLength  ); 
      		if  (  (  !ret  )  &&  (  varBind[1].value.asnValue.address.stream  !=  NULL  )  )  { 
        		if  (  (  varBind[1].value.asnValue.address.stream[0]  ==  0x44  ) 
          			&&  (  varBind[1].value.asnValue.address.stream[1]  ==  0x45  ) 
          			&&  (  varBind[1].value.asnValue.address.stream[2]  ==  0x53  ) 
          			&&  (  varBind[1].value.asnValue.address.stream[3]  ==  0x54  ) 
          			&&  (  varBind[1].value.asnValue.address.stream[4]  ==  0x00  )  ) 
        		{           
        			continue; 
        		} 
        		if  (  (  varBind[1].value.asnValue.address.stream[0]  ==  0x00  ) 
            		&&  (  varBind[1].value.asnValue.address.stream[1]  ==  0x00  ) 
            		&&  (  varBind[1].value.asnValue.address.stream[2]  ==  0x00  ) 
            		&&  (  varBind[1].value.asnValue.address.stream[3]  ==  0x00  ) 
            		&&  (  varBind[1].value.asnValue.address.stream[4]  ==  0x00  ) 
            		&&  (  varBind[1].value.asnValue.address.stream[5]  ==  0x00  )  ) 
        		{ 
        			/* 忽略由其他的网络接口卡返回的NULL地址 */ 
        			continue; 
        		} 
        		sprintf(  TempEthernet,  "%02x%02x%02x%02x%02x%02x", 
										  varBind[1].value.asnValue.address.stream[0], 
                						  varBind[1].value.asnValue.address.stream[1], 
                						  varBind[1].value.asnValue.address.stream[2], 
                						  varBind[1].value.asnValue.address.stream[3], 
                						  varBind[1].value.asnValue.address.stream[4], 
                						  varBind[1].value.asnValue.address.stream[5]  ); 
        		// char buf[1024];
				// wsprintf(buf, "MAC Address of interface #%i: %s", j, TempEthernet);
				// AfxMessageBox( buf );
				memcpy(  macAddr,  TempEthernet,  12  );
				iErr  =  0;
				goto  errLabel;
		
	  		} 
	   	} 
    } 
  
  }  while  (  !ret  );         /* 发生错误终止。 */ 

errLabel:

  /* 解除绑定 */ 
  SNMP_FreeVarBind(  &varBind[0]  ); 
  SNMP_FreeVarBind(  &varBind[1]  ); 
  
  return  iErr;

}



//  这里对每块mac仅填充前面的12字节，不补'\0'
//  返回所取mac数
 extern  "C"  int  qyGetMacAddrs(  unsigned  char  *  macAddrs[],  unsigned  int  * pMaxMacs  )
{
	int  iErr  =  -1;

	UINT					OID_ifEntryType[]	=  {  1,  3,  6,  1,  2,  1,  2,  2,  1,  3  }; 
	UINT					OID_ifEntryNum[]	=  {  1,  3,  6,  1,  2,  1,  2,  1  }; 
	UINT					OID_ipMACEntAddr[]	=  {  1,  3,  6,  1,  2,  1,  2,  2,  1,  6  }; 
	AsnObjectIdentifier		MIB_ifMACEntAddr	=  {  sizeof(  OID_ipMACEntAddr  )  /  sizeof(  UINT  ),  OID_ipMACEntAddr  }; 
	AsnObjectIdentifier		MIB_ifEntryType		=  {  sizeof(  OID_ifEntryType  )  /  sizeof(  UINT  ),  OID_ifEntryType  }; 
	AsnObjectIdentifier		MIB_ifEntryNum		=  {  sizeof(  OID_ifEntryNum  )  /  sizeof(  UINT  ),  OID_ifEntryNum  }; 
 	RFC1157VarBindList		varBindList; 
  	RFC1157VarBind			varBind[2]; 
  	AsnInteger				errorStatus; 
  	AsnInteger				errorIndex; 
	AsnObjectIdentifier		MIB_NULL			=  {  0,  0  }; 
  	int						ret; 
  	int						dtmp; 
  	int						i  =  0,  j  =  0; 
  	bool					found  =  false; 
  	char					TempEthernet[13]; 
	int						index	=	0;
	unsigned  int			maxMacs  =  *pMaxMacs;

	//  2004/05/20增加了对ghDll_InetMib1的判断
	if  (  !ghDll_InetMib1  )  {
		traceLogA(  "InetMib1 is not loaded."  );  return  -1;
	}

	/* 初始化用来接收m_Query查询结果的变量列表 */ 
  	varBindList.list  =  varBind; 
  	varBind[0].name  =  MIB_NULL; 
  	varBind[1].name  =  MIB_NULL; 

  	/* 在OID中拷贝并查找接口表中的入口数量 */ 
  	varBindList.len  =  1;        /* Only retrieving one item */ 
  	SNMP_oidcpy(  &varBind[0].name,  &MIB_ifEntryNum  ); 
  	ret  =  m_Query(  ASN_RFC1157_GETNEXTREQUEST,  &varBindList,  &errorStatus,  &errorIndex  ); 
 
	SNMP_FreeVarBind(  &varBind[0]  ); 

	varBindList.len  =  2; 

	/* 拷贝OID的ifType－接口类型 */ 
  	SNMP_oidcpy(  &varBind[0].name,  &MIB_ifEntryType  ); 

  	/* 拷贝OID的ifPhysAddress－物理地址 */ 
  	SNMP_oidcpy(  &varBind[1].name,  &MIB_ifMACEntAddr  ); 

	do  { 

    	/* 提交查询，结果将载入 varBindList。 
    	   可以预料这个循环调用的次数和系统中的接口卡数量相等 */ 
    	ret  =  m_Query(  ASN_RFC1157_GETNEXTREQUEST,  &varBindList,  &errorStatus,  &errorIndex  ); 
    	if  (  !ret  )  ret  =  1; 
		else  {        /* 确认正确的返回类型 */ 
      		ret  =  SNMP_oidncmp(  &varBind[0].name,  &MIB_ifEntryType,  MIB_ifEntryType.idLength  ); 
		}
		if  (  !ret  )  { 
    		j  ++  ; 
    		dtmp  =  varBind[0].value.asnValue.number; 
    
			/* Type 6 describes ethernet interfaces */ 
    		if  (  dtmp  ==  6  )  { 
				/* 确认我们已经在此取得地址 */ 
				ret  =  SNMP_oidncmp(  &varBind[1].name,  &MIB_ifMACEntAddr,  MIB_ifMACEntAddr.idLength  ); 
      			if  (  (  !ret  )  &&  (  varBind[1].value.asnValue.address.stream  !=  NULL  )  )  { 
					if  (  (  varBind[1].value.asnValue.address.stream[0]  ==  0x44  ) 
          				&&  (  varBind[1].value.asnValue.address.stream[1]  ==  0x45  ) 
          					&&  (  varBind[1].value.asnValue.address.stream[2]  ==  0x53  ) 
          						&&  (  varBind[1].value.asnValue.address.stream[3]  ==  0x54  ) 
          							&&  (  varBind[1].value.asnValue.address.stream[4] == 0x00  )  ) 
        			{           
        				continue; 
        			} 
        			if  (  (  varBind[1].value.asnValue.address.stream[0]  ==  0x00  ) 
            			&&  (  varBind[1].value.asnValue.address.stream[1]  ==  0x00  ) 
            				&&  (  varBind[1].value.asnValue.address.stream[2]  ==  0x00  ) 
            					&&  (  varBind[1].value.asnValue.address.stream[3]  ==  0x00  ) 
            						&&  (  varBind[1].value.asnValue.address.stream[4]  ==  0x00  ) 
            							&&  (  varBind[1].value.asnValue.address.stream[5]  ==  0x00  )  ) 
        			{ 
        				/* 忽略由其他的网络接口卡返回的NULL地址 */ 
        				continue; 
        			} 
        			sprintf(  TempEthernet,  "%02x%02x%02x%02x%02x%02x", 
        					varBind[1].value.asnValue.address.stream[0], 
        					varBind[1].value.asnValue.address.stream[1], 
        					varBind[1].value.asnValue.address.stream[2], 
        					varBind[1].value.asnValue.address.stream[3], 
        					varBind[1].value.asnValue.address.stream[4], 
        					varBind[1].value.asnValue.address.stream[5]); 
        			// char buf[1024];
					// wsprintf(buf, "MAC Address of interface #%i: %s", j, TempEthernet);
					// AfxMessageBox( buf );
					memcpy( macAddrs[index],  TempEthernet,  12  );
					index  ++  ;
					if  (  index  >=  (  int  )maxMacs  )  {
						//  缓冲已满
						iErr  =  0;  goto  errLabel;
					}		
	  			} 
	       	} 
    	} 
	}  while  (  !ret  );         /* 发生错误终止。 */ 

	iErr  =  0;

errLabel:

  	/* 解除绑定 */ 
  	SNMP_FreeVarBind(  &varBind[0]  ); 
  	SNMP_FreeVarBind(  &varBind[1]  ); 
  
	if  (  !iErr  )  *pMaxMacs  =  index;

	return  iErr;

}


 //  对返回void类型的函数，应在函数里清除返回内容
 extern  "C"  int  getQwmMacsBySnmp(  QWM_MACS_INFO  *  pMacsInfo  )
{
	 unsigned  char		*	pMacs[sizeof(  pMacsInfo->macs  )  /  sizeof(  pMacsInfo->macs[0]  )];
	 unsigned  int			nMacs; 
	 int					i;

	 if  (  !pMacsInfo  )  return  -1;
	 memset(  pMacsInfo,  0,  sizeof(  QWM_MACS_INFO  )  );

	 nMacs  =  sizeof(  pMacsInfo->macs  )  /  sizeof(  pMacsInfo->macs[0]  );
	 for  (  i  =  0;  i  <  (  int  )nMacs;  i  ++  )  {
		  pMacs[i]  =  pMacsInfo->macs[i];
	 }
	 
	 if  (  !qyGetMacAddrs(  pMacs,  &nMacs  )  )  {
	 	 for  (  i  =  0;  i  <  (  int  )nMacs;  i  ++  )  pMacsInfo->macs[i][CONST_qyMacLen]  =  0;
		 pMacsInfo->nMacs  =  nMacs;	 
	 }

	 return  0;
}

 //  下面这个函数有内存泄露，需要再检查代码
 extern "C" BOOL bQyMacFound( unsigned char *macAddr )
{
  BOOL	bErr = FALSE;

  UINT OID_ifEntryType[] = {1, 3, 6, 1, 2, 1, 2, 2, 1, 3}; 
  UINT OID_ifEntryNum[] = {1, 3, 6, 1, 2, 1, 2, 1}; 
  UINT OID_ipMACEntAddr[] = {1, 3, 6, 1, 2, 1, 2, 2, 1, 6}; 
  AsnObjectIdentifier MIB_ifMACEntAddr = 
    { sizeof(OID_ipMACEntAddr) / sizeof(UINT), OID_ipMACEntAddr }; 
  AsnObjectIdentifier MIB_ifEntryType = 
    {sizeof(OID_ifEntryType) / sizeof(UINT), OID_ifEntryType}; 
  AsnObjectIdentifier MIB_ifEntryNum = 
    {sizeof(OID_ifEntryNum) / sizeof(UINT), OID_ifEntryNum}; 
  RFC1157VarBindList varBindList; 
  RFC1157VarBind varBind[2]; 
  AsnInteger errorStatus; 
  AsnInteger errorIndex; 
  AsnObjectIdentifier MIB_NULL = {0, 0}; 
  int ret; 
  int dtmp; 
  int i = 0, j = 0; 
  bool found = false; 
  char TempEthernet[13]; 


  /* 初始化用来接收m_Query查询结果的变量列表 */ 
  varBindList.list = varBind; 
  varBind[0].name = MIB_NULL; 
  varBind[1].name = MIB_NULL; 

  /* 在OID中拷贝并查找接口表中的入口数量 */ 
  varBindList.len = 1;        /* Only retrieving one item */ 
  SNMP_oidcpy(&varBind[0].name, &MIB_ifEntryNum); 
  ret  =  m_Query(ASN_RFC1157_GETNEXTREQUEST, &varBindList, &errorStatus, &errorIndex); 

  SNMP_FreeVarBind(  &varBind[0]  ); 

  varBindList.len = 2; 

  /* 拷贝OID的ifType－接口类型 */ 
  SNMP_oidcpy(&varBind[0].name, &MIB_ifEntryType); 

  /* 拷贝OID的ifPhysAddress－物理地址 */ 
  SNMP_oidcpy(&varBind[1].name, &MIB_ifMACEntAddr); 

  do 
  { 

    /* 提交查询，结果将载入 varBindList。 
       可以预料这个循环调用的次数和系统中的接口卡数量相等 */ 
    ret = m_Query(ASN_RFC1157_GETNEXTREQUEST, &varBindList, &errorStatus, &errorIndex); 
    if (!ret)  ret = 1; 
    else 
        /* 确认正确的返回类型 */ 
      ret = SNMP_oidncmp(&varBind[0].name, &MIB_ifEntryType, MIB_ifEntryType.idLength); 
	if (!ret) { 
    j++; 
    dtmp = varBind[0].value.asnValue.number; 
    
    /* Type 6 describes ethernet interfaces */ 
    if (dtmp == 6) 
    { 

      /* 确认我们已经在此取得地址 */ 
      ret = 
          SNMP_oidncmp(&varBind[1].name, &MIB_ifMACEntAddr, 
                       MIB_ifMACEntAddr.idLength); 
      if ((!ret) && (varBind[1].value.asnValue.address.stream != NULL)) 
      { 
        if((varBind[1].value.asnValue.address.stream[0] == 0x44) 
          && (varBind[1].value.asnValue.address.stream[1] == 0x45) 
          && (varBind[1].value.asnValue.address.stream[2] == 0x53) 
          && (varBind[1].value.asnValue.address.stream[3] == 0x54) 
          && (varBind[1].value.asnValue.address.stream[4] == 0x00)) 
        {           
          continue; 
        } 
        if ((varBind[1].value.asnValue.address.stream[0] == 0x00) 
            && (varBind[1].value.asnValue.address.stream[1] == 0x00) 
            && (varBind[1].value.asnValue.address.stream[2] == 0x00) 
            && (varBind[1].value.asnValue.address.stream[3] == 0x00) 
            && (varBind[1].value.asnValue.address.stream[4] == 0x00) 
            && (varBind[1].value.asnValue.address.stream[5] == 0x00)) 
        { 
          /* 忽略由其他的网络接口卡返回的NULL地址 */ 
         
          continue; 
        } 
        sprintf(TempEthernet, "%02x%02x%02x%02x%02x%02x", 
                varBind[1].value.asnValue.address.stream[0], 
                varBind[1].value.asnValue.address.stream[1], 
                varBind[1].value.asnValue.address.stream[2], 
                varBind[1].value.asnValue.address.stream[3], 
                varBind[1].value.asnValue.address.stream[4], 
                varBind[1].value.asnValue.address.stream[5]); 
        // char buf[1024];
		// wsprintf(buf, "MAC Address of interface #%i: %s", j, TempEthernet);
		// AfxMessageBox( buf );
		if  (  !memcpy( macAddr, TempEthernet, 12 )  )  {
			bErr = TRUE;
			goto errLabel;
		}
		
	  } 
	  
      } 
    } 
  } while (!ret);         /* 发生错误终止。 */ 

errLabel:

  /* 解除绑定 */ 
  SNMP_FreeVarBind(&varBind[0]); 
  SNMP_FreeVarBind(&varBind[1]); 
  
  return bErr;

}

#else

  extern  "C"  int  getQwmMacsBySnmp(  QWM_MACS_INFO  *  pMacsInfo  )
 {
	 traceLogA(  "getQwmMacsBySnmp is not supported in ce"  );
	 return  -1;
 }

#endif



