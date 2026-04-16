#pragma once



//
typedef  struct  __dlgGuiDataMsgInput_t									{

				 //
				 BOOL												bInfoSet;

				 //  2012/05/18
				 int												iIDC_EDIT_input;

				 //
				 BOOL												bFinished_createCtrls;
				 BOOL												bCreated;					//  这个标志位用来表明是否Create(  )成功了。成功了，则将资源的释放留给了dlg自己(在PostNcDestroy(  )中delete)


}		 DLG_guiData_msgInput;


typedef	struct  __dlgMsgInputVar_t			{
			HWND							m_hParent;
			int								m_nID;
			
			//
			BOOL							bInitFailed;				//  2007/09/04

			//
			HWND							hDlgTalk;


			//
			DLG_guiData_msgInput			guiData;

			//
			DLG_syncFlgs					syncFlgs;

	}		DLG_msgInput_var;





// CDlgMsgInput dialog

class CDlgMsgInput : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMsgInput)

public:
	CDlgMsgInput(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMsgInput();

// Dialog Data
	enum { IDD = IDD_msgInput };

	//
	DLG_msgInput_var	m_var;
	
	//
	BOOL  bSetInfo(  );
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
};
