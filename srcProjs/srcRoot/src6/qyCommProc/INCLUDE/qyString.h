

#ifndef  __QYSTRING_H__
#define  __QYSTRING_H__		//  {


class  CQyString						{

		TCHAR					*		m_ptBuf;

public:
		CQyString(  );
		CQyString(  LPCTSTR  val  );
		CQyString(  char  *  val  );

		//
		CQyString(  const  CQyString  &  );

		//
		~CQyString(  );

protected:
		void							clear(  );
		void							stringCpy(  LPCTSTR  src  );
		void							concatCpy(  LPCTSTR  src1,  LPCTSTR  src2  );

public:
		//
		operator  LPCTSTR(  )  const;
		CQyString  &  operator  =  (  const  CQyString  &  );
		CQyString  &  operator  +=  (  const  CQyString  &  );
		//  
		friend  CQyString  operator+  (  CQyString  &  src1,  CQyString  &  src2  );
		friend  CQyString  operator+  (  CQyString  &  src1,  LPCTSTR  str2  );
		friend  CQyString  operator+  (  CQyString  &  src1,  char  *  str2  );

		//
		friend  CQyString  operator+  (CQyString src1, CQyString src2);


		//
		TCHAR  operator  [](  int  nIndex  );

		//
		CQyString  &  Trim(  );
		
		//
		LPCTSTR							GetBuffer(  int nMinBufferLength  =  0  );
		unsigned  int					GetLength(  );


};



#endif  //  }


