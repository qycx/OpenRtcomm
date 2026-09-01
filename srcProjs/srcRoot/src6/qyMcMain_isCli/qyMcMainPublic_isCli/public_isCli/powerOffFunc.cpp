
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include    "ctxQmc.h"
#include    "powerOffFunc.h"





bool improvePv()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken)) return false;
    if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid)) return false;
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, NULL, NULL, NULL)) return false;
    return true;
}

/*
关机
*/
bool powerOffProc()
{
    if (!improvePv() || !ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, SHTDN_REASON_MAJOR_APPLICATION)) return false;
    return true;
}

/*
注销
*/
bool logOffProc()
{
    if (!improvePv() || !ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, SHTDN_REASON_MAJOR_APPLICATION)) return false;
    return true;
}

/*
重启
*/
bool reBootProc()
{
    if (!improvePv() || !ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_APPLICATION)) return false;
    return true;
}
