

#ifndef  __QYHOOKHELP_H__
#define  __QYHOOKHELP_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

 __declspec(dllexport)  BOOL InstallMyHook(HWND hWnd, UINT msg);
 __declspec(dllexport)  BOOL UninstallMyHook(HWND hWnd);

#undef LIBSPEC

#ifdef __cplusplus
}
#endif // __cplusplus


#define		CONST_wmStr_avRecord_cursor			_T(  "WM_avRecord_cursor"  )
#define		CONST_wmStr_avRecord_start			_T(  "WM_avRecord_start"  )
#define		CONST_wmStr_avRecord_stop			_T(  "WM_avRecord_stop"  )



#endif


