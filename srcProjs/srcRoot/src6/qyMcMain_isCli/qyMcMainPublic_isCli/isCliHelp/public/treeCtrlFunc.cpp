
#include	"stdafx.h"
#include	<CommCtrl.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"


#include	"myresource.h"

#include	"qyMcMainWndProc.h"

#include	"afxdialogex.h"


#include	"funcsForIsCliHelp.h"
#include	"isCliHelpPublic.h"
#include	"dlgtalkproc.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcCmdProc.h"
#include	"qyAvRecordPublic.h"
#include	"tmpCeLib.h"

#include	"myDb.h"

#include	"qyDynLib.h"
#include	"qyCusResTemp.h"
#include	"qmcSharePublic.h"
#include	"funcsForIsCliHelp.h"
#include	"isCliD3dPublic.h"
#include	"imgProcessPublic.h"
#include	"genericHash.h"
#include	"imObjHash.h"

#include	"qmcCommFunc_isCli.h"
#include	"qmcCopyData.h"
#include	"rtspUsrData.h"

#include	"qisPipe_open.h"

//
#include	"objType_tmp.h"
#include	"qyMessengerHelpPublic.h"
#include	"isCliExPublic.h"


//
 // 执行此函数须通过SetItemData( )设置数据，条目掩码中须包括TVIF_PARAM.
 // 注：未测试，摘自《Visual C++ 图形用户界面开发指南》P277.
 __declspec(  dllexport  )  HTREEITEM treeCtrl_FindItemData( void  *  pTreeCtrl,  DWORD lParam, BOOL bDownDir, HTREEITEM hItem )
{
	CTreeCtrl  *  m_TreeCtrl  =  (  CTreeCtrl  *  )pTreeCtrl;

	 HTREEITEM htiSel = hItem ? hItem : m_TreeCtrl->GetSelectedItem( );
	 HTREEITEM htiCur = bDownDir ? treeCtrl_GetNextItem( m_TreeCtrl,  htiSel,  FALSE ) : treeCtrl_GetPrevItem( m_TreeCtrl,  htiSel,  FALSE );
	 if ( htiCur == NULL ) {
		 if ( bDownDir ) 
			 htiCur = m_TreeCtrl->GetRootItem( );
		 else
			 htiCur = treeCtrl_GetLastItem( m_TreeCtrl,  NULL );
	 }
	 while ( htiCur && htiCur != htiSel ) {

		 DWORD sItemData = m_TreeCtrl->GetItemData( htiCur );
		 
		 if ( sItemData == lParam )
			 return htiCur;
		 htiCur = bDownDir ? treeCtrl_GetNextItem( m_TreeCtrl,  htiCur,  FALSE ) : treeCtrl_GetPrevItem( m_TreeCtrl,  htiCur,  FALSE );
		 if ( htiCur == NULL ) {
			 if ( bDownDir )
				 htiCur = m_TreeCtrl->GetRootItem( );
			 else
				 htiCur = treeCtrl_GetLastItem( m_TreeCtrl,  NULL );
		 }
	 }
	 return NULL;
}



 //
  __declspec(  dllexport  )  HTREEITEM treeCtrl_FindChildItemData( void  *  pTreeCtrl,  DWORD lParam, BOOL bDownDir, HTREEITEM hItem )
{
	CTreeCtrl  *  m_TreeCtrl  =  (  CTreeCtrl  *  )pTreeCtrl;
	
	BOOL  bNoParentItem  =  TRUE;

	//
	if  (  !m_TreeCtrl->ItemHasChildren(  hItem  )  )  {
		return  NULL;
	}
	hItem  =  m_TreeCtrl->GetChildItem(  hItem  );

	//
	 HTREEITEM htiSel = hItem;
	 HTREEITEM htiCur = bDownDir ? treeCtrl_GetNextItem( m_TreeCtrl,  htiSel,  bNoParentItem ) : treeCtrl_GetPrevItem( m_TreeCtrl,  htiSel,  bNoParentItem );
	 if ( htiCur == NULL ) {
#if  0
		 if ( bDownDir ) 
			 htiCur = m_TreeCtrl->GetRootItem( );
		 else
			 htiCur = treeCtrl_GetLastItem( m_TreeCtrl,  NULL );
#endif
		 return  NULL;
	 }
	 while ( htiCur && htiCur != htiSel ) {

		 DWORD sItemData = m_TreeCtrl->GetItemData( htiCur );
		 
		 if ( sItemData == lParam )
			 return htiCur;
		 htiCur = bDownDir ? treeCtrl_GetNextItem( m_TreeCtrl,  htiCur,  bNoParentItem ) : treeCtrl_GetPrevItem( m_TreeCtrl,  htiCur,  bNoParentItem );
		 if ( htiCur == NULL ) {
			 if ( bDownDir )
				 htiCur = m_TreeCtrl->GetRootItem( );
			 else
				 htiCur = treeCtrl_GetLastItem( m_TreeCtrl,  NULL );
		 }
	 }
	 return NULL;
}


 //
 // GetLastItem  - Gets last item in the branch
