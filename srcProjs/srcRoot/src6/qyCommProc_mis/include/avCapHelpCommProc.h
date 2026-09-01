

#ifndef  __AVCAPHELPCOMMPROC_H__
#define  __AVCAPHELPCOMMPROC_H__	//  {


#define		CONST_shmName_qm_cmd								_T(  "QmShm_cmd_yxyb"  )  
#define		CONST_shmName_qm_data								_T(  "QmShm_data_yxyb"  )  
//
#define		CONST_evtName_qm_app								_T(  "QmEvt_app"  )			//  2017/01/29
#define		CONST_evtName_qm_vpp								_T(  "QmEvt_vpp"  )			//  2011/12/04
//
#define		CONST_evtName_qm_data_a								_T(  "QmEvt_data_a"  )
#define		CONST_evtName_qm_data_v								_T(  "QmEvt_data_v"  )
#define		CONST_mutexName_qm_syncData_a						_T(  "QmMtx_data_a"  )
#define		CONST_mutexName_qm_syncData_v						_T(  "QmMtx_data_v"  )
//
#define		CONST_evtName_qm_toShareVideo_post					_T(  "QmEvt_v_post"  )		//  2011/12/06


typedef  struct  __qmShmPktHead_t								{
				 int											iSampleTimeInMs;
#ifdef  __DEBUG__
				TCHAR											tHint[64];
#endif
}		 QM_SHM_pktHead;

typedef  struct  __qmShm_data_t									{
				 WCHAR											hint[128];

				 QY_VIDEO_HEADER								vh_org;
				 QY_AUDIO_HEADER								ah_org;
				 unsigned  char									ucbAudioOnly;
				 unsigned  char									ucbNoAudio;

				 struct											{
					unsigned  int								nBytes_pktHead;
					unsigned  int								nBytes_pktData;				//  video data, or audio data
					unsigned  short								usMaxCnt;				

					int											iIndex_post;				//  set by sub process
					int											iIndex_get;					//  set by main process
					int											nCnt;
				 }												a,  v;

				 char											buf[1];

}		 QM_SHM_DATA,  QM_SHM_data;															//  totol shmData  =  head  +  (  nBytes_audioPktHeader  +  nBytes_audioPktData  )  *  usMaxCnt_a  +  (  nBytes_videoPktHeader  +  biSizeImage  )  *  usMaxCnt_v


#endif  //  }


