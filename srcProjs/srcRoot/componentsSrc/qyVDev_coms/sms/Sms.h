
#if !defined(__SMS_H__)
#define __SMS_H__

// 用户信息编码方式
#define			GSM_7BIT					0
#define			GSM_8BIT					4
#define			GSM_UCS2					8

// 应答状态
#define			GSM_WAIT					0							//  等待，不确定
#define			GSM_OK						1							//  OK
#define			GSM_ERR						-1							//  ERROR


#define			CONST_maxCharsPerSend_UCS2	70


//  for SMS_DELIVER
typedef  struct  __firstOctet_deliver_t		{
				 unsigned  char				bTP_MTI:2;					//  TP - Message - Type - Indicator
				 unsigned  char				bTP_MMS:1;					//  TP - More - Message - to - Send
				 unsigned  char				bTP_notUsed:2;				//  not used
				 unsigned  char				bTP_SRI:1;					//  TP - Status - Report - Indication
				 unsigned  char				bTP_UDHI:1;					//  TP - User - Data - Header - Indicator
				 unsigned  char				bTP_RP:1;					//  TP - Reply - Path
}		 FIRST_OCTET_deliver;

//  for SMS_SUBMIT
typedef  struct  __firstOctet_submit_t		{
				 unsigned  char				bTP_MTI:2;					//  TP - Message - Type - Indicator
				 unsigned  char				bTP_RD:1;					//  TP - Reject - Duplicates
				 unsigned  char				bTP_VPF:2;					//  TP - Validity - Period - Format 
				 unsigned  char				bTP_SRR:1;					//  TP - Status - Report - Request
				 unsigned  char				bTP_UDHI:1;					//  TP - User - Data - Header - Indicator
				 unsigned  char				bTP_RP:1;					//  TP - Reply - Path				 
}		 FIRST_OCTET_submit;


typedef  struct  __tpUdh_t					{
				 unsigned  char				ucUDHL;						
				 unsigned  char				ucIEI;
				 unsigned  char				ucIEIDL;
				 unsigned  char				ucIED[1];
}		 TP_UDH;


typedef  struct  __tpUdh_concatenatedSm_t	{
					 unsigned  char			ucUDHL;						
					 unsigned  char			ucIEI;
					 unsigned  char			ucIEIDL;
					 unsigned  char			ucRefrenceNo;
					 unsigned  char			ucMaxNum;
					 unsigned  char			ucSeqNo;
}		 TP_UDH_concatenatedSm;

//  050003070201

typedef  union  __tpUdhU_t					{
				TP_UDH						common;
				TP_UDH_concatenatedSm		concatenatedSm;
}		 TP_UDH_U;




// 短消息参数结构，编码/解码共用
// 其中，字符串以'\0'结尾
typedef  struct  __smPkt_t					{
				 char						SCA[16];					//  短消息服务中心号码(SMSC地址)
				 //
				 char						firstOctet;
				 //
				 char						TPA[16];					//  目标号码或回复号码(TP-DA或TP-RA)
				 char						TP_PID;						//  用户信息协议标识(TP-PID)
				 char						TP_DCS;						//  用户信息编码方式(TP-DCS)
				 char						TP_SCTS[16];				//  服务时间戳字符串(TP_SCTS), 接收时用到

				 TP_UDH_U					tpUdhU;


				 //  char					TP_UD[160];					//  原始用户信息(编码前或解码后的TP-UD)		// 应该用utf8来存储。			//  最大容量为140字节。可以有7-bit,8-bit,UCS2三种编码方式。每种对应的最大可发字符数为160, 140, 70. 
				 WCHAR						TP_UD[280  +  32];	
				 short						index;						//  短消息序号，在读取时用到
				 //				 
}		 SM_PKT;


#define		SM_PARAM						SM_PKT


// 读取应答的缓冲区
typedef  struct	 __smBuff_t					{
				 int						len;
				 char						data[16384];
}		 SM_BUFF;


int  gsmBytes2String(  const  unsigned  char  *  pSrc,  unsigned  char  *  pDst,  int  nSrcLength  );
int  gsmString2Bytes(  const  unsigned  char  *  pSrc,  unsigned  char  *  pDst,  int  nSrcLength  );
int  gsmEncode7bit(  const char* pSrc, unsigned char* pDst, int nSrcLength);
int  gsmDecode7bit(  const  unsigned  char  *  pSrc,  int  nSrcLength,  int  nRealDstLen,  unsigned  char  *  pDstParam,  int  nDstSize  );
int  gsmEncode8bit(  const char* pSrc, unsigned char* pDst, int nSrcLength);
int  gsmDecode8bit(  const unsigned char* pSrc, char* pDst, int nSrcLength);
int  gsmEncodeUcs2(  TP_UDH_concatenatedSm  *  pUdh,  LPCTSTR  pSrc, int  nSrcLength,  unsigned char* pDst,  unsigned  int  nDstSize  );
int  gsmDecodeUcs2(  const  unsigned  char  *  pSrc,  unsigned  int  nSrcLength,  TCHAR  *  pDst,  unsigned  int  nDstSize  );
int  gsmInvertNumbers(  const  unsigned  char  *  pSrc,  unsigned  char  *  pDst,  int  nSrcLength  );
int  gsmSerializeNumbers(  const  char  *  pSrc,  char  *  pDst,  int  nSrcLength  );
int  gsmEncodePdu(  SM_PARAM  *  pSrc, unsigned  char  *  pDst,  unsigned  int  nDstSize  );
int  gsmDecodePdu(  const  unsigned  char  *  pSrc,  SM_PARAM  *  pDst  );


int gsmSendMessage(  HANDLE  hComm,  SM_PARAM* pSrc);
int gsmReadMessageList(  HANDLE  hComm  );
int gsmDeleteMessage(  HANDLE  hComm,  int index);

int gsmGetResponse(  HANDLE  hComm,  SM_BUFF* pBuff);

int gsmParseMessageList(SM_PARAM* pMsg, SM_BUFF* pBuff);


#endif  // !defined(__SMS_H__)
