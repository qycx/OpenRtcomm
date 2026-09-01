
#ifndef  __QYWND_H__
#define  __QYWND_H__	//  {




class  CQyWnd					{
public:
		HWND					m_hWnd;

		struct					{
			int					iWndContentType;	
			int					iSubtype;					//  2012/04/02
		}						m_var;
		
		//
		CQyWnd(  );
		virtual  ~CQyWnd(  );
		
		int				getWndContentType(  );  
		int				getWndContentSubtype(  );

		//
		virtual  void  *  getGuiData(  )  =  NULL;
		virtual  void  *  getVar(  )  =  NULL;

		//  BOOL Attach(  HWND hWndNew  );
		static CQyWnd* FromHandle(  HWND  hWnd  );
		static CQyWnd* FromHandlePermanent(HWND hWnd);



};



#endif  //  }


