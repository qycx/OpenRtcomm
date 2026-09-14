

#ifndef  __amd_filter_msg_public_h__
#define  __amd_filter_msg_public_h__		//  {


//
#define		CONST_nWhere_hg_afterAccepted					1
//
//#define		CONST_nWhere_hg_serviceAccepted				3





//
extern  "C"  __declspec(dllexport)  int  and_filter_msg_skipMyData(char** ppContentParam, unsigned  int* plen_contentParam, BOOL* pbNeedContentConvrted,
		QY_BUF* pBuf_help,
		QY_MESSENGER_ID* pIdInfo_from, QY_MESSENGER_ID* pIdInfo_to);




#endif  //  }


