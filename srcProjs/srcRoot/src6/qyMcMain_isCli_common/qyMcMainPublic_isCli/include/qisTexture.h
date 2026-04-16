
#ifndef  __qisTexture_h__
#define  __qisTexture_h__	//  {

//
#include	"qisD3d_open.h"
#include	"texIndics.h"
//


//
//
XMMATRIX  loadMY_MATRIX(  MY_MATRIX  *  p  );
void  storeMY_MATRIX(  XMMATRIX  *pm,  MY_MATRIX  *  pDst  );


//
//
//  2015/01/01
#define		CONST_texType_null										0
#define		CONST_texType_sharedTex									1			//  2015/10/21

//
struct  __qisTextureInfo_t {
	//
	int												iType;

	//
	TCHAR											name[128];

	//
#ifdef  __USE_dx10__
	ID3D10Texture2D* g_pTexture10;
	ID3D10ShaderResourceView* g_pTextureRV10;				// = NULL;

	//  2013/10/23				
	ID3D10RenderTargetView* g_pRTV;
#endif

	//
#ifdef  __USE_dx11__
	ID3D11Texture2D* g_pTexture11;
	ID3D11ShaderResourceView* m_pSRV11;	//  2016/05/08	//  g_pTextureRV11;				// = NULL;

	//  2013/10/23				
	ID3D11RenderTargetView* g_pRTV;

#endif

	//
#ifdef  __USE_dx12__

	//
	ID3D12Resource			*			g_pTexture12;
	//
	Tex_ind								m_texIndex;

	//
	HANDLE                              m_sharedVideoTexture;


#endif


	//					
#if  0
	struct {
		int											index_D3D_dev_ctx;
		unsigned  int									uiTranNo_D3D_dev_ctx;
	}													info_d3dD3vCtx;
#endif

	//
	BOOL												bDataReady;					//  ×°ÔØÏß³Ì×°ÍêÊý¾Ýºó,ÉèÖÃbReadyÎªtrue
																				   //  renderÏß³ÌÊ¹ÓÃbReadyÎªtrueµÄtexture½øÐÐ»æÖÆ.
																				   //  µÈÁíÒ»¸ötexture readyÊ±,¾Í½«ÕýÊ¹ÓÃµÄbReadyÉèÖÃÎªfalse, È»ºó. ÇÐ»»±êÖ¾Î»bFlag_toRend_mem1 

	//
	//long												lCnt_used;					//  toFillÔÚ´¦ÀíÇ°Ê±,Òª¶Ô´ËÖµ+1,´¦ÀíÍê-1


};


//
namespace DX{
	class  RenderTexture;
};

//
namespace DirectX {
	class  DescriptorHeap;
};


//
struct  __rttTextureInfo_t {
	//
	int												iType;

	//
#ifdef  __USE_dx10__
	ID3D10Texture2D* g_pTexture10;
	ID3D10ShaderResourceView* g_pTextureRV10;				// = NULL;

	//  2013/10/23				
	ID3D10RenderTargetView* g_pRTV;
#endif

	//
#ifdef  __USE_dx11__
	ID3D11Texture2D* g_pTexture11;
	ID3D11ShaderResourceView* m_pSRV11;	//  2016/05/08	//  g_pTextureRV11;				// = NULL;

	//  2013/10/23				
	ID3D11RenderTargetView* g_pRTV;

#endif

	//
#ifdef  __USE_dx12__

	//
#ifdef   __DEBUG__
	ID3D12Resource* g_pTexture12;
	//
	Tex_ind								m_texIndex1;

#endif

	//
	//std::unique_ptr<DirectX::DescriptorHeap>        m_resourceDescriptors;
	DirectX::DescriptorHeap			*   m_resourceDescriptors;

	//
	//std::unique_ptr<DX::RenderTexture> m_renderTexture;
	DX::RenderTexture				*	m_renderTexture;

	//
	//std::unique_ptr<DirectX::DescriptorHeap> m_renderDescriptors;
	DirectX::DescriptorHeap			*	m_renderDescriptors;

