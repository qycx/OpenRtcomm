
#ifndef  __qyStatusStruct_h__
#define  __qyStatusStruct_h__	//  {


typedef  struct  __qyStatusStruct_t {

	unsigned  short				usLangId;

	QNM_CUSRES_INFO				cusRes;
	unsigned  char					ucbCusResInited;

	BOOL							bQuit;

	//
	GENERIC_Q						inputQ;
	bool							bInited_inputQ;

	//
	HANDLE							hThreads[2];

	HWND							hPs;									//  propertySheet的句柄，2006/08/16

	TCHAR							serviceStatus_netMc[255 + 1];				//  用来保存
	TCHAR							qmdState_netMc[255 + 1];
	TCHAR							serviceStatus_is[255 + 1];
	TCHAR							qmdState_is[255 + 1];

	//
	struct {
		int						nPipes;
		int						nConnections;
	}								pipe;

	//
	struct {
		unsigned  short			usPort;
		int						maxConns;
		long						nConnetions;
	}								sock;

	//
	HWND							hWnd_sys;
	HWND							hWnd_tasks;
	HWND							hWnd_players;
	HWND							hWnd_talks;
	HWND							hWnd_qs;
	HWND							hWnd_others;


	//
}		 QY_STATUS_STRUCT;

#endif  //  }


