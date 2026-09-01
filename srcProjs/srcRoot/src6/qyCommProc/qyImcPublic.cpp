
#include	"stdafx.h"

#include	<stdlib.h>
#include	<string.h>
#include	<windows.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qyImcComm.h"
#include	"qyImcCommProc.h"
#include	"qyImcPublic.h"

// 表l 	证件类型代码表
//

 QIM_CERTTYPEITEM	 CONST_qimCertTypeTable[]  =
{
#if  0
	{	(char*)"11",	(char*)"身份证",	},	//
	{	(char*)"15",	(char*)"学生证",	},
	{	(char*)"90",	(char*)"军官证",	},
	{	(char*)"91",	(char*)"警官证",	},	//		武警现役干部的身份证件	
	{	(char*)"92",	(char*)"士兵证",	},
	{	(char*)"93",	(char*)"户口簿",	},
	{	(char*)"94",	(char*)"护照",		},
	{	(char*)"95",	(char*)"台胞证",	},
	{	(char*)"96",	(char*)"回乡证",	},
	{	(char*)"99",	(char*)"其他证件",	},
#endif
	//
	 {	(char*)"99",	(char*)"",	},

};

 int  getItemsCnt_CONST_qimCertTypeTable( )
{
	 return  sizeof(  CONST_qimCertTypeTable  )  /  sizeof(  QIM_CERTTYPEITEM  );
}


// 表2 	网吧状态代码表								//	代码	网吧状态	说 明	
//												
QIM_BARSTATUSITEM	CONST_qimBarStatusTable[]  =
{
#if  0
	{	(char*)"1",	(char*)"装机开业在线",		},				//	表示网吧开业并且安装了网吧安全管理软件，现在正上网	
	{	(char*)"2",	(char*)"装机开业离线",		},				//	表示网吧开业并且安装了网吧安全管理软件，现在没上网	
	{	(char*)"3",	(char*)"装机停业",			},				//	表示网吧停业但安装了网吧安全管理软件	
	{	(char*)"4",	(char*)"未装机开业",		},				//	表示网吧开业但还没有安装网吧安全管理软件	
	{	(char*)"5",	(char*)"未装机停业",		},				//	表示网吧停业并且没有安装网吧安全管理软件	
	{	(char*)"9",	(char*)"其他",				},
#endif
	//
	{	(char*)"0",	(char*)"",				},

};

 char  *  qimBarStatusStr(  char  *  pStatus  )
{
	 int	i;
	 int	lastIndex;

	 for  (  i  =  0;	i  <  sizeof(  CONST_qimBarStatusTable  )  /  sizeof(  QIM_BARSTATUSITEM  );  i  ++  )  {
		  if  (  !strcmp(  pStatus,  CONST_qimBarStatusTable[i].dm  )  )  
			  return  CONST_qimBarStatusTable[i].zt;
	 }
	 lastIndex  =  i  -  1;

	 return  CONST_qimBarStatusTable[lastIndex].zt;
		
}

 char * qimBarStatusFromStr(  char * pStatusStr  )
{
	 int	i;

	 for  (  i  =  0;	i  <  sizeof(  CONST_qimBarStatusTable  )  /  sizeof(  QIM_BARSTATUSITEM  );  i  ++  )  {
		  if  (  !strcmp(  pStatusStr,  CONST_qimBarStatusTable[i].zt  )  )  
			  return  CONST_qimBarStatusTable[i].dm;
	 }

	 return  CONST_qimBarStatusQtDm;
		 
}

// 表3 	网吧报警事件级别代码表
//													//	代码	说明	
QIM_WARNLEVELTABLE	CONST_qimWarnLevelTablt  =
{
	(char*)"1",		//	I
	(char*)"2",		//	II	
	(char*)"3",		//	III
};				//	备注：I、II和III代表触发报警的事件程度分别是严重、中等和一般。


// 表4 	网吧处罚结果代码表
//												//	代码	说明	描述

QIM_PROCRESULTTABLE  CONST_qimProcResultTable  =
{
	1,
};

// 表5 	服务类型代码表
//												//	代码	说明	
 QIM_DMITEM  CONST_qimServiceTypeTable[]  =
{	
	(char*)"01",		(char*)"HTTP",
	(char*)"02",		(char*)"FTP",
	(char*)"03",		(char*)"SMTP",
	(char*)"04",		(char*)"POP",
	(char*)"05",		(char*)"TELNET",
	(char*)"06",		(char*)"ICQ",
	(char*)"07",		(char*)"NNTP",
	(char*)"99",		(char*)"其他",
	(char*)"",			(char*)"",
};