	//
	
#endif


	//					
#if  0
	struct {
		int											index_D3D_dev_ctx;
		unsigned  int									uiTranNo_D3D_dev_ctx;
	}													info_d3dD3vCtx;
#endif

	//
	BOOL												bDataReady;					//  ×°ÔØÏß³Ì×°ÍêÊý¾Ýºó,ÉèÖÃbReadyÎªtrue
																				   //  renderÏß³ÌÊ¹ÓÃbReadyÎªtrueµÄtexture½øÐÐ»æÖÆ.
																				   //  µÈÁíÒ»¸ötexture readyÊ±,¾Í½«ÕýÊ¹ÓÃµÄbReadyÉèÖÃÎªfalse, È»ºó. ÇÐ»»±êÖ¾Î»bFlag_toRend_mem1 

	//
	//long												lCnt_used;					//  toFillÔÚ´¦ÀíÇ°Ê±,Òª¶Ô´ËÖµ+1,´¦ÀíÍê-1


};



//  2014/11/02
typedef  struct  __texInfosParam_t									{
				 int												iW;
				 int												iH;
				 
				 //
				 unsigned  short									usPktResType;				//  2015/10/01

}		 TEX_infos_param;


//  2015/01/05
#define		CONST_tex2Type_null										0
#define		CONST_tex2Type_cpu										1							//  2015/01/05. tex_cpus mems[0]. mems[0].( mems[1] ) 
#define		CONST_tex2Type_sharedTex								2							//  2015/10/01. 


//  2015/01/05
struct  __tex_help_t {
	//
	QIS_textureInfo									tex_cpu;
	//
#ifdef  __USE_dx11__
	UINT												Subresource;
	D3D11_MAPPED_SUBRESOURCE							mappedResource;		//  2015/01/03
#endif
				 //
#ifdef  __USE_dx12__
	void* pData12;
#endif

	//  render扢离
	struct {
		//
		BOOL											bMapped_tex_cpu;

		//  2015/01/12
		BOOL											bCopied;
		unsigned  int									uiTranNo_render_copied;

	}													render;

	//
	int		curState;

};



//  2015/10/05
typedef  struct  __tex2_sharedTexCfgMem_t							{
				 //PKT_sharedTex_info								pktSharedTexInfo;
				 //
				 PKT_sharedTex_info1								pktSharedTexInfo;
				 //				
				 BOOL												bDataReady;					
}		 TEX2_sharedTex_cfgMem;






//
struct  __myUpdateTexInfo_t {
	//
	//D3D12_PLACED_SUBRESOURCE_FOOTPRINT
	char	buf_pLayouts[256];
	UINT64	MemToAlloc_pLayouts;

	D3D12_RESOURCE_DESC	pDestination_desc;
	D3D12_RESOURCE_DESC	pIntermediate_desc;

	UINT64 RequiredSize;
	UINT* pNumRows;
	UINT64* pRowSizesInBytes;



};


//  2015/05/05
//
typedef  struct  __qisTextureInfo2_t								{
				 //
				 int												iType;
				 //
				 TEX_infos_param									param;
				
				 //
				 int												index_tex2;				//  2026/03/12

				 //
				 TCHAR												name1[128];

				 //
#ifdef  __DEBUG__
				 //BOOL												bFlag_toRend_mem1;
#endif
				 //
				 unsigned  int										uiCnt_filled;
				 //
				 unsigned  int										uiCnt_copied;
				 //
				 unsigned  int										uiCnt_rendered;


				 //
#define		MAX_texHelps	3
				 //
				 QIS_textureInfo									texes[MAX_texHelps];				//  2015/01/05	//  mems[2];
				 
				 //
				 TEX_help											texHelps[MAX_texHelps];				//  2015/01/05

				 //
				 BOOL												bAvail3;							//  false. iCnt_used
				 
				 //
				 bool												bStartToFree;						//  在释放tex2时，需要延时一段时间
				 DWORD												dwTickCnt_startToFree;

				 //
				 MyUpdateTexInfo									myUpdateTexInfo;

				 //  2015/10/03
				 struct												{
					 
					 //  ??在createTex?就要建立.
					 ID3D11VideoProcessorEnumerator			*		pVideoProcessorEnum;
					 ID3D11VideoProcessor					*		m_pVideoProcessor;    

					 //
					 TEX2_sharedTex_cfgMem							cfgMems[MAX_sharedTexes_dec];
					 
					 //
					 CLI_sharedTex									mems[MAX_sharedTexes_dec];

					 //  2015/10/06
					 unsigned  int									uiSeqNo_lastRender;

				 }													sharedTex;
				 //


				 //	for rtt
				 QIS_quad											quad;

				 //
				 UINT64 lastFenceUsed;   // GPU最后一次使用这个texture

				 //
}		 QIS_textureInfo2;



