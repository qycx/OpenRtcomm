

#ifndef  __IMCLOG_H__
#define  __IMCLOG_H__	/*  {  */


#define		QIM_BARIDLEN						10
#define		QIM_BARNAMELEN						40
#define		QIM_GUESTNAMELEN					30
#define		QIM_PCIDLEN							4
#define		QIM_GUESTNAMELEN					30
#define		QIM_FEELEN							16
#define		QIM_NAMELEN							30
#define		QIM_CERTTYPELEN						2
#define		QIM_CERTIDLEN						18
#define		QIM_OFFICELEN						30
#define		QIM_COUNTRYLEN						10		
#define		QIM_DETAILLEN						30	
#define		QIM_SERVICETYPELEN					2
#define		QIM_KEYTYPENAMELEN					8

// 五类数据格式:

// 类1	顾客信息基本数据交换格式
typedef  struct  __qimGuest_t  {			//		序号 	数据项名称 		数据项类型 	数据项长度 	 备注
				 char	barId[10];			//		1 		网吧编码 		字符 		10
				 char	name[30];			//		2 		姓名 			字符 		30
				 char	certType[2];		//		3 		证件类型		字符 		2 			表1
				 char	certId[18];			//		4 		证件号码 		字符 		18
				 char	startTime[14];		//		5 		上网开始时间 	字符 		14			YYYYMMDDHHMMSS(时间以24小时制表示)
				 char	pcId[4];			//		6 		顾客机器号 		字符 		4
				 char	ip[12];				//		7 		使用机器IP号 	字符 		12			AAABBBCCCDDD
				 char	endTime[14];		//		8 		上网结束时间 	字符 		14
				 char	office[30];			//		9 		单位名 			字符 		30			表示除身份证外的其它证件的发证单位
				 char	country[10];		//		10 		国家名 			字符 		10
				 char	detail[30];			//		11		详细描述 		字符 		30			其它需要备注的内容
}		QIM_GUEST;							//		
											//			顾客信息基本数据交换格式共包含有11个数据项。顾客编码具有唯一性。
											//		其中1、2、3、4、5、6、7、8为不可缺省项，


typedef  struct  __qimGuestC_t		{		//		序号 	数据项名称 		数据项类型 	数据项长度 	 备注
				 char	barId[10 + 1];		//		1 		网吧编码 		字符 		10
				 char	name[30 + 1];		//		2 		姓名 			字符 		30
				 char	certType[2 + 1];	//		3 		证件类型		字符 		2 			表1
				 char	certId[18 + 1];		//		4 		证件号码 		字符 		18
				 char	startTime[14 + 1];	//		5 		上网开始时间 	字符 		14			YYYYMMDDHHMMSS(时间以24小时制表示)
				 char	pcId[4 + 1];		//		6 		顾客机器号 		字符 		4
				 char	ip[12 + 1];			//		7 		使用机器IP号 	字符 		12			AAABBBCCCDDD
				 char	endTime[14 + 1];	//		8 		上网结束时间 	字符 		14
				 char	office[30 + 1];		//		9 		单位名 			字符 		30			表示除身份证外的其它证件的发证单位
				 char	country[10 + 1];	//		10 		国家名 			字符 		10
				 char	detail[30 + 1];		//		11		详细描述 		字符 		30			其它需要备注的内容
}		QIM_GUEST_C;						//		
											//			顾客信息基本数据交换格式共包含有11个数据项。顾客编码具有唯一性。
											//		其中1、2、3、4、5、6、7、8为不可缺省项，


// 类2	网吧信息基本数据交换格式
typedef  struct  __qimBar_t  {				//		序号 	数据项名称 		数据项类型 	数据项长度 	备注
				 char	barId[10];			//		1 		网吧编码		字符 		10 		
				 char	name[40];			//		2 		名称 			字符 		40	
				 char	frdb[30];			//		3 		法定代表人		字符 		30	
				 char	fzr[30];			//		4 		负责人 			字符 		30		
				 char	aqy[30];			//		5 		信息安全员		字符 		30
				 char	addr[40];			//		6 		地址 			字符 		40		
				 char	tel[16];			//		7		联系电话 		字符 		16		
				 char	aqyTel[16];			//		8 		信息安全员电话 	字符 		16
				 char	barStatus[1];		//		9 		状态 			字符 		1 		表2
				 char	nTerms[4];			//		10		终端数 			字符 		4
}		QIM_BAR;							//
											//			网吧信息基本数据交换格式共包含有10个数据项。网吧编码具有唯一性。
											//		其中1、2、3、4、6、7、9为不可缺省项，其余由各地网络安全监察部门酌情选用。
