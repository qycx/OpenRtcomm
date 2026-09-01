 

/*
 *
 * It requires WinPcap (http://winpcap.polito.it/)
 *
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<conio.h>
#include	<time.h>
#include	<windows.h>

#include	<iphlpapi.h>
//  #include	"myiphlpapi.h"

//  #include	"packet32.h"
#include	"winpcap_common.h"
#include	"winarp_sk.h"
#include	"Ntddndis.h"

#include	"qyCommon.h"
#include	"qwmDynFunc.h"

#define		SIMULTANEOU_READS				10
#define		MAX_ETHERNET_FRAME_SIZE			1514
#define		Max_Num_Adapter					10

// Prototypes
//  void PrintPackets(LPPACKET lpPacket);
extern  "C"  void  GetOSVersion(  void  );
extern  "C"  BOOL  g_bIsWinNT;

char        AdapterList[Max_Num_Adapter][1024];

/*
 extern  "C"  int  qyOpenAdapter(  LPADAPTER  *  lppAdapter  ) 
{

	int			iErr			=		-1;
	// define a pointer to a ADAPTER structure
	LPADAPTER	lpAdapter		=		0;
		
	int			i;
	DWORD		dwErrorCode;
	
	DWORD		dwVersion;
	DWORD		dwWindowsMajorVersion;
	
	//unicode strings (winnt)
	WCHAR		AdapterName[512]; // string that contains a list of the network adapters
	WCHAR		*temp,*temp1;
	
	//ascii strings (win95)
	char		AdapterNamea[512]; // string that contains a list of the network adapters
	char		*tempa,*temp1a;
	
	int			AdapterNum  =  0,  Open;
	ULONG		AdapterLength;
	
	AdapterNamea[0]  =  0;
	
	if  (  AdapterNamea[0]  ==  0  )  {
		
		// obtain the name of the adapters installed on this machine
		AdapterLength  =  1024;
		
		printf(  "Adapters installed:\n"  );
		i  =  0;
		
		// the data returned by PacketGetAdapterNames is different in Win95 and in WinNT.
		// We have to check the os on which we are running
		dwVersion  =  GetVersion(  );
		dwWindowsMajorVersion  =  (  DWORD  )(  LOBYTE(  LOWORD(  dwVersion  )  )  );
		if  (  !(  dwVersion  >=  0x80000000  &&  dwWindowsMajorVersion  >=  4  )  )  {  // Windows NT
			PacketGetAdapterNames(  (  char  *  )AdapterName,  &AdapterLength  );
			temp  =  AdapterName;
			temp1  =  AdapterName;
			while  (  (  *temp  !=  '\0'  )  ||  (  *(  temp  -  1  )  !=  '\0'  )  )  {
				   if  (  *temp  ==  '\0'  )  {
					   memcpy(  AdapterList[i],  temp1,  (  temp  -  temp1  )  *  2  );
					   temp1  =  temp  +  1;
					   i ++  ;
				   }
				
				   temp  ++  ;
			}
			
			AdapterNum  =  i;
			for  (  i  =  0;  i  <  AdapterNum;  i  ++  )
				wprintf(  L"\n%d- %s\n",  i  +  1,  AdapterList[i]  );
			printf(  "\n"  );
			
			}
		else  {  //windows 95
			  PacketGetAdapterNames(  AdapterNamea,  &AdapterLength  );
			  tempa  =  AdapterNamea;
			  temp1a=AdapterNamea;
			
			  while  (  (  *tempa  !=  '\0'  )  ||  (  *(  tempa  -  1  )  !=  '\0'  )  )  {
					 if  (  *tempa  ==  '\0'  )  {
						 memcpy(  AdapterList[i],  temp1a,  tempa  -  temp1a  );
						 temp1a  =  tempa  +  1;
						 i  ++  ;
					 }
					 tempa  ++  ;
			  }
			
			  AdapterNum  =  i;
			  for  (  i  =  0;  i  <  AdapterNum;  i  ++  )
				   printf(  "\n%d- %s\n",  i + 1,  AdapterList[i]  );
			  printf("\n");
			
		}
		
		do  {
			printf(  "Select the number of the adapter to open : "  );
			scanf(  "%d",  &Open  );
			if  (  Open  >  AdapterNum  ) printf(  "\nThe number must be smaller than %d",  AdapterNum  ); 
		}  while  (  Open  >  AdapterNum  );
				
		lpAdapter  =  PacketOpenAdapter(  AdapterList[Open - 1]  );
		
		if  (  !lpAdapter  ||  (  lpAdapter->hFile  ==  INVALID_HANDLE_VALUE  )  )  {
			dwErrorCode  =  GetLastError( );
			printf(  "Unable to open the driver, Error Code : %lx\n",  dwErrorCode  ); 
			
			return(  -1  );
		}	
		}
	else  {
		
		  lpAdapter  =  PacketOpenAdapter(  AdapterNamea  );
		  if  (  !lpAdapter  ||  (  lpAdapter->hFile  ==  INVALID_HANDLE_VALUE  )  )  {
			  dwErrorCode  =  GetLastError(  );
			  printf(  "Unable to open the driver, Error Code : %lx\n",  dwErrorCode  ); 
			  return(  -1  );
		  }
		
	}

	*lppAdapter  =  lpAdapter;

	iErr  =  0;

//  errLabel:

	return  iErr;

}
*/

