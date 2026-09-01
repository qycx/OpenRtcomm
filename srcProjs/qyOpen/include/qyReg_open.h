
#ifndef  __qyReg_open_h__
#define  __qyReg_open_h__	//  {

//
#include	"qyDefs_open.h"




//
typedef  struct  __qyReg_t {
	void* pEncCtx;
	HKEY			hKeyRoot0;			//  2003/09/12, 取HKEY_CLASSES_ROOT,HKEY_CURRENT_CONFIG,HKEY_CURRENT_USER,等
	//  char			rootKey[CONST_qyMaxRegKeyLen  +  1];
	TCHAR			rootKey[CONST_qyMaxRegKeyLen + 1];

	unsigned  int	uiType;				//  2004/08/06, RegQueryValueEx(  )调用后的值的类型
	unsigned  int	uiDataLen;			//  2005/07/03
}		  QY_REG;



#endif  //  }



