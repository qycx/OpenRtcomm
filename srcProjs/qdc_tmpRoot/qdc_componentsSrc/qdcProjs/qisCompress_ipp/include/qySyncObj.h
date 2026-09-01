

#ifndef  __QYSYNCOBJ_H__
#define  __QYSYNCOBJ_H__	//  {

#define		DEFAULT_milliseconds_syncQmObjQ			10  *  1000


 HANDLE  syncQmObjQ(  LPCTSTR  mutexName,  unsigned  int  uiTimeoutInMilliseconds  ); 
 void  cancelSyncQmObjQ(  HANDLE  hMutex  );


typedef  struct  __syncObjParam_t					{
				 LPCRITICAL_SECTION					lpCriticalSection;					 
				 TCHAR							*	pMutexName;
}		 SYNC_OBJ_PARAM;


class  CQySyncObj  {
 
		struct					{
			LPCRITICAL_SECTION	lpCriticalSection;	
			HANDLE				hMutex;		
			BOOL				bLocked;
		}						m_var;

 public:
	    CQySyncObj(  )  {  memset(  &m_var,  0,  sizeof(  m_var  )  );	  };
		
		//  int  sync(  LPCTSTR  mutexName  )  {  m_var.hMutex  =  syncQmObjQ(  mutexName,  DEFAULT_milliseconds_syncQmObjQ  );  return  m_var.hMutex  ?  0  :  -1;  };
		int  sync(  LPCTSTR  mutexName,  unsigned  int  uiMilliSeconds  =  DEFAULT_milliseconds_syncQmObjQ  )  {  m_var.hMutex  =  syncQmObjQ(  mutexName,  uiMilliSeconds  );  return  m_var.hMutex  ?  0  :  -1;  };

		int  sync(  SYNC_OBJ_PARAM  *  p,  unsigned  int  uiMilliSeconds  =  DEFAULT_milliseconds_syncQmObjQ  )  {  
				if  (  !p  )  return  -1;
				if  (  m_var.bLocked  )  return  -1;
				if  (  p->lpCriticalSection  )  {
					if  (  !uiMilliSeconds  )  {
						if  (  !TryEnterCriticalSection(  p->lpCriticalSection  )  )  return  -1;
						}
					else  {
						  EnterCriticalSection(  p->lpCriticalSection  );
					}
					m_var.lpCriticalSection  =  p->lpCriticalSection;
					m_var.bLocked  =  TRUE;
					return  0;
				}
				return  sync(  p->pMutexName,  uiMilliSeconds  );
		}

		~CQySyncObj(  )  {  
			if  (  m_var.lpCriticalSection  )  LeaveCriticalSection(  m_var.lpCriticalSection  );
			if  (  m_var.hMutex  )  cancelSyncQmObjQ(  m_var.hMutex  );  
		};
 };



#endif  //  }


