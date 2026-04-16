
#ifndef  __QWMDJCOMMPROC_H__
#define  __QWMDJCOMMPROC_H__		//  {

#define		CONST_subDir_dat				"qyDat"
//
#define		CONST_qyFileObj_djMagic			"qyDjDat"
#define		CONST_qyFileObj_djVer			"ver"
#define		CONST_qyFileObj_djMac			"mac"		//  后面都跟一个'='
#define		CONST_qyFileObj_djDw			"dw"		//  
#define		CONST_qyFileObj_djBm			"bm"
#define		CONST_qyFileObj_djSyr			"syr"
#define		CONST_qyFileObj_djEnd			"objEnd"	//  
//
#define		CONST_maxDjValLen				128


#ifdef  __cplusplus
  extern  "C"  {
#endif

 int  getQwmFileObj(  LPCTSTR  fileName,  char  *  objName,  char  *  val,  unsigned  int  size  );		//  文件采用utf8格式存储


#ifdef  __cplusplus
  }
#endif


#endif  //  }


