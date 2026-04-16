#pragma once


typedef  struct  __dlgGuiDataMenuIsCli_t							{
				 BOOL												bInited;

				 int												iWndContentType;
				 
				 //
				 int												w_org,  h_org;

				 //
				 int												iIDC_BUTTON_contact;
				 RECT												rcIDC_BUTTON_contact;	
				 				 
				 int												iIDC_BUTTON_group;
				 RECT												rcIDC_BUTTON_group;

				 //
				 int												iIDC_BUTTON_fullScreen;
				 RECT												rcIDC_BUTTON_fullScreen;
				 //
				 int												iIDC_BUTTON_viewOfflineRes;
				 RECT												rcIDC_BUTTON_viewOfflineRes;
				 //
				 int												iIDC_BUTTON_testLocalAv;
				 RECT												rcIDC_BUTTON_testLocalAv;
				 int												iIDC_BUTTON_playRemoteAudio;
				 RECT												rcIDC_BUTTON_playRemoteAudio;
				 //
				 int												iIDC_BUTTON_policy;
				 RECT												rcIDC_BUTTON_policy;
				 //
				 int												iIDC_BUTTON_openQvw;					//  2015/11/29
				 RECT												rcIDC_BUTTON_openQvw;					//  2015/11/29
				 int												iIDC_BUTTON_closeQvw;
				 RECT												rcIDC_BUTTON_closeQvw;
				 //
				 int												iIDC_BUTTON_conferenceQuality;
				 RECT												rcIDC_BUTTON_conferenceQuality;
				 //
				 int												iIDC_BUTTON_close;
				 RECT												rcIDC_BUTTON_close;
				 int												iIDC_BUTTON_about;
				 RECT												rcIDC_BUTTON_about;
				 //
				 int												iIDC_STATIC_meDesc;
				 RECT												rcIDC_STATIC_meDesc;
				 //
				 int												iIDCANCEL;
				 RECT												rcIDCANCEL;
				 //

				 //			 
				 int												iWndContentType_hParent;		//  2013/07/12


}		 DLG_guiData_menuIsCli;

typedef  struct  __dlgMenuIsCliVar_t								{	
				 DLG_guiData_menuIsCli								guiData;

				 //  UINT_PTR											wTimerID;

}		 DLG_menuIsCli_var;

// CDlgMenuIsCli dialog


#include	"qyWnd.h"

class CDlgMenuIsCli : public CQyWnd
{

public:
	CDlgMenuIsCli(  );   // standard constructor
	virtual ~CDlgMenuIsCli();

// Dialog Data
	//  enum { IDD = IDD_mcClient_logon };

	DLG_menuIsCli_var			m_var;


	virtual  void  *  getGuiData(  )  {  return  &m_var.guiData;  }
	virtual  void  *  getVar(  )  {  return  &m_var;	}

};
