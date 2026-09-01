

#ifndef  __QYMCDLGBARCFG_H__
#define	 __QYMCDLGBARCFG_H__	/*  {  */


typedef  struct  __barBtnCfg_t			{
				 UINT					uId;
				 int					iIcon;
}				 BAR_BTN_CFG;


#define		CONST_qyBarBtns				10
#define		NUM_BARBTNS					CONST_qyBarBtns 


typedef  struct  __barCfg_t				{
				int						n; 
				struct					{
					char  *				name;	
					int					status;
				}						btns[NUM_BARBTNS];
}		 BAR_CFG;


#endif	/*  }  */


