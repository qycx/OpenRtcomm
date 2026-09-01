

#ifndef  __imgProcessCommon_h__
#define  __imgProcessCommon_h__		//  {

#include	"imgProcessPublic.h"
#define		CONST_mutexName_syncImgProcessCfg		_T(  "syncImgProcCfg"  )



class  CCtxImgProcess	{
public:
			CCtxImgProcess(  );
			~CCtxImgProcess(  );

			struct								{
												
				IMG_process_cfg					new_Cfg;
				 DWORD							dwTickCnt_modified_new;

#if  0
				//
				IMG_process_cfg					cfg;
				DWORD							dwTickCnt_modified;
#endif

			}									m_var;



};

//
extern  CCtxImgProcess	gCtx_imgProcess;

//
float  colorDistance(  int  h_p,  int  s_p,  int  h_key,  int  s_key  );

//
//
float  hlsl_colorDistance(  MY_float3 color_hsl_p,  MY_float3  color_hsl_key  );
colorDistance_keys_res  hlsl_getColorDistance_keys(  MY_float3 p_xyz  );
MY_float4  hlsl_procChromaKey(  MY_RGBA  p_rgba  );
int	hlsl_init(  );
//  HLSL_imgProcessCfg  hlsl_getCfg(  );



//
#if  0
int  dumpKeyFile(  );
int  parseBmpFile( LPCTSTR bmpFileName,  LPTSTR  oFileName,  BOOL  bFlipImg  );
#endif


#endif  //  }