// Returns      - Last item
// hItem        - Node identifying the branch. NULL will 
//                return the last item in outine

__declspec(  dllexport  )  HTREEITEM treeCtrl_GetLastItem( void  *  pTreeCtrl,  HTREEITEM hItem )
{
	CTreeCtrl  *  m_TreeCtrl  =  (  CTreeCtrl  *  )pTreeCtrl;

        // Last child of the last child of the last child ...
        HTREEITEM htiNext;

        if( hItem == NULL ){
                // Get the last item at the top level
                htiNext = m_TreeCtrl->GetRootItem();
                while( htiNext ){
                        hItem = htiNext;
                        htiNext = m_TreeCtrl->GetNextSiblingItem( htiNext );
                }
        }

        while( m_TreeCtrl->ItemHasChildren( hItem ) ){
                htiNext = m_TreeCtrl->GetChildItem( hItem );
                while( htiNext ){
                        hItem = htiNext;
                        htiNext = m_TreeCtrl->GetNextSiblingItem( htiNext );
                }
        }

        return hItem;
}

 

// GetNextItem  - Get next item as if outline was completely expanded
// Returns      - The item immediately below the reference item
// hItem        - The reference item
__declspec(  dllexport  )  HTREEITEM treeCtrl_GetNextItem( void  *  pTreeCtrl,  HTREEITEM hItem,  BOOL  bNoParentItem )
{
	CTreeCtrl  *  m_TreeCtrl  =  (  CTreeCtrl  *  )pTreeCtrl;

        HTREEITEM       hti;

        if( m_TreeCtrl->ItemHasChildren( hItem ) )
                return m_TreeCtrl->GetChildItem( hItem );           // return first child
        else  {

				//
				if  (  bNoParentItem  )  {  //  2018/06/28
					hti = m_TreeCtrl->GetNextSiblingItem( hItem );
					return  hti;
				}

                // return next sibling item
                // Go up the tree to find a parent's sibling if needed.
                while( (hti = m_TreeCtrl->GetNextSiblingItem( hItem )) == NULL ){
                        if( (hItem = m_TreeCtrl->GetParentItem( hItem ) ) == NULL )
                                return NULL;
                }
        }
        return hti;
}



// GetNextItem  - Get previous item as if outline was completely expanded
// Returns              - The item immediately above the reference item
// hItem                - The reference item
__declspec(  dllexport  )  HTREEITEM treeCtrl_GetPrevItem( void  *  pTreeCtrl,  HTREEITEM hItem,  BOOL  bNoParentItem )
{
	CTreeCtrl  *  m_TreeCtrl  =  (  CTreeCtrl  *  )pTreeCtrl;

        HTREEITEM       hti;

        hti = m_TreeCtrl->GetPrevSiblingItem(hItem);
        if( hti == NULL )  {
				//  2018/06/28
				if  (  bNoParentItem  )  return  NULL;
				//
                hti = m_TreeCtrl->GetParentItem(hItem);
				}
        else
                hti = treeCtrl_GetLastItem(pTreeCtrl,  hti);
        return hti;
}



//
__declspec(  dllexport  )  int  treeCtrl_DelAllChildOfItem(void  *  pTreeCtrl,  HTREEITEM hItem)
{
	CTreeCtrl  & m_Tree  =  *(  CTreeCtrl  *  )pTreeCtrl;

	BOOL bRet=FALSE;
	HTREEITEM hChildItem=NULL;
	while (TRUE)
	{
		bRet= m_Tree.ItemHasChildren(hItem);
		if (!bRet)//没有孩子
		{
			break;
		} 
		else
		{
			hChildItem=m_Tree.GetChildItem(hItem);
			m_Tree.DeleteItem(hChildItem);
		}
	}

	return  0;
 
}


