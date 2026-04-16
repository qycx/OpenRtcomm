
// testOpenCVDlg.h: 头文件
//

#pragma once
#ifdef _EXPORTING
#define _DLL_API _declspec(dllexport)
#else
#define _DLL_API _declspec(dllimport)
#endif

#ifdef __cplusplus
// CtestOpenCVDlg 对话框
class CtestOpenCVDlg 
{
// 构造
public:
	CtestOpenCVDlg();
	~CtestOpenCVDlg();
};



extern "C"
{
	_DLL_API int DoMvs(void* p, bool& stop);
}


#endif
