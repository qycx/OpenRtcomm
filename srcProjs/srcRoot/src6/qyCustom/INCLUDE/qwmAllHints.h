

#ifndef  __QWMALLHINTS_H__
#define  __QWMALLHINTS_H__	//  {

#include	"qyLangCommProc.h"

typedef  struct  {
		TCHAR	regToolTitle[32  +  1];
		//
		TCHAR	zb[8  +  1];
		TCHAR	bb[12  +  1];								//	2009/01/04	TCHAR	bb[8  +  1];	+4
		TCHAR	dw[8  +  1];								//	2009/01/04	TCHAR	dw[12  +  1];	-4
		TCHAR	qtdw[0  +  1];								//  2009/01/04	TCHAR	qtdw[8  +  1];	-8			
		TCHAR	bm[12  +  1];								//	2009/01/04	TCHAR	bm[8  +  1];	+4
		TCHAR	syr[12  +  1];
		TCHAR	jqlx[8  +  1];
		TCHAR	zyyt[8  +  1];								
		TCHAR	lxdh[12  +  1];
		TCHAR	sydd[12  +  1];								//	2009/01/04	TCHAR	sydd[8  +  1];	+4
		TCHAR	zcbh[10  +  1];
		TCHAR	zcbh1[10  +  1];
		TCHAR	zcbh2[10  +  1];
		TCHAR	zcsm1[12  +  1];
		TCHAR	zcsm2[12  +  1];
		TCHAR	hint0[40  +  1];		
		TCHAR	hint0_reged[40  +  1];		//  2006/04/02
		TCHAR	hint1[64  +  1];
		TCHAR	wj[12  +  1];
		TCHAR	bxj[12  +  1];
		TCHAR	fwq[12  +  1];
		TCHAR	xxj[12  +  1];
		TCHAR	ok[8  +  1];
		TCHAR	cancel[8  +  1];
		//
		TCHAR	ssfwqsb[24  +  1];			//  搜索服务器失败, 2006/07/01
		TCHAR	ljfwqsb[24  +  1];			//  连接服务器失败
		TCHAR	zbgx[8  +  1];				//  "准备更新"
		TCHAR	zbzc[8  +  1];				//  "准备注册"
		TCHAR	gxwwcqcxjx[22  +  1];		//  "更新未完成，请重新进行"  
		TCHAR	wwczcqcxjx[22  +  1];		//  "未完成注册，请重新进行"
		TCHAR	ljfwq[17  +  1];			//  "连接服务器"
		TCHAR	ljfwqsbqcxjx[26  +  1];		//  "连接服务器失败，请重新进行"
		TCHAR	khdbyxdjqlxwlgly[36  +  1];	//  "客户端不允许登记,请联系网络管理员"
		TCHAR	zcrjbbbfqcxxz[30  +  1];	//  "注册软件版本不符。请重新下载。"
		TCHAR	zcjsjxx[18  +  1];			//  "注册计算机信息"
		TCHAR	wc[8  +  1];				//  "完成"
		TCHAR	zcwb[12  +  1];				//  "注册完毕"
		TCHAR	wwcqcxjx[22  +  1];			//  "未完成，请重新进行"
		TCHAR	bt[15  +  1];				//  "必填"

}		QWM_ALL_HINTS;


extern  QWM_ALL_HINTS	gAllHints;


#endif  //  }