/*
 void  qyCloseAdapter(  LPADAPTER  lpAdapter  ) 
{ 
  	 PacketCloseAdapter(  lpAdapter  );
}
*/


typedef  struct  __qyArpParam_t  {
				 int		count;				/* Number of packets to send */
  				 int		opcode;	 			/* ARP mode (request or reply), ARP_OP_REQUEST, ARP_OP_REPLY */
				 char 		ethDst[256]; 		/* Ethernet destination address */
				 char		ethSrc[256];		/* Ethernet source address */
				 char		targetIp[256]; 		/* Target IP address */      
				 char		targetMac[256];		/* Target MAC address */
				 char		sndIp[256];			/* Sender IP address */
				 char		sndMac[256];		/* Sender MAC address */
				 BOOL		bEnumStop;
}		 QY_ARPPARAM;    

//  -m 1 -s 192.168.103.129 -d 192.168.103.129 -S 00-11-22-33-44-55 -D ff-ff-ff-ff-ff-ff  -F 00-11-22-33-44-55 -T 00-00-00-00-00-00
//  int  fakeIp(  LPADAPTER  lpAdapter,  QY_ARPPARAM  *  pArp  );
//  int  qyGetRemoteMac(  LPADAPTER  lpAdapter,  char  *  targetIp,  unsigned  char  *  remotemac  );
//  int  tmpGetRemoteMac(  LPADAPTER  lpAdapter,  QY_ARPPARAM  *  pArp  );


 extern  "C"  int  qyGetRemoteMacByIp(  QY_ENV  *  pEnv,  char  *  ip,  char  *  mac,  unsigned  int  macSize  )
{
	 int				iErr			=	-1;	
	 HRESULT			hr;
   	 IPAddr				ipAddr;
     ULONG				pulMac[2];
     ULONG				ulLen;
	 char			*	szMac			=	NULL;
	 QWM_DYN_LIB	*	pDynLib			=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	 //  traceLogA(  "qyGetRemoteMacByIp( ): 这个函数应该重写,用SendArp( )来实现"  );
	 if  (  !pDynLib->pSendARP  )  {
		 traceLogA(  "qyGetRemoteMacByIp(  ) failed:  pSendARP is null"  );  goto  errLabel;
	 }
	 if  (  !bIpValid(  ip  )  )  goto  errLabel;
    
	 ipAddr  =  inet_addr(  ip  );
     memset (pulMac, 0xff, sizeof (pulMac));
     ulLen  =  6;
    
     if  (  (  hr  =  pDynLib->pSendARP(  ipAddr,  0,  pulMac,  &ulLen  )  )  !=  NO_ERROR    )  goto  errLabel;
     traceLogA(  "Return %08x, length %8d\n", hr, ulLen  );
	 if  (  !ulLen  )  goto  errLabel;
	
     size_t  i, j;
     if  (  !(  szMac  =  (  char  *  )malloc(  ulLen  *  3  )  )  )  goto  errLabel;
	 memset(  szMac,  0,  ulLen  *  3  );

     PBYTE  pbHexMac;
	 pbHexMac  =  (  PBYTE  )pulMac;

     //
     // Convert the binary MAC address into human-readable
     //
     for  (  i  =  0, j  =  0;  i  <  ulLen  -  1;  ++  i  )  {
          j  +=  sprintf(  szMac  +  j,  "%02x",  pbHexMac[i]  );
     }    
     sprintf(  szMac  +  j,  "%02X",  pbHexMac[i]  );
     traceLogA(  "MAC address %s\n", szMac  );
	 
	 safeStrnCpy(  szMac,  mac,  macSize  );	//  这里设了值

	 /*
	 QY_ARPPARAM	tmpArpParam;

	 if  (  macSize  <  CONST_qyMacLen  )  return  -1;
	 
	 strcpy(  tmpArpParam.targetIp,  fakedIp  );
	 qyEnumAdapters(  &tmpArpParam,  (  PF_adapterProc  )tmpGetRemoteMac  );
	 if  (  !tmpArpParam.bEnumStop  )  {
		 printf(  "mac is not found.\n"  );
		 goto  errLabel;
	 }

	 traceLogA(  "mac of %s is %s.\n",  tmpArpParam.targetIp,  tmpArpParam.targetMac  );
	 if  (  strlen(  tmpArpParam.targetMac  )  !=  CONST_qyMacLen  )  goto  errLabel;
	 memcpy(  mac,  tmpArpParam.targetMac,  CONST_qyMacLen  );
	 if  (  macSize  >  CONST_qyMacLen  )  mac[CONST_qyMacLen]  =  0;
	 */

	 iErr  =  0;

errLabel:

	 if  (  szMac  )  free(  szMac  );

	 return  iErr;

}


 extern  "C"  int  attackHost(  char  *  fakedIp,  void  *  l  )
{
	 
	 traceLogA(  "attackHost( ) 此函数已被废弃"  );
	 /*
	 QY_ARPPARAM	tmpArpParam;

	 memset(  &tmpArpParam,  0,  sizeof(  tmpArpParam  )  );
	 
	 tmpArpParam.count  =  1;
	 tmpArpParam.opcode  =  ARP_OP_REQUEST;
	 strcpy(  tmpArpParam.ethDst,		"ff-ff-ff-ff-ff-ff"  );
	 strcpy(  tmpArpParam.ethSrc,		"00-11-22-33-44-55"  );
	 strcpy(  tmpArpParam.targetIp,		fakedIp  );
	 strcpy(  tmpArpParam.targetMac,	"00-00-00-00-00-00"  );
	 strcpy(  tmpArpParam.sndIp,		fakedIp  );
	 strcpy(  tmpArpParam.sndMac,		"00-11-22-33-44-55"  );

	 qyEnumAdapters(  &tmpArpParam,  (  PF_adapterProc  )fakeIp  );

  */

//  errLabel:

	 return  0;

}

 /*
#ifdef  __DEBUG__
 extern  "C"  int  testAttackHost(  char  *  fakedIp  )
{
	 QY_ARPPARAM	tmpArpParam;
	 //  char  *  fakedMac  =  "00-11-22-33-44-55";
	 //  char  *  fakedMac  =  "00-40-d0-25-ec-c7";
	 char  *  fakedMac  =  "00-0a-eb-10-22-2c";
	 
	 //  fakedIp  =  "192.168.10.68";
	 fakedIp  =  "192.168.103.68";	 
	 
	 memset(  &tmpArpParam,  0,  sizeof(  tmpArpParam  )  );
	 
	 tmpArpParam.count  =  1;
	 tmpArpParam.opcode  =  ARP_OP_REQUEST;
	 strcpy(  tmpArpParam.ethDst,		"ff-ff-ff-ff-ff-ff"  );
	 strcpy(  tmpArpParam.ethSrc,		fakedMac  );
	 strcpy(  tmpArpParam.targetIp,		"192.168.103.30"  );
	 //  strcpy(  tmpArpParam.targetMac,	"00-00-00-00-00-00"  );
	 strcpy(  tmpArpParam.targetMac,	"ff-ff-ff-ff-ff-ff"  );
	 strcpy(  tmpArpParam.sndIp,		fakedIp  );
	 strcpy(  tmpArpParam.sndMac,		fakedMac  );

	 qyEnumAdapters(  &tmpArpParam,  (  PF_adapterProc  )fakeIp  );

//  errLabel:

	 return  0;

}
#endif
*/

 /*
 //  remoteMacBuf大小至少12字节
 int  qyGetRemoteMac(  LPADAPTER  lpAdapter,  char  *  targetIp,  unsigned  char  *  remoteMacBuf  )
{
	int					iErr				=	-1;
  	//* WinPcap 
  	LPPACKET			lpPacketRequest		=	NULL;
  	LPPACKET			lpPacketReply		=	NULL;
  	char				buffer[256000];

  	///* Packet 
  	struct  arp_packet	arp_pkt;
  	unsigned char		broadcast[ETH_ADD_LEN];
  	unsigned char		macsender[ARP_ETH_ADD_SPACE];  
  	unsigned char		mactarget[ARP_ETH_ADD_SPACE];
  	unsigned char		ipsender[ARP_IP_ADD_SPACE];  

  	//* Others 
  	int					send_ok				=	0;
  	DWORD				timestamp			=	0;

  	unsigned  char			ipdest[ARP_IP_ADD_SPACE];
  	unsigned  int			tmpaddr[6];  
  	unsigned  char  *		iptarget		=	ipdest;
  	int						i;
	unsigned  char			remotemac[7];
	unsigned  char			tmpMacBuf[12  +  1];

  	sscanf(  targetIp,  "%d.%d.%d.%d",  &tmpaddr[0], &tmpaddr[1], &tmpaddr[2], &tmpaddr[3]  );
  	for  (  i  =  0;  i  <  4;  i  ++  )  {
  		 ipdest[i]  =  (  unsigned  char  )tmpaddr[i]; 
  	}
  	
	//* Init fields 
  	memset(broadcast, 0xFF, 6);
  	memset(mactarget, 0, 6);  
  	if  (  get_ether_addr(lpAdapter, macsender)  )  goto  errLabel;
  	if  (  get_ip_addr(ipsender)  !=  EXIT_SUCCESS  )  goto  errLabel;
  
  	//* Allocate PACKET structure for ARP Request packet 
  	if  (  (  lpPacketRequest  =  PacketAllocatePacket(  )  )  ==  NULL  )  {
    	//  fprintf(stderr, "\nError : failed to allocate the LPPACKET structure.\n");
		goto  errLabel;
	}  
	//* Init packet structure 
	memset(  &arp_pkt,  0,  sizeof(  struct  arp_packet  )  );          

	//* Build ARP Request packet 
  	arp_build(&arp_pkt, broadcast, macsender, ARP_OP_REQUEST, macsender, ipsender, mactarget, iptarget);     
 
	//* Init ARP Request packet 
  	PacketInitPacket(lpPacketRequest, &arp_pkt, sizeof(arp_pkt));
		
  	//* Set number of ARP Request packets to send 
  	if  (  PacketSetNumWrites(  lpAdapter,  1  )  ==  FALSE  )  {
    	fprintf(stderr, "\nWarning : unable to send more than one packet in a single write.\n");
		goto  errLabel;
  	}
   	  
	//* Set hardware filter to directed mode 
  	if  (  PacketSetHwFilter(lpAdapter, NDIS_PACKET_TYPE_DIRECTED)  ==  FALSE  )  {
    	printf("\nWarning: unable to set directed mode.\n");	
		goto  errLabel;
  	}

  	//* Set a 512K buffer in the driver 
  	if  (  PacketSetBuff(lpAdapter, 512000)  ==  FALSE  )  {
    	printf("\nError: unable to set the kernel buffer.\n");
		goto  errLabel;
	}

	//* Set a 1 second read timeout 
	if  (  PacketSetReadTimeout(  lpAdapter,  1000  )  ==  FALSE  )  {
    	printf("\nWarning: unable to set the read tiemout.\n");
		goto  errLabel;
  	}
  
  	//* Allocate PACKET structure for ARP Reply packet 
  	if  (  (  lpPacketReply  =  PacketAllocatePacket(  )  )  ==  NULL  )  {
    	printf("\nError: failed to allocate the LPPACKET structure.\n");
		goto  errLabel;
	}
  
	//* Init ARP Reply packet 
	PacketInitPacket(lpPacketReply, (char*)buffer, 256000);
	
  	timestamp = GetTickCount();

  	//* Main capture loop 
  	while  (  1  )  {
    	   if  (  send_ok  !=  1  )  {
	  		   //* Send packet 
      		   if  (  PacketSendPacket(lpAdapter, lpPacketRequest, TRUE) == FALSE  )  {
      			   fprintf(stderr, "\nError : unable to send the packets.\n");	                
				   goto  errLabel;
			   }

			   ///* Free packet 
			   PacketFreePacket(lpPacketRequest);  lpPacketRequest  =  NULL;
			   send_ok = 1;
		   }
  
		   //* Capture the packets 
		   if  (  PacketReceivePacket(lpAdapter, lpPacketReply, TRUE) == FALSE  )  {
			   printf("\nError: PacketReceivePacket failed.\n");      
			   goto  errLabel;
		   }
    	
		   if  (  lpPacketReply->ulBytesReceived > 0  )  {  
	  		   if  (  read_arp_reply(  lpPacketReply,  iptarget,  remotemac  )  ==  EXIT_SUCCESS  )  {
				   printf(  "\n+ Sender IP address  : %d.%d.%d.%d\n", iptarget[0], iptarget[1], iptarget[2], iptarget[3]  );    
    	  		   printf(  "+ Sender MAC address : %02X-%02X-%02X-%02X-%02X-%02X\n", 
	        				   remotemac [0], remotemac [1], remotemac [2], 
	            			   remotemac [3], remotemac [4], remotemac [5]  );
           		   printf("\n");
				   break;
			   }
		   }	

		   if  (  (  GetTickCount(  )  -  timestamp  )  >  2000  )  {
      		   printf(  "\nError: unable to get MAC address from %d.%d.%d.%d\n", 
	  				    iptarget[0], iptarget[1], iptarget[2], iptarget[3]);    
			   goto  errLabel;
		   }
	
	}

	sprintf(  (  char  *  )tmpMacBuf,  "%02x%02x%02x%02x%02x%02x",  
									   remotemac[0],  remotemac[1],  remotemac[2],  
									   remotemac [3], remotemac [4], remotemac [5]  );
	memcpy(  remoteMacBuf,  tmpMacBuf,  12  );

	iErr  =  0;

errLabel:

  	
  	//* Free packet 

	if  (  lpPacketRequest  )  PacketFreePacket(  lpPacketRequest  );				   
	if  (  lpPacketReply  )  PacketFreePacket(  lpPacketReply  );  
  
	return  iErr;

}


 BOOL  bAdapterEth(  LPADAPTER  lpAdapter  )
{
	BOOL		bRet  =  FALSE;
	int			i;
	NetType		netType;
	char		adapterName[256];
	int			len;
	char	 *	CONST_ndisWan  =  "NdisWan";
	int			len1;

 	GetOSVersion(  );
	if  (  g_bIsWinNT  )  _snprintf(  adapterName,  sizeof(  adapterName  ),  "%S",  lpAdapter->SymbolicLink  );
	else  _snprintf(  adapterName,  sizeof(  adapterName  ),  "%s",  lpAdapter->SymbolicLink  );
	adapterName[sizeof(  adapterName  )  -  1]  =  0;
	printf(  "adapterName is [%s].\n",  adapterName  );
	len  =  strlen(  adapterName  );
	len1  =  strlen(  CONST_ndisWan  );
	for  (  i  =  0;  i  <  len;  i  ++  )  {
		 //  printf(  "adapterName  +  %d is [%s].\n",  i,  adapterName  +  i  );
		 if  (  !_strnicmp(  adapterName  +  i,  CONST_ndisWan,  len1  )  )  goto  errLabel;
	}

	if  (  !PacketGetNetType(  lpAdapter,  &netType  )  )  goto  errLabel;
	if  (  netType.LinkType  !=  NdisMedium802_3  )  goto  errLabel;
	if  (  netType.LinkSpeed  <  1000000  )  goto  errLabel;	// 通常网卡的速度在10兆以上

	bRet  =  TRUE;
	
errLabel:

	return  bRet;
	
}

  int  tmpGetRemoteMac(  LPADAPTER  lpAdapter,  QY_ARPPARAM  *  pArp  )
{
	int  iErr  =  -1;
	
	if  (  !lpAdapter  )  return  -1;
	if  (  !bAdapterEth(  lpAdapter  )  )  goto  errLabel;
	if  (  qyGetRemoteMac(  lpAdapter,  pArp->targetIp,  (  unsigned  char  *  )pArp->targetMac  )  )  goto  errLabel;
	pArp->targetMac[12]  =  0;
	
	pArp->bEnumStop  =  TRUE;

	iErr  =  0;

errLabel:
	 
	return  0;

}
*/

