

#include	"stdafx.h"
#include	<tchar.h>
#include	<stdlib.h>
#include	<Dshow.h>

#include	<assert.h>
#include	"base_allocator.h"

#include	"tmpGuiOpenFunc.h"
#include	"qisCompressProc.h"
#include	"myFunc_mediaSdk.h"

#include	"sample_defs.h"

//
LPCTSTR  getImplStr(  int  implType  )
{
	LPCTSTR  pT  =  _T(  ""  );

	switch  (  implType  )  {
			case  0:
				  pT  =  _T(  "type 0"  );
				  break;
			case  MFX_IMPL_HARDWARE:
				  pT  =  _T(  "hw"  );
				  break;				
			case  MFX_IMPL_HARDWARE2:
				  pT  =  _T(  "hw2"  );
				  break;				  
			case  MFX_IMPL_HARDWARE3:
				  pT  =  _T(  "hw3"  );
				  break;
			case  MFX_IMPL_HARDWARE4:
				  pT  =  _T(  "hw4"  );
				  break;
			default:
					pT  =  _T(  "Unkown hw"  );
					break;
	}


	return  pT;
}


//
BOOL IsHwAcclSupported( void  *  pmfxVersion )

{
	BOOL	bRet	=	FALSE;

#if  0	//  2012/08/24

	mfxIMPL impl = MFX_IMPL_AUTO;
	mfxSession session = NULL;
	mfxVersion ver = {MFX_VERSION_MINOR, MFX_VERSION_MAJOR};
	if  (  pmfxVersion  )  {
		ver  =  *(  mfxVersion  *  )pmfxVersion;
	}

	MFXInit( MFX_IMPL_AUTO, &ver, &session );
	MFXQueryIMPL( session, &impl );
	MFXClose( session );

	switch  (  MFX_IMPL_BASETYPE(  impl  )  )  {
			case  MFX_IMPL_HARDWARE:
				  bRet  =  TRUE;
				  break;
			default:
				    break;
	}

#else

		mfxIMPL impl = MFX_IMPL_SOFTWARE; // default in case no HW IMPL is found

        // an auxiliary session, internal for this function
        mfxSession auxSession; 
        memset(&auxSession, 0, sizeof(auxSession));

        mfxVersion ver = {1, 1}; // minimum API version which supports multiple devices
        MFXInit(MFX_IMPL_HARDWARE_ANY, &ver, &auxSession); 
        MFXQueryIMPL(auxSession, &impl);
        MFXClose(auxSession);

		int  impl_baseType  =  MFX_IMPL_BASETYPE(  impl  );
		//switch  (  MFX_IMPL_BASETYPE(  impl  )  )  
		switch  (  impl_baseType  )
		{
				case  MFX_IMPL_HARDWARE:
				case  MFX_IMPL_HARDWARE2:
				case  MFX_IMPL_HARDWARE3:
				case  MFX_IMPL_HARDWARE4:
					  bRet  =  TRUE;
					  break;
				default:
						break;
		}
#endif

		TCHAR	tBuf[128]	=	_T(  ""  );
		TCHAR  *  implStr  =  (  TCHAR  *  )getImplStr(  impl_baseType  );
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "Hw%d.%d: impl %d, impl_baseType %d, %s, bRet %d"  ),  (  int  )ver.Major,  (  int  )ver.Minor,  impl,  impl_baseType,  implStr,  bRet  );
		tmp_showInfo(  tBuf  );

		return  bRet;
}

//  2015/09/28
#if  0
int  getMSDKVersion( void  *  pmfxVersion,  int  *  piImpl,  int  *  piImpl_baseType  )
{
	mfxSession session = NULL;
	mfxVersion ver = {MFX_VERSION_MINOR, MFX_VERSION_MAJOR};
	mfxStatus  sts;
	mfxIMPL  impl  =  MFX_IMPL_SOFTWARE;

	sts  =  MFXInit( MFX_IMPL_AUTO, &ver, &session );
	if  (  sts  ==  MFX_ERR_NONE  )  {
		MFXQueryVersion( session, &ver);
		MFXQueryIMPL(  session,  &impl  );
		MFXClose( session );
	}

	//
	int  impl_baseType  =  MFX_IMPL_BASETYPE(  impl  );
		
	//
	if  (  sts  ==  MFX_ERR_NONE  )  {
		if  (  pmfxVersion  )  {
			*(  mfxVersion  *  )pmfxVersion  =  ver;
		}
		if  (  piImpl  )  *piImpl  =  impl;
		if  (  piImpl_baseType  )  *piImpl_baseType  =  impl_baseType;


	}

	//
	//		
	TCHAR	tBuf[128]	=	_T(  ""  );		
	if  (  sts  ==  MFX_ERR_NONE  )  {
		TCHAR  *  implStr  =  (  TCHAR  *  )getImplStr(  impl_baseType  );
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "getMSDKVersion: Hw%d.%d: impl %d, impl_baseType %d, %s"  ),  (  int  )ver.Major,  (  int  )ver.Minor,  impl,  impl_baseType,  implStr  );
	    }
	else  {
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "getMSDKVersion failed"  )  );
	}
	tmp_showInfo(  tBuf  );


	return  sts  ==  MFX_ERR_NONE  ?  0  :  -1;
}
#endif

