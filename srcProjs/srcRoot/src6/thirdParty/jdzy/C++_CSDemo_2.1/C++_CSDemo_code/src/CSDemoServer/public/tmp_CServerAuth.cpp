

#include "stdafx.h"
#include "CSDemoServer.h"
#include "CSDemoServerDlg.h"

#define  __CServerAuth_body__

#include "CServerAuth.h"


/*
 * 当libjpeg-turbo为vs2010编译时，vs2015下静态链接libjpeg-turbo会链接出错:找不到__iob_func,
 * 增加__iob_func到__acrt_iob_func的转换函数解决此问题,
 * 当libjpeg-turbo用vs2015编译时，不需要此补丁文件
 */

/*
#if _MSC_VER>=1900
#include "stdio.h" 
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned);
#ifdef __cplusplus 
extern "C"
#endif 
FILE * __cdecl __iob_func(unsigned i) {
    return __acrt_iob_func(i);
}
#endif 
*/
/* _MSC_VER>=1900 */
