

#ifndef  __QYTHREAD_H__
#define  __QYTHREAD_H__		//  {


class  CQyThread  {
public:
		CQyThread(  );
		virtual  ~CQyThread(  );

		HANDLE				m_hThread;       // this thread's HANDLE
		DWORD				m_nThreadID;      // this thread's ID

		BOOL  CreateThread(  DWORD dwCreateFlags = 0,  UINT nStackSize = 0,  LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL );
 
		DWORD  ResumeThread();
		BOOL  PostThreadMessage(UINT message, WPARAM wParam, LPARAM lParam);

		virtual  BOOL InitInstance();
		virtual  int ExitInstance(); // default will 'delete this'

		virtual  LRESULT procMsg(  UINT  msg,  WPARAM wParam, LPARAM lParam);

};



#endif  //  }


