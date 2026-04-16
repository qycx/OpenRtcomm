

#ifndef  __QNMHOTKEYS_H__
#define  __QNMHOTKEYS_H__	//  {


typedef  struct  __qyMcHotKey_t  {
				 int	id;				//	identifier of hot key
				 UINT	fsModifiers;	//	key-modifier flags
				 UINT	vk;				//	virtual-key code
				 BOOL	bRegistered;	//  是否已注册成功

}		 QYMC_HOTKEY;


#ifdef  __cplusplus
  extern  "C"  {
#endif


 //  extern  QYMC_HOTKEY	gHotKeys_main[];
 //  extern  QYMC_HOTKEY	gHotKeys_qrt[];


BOOL bQnmAddHotKeys(  QYMC_HOTKEY  *  pHotKeys,  HWND  hWnd  );
void qnmRemoveHotKeys(  QYMC_HOTKEY  *  pHotKeys,  HWND  hWnd  );



#ifdef  __cplusplus
  }
#endif


#endif  //  }

