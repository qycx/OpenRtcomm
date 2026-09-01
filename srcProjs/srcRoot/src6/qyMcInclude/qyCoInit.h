

#ifndef  __qyCoInit_h__
#define  __qyCoInit_h__		//  {

//
#ifndef  __useQt__
#define  __USE_oleInit__
#endif

//
//  2010/06/07
class  CQyCoInit	{
		struct		{
			BOOL	bInited;
		}			m_var;
public:
		CQyCoInit(  )  {
			memset(  &m_var,  0,  sizeof(  m_var  )  );
			DWORD dwCoInit  =  COINIT_APARTMENTTHREADED;	// COINIT_MULTITHREADED. 2013/06/17
			//
			#ifdef  __USE_oleInit__		//  2018/07/03
					if  (  S_OK  ==  OleInitialize(  NULL  )  )  {
						m_var.bInited  =  TRUE;
					}
			#else
				if  (  SUCCEEDED(  CoInitializeEx(  NULL,  dwCoInit  )  )  )  {
					m_var.bInited  =  TRUE;
				}
			#endif
		}
		~CQyCoInit(  )  {
			if  (  m_var.bInited  )  {
				#ifdef  __USE_oleInit__  //  2018/07/03
						OleUninitialize(  );
				#else
						CoUninitialize(  );
				#endif
			}
		}
};





#endif  //  }



