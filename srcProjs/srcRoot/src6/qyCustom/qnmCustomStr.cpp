

#include	"stdafx.h"
#include <string>
#include	<tchar.h>


//

TCHAR* CONST_yhlx_bdwyh = (TCHAR*)_T("本单位用户");				//  CONST_shhgYhlxTable[0].des
//
TCHAR* CONST_yhlx_wdwlsyh = (TCHAR*)_T("外单位临时用户");			//	CONST_shhgYhlxTable[1].des
TCHAR * CONST_yhlx_wzcyh = (TCHAR*)_T("未注册用户");				//  CONST_shhgYhlxTable[2].des
TCHAR* CONST_yhlx_qtdwyh = (TCHAR*)_T("其它单位用户");				//  




//

//
std::wstring CONST_yhlx_ttttt = _T("无法打开数据库，程序将退出");

TCHAR* QY_MMnnnn = (TCHAR*)_T("无法打开数据库，程序将退出");
//
TCHAR* QY_MC_HINT_NODSN = (TCHAR*)_T("无法打开数据库，程序将退出");		// _T("无法打开数据库，程序将退出。");
//
TCHAR* QY_MC_HINT_NONEWWINDOW = (TCHAR*)_T("资源限制，不能再打开新窗口了。");
TCHAR* QY_MC_HINT_NOIE4 = (TCHAR*)_T("此系统须运行在装有4.0以上的IE的环境里");
TCHAR* QY_MC_HINT_URL0LEN = (TCHAR*)_T("网址不能为空");
TCHAR* QY_MC_HINT_BARID0LEN = (TCHAR*)_T("网吧编码不能为空");
TCHAR* QY_MC_HINT_NAME0LEN = (TCHAR*)_T("名称不能为空");
TCHAR* QY_MC_HINT_FRDB0LEN = (TCHAR*)_T("法人代表不能为空");
TCHAR* QY_MC_HINT_FZR0LEN = (TCHAR*)_T("负责人不能为空");
TCHAR* QY_MC_HINT_AQY0LEN = (TCHAR*)_T("安全员不能为空");
TCHAR* QY_MC_HINT_ADDR0LEN = (TCHAR*)_T("地址不能为空");
TCHAR* QY_MC_HINT_TEL0LEN = (TCHAR*)_T("电话不能为空");
TCHAR* QY_MC_HINT_STATUS0LEN = (TCHAR*)_T("状态不能为空");
TCHAR* QY_MC_HINT_GUESTNAME0LEN = (TCHAR*)_T("姓名不能为空");
TCHAR* QY_MC_HINT_CERTID0LEN = (TCHAR*)_T("证件号码不能为空");
TCHAR* QY_MC_HINT_PCID0LEN = (TCHAR*)_T("顾客机器号不能为空");
TCHAR* QY_MC_HINT_OFFICE0LEN = (TCHAR*)_T("单位名称不能为空");
TCHAR* QY_MC_HINT_COUNTRY0LEN = (TCHAR*)_T("国家名不能为空");
TCHAR* QY_MC_HINT_BARIDFIXEDLEN = (TCHAR*)_T("网吧编码须输满10位");


//	TCHAR*		QY_MC_HINT_URLEXISTS						=(TCHAR*)_T((  "网址已存在"  )
//	TCHAR*		QY_MC_HINT_KEYTYPENAMEEXISTS				=(TCHAR*)_T((  "类别名已存在"  )
TCHAR* QY_MC_HINT_INSERTFAILED = (TCHAR*)_T("数据库错误，不能完成添加操作");
TCHAR* QY_MC_HINT_MODIFYFAILED = (TCHAR*)_T("数据库错误，不能完成修改操作");
TCHAR* QY_MC_HINT_UPDATEFAILED = (TCHAR*)_T("数据库错误，不能完成修改操作");
TCHAR* QY_MC_HINT_DELFAILED = (TCHAR*)_T("数据库错误，不能完成删除操作");
//TCHAR* QY_MC_HINT_DELETEFAILED						QY_MC_HINT_DELFAILED
TCHAR* QY_MC_HINT_DBERR = (TCHAR*)_T("数据库错误，操作失败");
TCHAR* QY_MC_HINT_CANBARINFOUPDATE = (TCHAR*)_T("网吧信息已修改，保存吗?");
TCHAR* QY_MC_HINT_CANGUESTREGISTER = (TCHAR*)_T("登记信息是否确认?");
TCHAR* QY_MC_HINT_CANPCINFOUPDATE = (TCHAR*)_T("机器信息已修改，保存吗?");
TCHAR* QY_MC_HINT_CANPCINFODEL = (TCHAR*)_T("机器将被删除，继续吗?");
TCHAR* QY_MC_HINT_CANBARDEL = (TCHAR*)_T("网吧将被删除，继续吗?");
TCHAR* QY_MC_HINT_PCNOID = (TCHAR*)_T("没有空闲的机器了(有机器但未被分配机器号)");
TCHAR* QY_MC_HINT_NOSPAREPC = (TCHAR*)_T("没有空闲的机器了");
TCHAR* QY_MC_HINT_NOSPAREKEYTYPECODE = (TCHAR*)_T("没有可用的类别了(仅限于使用255种类别)");
TCHAR* QY_MC_HINT_NOGUEST = (TCHAR*)_T("该机器上没有顾客上网");
TCHAR* QY_MC_HINT_NOPCID = (TCHAR*)_T("没有这台机器");
TCHAR* QY_MC_HINT_GETDISCOUNTFAILED = (TCHAR*)_T("取不到折扣");
TCHAR* QY_MC_HINT_DISCOUNTERR = (TCHAR*)_T("折扣值有误");
TCHAR* QY_MC_HINT_ISFEEOK = (TCHAR*)_T("继续吗?");
TCHAR* QY_MC_HINT_FEEERR = (TCHAR*)_T("计费错误");
TCHAR* QY_MC_HINT_KEYTYPENAME0LEN = (TCHAR*)_T("类别名字不能为空");
TCHAR* QY_MC_HINT_KEYTYPEBEINGUSED = (TCHAR*)_T("该类别尚在使用中，须在属于该类别的网址都删除后，才能删除");
TCHAR* QY_MC_HINT_DISTRIBUTINGPOLICYFAILED = (TCHAR*)_T("下发策略失败，请重试");


//
TCHAR* QY_MC_DLGFACENAME = (TCHAR*)_T("仿宋体");	//  对话框的字体


//
TCHAR* CONST_ID_startShareMediaDevice_grp1 = (TCHAR*)_T("查看一组设备");
TCHAR* CONST_ID_startShareMediaDevice_grp2 = (TCHAR*)_T("查看二组设备");
TCHAR* CONST_ID_startShareMediaDevice_grp3 = (TCHAR*)_T("查看三组设备");
TCHAR* CONST_ID_startShareMediaDevice_grp4 = (TCHAR*)_T("查看四组设备");





