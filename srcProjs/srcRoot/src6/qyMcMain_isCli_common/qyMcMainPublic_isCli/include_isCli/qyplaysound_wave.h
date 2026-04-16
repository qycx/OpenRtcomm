#if !defined(AFX_QYPLAYSOUND_H__E8DE0E0A_F43E_49F8_A765_B6AA0427DB5C__INCLUDED_)
#define AFX_QYPLAYSOUND_H__E8DE0E0A_F43E_49F8_A765_B6AA0427DB5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyPlaySound.h : header file
//

#ifndef  __WINCE__
	//#include	<afxmt.h>
#endif

#include	"qyMcMainRealTimeMediaProc.h"


#if  0  

/////////////////////////////////////////////////////////////////////////////
// CQyPlaySound thread

class CQyPlaySound : public CWinThread
{
	DECLARE_DYNCREATE(CQyPlaySound)
public:
	CQyPlaySound(  );           // protected constructor used by dynamic creation

// Attributes
private:
	struct							{
		MC_VAR_isCli				*	pProcInfo;
		QY_PLAYER				*	pPlayer;

		//  BOOL						bStarted;
		BOOL						bDevOk;
		DWORD						dwTickCnt_startToEndThread;
				
		int							m_nOutputBuffers;
		
		HWAVEOUT					m_hPlay;
		
		char					*	pBuf;
		unsigned  int				uiBufSize;


		//  2010/06/21
		struct						{
			LONGLONG				rtPlaying;
			BOOL					bModified_uiSampleTimeInMs_audio;
			//
			int						iIndex_toFill;
			struct					{
				void			*	lpHdr;
				int					iSampleTimeInMs;
				unsigned  int		ui_rtTimeLen;
				DWORD				dwTickCnt;
			}						mems[10];
		}							helpStruct;

public:



	}								m_var;

private:

// Operations

	
private:
	
	BOOL bStartPlaying(WPARAM wParam, LPARAM lParam);
	BOOL bStopPlaying(WPARAM wParam, LPARAM lParam);
	BOOL bEndThread(WPARAM wParam, LPARAM lParam);

private:

	LPWAVEHDR  CreateWaveHeader(  unsigned  int  uiBytesRecorded_perBlockAlign  );

	void displayError(int code,char []);
	virtual void ProcessSoundData(BYTE *sound, DWORD dwSamples);
	LRESULT OnWriteSoundData(WPARAM wParam, LPARAM lParam);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyPlaySound)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQyPlaySound();
private:

	// Generated message map functions
	//{{AFX_MSG(CQyPlaySound)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg  void  OnMmWomOpen(WPARAM wParam, LPARAM lParam);
	afx_msg  void  OnEndPlaySoundData(WPARAM wParam, LPARAM lParam);
	afx_msg  void  OnQyPostComm( UINT, LONG );

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif

#include	"qyThread.h"
#include	"ctxQmc.h"

class CQyPlaySound : public CQyThread
{
public:
	CQyPlaySound(  );           // protected constructor used by dynamic creation

// Attributes
private:
	struct							{
		MC_VAR_isCli				*	pProcInfo;
		QY_PLAYER				*	pPlayer;

		//  BOOL						bStarted;
		BOOL						bDevOk;
		DWORD						dwTickCnt_startToEndThread;
				
		int							m_nOutputBuffers;
		
		HWAVEOUT					m_hPlay;
		
		char					*	pBuf;
		unsigned  int				uiBufSize;


		//  2010/06/21
		struct						{
			LONGLONG				rtPlaying;
			BOOL					bModified_uiSampleTimeInMs_audio;
			//
			int						iIndex_toFill;
			struct					{
				void			*	lpHdr;
				int					iSampleTimeInMs;
				unsigned  int		ui_rtTimeLen;
				DWORD				dwTickCnt;
			}						mems[20];
		}							helpStruct;

public:



	}								m_var;

private:

// Operations

	
private:
	
	BOOL bStartPlaying(WPARAM wParam, LPARAM lParam);
	BOOL bStopPlaying(WPARAM wParam, LPARAM lParam);
	BOOL bEndThread(WPARAM wParam, LPARAM lParam);

private:

	LPWAVEHDR  CreateWaveHeader(  unsigned  int  uiBytesRecorded_perBlockAlign  );

	void displayError(int code,char []);
	virtual void ProcessSoundData(BYTE *sound, DWORD dwSamples);
	LRESULT OnWriteSoundData(WPARAM wParam, LPARAM lParam);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyPlaySound)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual  LRESULT procMsg(  UINT  msg,  WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQyPlaySound();
private:

	// Generated message map functions
	//{{AFX_MSG(CQyPlaySound)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	void  OnMmWomOpen(WPARAM wParam, LPARAM lParam);
	void  OnEndPlaySoundData(WPARAM wParam, LPARAM lParam);
	void  OnQyPostComm( UINT, LONG );

};


#endif // !defined(AFX_QYPLAYSOUND_H__E8DE0E0A_F43E_49F8_A765_B6AA0427DB5C__INCLUDED_)
