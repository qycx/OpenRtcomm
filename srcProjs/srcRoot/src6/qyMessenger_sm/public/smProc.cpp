


//#include	<qstring.h>


#include	"stdafx.h"
//#include	<Windows.h>
#include	"qyMcMainCommon.h"
#include <ctxQmc.h>
#include	"myCmdParams_open.h"
#include	"myTChar.h"
#include	"hgCommProc.h"
#include	"smProc.h"



//  ulIp应该是网络字节顺序的
extern  "C"  BOOL  bulMaskValid(unsigned  long  ulIp)
{
	ulIp = qyntohl(ulIp);
	//if (MACRO_byte0(ulIp) == 0 || MACRO_byte0(ulIp) == 255)  return  FALSE;
	//if (MACRO_byte3(ulIp) == 0 || MACRO_byte3(ulIp) == 255)  return  FALSE;
	return  TRUE;
}


//
extern  "C"  BOOL  bMaskValid(char* ip)
{
	unsigned  long		ulIp = 0;

	if (!ip)  return  FALSE;
	if ((ulIp = inet_addr(ip)) == INADDR_NONE)  return  FALSE;
	return  bulMaskValid(ulIp);
}

//smInitCfgFile
			
//






 //
 int getHkPortStatus(LPCTSTR  cfgFileName, HkPortStatus* pCfg)
{

	 int  iErr = -1;
	 TCHAR  tBuf[256];
	 char  buf[256];

	 if (!pCfg)  return  -1;

	 //
	 memset(pCfg, 0, sizeof(pCfg[0]));


	 //
	 if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bDisable_hdmi1Out_hdmi), tBuf, mycountof(tBuf))) {
		 tBuf[0] = 0;
	 }
	 pCfg->bDisable_hdmi1Out_hdmi = _ttol(tBuf);

	 //
	 if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bDisable_hdmi2Out_dvi), tBuf, mycountof(tBuf))) {
		 tBuf[0] = 0;
	 }
	 pCfg->bDisable_hdmi2Out_dvi = _ttol(tBuf);

	 //
	 if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bDisable_hdmiIn_vga), tBuf, mycountof(tBuf))) {
		 tBuf[0] = 0;
	 }
	 pCfg->bDisable_hdmiIn_vga = _ttol(tBuf);

	 //
	 if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bDisable_usb_sxt_usb1), tBuf, mycountof(tBuf))) {
		 tBuf[0] = 0;
	 }
	 pCfg->bDisable_usb_sxt_usb1 = _ttol(tBuf);

	 //
	 if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bDisable_usb_mkf_usb2), tBuf, mycountof(tBuf))) {
		 tBuf[0] = 0;
	 }
	 pCfg->bDisable_usb_mkf_usb2 = _ttol(tBuf);
	 
	 //
	 if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bDisable_lb_out), tBuf, mycountof(tBuf))) {
		 tBuf[0] = 0;
	 }
	 pCfg->bDisable_lb_out = _ttol(tBuf);

	 //
	 if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bDisable_usb_key_usb3), tBuf, mycountof(tBuf))) {
		 tBuf[0] = 0;
	 }
	 pCfg->bDisable_usb_key_usb3 = _ttol(tBuf);

	 //
	 if (getCfgValByNameT(cfgFileName, (TCHAR*)_T(CONST_cfgName_bDisable_network), tBuf, mycountof(tBuf))) {
		 tBuf[0] = 0;
	 }
	 pCfg->bDisable_network = _ttol(tBuf);


	 //
	 return  0;
 }


 int saveHkPortStatus(HkPortStatus* pCfg, LPCTSTR  cfgFileName)
 {
	 int  iErr = -1;
	 TCHAR  tBuf[256];
	 FILE* fp = _tfopen(cfgFileName, _T("w"));
	 if (!fp)  goto  errLabel;

	 //
	 fprintf(fp, "%s   %d\n", CONST_cfgName_bDisable_hdmi1Out_hdmi, pCfg->bDisable_hdmi1Out_hdmi);

	 fprintf(fp, "%s   %d\n", CONST_cfgName_bDisable_hdmi2Out_dvi, pCfg->bDisable_hdmi2Out_dvi);

	 fprintf(fp, "%s   %d\n", CONST_cfgName_bDisable_hdmiIn_vga, pCfg->bDisable_hdmiIn_vga);

	 fprintf(fp, "%s   %d\n", CONST_cfgName_bDisable_usb_sxt_usb1, pCfg->bDisable_usb_sxt_usb1);

	 fprintf(fp, "%s   %d\n", CONST_cfgName_bDisable_usb_mkf_usb2, pCfg->bDisable_usb_mkf_usb2);

	 fprintf(fp, "%s   %d\n", CONST_cfgName_bDisable_lb_out, pCfg->bDisable_lb_out);

	 fprintf(fp, "%s   %d\n", CONST_cfgName_bDisable_usb_key_usb3, pCfg->bDisable_usb_key_usb3);

	 fprintf(fp, "%s   %d\n", CONST_cfgName_bDisable_network, pCfg->bDisable_network);



	 //
	 iErr = 0;
 errLabel:

	 if (fp) {
		 fclose(fp);
	 }

	 return  iErr;
 }



