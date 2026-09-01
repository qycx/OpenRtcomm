
#ifndef  __meshLoaderPublic_h__
#define  __meshLoaderPublic_h__		//  {



#if 0
_declspec(  dllexport  )  void  *  meshLoader_new(  );
_declspec(  dllexport  )  void  meshLoader_free(  void  **  pp  );

//
_declspec(  dllexport  )  int  meshLoader_init(  void  *  pMeshLoaderParam,  void  *  pID3D11Device  );
_declspec(  dllexport  )  void  meshLoader_Shutdown(  void  *  pMeshLoaderParam  );

//
_declspec(  dllexport  )  int  meshLoader_loadFile(  void  *  pMeshLoaderParam,  LPCTSTR  fn  );

_declspec(  dllexport  )  int  meshLoader_OnFrameMove( void  *  pMeshLoaderParam,  double fTime, float fElapsedTime );
_declspec(  dllexport  )  int  meshLoader_OnFrameRender( void  *  pMeshLoaderParam,  void  *  pID3D11DeviceContextParam,  double fTime, float fElapsedTime );
#endif











#endif  //  }




