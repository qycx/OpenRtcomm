

#ifndef  __tmp_d3d11_dev_open_h__
#define  __tmp_d3d11_dev_open_h__	//  {

//
#ifdef  __d3d11_h__
		#define  __USE_d11__
#endif
//
#ifdef  __d3d11_1_h__
		#define  __USE_d11_1__
#endif

//
#ifdef  __USE_d11__
		typedef  ID3D11Device	  *		LP_ID3D11Device;
#else
		typedef  void  *				LP_ID3D11Device;
#endif
//
#ifdef  __USE_d11__
		typedef  ID3D11DeviceContext  *	LP_ID3D11DeviceContext;
#else
		typedef  void  *				LP_ID3D11DeviceContext;
#endif
//
#ifdef  __USE_d11_1__
		typedef  ID3D11Device1	  *		LP_ID3D11Device1;
#else
		typedef  void  *				LP_ID3D11Device1;
#endif


//
#ifdef  __USE_d11__
		typedef  ID3D11VideoDevice  *	LP_ID3D11VideoDevice;
#else
		typedef  void  *				LP_ID3D11VideoDevice;
#endif
//
#ifdef  __USE_d11__
		typedef  ID3D11VideoContext  *  LP_ID3D11VideoContext;
#else
		typedef  void  *				LP_ID3D11VideoContext;
#endif


//
#ifdef  __USE_d11__
		typedef  ID3D11VideoProcessorEnumerator	*	LP_ID3D11VideoProcessorEnumerator;
#else
		typedef  void  *							LP_ID3D11VideoProcessorEnumerator;
#endif
//
#ifdef  __USE_d11__
		typedef  ID3D11VideoProcessor  *			LP_ID3D11VideoProcessor;
#else
		typedef  void  *							LP_ID3D11VideoProcessor;
#endif
	
//
#ifdef  __USE_d11__
		typedef  ID3D11Texture2D  *					LP_ID3D11Texture2D;
		typedef  ID3D11ShaderResourceView  *		LP_ID3D11ShaderResourceView;
		typedef  ID3D11RenderTargetView  *			LP_ID3D11RenderTargetView;
#else
		typedef  void  *							LP_ID3D11Texture2D;
		typedef  void  *							LP_ID3D11ShaderResourceView;
		typedef  void  *							LP_ID3D11RenderTargetView;
#endif


#endif  //  }



