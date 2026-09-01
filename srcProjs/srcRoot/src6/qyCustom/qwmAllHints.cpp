
//#include	"stdafx.h"

#include	<WinSock2.h>
#include	<windows.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qwmAllHints.h"
#include	"qyTCharCommProc.h"



QWM_ALL_HINTS	gAllHints;
//  #define		MACRO_setHint(  src,  dst  )	myStr2TChar(  src,  gAllHints.dst,  sizeof(  gAllHints.dst  )  /  sizeof(  TCHAR  )  );
//  #define		MACRO_setHint(  src,  dst  )	lstrcpyn(  gAllHints.dst,  _T(  src  ),  sizeof(  gAllHints.dst  )  /  sizeof(  TCHAR  )  );
#define		MACRO_setHint(  src,  dst  )	myWChar2TChar(  L  ##  src,  gAllHints.dst,  sizeof(  gAllHints.dst  )  /  sizeof(  TCHAR  )  );

 int  setAllHints(  unsigned  short  usLangId  )
{
	 memset(  &gAllHints,  0,  sizeof(  gAllHints  )  );

	 if  (  usLangId  ==  CONST_langId_PRC  )  {
		 MACRO_setHint(  "计算机登记表",	regToolTitle  );
		 //
		 MACRO_setHint(  "总部",			zb		);
		 MACRO_setHint(  "本部",			bb		);
		 MACRO_setHint(  "单位",			dw		);
		 MACRO_setHint(  "其他单位",		qtdw	);
		 MACRO_setHint(  "部门",			bm		);
		 MACRO_setHint(  "使用人 ",			syr		);
		 MACRO_setHint(  "机器类型",		jqlx	);
		 MACRO_setHint(  "主要用途 ",		zyyt	);
		 MACRO_setHint(  "联系电话",		lxdh	);
		 MACRO_setHint(  "使用地点",		sydd	);
		 MACRO_setHint(  "资产编号",		zcbh	);
		 MACRO_setHint(  "资产编号1",		zcbh1	);
		 MACRO_setHint(  "资产编号2",		zcbh2	);
		 MACRO_setHint(  "资产说明1",		zcsm1	);
		 MACRO_setHint(  "资产说明2",		zcsm2	);
		 MACRO_setHint(  "使用人登录时填写下表",	hint0	);
		 MACRO_setHint(  "请点确定更新.",			hint0_reged  );		//  2006/04/02
		 MACRO_setHint(	 "* 代表必选项",	hint1  );
		 MACRO_setHint(  "微机",			wj		);
		 MACRO_setHint(	 "便携机 ",			bxj		);
		 MACRO_setHint(  "服务器 ",			fwq		);
		 MACRO_setHint(  "小型机 ",			xxj		);
		 MACRO_setHint(  "确定",			ok		);
		 MACRO_setHint(  "取消",			cancel	);
		 //
		 MACRO_setHint(  "搜索服务器失败 ",  ssfwqsb  );
		 MACRO_setHint(  "连接服务器失败 ",	ljfwqsb	);
		 MACRO_setHint(  "准备更新",							zbgx	);
		 MACRO_setHint(  "准备注册",							zbzc	);		 
		 MACRO_setHint(	 "更新未完成，请重新进行 ",				gxwwcqcxjx  );
		 MACRO_setHint(	 "未完成注册，请重新进行 ",				wwczcqcxjx  );
		 MACRO_setHint(	 "连接服务器 ",							ljfwq	);
		 MACRO_setHint(  "连接服务器失败，请重新进行 ",			ljfwqsbqcxjx	);
		 MACRO_setHint(	 "客户端不允许登记，请联系网络管理员 ",	khdbyxdjqlxwlgly  );
		 MACRO_setHint(	 "注册程序版本不符，请联系网络管理员 ",		zcrjbbbfqcxxz  );
		 MACRO_setHint(	 "注册计算机信息 ",						zcjsjxx  );
		 MACRO_setHint(	 "完成",								wc  );
		 MACRO_setHint(	 "注册完毕",							zcwb  );
		 MACRO_setHint(	 "未完成，请重新进行 ",					wwcqcxjx  );
		 MACRO_setHint(  "必填",								bt  );

		}
	 else  {
		   MACRO_setHint(  "Registration Form",	 regToolTitle  );
		   //
		   MACRO_setHint(  "Company",		zb		);
		   MACRO_setHint(  "Branch",		bb		);
		   MACRO_setHint(  "Dept",			dw		);
		   MACRO_setHint(  "Other",			qtdw	);
		   MACRO_setHint(  "Section",		bm		);
		   MACRO_setHint(  "User Name",		syr		);
		   MACRO_setHint(  "PC Type",		jqlx	);
		   MACRO_setHint(  "Usage",			zyyt	);
		   MACRO_setHint(  "Telephone",		lxdh	);
		   MACRO_setHint(  "Place",			sydd	);
		   MACRO_setHint(  "Assets No",		zcbh	);
		   MACRO_setHint(  "Assets No1",	zcbh1	);
		   MACRO_setHint(  "Assets No2",	zcbh2	);
		   MACRO_setHint(  "Assets Desc1",	zcsm1	);
		   MACRO_setHint(  "Assets Desc2",	zcsm2	);
		   MACRO_setHint(  "Please fill in the following form:",	hint0	);
		   MACRO_setHint(  "Please click OK to update.",			hint0_reged  );		//  2006/04/02
		   MACRO_setHint(  "Note: * means the item must be filled in.",  hint1  );
		   MACRO_setHint(  "Desktop",		wj		);
		   MACRO_setHint(  "Notebook",		bxj		);
		   MACRO_setHint(  "Server",		fwq		);
		   MACRO_setHint(  "Minicomputer",	xxj		);
		   MACRO_setHint(  "OK",			ok		);
		   MACRO_setHint(  "Cancel",		cancel	);
		   //
		   MACRO_setHint(  "Can't find the server",					ssfwqsb  );			//  2006/07/01			
		   MACRO_setHint(  "Can't connect to server",				ljfwqsb	);
		   MACRO_setHint(  "Ready to update",						zbgx	);
		   MACRO_setHint(  "Ready to reg",							zbzc	);		 
		   MACRO_setHint(  "Update failed, try again",				gxwwcqcxjx  );
		   MACRO_setHint(  "Reg failed, try again",					wwczcqcxjx  );
		   MACRO_setHint(  "Connect to server",						ljfwq	);
		   MACRO_setHint(  "Connect failed, try again",				ljfwqsbqcxjx	);
		   MACRO_setHint(  "Not allowed to reg, contact admin",		khdbyxdjqlxwlgly  );
		   MACRO_setHint(  "Version error, download again",			zcrjbbbfqcxxz  );
		   MACRO_setHint(  "Reg computer info",						zcjsjxx  );
		   MACRO_setHint(  "Finished",								wc  );
		   MACRO_setHint(  "Reg finished",							zcwb  );
		   MACRO_setHint(  "Not finished, try again",				wwcqcxjx  );
		   MACRO_setHint(  " must be filled",						bt  );


	 }
	 return  0;
}


