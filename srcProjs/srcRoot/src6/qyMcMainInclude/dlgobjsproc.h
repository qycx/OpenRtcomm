
#ifndef  __DLGOBJSPROC_H__
#define  __DLGOBJSPROC_H__	//  {

typedef  struct  __param_layout_dlgObjs_t				{
}		 PARAM_layout_dlgObjs;

typedef  struct  __dlgObjsVar_t							{
	 			 HWND									m_hParent;			//  2016/08/09
				 //
				 void							*		pMisCnt;
				 unsigned short							usItemCount;

				 DLG_guiData_objs						guiData;


				 PARAM_layout_dlgObjs					layoutParam;

				 //
				 int									nItems;

				 //
#if  0
				 struct									{
					 union								{

					 }									u;
				 }										dataHead;
#endif

				 //
				 void							*		pData_items;				//  to store display info
				 unsigned  int							uiSize_pData_items;
				 //
				 int									iType_pData;				//  2014/05/14
				 void							*		pData;						//  to store object data info
				 unsigned  int							uiSize_pData;				



}		DLG_objs_var;

//
#define		CONST_iType_pData_null						0
#define		CONST_iType_pData_dynBmps					2


#endif  //  }



