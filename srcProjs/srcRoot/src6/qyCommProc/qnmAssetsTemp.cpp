
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyCommProc.h"
//  #include	"qnmCommProc.h"
#include	"qnmAssetsCommProc.h"
 
 QY_DMITEM	CONST_assetTypeTable[]	=
{
#if  0
	{	CONST_assetType_cpu,					(TCHAR*)_T(  "CPU"  ),								},
	{	CONST_assetType_mem,					(WCHAR*)_T(  "内存"  ),								},
	{	CONST_assetType_bios,					(WCHAR*)_T(  "BIOS"  ),								},
	{	CONST_assetType_floppy,					(WCHAR*)_T(  "软盘驱动器"  ),						},
	{	CONST_assetType_ideHardDisk,			(WCHAR*)_T(  "磁盘驱动器"  ),						},
	{	CONST_assetType_usbDisk,				(WCHAR*)_T(  "USB磁盘"  ),							},
	//  {	CONST_assetType_scsiHardDisk,			_T(  "SCSI硬盘"  ),						},
	{	CONST_assetType_ideCdrom,				(WCHAR*)_T(  "DVD/CD-ROM"  ),						},
	{	CONST_assetType_display,				(WCHAR*)_T(  "显卡"  ),								},
	{	CONST_assetType_monitor,				(WCHAR*)_T(  "监视器"  ),							},
	{	CONST_assetType_networkCard,			(WCHAR*)_T(  "网卡"  ),								},
	//  {	CONST_assetType_soundCard,				_T(  "声卡"  ),							},
	{	CONST_assetType_software,				(WCHAR*)_T(  "软件"  ),								},
#endif
	//
	{	-1,										NULL,								},
};



#ifdef  __DEBUG__

 extern  "C"  int  printComponentInfo(  int  i,  QWM_COMPONENT_INFO  *  pComponent  )
{	 
	 switch  (  pComponent->uiType  )  {
			 case  CONST_assetType_cpu:
				   traceLogA(  (char*)"assets[%d] is cpu, frequency %d",  i,  pComponent->u.cpu.iFrequency  );
				   break;
			 case  CONST_assetType_mem:
				   traceLogA(  (char*)"assets[%d] is memory %d",  i,  pComponent->u.mem.uiTotalPhys  );
				   break;
			 case  CONST_assetType_bios:
				   traceLogA(  (char*)"assets[%d] is bios,  identifier %s,  ver %s,  date %s",  i,  pComponent->u.bios.identifier,  pComponent->u.bios.systemBiosVer,  pComponent->u.bios.systemBiosDate  );
				   break;
			 case  CONST_assetType_ideHardDisk:
				   traceLogA(  (char*)"assets[%d] is ideDisk, 型号为%S, 固件号为%S, 序列号为%S",  i,  pComponent->u.disk.modelNo,  pComponent->u.disk.firmwareRevision,  pComponent->u.disk.serialNo  );
				   break;
			 case  CONST_assetType_ideCdrom:
				   traceLogA(  (char*)"assets[%d] is cdrom, 型号为%S, 固件号为%S, 序列号为%S",  i,  pComponent->u.disk.modelNo,  pComponent->u.disk.firmwareRevision,  pComponent->u.disk.serialNo  );
				   break;				
			 case  CONST_assetType_display:
				   traceLogA(  (char*)"assets[%d]  is  display, 型号为%S,  驱动版本号为%S， 驱动日期为%s,  厂家为%S",  i,  pComponent->u.display.driverDesc, pComponent->u.display.driverVersion,  pComponent->u.display.driverDate,  pComponent->u.display.vendor  );
				   break;
			 case  CONST_assetType_networkCard:
				   traceLogA(  (char*)"assets[%d]  is  networkCard, 型号为%S,  驱动版本号为%S， 驱动日期为%s,  厂家为%S",  i,  pComponent->u.net.driverDesc, pComponent->u.net.driverVersion,  pComponent->u.net.driverDate,  pComponent->u.net.vendor  );
				   break;
			 case  CONST_assetType_monitor:
				   traceLogA(  (char*)"assets[%d]  is  monitor,  driverDesc %s,  ver %s, date %s,  vendor %s",  i,  pComponent->u.monitor.driverDesc, pComponent->u.monitor.driverVersion,  pComponent->u.monitor.driverDate,  pComponent->u.monitor.vendor  );
				   break;
			 case  CONST_assetType_usbDisk:
				   traceLogA(  (char*)"assets[%d] is usb, 型号为%S, 固件号为%S, 序列号为%S",  i,  pComponent->u.disk.modelNo,  pComponent->u.disk.firmwareRevision,  pComponent->u.disk.serialNo  );
				   break;		
			 case  CONST_assetType_floppy:
				   traceLogA(  (char*)"assets[%d] is floppy,  型号为%S,  驱动程序日期为%S,  驱动程序版本为%S,  制造商为%S",  i,  pComponent->u.floppy.driverDesc, pComponent->u.floppy.driverDate,  pComponent->u.floppy.driverVersion, pComponent->u.floppy.vendor  );
				   break;
			 case  CONST_assetType_software:
				   traceLogA(  (char*)"assets[%d] is software %S",  i,  pComponent->u.software.displayName  );
				   break;
			 case  CONST_assetType_cpu1:
				   traceLogA(  (char*)"assets[%d] is, cpu, %s",  i,  pComponent->u.cpu1.processorName  );
				   break;
			 default:
					 traceLogA(  (char*)"asset[%d] is unknown, type is %d",  i,  pComponent->uiType  );
					 break;
	 }		  

	 return  0;
}



 extern  "C"  int  printQwmAssetsInfo(  QWM_ASSETS_INFO  *  pAssetInfo  )
{
	 unsigned  int			i			=  0;
	 QWM_COMPONENT_INFO  *  pComponent  =  NULL;		

	 if  (  pAssetInfo->cnt  >  sizeof(  pAssetInfo->components  )  /  sizeof(  pAssetInfo->components[0]  )  )  {
		 traceLogA(  (char*)"showQwmAssetInfo: cnt 过大"  );  goto  errLabel;
	 }
	 traceLogA(  (char*)"total %d assets",  pAssetInfo->cnt  );
	 for  (  i  =  0;  i  <  pAssetInfo->cnt;  i  ++  )  {
		  pComponent  =  &pAssetInfo->components[i];

		  printComponentInfo(  i,  pComponent  );
	 
	 }

errLabel:
	 return  0;
}


#endif

