
#ifndef  __aecPublic_h__
#define  __aecPublic_h__  //  {

//
#define		CONST_bufSize_orgAudioPktBuf		16  *  480		// 10ms, 4channels, 4bytes

//
#define		CONST_cntof_aecPlayers			50


//
typedef  struct  __orgAudioPkt_t			{
				 int						iSampleTimeInMs;				 
				 //
				 int						len;
				 char						buf[CONST_bufSize_orgAudioPktBuf];
}		 ORG_audio_pkt;


//
typedef  struct  __aecPlayerCfg_t			{
				 //
				 QY_MESSENGER_ID			idInfo;
				 unsigned  int				tn_a;

				 //
				 PLAYER_ID					playerId;
				 
				 //
				 FILE* fp_debug;

}		 AEC_player_cfg;


//
typedef  struct  __aecLayout_t				{
				 unsigned  int				tn_modified;
				 //
				 int						iTaskId;
				 unsigned  short			usCntLimit_activeMems_from;
				 //
				 unsigned  short			usCnt;
				 AEC_player_cfg				mems[CONST_cntof_aecPlayers];

}		 AEC_layout;


//
int AEC_layout_init(int  iTaskId,  unsigned  short  usCntLimit_activeMems_from, AEC_layout* pLayout);
int AEC_layout_exit(AEC_layout* pLayout);
int AEC_layout_chk(AEC_layout* pLayout);





int  addToAecLayout(  void  *  pProcInfo,  PLAYER_ID  playerId,  AEC_layout  *  pLayout  );
int  removeFromAecLayout(  void  *  pProcInfoParam,  PLAYER_ID  playerId,  AEC_layout  *  pLayout  );



#endif  //  }

