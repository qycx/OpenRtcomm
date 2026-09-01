// help_webRtc.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

//
extern  "C"  __declspec(  dllexport  )  char  *  voe_ver(  )
{
	return  "01010101";
}

//
extern  "C"  __declspec(  dllexport  )  int  voe_init(  )
{
	return  -1;
}

//
extern  "C"  __declspec(  dllexport  )  int  voe_exit(  )
{
	return  -1;
}

//
typedef  int  (*PF_outStream  )(  void  *  p0,  void  * p1,  void  *  p2  );

//
extern  "C"  __declspec(  dllexport  )  int  voe_record_init(  void  *  pRecordSoundProcInfo,  PF_outStream  pf  )
{
	return  -1;
}


extern  "C"  __declspec(  dllexport  )  int  voe_record_setDevice(  void  *  pRecordSoundProcInfo,  int  index_record  )
{
	return  -1;
}

extern  "C"  __declspec(  dllexport  )  int  voe_record_start(  void  *  pRecordSoundProcInfo  )
{
	return  -1;
}


extern  "C"  __declspec(  dllexport  )  int  voe_record_exit(  )
{
	return  -1;
}



extern  "C"  __declspec(  dllexport  )  int  voe_list_device(  char  *  recorder_buf,  int  size,  char  *  recorder_selected_utf8  )
{
	return  -1;
}


extern  "C"  __declspec(dllexport)  int  voe_getADeviceIndex(  char  *  recorder_selected_utf8,  int  *  pIndex  )
{
	return  -1;
}

//
typedef  int  (*PF_inStream  )(  void  *  p0,  void  * p1,  void  *  p2  );

//
//
extern  "C"  __declspec(  dllexport  )  int  voe_play_init(  void  *  pPlayer,  PF_inStream  pf,  void  **  ppVoePlay  )
{
	return  -1;
}

//
extern  "C"  __declspec(  dllexport  )  int  voe_play_exit(  void  **  ppVoePlay  )
{
	return  -1;
}









