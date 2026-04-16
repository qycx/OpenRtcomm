#ifndef  __qdcSplitter_open_h__
#define  __qdcSplitter_open_h__	//  {

//
#define		CONST_bufSize_mediaDataForSpl							1024  *  1024

//
typedef  struct  __mediaDataMemHead_t {
	unsigned  int										uiLen;
	//
	int												iMediumType;
	int												iCodecType;
	int												iSampleTimeInMs;

}		 MEDIA_data_memHead;

//
typedef  struct  __qdcMediaData_t {
	MEDIA_data_memHead									head;
	//
	char												buf[CONST_bufSize_mediaDataForSpl];
}		 QDC_MEDIA_data, QDC_media_data;

//
#define		MAX_uiBufSize_streamBuf									1024  *  4  *  1024

//
typedef  struct  __qdcStreamBuf_t {
	char									*			pBuf;
	unsigned  int										uiBufSize;
	unsigned  int										uiLen;
	//
	unsigned  int										nBytes_processed;
}		 QDC_stream_buf;



//
typedef  struct  __qdcSplCfg_t {
	int  iMediumType;
	int  iCodecType;
	//
	QDC_stream_buf						*			pStreamBuf;
	void									*			pStreamDataQ;
	//  void									*			pBUF_pretrans;
	//
	PF_commonHandler									pf_streamDataQ_qNodes;
	PF_commonHandler									pf_readData;					//  pQDC_splitter_info, void  *  p1,  void  *  pMEDIA_data_forSpl
	PF_commonHandler									pf_writeData;					//  not finished
																						//  PF_commonHandler								pf_chkBufPretrans;				//  pQDC_spl_info,  p1,  p2
}		  QDC_spl_cfg;



//
typedef  struct  __qdcSplInfo_t {
	//
	BOOL												bInited;
	//
	QDC_spl_cfg										cfg;
	//
	void									*			pObj;

	//
	void									*			pMediaDataForSpl_toGet;						//  放到streamDataQ去的buf

																									//
	QDC_MEDIA_data							*			pMediaDataForSpl_pkt;						//  dumuxed pkt

																									//
	void									*			pDebugStep;									//  2010/04/28

}		 QDC_spl_info;


#if  1	//  def  _DEBUG

extern  "C"  __declspec(dllexport)  int  qdcInit(QDC_MGR  *  p);

__declspec(dllexport)  int  qdcInitSplInfo(QDC_spl_cfg  *  pCfg, void  *  p0, void  *  p1, QDC_spl_info  *  pSplInfo);
__declspec(dllexport)  int  qdcExitSplInfo(QDC_spl_info  *  pSplInfo);
__declspec(dllexport)  int  qdcSplGetNextData(QDC_spl_info  *  pSplInfo, QDC_media_data  *  pMediaData);
//
__declspec(dllexport)  int  qdcSplGetSpsPps(QDC_spl_info  *  pSplInfo, char  *  spsBuf, unsigned  int  *  puiSpsSize, char  *  ppsBuf, unsigned  int  *  puiPpsSize, char  *  kk, unsigned  int  *  puiKkSize);

#endif


#endif


