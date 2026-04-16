
#ifndef  __ADDTXT_H__
#define  __ADDTXT_H__

//
#include	"qisTrace_open.h"

//  2014/11/16
#define		MAX_tBufCnt_subtitle									128	//  96

//
typedef  struct  __addTxtMem_t										{
				 
					 HFONT											hFont;
					 //
					 SIZE											size_GetTextExtentPoint32;
					 //  2014/12/24
					 int											shadow_xOffset;
					 int											shadow_yOffset;
					 //
					 //  2011/12/16. 为添加文字的专用img的buf
					 BITMAPINFOHEADER								bih_txt;
					 int											iTxtBufSize;
					 char									*		pTxtBuf;

					 //  2013/12/20
					 TCHAR											subtitle0_defaultTag[MAX_tBufCnt_subtitle];	//  
					 time_t											tTime;										//  2014/12/19

					 //
					 SUBTITLE_cfg_tickCnts							tickCnts;

					 //  2016/02/13. 2016/05/15
					 //int											addTxtCfgIndex;

}		 ADD_txt_mem;


//
//  2016/05/19
typedef  struct			{
			M_qisTrace_commonMems

			//
			BOOL		bChanged_tickCnts;
			BOOL		bChanged_defaultTag;
			BOOL		bChanged_tTime;
			//
			TCHAR		tBuf[128];
		
}		 QIS_trace_txt_change;



#if  0
typedef  struct  __addTxtSth_t										{
				 //
				 //  TCHAR												subtitle0_defaultTag[128];
				 //char												timeBuf[CONST_qyTimeLen  +  1];
}		 ADD_txt_sth;
#endif


//  2013/03/10
typedef  struct  __ctx_addTxt_t										{
				 SUBTITLES_cfg										subtitlesCfg;
				 //
				 //ADD_txt_sth										sth;

				 //
				 ADD_txt_mem										mems[MAX_subtitlesCfg_mems];

}		 CTX_addTxt;


void  ADD_txt_mem_free(  ADD_txt_mem  *  pMem  );

//  void  CTX_addTxt_free(  void  *  pCTX_addTxt  );
void  CTX_addTxt_free(  CTX_addTxt  *  pCTX  );


SUBTITLE_cfgEx  *  addTxt_getMemCfgByIndex(  CTX_addTxt  *  pCtx_addTxt,  int  addTxtCfgIndex  );
ADD_txt_mem  *  addTxt_getMemByIndex(  CTX_addTxt  *  pCtx_addTxt,  int  addTxtIndex  );



//
int  updateImg_addTxt( QY_MC  *  pQyMc, LPCTSTR  videoHint,  BITMAPINFO  *  pBmi_pic,  BOOL  bLine0,  	SUBTITLE_cfgEx  *  pMemCfg,  ADD_txt_mem  *  pMem,  BOOL  *  pbModified_img,  LPCTSTR  dbgHint  );
BOOL  bNeedUpdate_addTxt(  LPCTSTR  videoHint,  BITMAPINFO  *  pBmi_pic,  BOOL  bLine0,  	SUBTITLE_cfgEx  *  pMemCfg,  ADD_txt_mem  *  pMem,  BOOL  *  pbModified_img,  QIS_trace_txt_change  *  pChange  );
int  getRealTxt_addTxt(  LPCTSTR  videoHint,  BOOL  bDemo,  BOOL  bLine0,  SUBTITLE_cfgEx  *  pMemCfg,  ADD_txt_mem  *  pMem,  TCHAR  *  txt,  int  cnt_txt  );





#endif

