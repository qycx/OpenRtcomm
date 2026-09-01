

#include	"stdafx.h"

#include	<windows.h>
#include	<MMSystem.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qwmAllHints.h"


#include	"qyCusResPublic.h"
#include	"qnmResDefs.h"
#include	"qyCusResTemp.h"
#include	"qmOpenCommon.h"


 QWM_ALL_HINTS	gAllHints;	//  
 
#define		MACRO_setHint(  src,  dst  )	lstrcpyn(  gAllHints.dst,  src,  mycountof(  gAllHints.dst  )  );
 int  setAllHints(  void  *  pResInfoParam,  unsigned  short  usLangId  )
{
	QNM_CUSRES_INFO	*	pCusRes	=	(  QNM_CUSRES_INFO  *  )pResInfoParam;							//  2005/11/03

	 memset(  &gAllHints,  0,  sizeof(  gAllHints  )  );

	 //
	 if  (  !pCusRes  ||  !pCusRes->hDll  )  return  -1;

	 //
	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc0_zongBu  ),	zb		);
	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc2_benBu  ),	bb		);
	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc4_danWei  ),	dw		);
	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc8_buMen  ),	bm		);
	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc10_shiYongRen  ),	syr		);
	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc12_jiQiLeiXing  ),	jqlx	);
	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc16_zhuYaoYongTu  ),	zyyt	);
 	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc18_lianXiDianHua  ),	lxdh	);
 	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc20_shiYongDiDian  ),	sydd	);
 	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc14_ziChanBianHao  ),	zcbh	);
 	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc24_ziChanBianHao1  ),	zcbh1	);
 	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc28_ziChanBianHao2  ),	zcbh2	);
 	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc26_ziChanShuoMing1  ),	zcsm1	);
 	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_pc30_ziChanShuoMing2  ),	zcsm2	);
 	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_y  ),	ok		);
 	 MACRO_setHint(  getResStr(  0,  pCusRes,  CONST_resId_n  ),	cancel	);





	 /*
		 MACRO_setHint(  "总部",			zb		);
		 MACRO_setHint(  "本部",			bb		);
		 MACRO_setHint(  "单位",			dw		);
		 MACRO_setHint(  "其他单位",		qtdw	);
		 MACRO_setHint(  "部门",			bm		);
		 MACRO_setHint(  "使用人",			syr		);
		 MACRO_setHint(  "机器类型",		jqlx	);
		 MACRO_setHint(  "主要用途",		zyyt	);
		 MACRO_setHint(  "联系电话",		lxdh	);
		 MACRO_setHint(  "使用地点",		sydd	);
		 MACRO_setHint(  "资产编号",		zcbh	);
		 MACRO_setHint(  "资产编号1",		zcbh1	);
		 MACRO_setHint(  "资产编号2",		zcbh2	);
		 MACRO_setHint(  "资产说明1",		zcsm1	);
		 MACRO_setHint(  "资产说明2",		zcsm2	);
		 MACRO_setHint(  "使用人登录时填写下表(*表示必填项)",	hint0	);
		 MACRO_setHint(	 "请您在2005年 月 日前完成上表登记，过期将无法登录网络",	hint1  );
		 MACRO_setHint(  "微机",			wj		);
		 MACRO_setHint(	 "便携机",			bxj		);
		 MACRO_setHint(  "服务器",			fwq		);
		 MACRO_setHint(  "小型机",			xxj		);
		 MACRO_setHint(  "确定",			ok		);
		 MACRO_setHint(  "取消",			cancel	);

*/


	 return  0;
}


