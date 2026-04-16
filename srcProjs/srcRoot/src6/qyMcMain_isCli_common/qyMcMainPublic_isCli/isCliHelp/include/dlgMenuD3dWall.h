

#pragma once


typedef  struct  __dlgGuiDataMenuD3dWall_t							{
				 BOOL												bInited;

				 int												iWndContentType;

				 int												iIDC_BUTTON_contact;
				 int												iIDC_BUTTON_group;
				 //
				 int												iIDC_BUTTON_fullScreen;
				 //
				 int												iIDC_BUTTON_openQvw;
				 int												iIDC_BUTTON_closeQvw;
				 //
				 int												iIDCANCEL;
				 //
				 int												iIDC_BUTTON_close;					//  2014/12/07
				 int												iIDC_BUTTON_setBg;
				 //
				 //
				 int												w_org,  h_org;
				 RECT												rcIDC_BUTTON_contact;	
				 RECT												rcIDC_BUTTON_group;
				 //
				 RECT												rcIDC_BUTTON_fullScreen;
				 //
				 RECT												rcIDC_BUTTON_openQvw;
				 RECT												rcIDC_BUTTON_closeQvw;
				 //
				 RECT												rcIDC_BUTTON_setBg;
				 //
				 RECT												rcIDCANCEL;

				 //
				 RECT												rcIDC_BUTTON_close;

			 
				 //  BOOL												m_bFullScreen_parent;
				 int												iWndContentType_hParent;		//  2013/07/12


}		 DLG_guiData_menuD3dWall;

typedef  struct  __dlgMenuD3dWallVar_t								{	
				 DLG_guiData_menuD3dWall							guiData;

				 //  UINT_PTR											wTimerID;

}		 DLG_menuD3dWall_var;



#include	"qyWnd.h"

class CDlgMenuD3dWall : public CQyWnd
{

public:
	CDlgMenuD3dWall(  );   // standard constructor
	virtual ~CDlgMenuD3dWall();

// Dialog Data
	//  enum { IDD = IDD_mcClient_logon };

	DLG_menuD3dWall_var			m_var;


	virtual  void  *  getGuiData(  )  {  return  &m_var.guiData;  }
	virtual  void  *  getVar(  )  {  return  &m_var;	}

};