//  2015/10/07
BOOL IsSupported_hwAcclD11( void  *  pmfxVersion )	//  mfxVersion  * 
{
	BOOL  bRet  =  FALSE;
	mfxInitParam initPar;
    
	mfxVersion ver = {MFX_VERSION_MINOR, MFX_VERSION_MAJOR};
	mfxStatus  sts;
	mfxIMPL  impl  =  MFX_IMPL_SOFTWARE;


    MSDK_ZERO_MEMORY(initPar);

    // we set version to 1.0 and later we will query actual version of the library which will got leaded
    initPar.Version.Major = 1;
    initPar.Version.Minor = 0;
	  
    

	//  2015/09/27
	BOOL  bUseHWLib =  TRUE;
	
	mfxSession m_mfxSession;     
	memset(&m_mfxSession, 0, sizeof(m_mfxSession));

	int  impl_baseType  =  0;

    // Init session
    //  if (bUseHWLib) 
	{
        // try searching on all display adapters
        initPar.Implementation = MFX_IMPL_HARDWARE_ANY;

        // if d3d11 surfaces are used ask the library to run acceleration through D3D11
        // feature may be unsupported due to OS or MSDK API version
        //  if (D3D11_MEMORY == pParams->memType)
            initPar.Implementation |= MFX_IMPL_VIA_D3D11;



		sts = MFXInitEx(  initPar,  &m_mfxSession);


        // MSDK API version may not support multiple adapters - then try initialize on the default
        if (MFX_ERR_NONE != sts) {
            initPar.Implementation = (initPar.Implementation & !MFX_IMPL_HARDWARE_ANY) | MFX_IMPL_HARDWARE;
			sts = MFXInitEx(initPar,  &m_mfxSession);
        }
	}
	
		
	if  (  sts  ==  MFX_ERR_NONE  )  {
		MFXQueryVersion( m_mfxSession, &ver);		
		MFXQueryIMPL(  m_mfxSession,  &impl  );		
		MFXClose( m_mfxSession );	
     
		//	
		impl_baseType  =  MFX_IMPL_BASETYPE(  impl  );	
		switch  (  impl_baseType  )  {
				case  MFX_IMPL_HARDWARE:
				case  MFX_IMPL_HARDWARE2:
				case  MFX_IMPL_HARDWARE3:
				case  MFX_IMPL_HARDWARE4:
					  bRet  =  TRUE;
					  break;
				default:
						break;
		}

		//
		if  (  pmfxVersion  )  {
			*(  mfxVersion  *  )pmfxVersion  =  ver;
		}
#if  0
		if  (  piImpl  )  *piImpl  =  impl;
		if  (  piImpl_baseType  )  *piImpl_baseType  =  impl_baseType;
#endif

	}


	//
	//		
	TCHAR	tBuf[128]	=	_T(  ""  );		
	if  (  sts  ==  MFX_ERR_NONE  )  {
		TCHAR  *  implStr  =  (  TCHAR  *  )getImplStr(  impl_baseType  );
		_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "IsSupported_hwAcclD11: Hw%d.%d: impl %d, impl_baseType %d, %s, bRet %d"  ),  (  int  )ver.Major,  (  int  )ver.Minor,  impl,  impl_baseType,  implStr,  bRet  );
	    }
	else  {
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "IsSupported_hwAcclD11 failed"  )  );
	}
	tmp_showInfo(  tBuf  );


	return  bRet;

}


//
BOOL  IsSupported_sharedTex_msdk(  const  void  *  pmfxVersion  )
{
	//	
	unsigned  char  ucbUsing_sharedTex  =  FALSE;

	if  (  !pmfxVersion  )  return  FALSE;	
	mfxVersion  *  pVer  =  (  mfxVersion  *  )pmfxVersion;
				   		
					
	//  2015/09/27
	#define		MIN_hdDec_majorVer_sharedTex	1
	#define		MIN_hdDec_minorVer_sharedTex	8	//  2015/10/18.1.8¬Ohd4400	//  11

	//  2017/10/08
#ifdef  _DEBUG
		#if  0
			 #undef			MIN_hdDec_minorVer_sharedTex
			 #define		MIN_hdDec_minorVer_sharedTex	4		//  2017/10/08. hd graphics 3000. dell notebook
		#endif
#endif
			
	//			
	if  (  pVer->Major  >=  MIN_hdDec_majorVer_sharedTex									
		&&  pVer->Minor  >=  MIN_hdDec_minorVer_sharedTex  )					   		
	{
		ucbUsing_sharedTex  =  TRUE;					
	}				   
	


errLabel:
	 return  ucbUsing_sharedTex;
}



