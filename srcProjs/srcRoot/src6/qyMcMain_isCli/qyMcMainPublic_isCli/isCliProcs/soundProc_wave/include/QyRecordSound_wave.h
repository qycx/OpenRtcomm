#if !defined(AFX_QYRECORDSOUND_H__E2DAB5D9_A1CA_4D40_A190_0C88FF4BEFB5__INCLUDED_)
#define AFX_QYRECORDSOUND_H__E2DAB5D9_A1CA_4D40_A190_0C88FF4BEFB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyRecordSound.h : header file
//

#include	"qyMcMainRealTimeMediaProc.h"



#if  0  

/////////////////////////////////////////////////////////////////////////////
// CQyRecordSound thread

class CQyRecordSound : public CWinThread
{
	DECLARE_DYNCREATE(CQyRecordSound)
public:
	CQyRecordSound(  );           // protected constructor used by dynamic creation

	CQyMalloc							mallocObj_pPkt;
	CQyMalloc							mallocObj_pMsgBuf;
	struct								{

		MC_VAR_isCli					*	pProcInfo;
		CAP_procInfo_recordSound	*	pRecord;

		BOOL							bStarted;
		DWORD							dwTickCnt_startToEndThread;

        HWAVEIN							m_hRecord;

		WAVEFORMATEX				*	pWfx;
		//  unsigned  int					uiBytesRecorded_perBlockAlign;
		unsigned  int					uiBytesRecorded;

		//
		int								m_iSoundBuffers;

		//
		myPLAY_AUDIO_DATA			*	pPkt;
		MIS_MSGU					*	pMsgBuf;

	}									m_var;

// Attributes
public:

// Operations
public:
	
	void displayError(int errcode,char []);

	LPWAVEHDR  CreateWaveHeader(  unsigned  int  uiBytesRecorded  );
	void  AllocateBuffers(  int  nBuffers,  unsigned  int  uiBytesRecorded  );

private:

	BOOL	bStartRecording(WPARAM wp,LPARAM lp);
	BOOL	bStopRecording(WPARAM wp,LPARAM lp);
	BOOL	bEndThread(WPARAM wp,LPARAM lp);

public:
	virtual void ProcessSoundData(BYTE* sound, DWORD dwSamples);
	void OnSoundData(HWAVEIN hwl,UINT uMsg,  DWORD dwInstance,  DWORD dwParam1, DWORD dwParam2);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyRecordSound)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQyRecordSound();

	// Generated message map functions
	//{{AFX_MSG(CQyRecordSound)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnQyPostComm( UINT, LONG );

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif

#include	"qyThread.h"

// CQyRecordSound thread

class CQyRecordSound : public CQyThread
{
public:
	CQyRecordSound(  );           // protected constructor used by dynamic creation

	struct								{
		RECORD_soundCb_var				cb;

		HWAVEIN							m_hRecord;

		void					*		pModule;
		void					*		pDev;
	}									m_var;

// Attributes
public:

// Operations
public:
	
	void displayError(int errcode,char []);

	LPWAVEHDR  CreateWaveHeader(  unsigned  int  uiBytesRecorded  );
	void  AllocateBuffers(  int  nBuffers,  unsigned  int  uiBytesRecorded  );

private:

	BOOL	bStartRecording(WPARAM wp,LPARAM lp);
	BOOL	bStopRecording(WPARAM wp,LPARAM lp);
	BOOL	bEndThread(WPARAM wp,LPARAM lp);

public:
	virtual void ProcessSoundData(BYTE* sound, DWORD dwSamples);
	void OnSoundData(HWAVEIN hwl,UINT uMsg,  LPWAVEHDR  lpWaveHdr  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyRecordSound)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual  LRESULT procMsg(  UINT  msg,  WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQyRecordSound();

	// Generated message map functions
	//{{AFX_MSG(CQyRecordSound)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	void OnQyPostComm( UINT, LONG );

};




#endif // !defined(AFX_QYRECORDSOUND_H__E2DAB5D9_A1CA_4D40_A190_0C88FF4BEFB5__INCLUDED_)
