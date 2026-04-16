

#ifndef  __QYMCMAINCOMMONOBJ_H__
#define  __QYMCMAINCOMMONOBJ_H__	/* { */


class  CQyMcObj : public  CQyObj  {

public:
	CQyMcObj(  );
	CQyMcObj(  unsigned int  n  );
	~CQyMcObj(  );

	struct		{
			int								m_objType;
			unsigned int					m_n;
			QY_BUF			*				m_pBufs;
	}										var;

	int										setQyBufData( void *data, unsigned int n, unsigned int index );
	void					*				getQyBufData( unsigned int index );

	QY_MC_SITE				*				getMcSite(  );
	QY_MC_WEB				*				getMcWeb(  );
	QY_MC_QUERY				*				getMcQuery(  );	


};


typedef  struct  __qyMcDocStruct_t				{

				 int							iDocType;
	
				 TCHAR							dsnName[64  +  1];					//  2006/12/31

				 TCHAR							preDocName[CONST_qyMaxPreDocNameLen + 1];
				 TCHAR							docName[CONST_qyMaxDocNameLen  +  1];
				 TCHAR							postDocName[CONST_qyMaxPostDocNameLen + 1];

				 CQyMcObj					*	m_pMcObj;

				 union							{
					 QY_MC_QUERY				query;
					 struct						{
						 QY_MCROOTTREE_SEL		tree;
						 QY_MCROOTLIST_SEL		list;
					 }							treeList;	//  树列表结构
					 QY_MCVIEW_SEL				mcView;
				 }								u;
				 
				 BAR_CFG					*	pBarCfg;				 

}		 QY_MC_DOCSTRUCT;


#endif  /* }  */