//  2014/11/05
typedef  struct  __qisTextureInfo2Sync_t							{
				 QIS_textureInfo2									textureInfo2;
				 //
				 SYNC_mt_cnt										syncMtCnt;
}		 QIS_textureInfo2_sync;

//
//  2014/11/02
typedef  struct  __rttPkt_											{							
				 //
				 Rtt_textureInfo									tex;
				
				 //
				 QIS_textureInfo									tex_cpu;			//  2014/11/07. 蚚懂參rtt蛌善cpu﹝綴婬黍善pkt爵.
				 
				 //
				 #ifdef  __USE_dx11__
						 UINT										Subresource;
						 D3D11_MAPPED_SUBRESOURCE					mappedResource;		//  2015/01/03
				 #endif

				 //
				 #ifdef  __USE_dx12__
						 void							*			pMappedData12;
						 bool										bMapped12;
				 #endif		

				 //
				 struct												{
					 BOOL											bProcessed;			//  thread_readRtt揭燴俇賸扢离
				 }													readRtt;

				 //  render扢离
				 struct												{
					 //
					 BOOL											bCopied;
					 //
					 BOOL											bMapped_tex_cpu;	

					 //
					 time_t											tStartTran_pkt_input;
					 BITMAPINFOHEADER								bih;
					 unsigned  int									uiSampleTimeInMs;
					 int											iTaskId;
					 BOOL											bResource;			//  2014/11/13

					 //
					 int											index_ok_thisSecond;

				 }													render;

				 //
}		 RTT_pkt;


//  2015/10/22
typedef  struct  __rtt_pkt_sharedTex_t								{
				 SHARED_tex											tex;
				 //
				 BOOL												bDataReady;			//  2015/10/22

				 //
				 struct												{
					 //
					 time_t											tStartTran_pkt_input;
					 BITMAPINFOHEADER								bih;
					 unsigned  int									uiSampleTimeInMs;
					 int											iTaskId;
					 BOOL											bResource;			//  2014/11/13

				 }													render;


}		 RTT_pkt_sharedTex;



//
//  2015/10/21
#define		CONST_mosaicRttType_null								0
#define		CONST_mosaicRttType_sharedTex							1


//
struct  __myReadStaging_t {
	int  imageSize;

	//
	int bmpW;
	int bmpH;
	//
	int dstRowPitch;
	//
	int rowPitch;
	int rowCount;

};





