
#ifndef  __muxStream_open_h__
#define  __muxStream_open_h__	//  {



//
#define		CONST_muxStreamType_null									0
#define		CONST_muxStreamType_conf									1
#define		CONST_muxStreamType_screen									2
#define		CONST_muxTreamType_map										3



//
typedef  struct {
				

				//  音频的采样率. 缺省为16000
				//  音频编码
				struct  {
					//
					//
					unsigned  char										ucCompressors;					//  
					unsigned  short										wFormatTag;
				}		a;
				//  视频分辨率. 
				//  编码
				struct {
					//
					unsigned  short										usW;
					unsigned  short										usH;
					//
					unsigned  char										ucCompressors;					//  
					int													iFourcc;
				}		v;

		
}		 MuxStreamOutputCfg;


//
#if  0
//
#define		MAX_muxStreamOutputs										8								//  仅声音。2个
																										//  100k. 2个
																										//  标清  2个
																										//  2k    1个
																										//  4k	  1个
//
#endif 

//
typedef  struct {
				//
				unsigned  short											usIndex;

				//
				unsigned  short											usType;

				//
				MuxStreamOutputCfg										output;

}		 MuxStreamCfg;





//
#define		MAX_muxStreams												10								//  




//  集中的策略定义
typedef  struct {
				//
				unsigned  short											usCnt;
				MuxStreamCfg											mems[MAX_muxStreams];

				//
				unsigned  short											default_usIndex;				//  缺省使用的uxIndex

				//
				void* tmp_pInsternal;
				unsigned  int		tmp_usCnt_mems;

}		 MuxStreamsCfg;


//////////////////////////////


#if  0

//
typedef  struct {
				//
				MuxStreamCfg											cfg;

}		 MuxStream;


//
typedef  struct {
				//
				unsigned  short											usCnt;
				MuxStream												mems[MAX_muxStreams];			//  
}		 MuxStreams;

//
#endif 







//
int  test_getMuxStreamsCfg(MuxStreamsCfg* pCfg);
int  testInit_getMuxStreamsCfg(int  avLevel, MuxStreamsCfg* pCfg);



//
#endif  //  }