//  qyIpFormat(  )将网吧安全管理传输规范的ip格式转成标准格式
 extern  "C"  char  *  qyIpFormat(	char  *  ip,  char  *  buf,  int  size  )
{
	 char	tmpBuf[4][4];

	 if  (  size  <  QY_MAXIPLEN  +  1  )  return  NULL;
	 memset(  tmpBuf,  0,  sizeof(  tmpBuf  )  );
	 memcpy(  tmpBuf[0],  ip,  3  );
	 memcpy(  tmpBuf[1],  ip + 3,  3  );
	 memcpy(  tmpBuf[2],  ip + 6,  3  );
	 memcpy(  tmpBuf[3],  ip + 9,  3  );
	 sprintf(  buf,  "%d.%d.%d.%d",  atol(  tmpBuf[0]  ),  atol(  tmpBuf[1]  ),  atol(  tmpBuf[2]  ),  atol(  tmpBuf[3]  )  );

	 return  buf;	 

}

 //  qyMcIpFormat(  )将标准格式的ip转成网吧安全管理传输规范的格式
 extern  "C"  char  *  qyMcIpFormat(  char  *  ip,  char  *  buf,  int  size  )
{
	 long  l1,l2,l3,l4;

	 if  (  size  < 12 + 1  ) return NULL;
	 if  (  sscanf( ip, "%d.%d.%d.%d", &l1, &l2, &l3, &l4 ) != 4  )  return NULL;
	 sprintf(  buf, "%03d%03d%03d%03d", l1, l2, l3, l4  );
	 return  buf;	 
}
 

// 0 bit, TRUE表禁止, FALSE表通过
// 1 bit, TRUE表记录，FALSE表不记录
QIM_DMITEM	CONST_imPolicyTable[]  =
{	
#if 0
	(char*)"01",		(char*)"禁止但不记录",
	(char*)"00",		(char*)"通过但不记录",
	(char*)"02",		(char*)"通过并记录",
	(char*)"03",		(char*)"禁止并记录",
#endif
	(char*)"",			(char*)"",
};

// 0 bit, TRUE表禁止网吧端查看，FALSE表允许
QIM_DMITEM	CONST_bmPolicyTable[]  =
{
#if  0
	(char*)"01",		(char*)"禁止网吧端查看",
	(char*)"00",		(char*)"允许网吧端查看",
#endif
	//
	(char*)"",			(char*)"",
};


 char  *  getQimDmItemDes(  QIM_DMITEM * pDms,  char * dm,  int defaultIndex  )
{
	 int	i;

	 for  (  i  =  0;  pDms[i].dm[0];  i  ++  )  {
		  if  (  strcmp(  pDms[i].dm,  dm  )  )  continue;
		  break;
	 }
	 
	 return  pDms[i].dm[0] ? pDms[i].des : pDms[defaultIndex].des;

}

 char  *  getQimDmItemDm(  QIM_DMITEM  *  pDms,  char * des,  int defaultIndex  )
{
	 int	i;

	 for  (  i  =  0;  pDms[i].dm[0];  i  ++  )  {
		  if  (  strcmp(  pDms[i].des,  des  )  )  continue;
		  break;
	 }

	 return  pDms[i].dm[0]  ?  pDms[i].dm  :  pDms[defaultIndex].dm;

}

 char  *  imPolicyStr(  char * policyType  )
{
	 return  getQimDmItemDes(  CONST_imPolicyTable,  policyType,  0  );
}

 char  *  imPolicyFromStr(  char * str  )
{
	 return  getQimDmItemDm(  CONST_imPolicyTable,  str,  0  );
}

 char  *  bmPolicyStr(  char * policyType  )
{
	 return  getQimDmItemDes(  CONST_bmPolicyTable,  policyType,  0  );
}
 
 char  *  bmPolicyFromStr(  char * str  )
{
	 return  getQimDmItemDm(  CONST_bmPolicyTable,  str,  0  );
}


 char  *  qimServiceTypeStr(  char * serviceType  )
{

	 return  getQimDmItemDes(  CONST_qimServiceTypeTable,  serviceType,  0  );
	 
}

 char  *  qimServiceTypeFromStr(  char  *  str  )
{
	 return  getQimDmItemDm(  CONST_qimServiceTypeTable,  str,  0  );
}

