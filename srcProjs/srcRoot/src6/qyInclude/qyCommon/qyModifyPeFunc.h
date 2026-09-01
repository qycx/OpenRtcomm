

#ifndef  __QYMODIFYPEFUNC_H__
#define  __QYMODIFYPEFUNC_H__	/*  {  */


#define		CONST_qySize_cfgs						1024	//  参与配置的参数区大小, 不宜太大

#define		CONST_qyCfgSym							"<**QY_CFG**>"
#define		CONST_qyCfgSym_regTool					"<**QY_CFG_REGTOOL**>"
#define		CONST_qyCfgSym_qnmProxy					"<**QY_CFG_QNMPROXY**>"


typedef  struct  {
				int		nPlugin;
				DWORD	dwPos;
				char	VarType; // B, N, S
				int		nNumLo;
				int		nNumHi;
				int		nStrLen;
				char	svVarValue[256];
				char	svVarName[256];
				char	svCategory[256];
}		 VARIABLE_INFO;

#ifdef  __cplusplus
 extern  "C"  {
#endif


//  BOOL  bQyUpdateImageData(  char  *  svPath,  char  *  symbol,  char  *  data,  unsigned  int  dataLen  );
BOOL  bQyUpdateImageData(  LPCTSTR  svPath,  char  *  symbol,  char  *  data,  unsigned  int  dataLen  );


#ifdef  __cplusplus
 }
#endif


#endif  /*  }  */


	