typedef  struct  __qimBarC_t  {				//		序号 	数据项名称 		数据项类型 	数据项长度 	备注
				 char	barId[10 + 1];		//		1 		网吧编码		字符 		10 		
				 char	name[40 + 1];		//		2 		名称 			字符 		40	
				 char	frdb[30 + 1];		//		3 		法定代表人		字符 		30	
				 char	fzr[30 + 1];		//		4 		负责人 			字符 		30		
				 char	aqy[30 + 1];		//		5 		信息安全员		字符 		30
				 char	addr[40 + 1];		//		6 		地址 			字符 		40		
				 char	tel[16 + 1];		//		7		联系电话 		字符 		16		
				 char	aqyTel[16 + 1];		//		8 		信息安全员电话 	字符 		16
				 char	barStatus[1 + 1];	//		9 		状态 			字符 		1 		表2
				 char	nTerms[4 + 1];		//		10		终端数 			字符 		4

}		QIM_BAR_C;							//
											//			网吧信息基本数据交换格式共包含有10个数据项。网吧编码具有唯一性。
											//		其中1、2、3、4、6、7、9为不可缺省项，其余由各地网络安全监察部门酌情选用。


// 类3	网吧处罚结果信息基本数据交换格式
typedef  struct  __qimProcResult_t  {			//		序号 	数据项名称 		数据项类型 	数据项长度 	备注
				 char	barId[10 + 1];		//		1 		网吧编码 		字符 		10
				 char	day[8 + 1];			//		2 		处罚日期 		字符 		8		YYYYMMDD
				 char	result[2 + 1];		//		3		网吧处罚结果 	字符 		2 		表4
}		 QIM_PROCRESULT;



// 类4	网吧日志信息基本数据交换格式

typedef  struct  __qimLogRcd_t  {			//		序号 	数据项名称 		数据项类型 	数据项长度 	备注
				 char	barId[10];			//		1 		网吧编码 		字符 		10
				 char	ip[12];				//		2 		上网顾客IP地址 	字符 		12			AAABBBCCCDDD
				 char	pcId[4];			//		3 		上网顾客机器号 	字符 		4
				 char	startTime[14];		//		4 		访问启始时间 	字符 		14			YYYYMMDDHHMMSS(时间以24小时制表示)
				 char	url[50];			//		5 		顾客访问的URL 	字符 		50
				 char	serviceType[2];		//		6 		服务类型		字符 		2			表5
				 char	detail[100];		//		7		详细描述		字符 		100 		针对不同服务存放相应的内容。如：SMTP								的收发信箱地址；ICQ的ICQ号等。
}		QIM_LOGRCD;


typedef  struct  __qimLogRcdC_t  {		//		序号 	数据项名称 		数据项类型 	数据项长度 	备注
				 char	barId[10 + 1];		//		1 		网吧编码 		字符 		10
				 char	ip[12 + 1];			//		2 		上网顾客IP地址 	字符 		12			AAABBBCCCDDD
				 char	pcId[4 + 1];		//		3 		上网顾客机器号 	字符 		4
				 char	startTime[14 + 1];	//		4 		访问启始时间 	字符 		14			YYYYMMDDHHMMSS(时间以24小时制表示)
				 char	url[50 + 1];		//		5 		顾客访问的URL 	字符 		50
				 char	serviceType[2 + 1];	//		6 		服务类型		字符 		2			表5
				 char	detail[100 + 1];	//		7		详细描述		字符 		100 		针对不同服务存放相应的内容。如：SMTP								的收发信箱地址；ICQ的ICQ号等。
}		QIM_LOGRCD_C;



