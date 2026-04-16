
#ifndef  __qisSyncTex_h__
#define  __qisSyncTex_h__	//  {

#include	"qysynccommproc.h"
#include <tmpDefs_open.h>


//
typedef  struct  __qisSharedTexInfo_t {
				 int dwProcessId;
				 int index_mosaic;
				 int tn_sharedTex;
				 int real_index;
				 void* m_shared_pTex12;

				 //
				 //int	index_

				 //
				 TCHAR  lockHint[128];

				 //
				 bool  bLocked;

}		 QisSharedTexInfo;

//
#define		isEmpty_qisSharedTexInfo(p)		(  !p->dwProcessId  &&  !p->index_mosaic  &&  !p->tn_sharedTex  )


//
#define		MAX_sharedTexInfos					100


//
#define		CONST_mtxName_syncSharedTexs		_T("syncSharedTexs")


//
typedef  struct  __qisSharedTexInfos_t	{
				 unsigned  int			uiMaxCnt;
				 unsigned  int			uiCnt;
				 QisSharedTexInfo		mems[MAX_sharedTexInfos];

}		 QisSharedTexInfos;


//
int qisSharedTexInfos_init(  int uiMaxCnt,  QisSharedTexInfos  **  pp);
int qisSharedTexInfos_exit(QisSharedTexInfos** pp);

//
int addToQisSharedTexInfos(int dwProcessId, int index_mosaic, int tn_sharedTex, int real_index, void* m_shared_pTex12, QisSharedTexInfos* pQisSharedTexInfos);
int removeFromQisSharedTexInfos(int dwProcessId, int index_mosaic, int tn_sharedTex, int real_index, QisSharedTexInfos* pQisSharedTexInfos);






//
class QisSyncTex
{
	struct {
		
		bool  m_bSynced;

		QisSharedTexInfos* m_pQisSharedTexInfos;
		int  m_index_mem;

	}		m_var;

	//
	CQySyncFlg  syncFlg;


	//
public:
	QisSyncTex();
	~QisSyncTex();


	//
	int getPtr(QisSharedTexInfos* pQisSharedTexInfos, int processId, int index_mosaic, int tn, LPCTSTR  lockHint,  void** pptr);

	//
	int showLock();
	


};




//
#endif  //  }


