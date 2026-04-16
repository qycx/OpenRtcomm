
#ifndef  __myDecode_render_h__
#define  __myDecode_render_h__	//  {

//
BOOL  bShowRenderWnd(  );


class  CMyDecodeD3DRender:public  CDecodeD3DRender  
{
public:
	CMyDecodeD3DRender(  );
	~CMyDecodeD3DRender(  );

	//
	virtual mfxStatus Init(sWindowParams pWParams);

};



#endif  //  }


