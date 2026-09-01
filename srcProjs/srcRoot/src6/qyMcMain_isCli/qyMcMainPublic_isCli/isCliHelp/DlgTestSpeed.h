#pragma once



//
		typedef  struct								{
			struct  {
				DWORD								dwTickCnt_start;
				int									nB_perSend;
				//	
				int									nTimes_sent_perTest;
				//	
				int									nTotal_perTest;		//  =  5
				//
				struct  {
					struct							{
						unsigned  int				tn_perSend;
						//
						BOOL						bReplied;
					}								mems[10];
				}									repliesInfo;

			}										cur;
			//
			//int							nBPerIncre;
			//
			struct						{
				int						nB_perSend;
			}							bottom;		//  ok
			
			struct						{
				int						nB_perSend;
			}							top;		//  failed

			//
			BOOL						bStopped;
	
		}								TEST_speed_info;




// CDlgTestSpeed dialog

class CDlgTestSpeed : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTestSpeed)

public:
	CDlgTestSpeed(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTestSpeed();

// Dialog Data
	enum { IDD = IDD_testSpeed };

	struct  {
		CWnd					*		m_pParent;		
		int								m_nID;
		
		BOOL							bCreated;					//  Õâ¸ö±êÖ¾Î»ÓÃÀ´±íÃ÷ÊÇ·ñCreate(  )³É¹¦ÁË¡£³É¹¦ÁË£¬Ôò½«×ÊÔ´µÄÊÍ·ÅÁô¸øÁËdlg×Ô¼º(ÔÚPostNcDestroy(  )ÖÐdelete)
		BOOL							bInited;					//  ±íÃ÷htmlEditºÍ¶Ô»°¶¼³õÊ¼»¯ÍêÁË.

		//
		int								iIntervalInMs_timer;
		float							fTimesPerSecond_timer;
		//
		int								timerId;
		BOOL							bTimerStarted;


		//  先设置一个初值，比如1M上传。传5次，不迟于100ms,回收5次，就算成功。
		//		如果行，则存入bottom. 设置kBPerIncre为1M上传，设置cur.kBPer=kbPerInc+last.kbPer,传5次。
		//			如果行，cur.kBPer存入bottom
		//			如果不行，存入top
		//		遇到top后，则kpPerIncre=(top-bottom)/2;设置cur再测试
		//      再top<=bottom+10kB后测试终止。
		//		如果一直没有top,就以bottom.kBPer到100MB终止测试。




		//
		TEST_speed_info					test;


	}		m_var;


	//
	BOOL  bSetDlgInfo(  int  iWndContentType,  int  iSubType,  LPCTSTR  title,  int  iResId_menu  );
	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		
	



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtontest();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