// 类5	报警信息基本数据交换格式
typedef  struct  __qimWarn_t  {				//		序号 	数据项名称 		数据项类型 	数据项长度 	备注
				 char	barId[10 + 1];			//		1 		网吧编码 		字符 		10
				 char	barWarnTime[14 + 1];	//		2 		网吧报警时间 	字符 		14		同上
				 char	cntWarnTime[14 + 1];	//		3 		控制中心报警时间 字符 		14		
				 char	srcIp[12 + 1];			//		4 		源内部IP地址 	字符 		12		AAABBBCCCDDD
				 char	pcNo[4 + 1];			//		5 		上网顾客机器号 	字符 		4		
				 char	url[50 + 1];			//		6 		目的地址的URL 	字符 		50
				 char	serviceType[2 + 1];		//		7 		服务类型 		字符 		2		表5
				 char	customerName[30 + 1];	//		8 		上网顾客姓名 	字符 		30
				 char	customerCertType[2 + 1];//		9 		上网顾客证件类型 字符 		2		表1
				 char	customerCertId[18 + 1];	//		10 		上网顾客证件号码 字符 		18
				 char	customerOffice[30 + 1];	//		11		上网顾客发证单位 字符 		30
				 char	level[1 + 1];			//		12 		网吧报警事件级别代码 字符 	1		表3
				 char	comment[100 + 1];		//		13		报警信息备注 	字符 		100		针对不同服务存放相应的内容。如：SMTP								的收发信箱地址；ICQ的ICQ号等。
}		QIM_WARN;


// 表l 	证件类型代码表
//										
typedef  struct  __qimCertTypeItem_t  {
				 char	*	dm;
				 char	*	lx;
}		 QIM_CERTTYPEITEM;

typedef  struct  __qimDmItem_t  {
				 char	*	dm;
				 char	*	des;
}		 QIM_DMITEM;

#define		CONST_qimCertTypeSfzDm		CONST_qimCertTypeTable[0].dm
#define		CONST_qimCertTypeHzDm		CONST_qimCertTypeTable[6].dm
#define		CONST_qimCertTypeTbzDm		CONST_qimCertTypeTable[7].dm
#define		CONST_qimCertTypeHxzDm		CONST_qimCertTypeTable[8].dm


// 表2 	网吧状态代码表
//											//	代码	网吧状态	说 明	
typedef  struct  __qimBarStatusItem_t	{
				 char	*	dm;
				 char	*	zt;
}		 QIM_BARSTATUSITEM;

#define	CONST_qimBarStatusZjkyzxDm		CONST_qimBarStatusTable[0].dm
#define	CONST_qimBarStatusZjkylxDm		CONST_qimBarStatusTable[1].dm
#define	CONST_qimBarStatusZjtyDm		CONST_qimBarStatusTable[2].dm
#define	CONST_qimBarStatusWzjkyDm		CONST_qimBarStatusTable[3].dm
#define	CONST_qimBarStatusWzjtyDm		CONST_qimBarStatusTable[4].dm
#define	CONST_qimBarStatusQtDm			CONST_qimBarStatusTable[5].dm


// 表3 	网吧报警事件级别代码表
//													//	代码	说明	
typedef  struct  __qimWarnLevelTable_t  {
				 char  *  I;						//	1	I	
				 char  *  II;						//	2	II	
				 char  *  III;						//  3	III
}		QIM_WARNLEVELTABLE;						//	备注：I、II和III代表触发报警的事件程度分别是严重、中等和一般。


// 表4 	网吧处罚结果代码表
//												//	代码	说明	描述
typedef  struct  __qimProcResultTable_t  {
		 int	 i;
}		QIM_PROCRESULTTABLE;

// 表5 	服务类型代码表
//												//	代码	说明	



extern  QIM_CERTTYPEITEM		CONST_qimCertTypeTable[];
extern  QIM_BARSTATUSITEM		CONST_qimBarStatusTable[];
extern  QIM_WARNLEVELTABLE		CONST_qimWarnLevelTablt;
extern  QIM_PROCRESULTTABLE		CONST_qimProcResultTable;
extern  QIM_DMITEM				CONST_qimServiceTypeTable[];

#define		CONST_qimServiceTypeDefault	CONST_qimServiceTypeTable[0]
#define		CONST_qimServiceTypeHttp	CONST_qimServiceTypeTable[0]

char  *  qimBarStatusStr(  char  *  pStatus  );
char  *  qimBarStatusFromStr(  char * pStatusStr  );
int  getItemsCnt_CONST_qimCertTypeTable(  );



typedef  struct  __qimCommBuf_t {
			int	 len;
			union	{
				QIM_LOGRCD	logRcd;
			}		u;
}		 QIM_COMMBUF;


extern  "C"  char  *  qyIpFormat(	char  *  ip,  char  *  buf,  int  size  );
extern "C" char * qyMcIpFormat( char * ip, char * buf, int size  );
// int qyImcTellService(  char * barId, SOCK_TIMEOUT * pTo, QY_SOCK * pSock, QY_COMM_SESSION * pSession  );




#endif	/* }  */



