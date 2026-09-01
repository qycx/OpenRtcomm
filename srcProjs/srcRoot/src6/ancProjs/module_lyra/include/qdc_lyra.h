#include <genericqueue.h>

#ifndef  __qdcLyra_h__
#define  __qdcLyra_h__	//  {

//
class CQdcObj_lyra {
public:
	
	//
	bool bDec;
	
	//
	struct {
		char *	pBuf;
		//
		int		iBufSize;
		int		len;
	}		in;

	//
	struct {
		char	* pBuf;
		//
		int		iBufSize;
		int		len;
	}		output;

	//
	struct {
		bool  bQuit;

		//
		void* pLyra_encDec;

		//
		HANDLE  hThread_encDec;
		DWORD  dwThreadId_encDec;

		//
		int last_pts;

	}	m_var;


	//
	GENERIC_Q	m_q_in;		bool  m_bInited_q_in;
	GENERIC_Q	m_q_out;	bool  m_bInited_q_out;





	//
public:
	CQdcObj_lyra() {
		//m_index_qdcUnit = -1;
		//
		bDec = false;
		//
		memset(&in, 0, sizeof(in));
		memset(&output, 0, sizeof(output));
		//
		memset(&m_var, 0, sizeof(m_var));

		//
		m_bInited_q_in = false;
		m_bInited_q_out = false;

		//
		return;
	}



};




//
#endif  //  }


