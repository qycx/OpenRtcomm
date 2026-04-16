

#ifndef  __subtitles_h__
#define  __subtitles_h__	//  {


//  2013/03/10
typedef  struct  __subtitleCfg_t		{
				 //
				 struct					{
					 LOGFONT			lf;
					 int				iFontSize;				//     INT             iPointSize;         // 10 * size in points of selected font
					 //
					 unsigned  char		ucbFixedSize;
				 }						font;
				 //
				 struct					{					 
					 //  COLORREF		fontColor;
					 unsigned  char		fontColor_r;
					 unsigned  char		fontColor_g;
					 unsigned  char		fontColor_b;

					 //
					 //  COLORREF		maskColor;
					 unsigned  char		maskColor_r;
					 unsigned  char		maskColor_g;
					 unsigned  char		maskColor_b;
					 
					 //  2014/12/08
					 struct					{
						 unsigned  char		ucbUsePath;				//  2014/12/08
						 //
						 unsigned  char		color_edge_r;
						 unsigned  char		color_edge_g;
						 unsigned  char		color_edge_b;
						 //
						 int				cWidth_pen;
						 //
						 unsigned  char		ucbFilled;

					 }						usePath;
					 
					 //
				 }							color;					//  color里的改变需要重新生成txtImg
 
				 //
				 struct					{
					 TCHAR				txt[64  +  1];
					 unsigned  char		ucbUseDefault;			//  如果注册表里没有txt字符串，就表示使用default
					 //
					 unsigned  char		ucbDisplayTime;
				 }						tag;
				 
				 //
				 struct					{
					 //
					 int				xStart;
					 int				yStart;
					 unsigned  char		ucbBottomUp;

					 //  2014/12/22
					 unsigned  char		ucbHorizontalCenter;

				 }						pos;


}		 SUBTITLE_cfg;

//
typedef  struct  __subtitleCfgTickCnts_t	{
				 //				
				 //  DWORD						dwModifiedTickCnt_flgs;
				 //
				 DWORD						dwModifiedTickCnt_font;
				 DWORD						dwModifiedTickCnt_color;
				 DWORD						dwModifiedTickCnt_tag;
				 //
				 DWORD						dwModifiedTickCnt_pos;

}		 SUBTITLE_cfg_tickCnts;







//
#define		MAX_subtitlesCfg_mems			15	//  
#define		CONST_realMax_subtitles			12	//  2014/12/21

//
typedef  struct  __subtitleCfgEx_t			{
				 SUBTITLE_cfg				subtitle;
				 SUBTITLE_cfg_tickCnts		tickCnts;
}		 SUBTITLE_cfgEx;

typedef  struct  __subtitlesCfg_t			{
				 struct						{
					 unsigned  char			ucbShowVideoHint;
					 unsigned  char			ucbEffectiveImmediately;
				 }							flgs;

				 //  2014/12/16. mems[i]里的尺寸都是根据wnd_w_org, wnd_h_org制定的，所以，当窗口高度变化时，应按比例伸缩. 为保持原字体宽高比，用wnd_h_org一个计算因子
				 int						wnd_w_org_unused;
				 int						wnd_h_org;

				 //
				 SUBTITLE_cfgEx				mems[MAX_subtitlesCfg_mems];
				 //
				 DWORD						dwModifiedTickCnt_any_start;
				 DWORD						dwModifiedTickCnt_any_end;

}											SUBTITLES_cfg;


//
int  saveSubtitlesCfg(  int  iCapType,  int  iCapSubType,  int  iUsage,  SUBTITLES_cfg  *  pSubtitlesCfg  );

//
int  SUBTITLES_cfg_update(  SUBTITLES_cfg  *  pInput,  int  wnd_w,  int  wnd_h,  SUBTITLES_cfg  *  pReal  );




#endif  //  }