/*
 int  fakeIp(  LPADAPTER  lpAdapter,  QY_ARPPARAM  *  pArp  )
{
	int			iErr		=	-1;
	//* WinPcap 
   	LPPACKET	lpPacket	=	NULL;
  
	//* ARP Packet 
  	struct arp_packet arp_pkt;

  	//* Ethernet & ARP packet 
  	unsigned char	arpsender[ARP_ETH_ADD_SPACE];
  	unsigned char	arptarget[ARP_ETH_ADD_SPACE];
  	unsigned char	ethersource[ETH_ADD_LEN];
  	unsigned char	etherdest[ETH_ADD_LEN];
  	unsigned char	ipsource[ARP_IP_ADD_SPACE];
  	unsigned char	ipdest[ARP_IP_ADD_SPACE];
  	int				opcode;
  
  	//* Flags 
  	int flag_mode = 0;
  	int flag_delay = 0;
  	int flag_count = 0;
  	int flag_dst_ethaddr = 0;
  	int flag_src_ethaddr = 0;
  	int flag_send_macaddr = 0;
  	int flag_send_ipaddr = 0;
  	int flag_tar_macaddr = 0;
  	int flag_tar_ipaddr = 0;

  	//* Others 
  	unsigned int tmpaddr[6];  
  	int          delay = 2000;
  	int          count = -1;
  	int          packetcount = 0;
	int          i;    

	if  (  !lpAdapter  )  goto  errLabel;

	if  (  !bAdapterEth(  lpAdapter  )  )  goto  errLabel;

  	//* Number of packets to send 
  	count  =  pArp->count;
  	flag_count  =  1;
 	///* ARP mode (request or reply) 
  	opcode  =  pArp->opcode;
  	flag_mode  =  1;
 	//* Ethernet destination address 
  	sscanf(  pArp->ethDst,  "%02X-%02X-%02X-%02X-%02X-%02X", 
	       					&tmpaddr[0], &tmpaddr[1], &tmpaddr[2], &tmpaddr[3], &tmpaddr[4], &tmpaddr[5]  );
  	for  (  i  =  0;  i  <  6;  i  ++  )  {
  		 etherdest[i] = (unsigned char)tmpaddr[i]; 
  	}
  	flag_dst_ethaddr = 1;
  	memset(tmpaddr, 0, sizeof(tmpaddr));
  	//* Ethernet source address 
  	sscanf(  pArp->ethSrc,  "%02X-%02X-%02X-%02X-%02X-%02X", 
							&tmpaddr[0], &tmpaddr[1], &tmpaddr[2], &tmpaddr[3], &tmpaddr[4], &tmpaddr[5]);
  	for  (  i  =  0;  i  <  6;  i  ++  )  {
  		 ethersource[i]  =  (  unsigned  char  )tmpaddr[i]; 
  	}
  	flag_src_ethaddr = 1;
  	memset(tmpaddr, 0, sizeof(tmpaddr));
  	//* Target IP address 
  	sscanf(  pArp->targetIp,  "%d.%d.%d.%d", 
							  &tmpaddr[0], &tmpaddr[1], &tmpaddr[2], &tmpaddr[3]  );
  	for  (  i  =  0;  i  <  4;  i  ++  )  {
  		 ipdest[i] = (unsigned char)tmpaddr[i]; 
  	}
  	flag_tar_ipaddr  =  1;
  	memset(tmpaddr, 0, sizeof(tmpaddr));
  	//* Target MAC address 
  	sscanf(  pArp->targetMac,  "%02X-%02X-%02X-%02X-%02X-%02X", 
							   &tmpaddr[0], &tmpaddr[1], &tmpaddr[2], &tmpaddr[3], &tmpaddr[4], &tmpaddr[5]);
  	for  (  i  =  0;  i  <  6;  i  ++  )  {
  		 arptarget[i] = (unsigned char)tmpaddr[i]; 
  	}
  	flag_tar_macaddr = 1;
  	memset(tmpaddr, 0, sizeof(tmpaddr));
  	//* Sender IP address 
  	sscanf(  pArp->sndIp,  "%d.%d.%d.%d", 
						   &tmpaddr[0], &tmpaddr[1], &tmpaddr[2], &tmpaddr[3]  );
  	for  (  i  =  0;  i  <  4;  i  ++  )  {
         ipsource[i] = (unsigned char)tmpaddr[i]; 
  	}
  	flag_send_ipaddr = 1;
  	memset(tmpaddr, 0, sizeof(tmpaddr));		  
  	//* Sender MAC address 
  	sscanf(  pArp->sndMac,  "%02X-%02X-%02X-%02X-%02X-%02X", 
							&tmpaddr[0], &tmpaddr[1], &tmpaddr[2], &tmpaddr[3], &tmpaddr[4], &tmpaddr[5]  );		  
  	for  (  i  =  0;  i  <  6;  i  ++  )  {
  		 arpsender[i] = (unsigned char)tmpaddr[i]; 
  	}
  	flag_send_macaddr = 1;
  	memset(tmpaddr, 0, sizeof(tmpaddr));        
    
  	//* Check minimal options 
  	if  (  (  flag_mode && flag_send_ipaddr && flag_tar_ipaddr  ) != 1  )  {
    	goto  errLabel;
	}

	//* Check ethernet source address 
	if  (  flag_src_ethaddr != 1  )  {  
		goto  errLabel;    	
  	}
 
  	//* Check ethernet destination address 
  	if  (  (  flag_dst_ethaddr  !=  1  )  &&  (  flag_tar_ipaddr  ==  1  )  )  {  
		goto  errLabel;
	}

	//* Check arp sender MAC address 
  	if  (  flag_send_macaddr  !=  1  )  {  
		goto  errLabel;
  	}
 
  	//* Check arp target MAC address 
  	if  (  (flag_tar_macaddr  !=  1  )  &&  (  flag_tar_ipaddr  ==  1  )  )  {  
		goto  errLabel;		
  	}  

  	//* Check options and set default fields 
  	if  (  (  flag_mode && flag_dst_ethaddr && flag_src_ethaddr && 
        flag_send_macaddr && flag_send_ipaddr && flag_tar_macaddr && 
        flag_tar_ipaddr  )  !=  1  ) 
  	{
		goto  errLabel;
  	}


	//  get_remote_mac(lpAdapter, ipdest, NULL, 1);
	//  get_remote_mac(  lpAdapter,  ipdest,  NULL,  1  );


  	//* Allocate PACKET structure 
  	if  (  (  lpPacket  =  PacketAllocatePacket(  )  )  ==  NULL  )  {
		goto  errLabel;
	}    

	//* Init packet structure 
	memset(&arp_pkt, 0, sizeof(struct arp_packet));         

	//* Build custom ARP packet 
	arp_build(  &arp_pkt,  etherdest,  ethersource,  opcode,  arpsender,  ipsource,  arptarget,  ipdest  );     
 
	//* Init packet 
	PacketInitPacket(  lpPacket,  &arp_pkt,  sizeof(  arp_pkt  )  );
		
	//* Set number of packets to send 
	if  (  PacketSetNumWrites(  lpAdapter,  1  )  ==  FALSE  )  {
    	//  fprintf(stderr, "\nWarning : unable to send more than one packet in a single write\n");
		goto  errLabel;
  	}

  	//* Print start informations 
  	print_start(  etherdest, ethersource, opcode, arpsender, ipsource, arptarget, ipdest  );
  
  	//* Send packet 
  	printf("+ Start sending\n");
  	printf("  ");  

  	while  (  1  )  {
    	   if  (  PacketSendPacket(lpAdapter, lpPacket, TRUE)  ==  FALSE  )  {
      		   //  fprintf(stderr, "\nError : unable to send the packets\n");	        
			   goto  errLabel;
		   }
    
		   printf(".");
		   packetcount  ++  ;

		   if  (  (  packetcount % 46  ) == 0  )  {
      		   printf("\n  ");
		   }

		   if  (  count > 0  )  {
			   count  --  ;
	  		   if  (  !(  (  count  !=  0  )  &&  (  count  !=  -1  )  )  )  {	
      			   //* Print statistics 
        		   printf("\n+ End sending\n");
				   break;
	  		   }
		   }

		   Sleep(delay);
		   
	}

	iErr  =  0;

errLabel:

	if  (  lpPacket  )  PacketFreePacket(  lpPacket  );
	statistics(  packetcount  );

  	return  iErr;

}
  
 
 int  qyEnumAdapters(  void  *  pArpParam,  PF_adapterProc  pProc  )
{

	int					iErr					=		-1;
	//  define a pointer to a ADAPTER structure
	LPADAPTER			lpAdapter				=		0;
		
	int					i;
	DWORD				dwErrorCode;
	
	DWORD				dwVersion;
	DWORD				dwWindowsMajorVersion;
	
	//  unicode strings (winnt)
	WCHAR				AdapterName[1024];			// string that contains a list of the network adapters
	WCHAR			*	temp,  *  temp1;
	
	//  ascii strings (win95)
	char				AdapterNamea[1024];			// string that contains a list of the network adapters
	char			*	tempa,  *  temp1a;
	
	int					AdapterNum				=		0;
	ULONG				AdapterLength;
	QY_ARPPARAM		*	pArp					=		(  QY_ARPPARAM  *  )pArpParam;
	
	AdapterNamea[0]  =  0;
	
	if  (  AdapterNamea[0]  ==  0  )  {
		
		// obtain the name of the adapters installed on this machine
		AdapterLength  =  1024;
		
		traceLogA(  "Adapters installed:\n"  ); 

		i  =  0;
		 
		// the data returned by PacketGetAdapterNames is different in Win95 and in WinNT.
		// We have to check the os on which we are running
		dwVersion  =  GetVersion(  );
		dwWindowsMajorVersion  =  (  DWORD  )(  LOBYTE(  LOWORD(  dwVersion  )  )  );
		if  (  !(  dwVersion  >=  0x80000000  &&  dwWindowsMajorVersion  >=  4  )  )  {  // Windows NT
			if  (  !PacketGetAdapterNames(  (  char  *  )AdapterName,  &AdapterLength  )  )  {
				traceLogA(  "PacketGetAdapterNames failed"  );
				goto  errLabel;
			}
			temp  =  AdapterName;
			temp1  =  AdapterName;
			while  (  (  *temp  !=  '\0'  )  ||  (  *(  temp  -  1  )  !=  '\0'  )  )  {
				   if  (  *temp  ==  '\0'  )  {
					   memcpy(  AdapterList[i],  temp1,  (  temp  -  temp1  )  *  2  );
					   temp1  =  temp  +  1;
					   i ++  ;
				   }
				
				   temp  ++  ;
			}
			
			AdapterNum  =  i;

			//  for  (  i  =  0;  i  <  AdapterNum;  i  ++  )  wprintf(  L"\n%d- %s\n",  i  +  1,  AdapterList[i]  );
			//  printf(  "\n"  );
			//  for  (  i  =  0;  i  <  AdapterNum;  i  ++  )  traceLogA(  "%d- %S",  i  +  1,  AdapterList[i]  );
			
			}
		else  {  //windows 95
			  PacketGetAdapterNames(  AdapterNamea,  &AdapterLength  );
			  tempa  =  AdapterNamea;
			  temp1a  =  AdapterNamea;
			
			  while  (  (  *tempa  !=  '\0'  )  ||  (  *(  tempa  -  1  )  !=  '\0'  )  )  {
					 if  (  *tempa  ==  '\0'  )  {
						 memcpy(  AdapterList[i],  temp1a,  tempa  -  temp1a  );
						 temp1a  =  tempa  +  1;
						 i  ++  ;
					 }
					 tempa  ++  ;
			  }
			
			  AdapterNum  =  i;
			  for  (  i  =  0;  i  <  AdapterNum;  i  ++  )  traceLogA(  "\n%d- %s\n",  i + 1,  AdapterList[i]  );
			  traceLogA(  "\n"  );			
		}
		
		pArp->bEnumStop  =  FALSE;
		for  (   i  =  0;  i  <  AdapterNum  &&  !pArp->bEnumStop;  i  ++  )  {
		
			lpAdapter  =  PacketOpenAdapter(  AdapterList[i]  );
			if  (  !lpAdapter  ||  (  lpAdapter->hFile  ==  INVALID_HANDLE_VALUE  )  )  {
				dwErrorCode  =  GetLastError( );
				traceLogA(  "Unable to open the driver, Error Code : %lx\n",  dwErrorCode  ); 
				continue;
			}

			pProc(  (  void  *  )lpAdapter,  (  void  *  )pArp  );
			
			PacketCloseAdapter(  lpAdapter  );  lpAdapter  =  NULL; 
		}		
		
	}
	
	iErr  =  0;

errLabel:

	if  (  lpAdapter  )  PacketCloseAdapter(  lpAdapter  );

	return  iErr;

}
 
*/