//  婓render瞳蚚iNextIndex_toRender梑善bDataReady峈false腔tex, 彆羶衄憩瞳蚚oneLeft.
//  參tex迡疑綴ㄛ憩參bDataReady董奻. ++  iNextIndex_toRender. 綴揖楷event
//  黍盄最坶隅mutex,瞳蚚iNextIndex_toRead佼唗黍bDataReady峈trueㄛbProcessing峈false腔ㄛ羶衄憩continue. 
//  綴董硉bProcessing. ++iNextIndex_toRead. 庋溫mutex
//  黍俇奀ㄛ參bDataReady董false. 坶隅mutex, 參pkt董奻ㄛbPktExists董奻﹝bProcessing董false. 
//  植iNextIndex_toSend脤梑岆瘁bPktExists峈true.彆峈true憩楷冞pkt,董硉bPktExists峈false. ++iNextIndex_toSend.
//  彆祥峈ture,潰脤bProcessing.彆峈trueㄛ桶隴帤絳堤俇救ㄛcontinue
//  彆峈false,寀桶隴蚕衾議砩俋絳祡絳堤囮啖ㄛ寀++iNextIndex-toSend.樟哿狟珨跺楷冞
//  庋溫mutex
//  樟哿狟珨跺黍
				 
struct  __mosaicRttInfo_t {

	//  2014/10/25
	TEX_infos_param									param;

	//
	HANDLE												hEvent;

	//  2015/01/02
	int												iMosaicRttType;

	//
	RTT_pkt											oneLeft;						//  彆羶衄褫蚚腔pkt(飲掩readRtt婬蚚賸ㄛ麼氪羶衄煦饜疑囀湔腔rttPkt.饒繫憩猁妏蚚oneLeft.

	//
	unsigned  char										ucCnt;							//  
	//
	RTT_pkt												mems1[3];
	//RTT_pkt											mems1[4];
	//RTT_pkt											mems1[6];
	//RTT_pkt											mems1[20];
	//RTT_pkt											mems1[30];

	//
	MyReadStaging										myReadStaging;

	//
	struct {

		//
		DWORD											dwProcessId;
		//
		int												index_mosaic;
		//
		unsigned  int									tn_sharedTex;

		//  这个在createTex时就要建立.
		ID3D11VideoProcessorEnumerator* pVideoProcessorEnum;
		ID3D11VideoProcessor* m_pVideoProcessor;

		//
		RTT_pkt_sharedTex								rttPktSharedTexes[MAX_sharedTexes_enc];

		//
		int												n_copied;						//  doRtt里设置，每次加1
		int												n_waitToEnc;					//  flushRtt里设置，割伤n_copied
		int												n_post;							//  readRtt里设置，要跟上n_waitToEnc;

		//
		unsigned  int									uiSeqNo_newSharedTex;

		unsigned  int									uiSeqNo_lastCopied;

		//
		unsigned  int									uiCnt_read;						//  2015/10/22
		DWORD											dwLastTickCnt_sendOldPkt;

		//  2015/11/01
		unsigned  int									uiSeqNo_lastRender;

	}													sharedTex;

	//
	struct {
		//
		BOOL											sync_bSending_unused;					//  衄珨跺盄最婓send. 硐夔衄珨跺婓send
		//
		DWORD											lastRead_sampleTimeInMs;		//  2014/11/26

	}													status_readRtt;

	//
	struct {
		unsigned  int									uiCnt_render;
		//
		unsigned  int									uiCnt__waitToMap;
		//
		unsigned  int									uiCnt_waitToPost;
	}													status_render;

	//  2014/11/13
	VIDEO_input_info1									input;
	//
	unsigned  short										usFrames_perSecond_expected1;

	//
	QIS_mats											mats_quad;
	QIS_quad											quad;

};



//
void ClearShaderResources11( ID3D11DeviceContext* pd3dDevice );
int  get_pt_far_mats(  void  *  p0_reserved,  float x_screen,  float y_screen,  QIS_mats  *  pMats,  float  z_1,  XMVECTOR  *  pPt_far  );


//  2015/10/22
//int  copyToSharedTex(  void  *  pD3D_context,  int  CropW,  int  CropH,  ID3D11Texture2D  *  pRTTexture2D,  MOSAIC_rtt_info  *  pRtt,  QIS_trace_common  *  pQtc  );
int  copyToSharedTex(  void  *  pD3D_context,  int  CropW,  int  CropH,  RTT_pkt  *  pRttPkt,  MOSAIC_rtt_info  *  pRtt,  QIS_trace_common  *  pQtc  );




#endif  //  }




