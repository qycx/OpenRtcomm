
#ifndef  __qmcStruct_defs_h__
#define  __qmcStruct_defs_h__	//  {


//
//
typedef  struct  __funcs_for_isCliHelp_t	FUNCS_for_isCliHelp;

//
//
typedef  struct  __qmShm_cmds_t				QM_SHM_CMDS,  QM_SHM_cmds;

//
//
typedef  struct  __policyAvParams_t			PolicyAvParams;

//
//
typedef  struct  __misCnt_t					MIS_CNT;

//
//
typedef  struct  __audioPlayCfg_t									AUDIO_PLAY_CFG;

//
typedef  struct  __myPlayAudioData_t								myPLAY_AUDIO_DATA, myPLAY_AUDIO_data;

//
typedef  struct  __qyPlayer_t	QY_PLAYER;

//
typedef  struct  __transferAudioData_t								TRANSFER_AUDIO_DATA;


//
typedef  struct  __qmcStatus_t										QMC_status;

//
typedef  struct  __qyTransform_t								QY_TRANSFORM;

//
typedef  struct  __qySharedObjInfo_t							QY_sharedObj_sync;

//
typedef  union  __capProcInfoBmpU_t								CAP_procInfo_bmpU;

//
typedef  union  __capProcInfoAudioU_t							CAP_procInfo_audioU;


typedef  struct  __capProcInfoRecordSound_t						CAP_procInfo_recordSound;

//
typedef  struct  __myDrawVideoData_t								myDRAW_VIDEO_DATA;

typedef  struct  __compressVideo_t								COMPRESS_VIDEO;

typedef  struct  __qySharedObj_t								QY_SHARED_OBJ;

//
typedef  struct  __audioCompressorCfg_t								AUDIO_COMPRESSOR_CFG;

//
typedef  struct  __videoCompressorCfg_t								VIDEO_COMPRESSOR_CFG;

//
typedef  struct  __myQoi_t		MY_qoi;

//
//
class  CCtxQmc;

//
__declspec(  dllexport  ) int  fixPlayCfg(  PolicyAvParams  *  p_gAvParams,  AUDIO_PLAY_CFG  *  pPlayCfg  );



#endif  //  }


