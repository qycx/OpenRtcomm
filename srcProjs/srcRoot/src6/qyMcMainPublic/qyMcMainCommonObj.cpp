

#include	"stdafx.h"
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyMcMainCommonObj.h"


CQyMcObj::CQyMcObj(  )
{
	qyDebugHint(  _T(  "CQyMcObj(  )." )  );
	memset(  &this->var,  0,  sizeof(  this->var  )  );
}

CQyMcObj::CQyMcObj(  unsigned int  n  )
{
	memset(  &this->var,  0,  sizeof(  this->var  )  );
	
	if  (  n  )  {
		this->var.m_pBufs  =  (  QY_BUF  *  )mymalloc(  sizeof(  QY_BUF  )  *  n  ); 
		if  (  !this->var.m_pBufs  )  throw  QY_EXCEPTION_MALLOCFAILED;
		else    {
			memset(  this->var.m_pBufs,  0,  sizeof(  QY_BUF  )  *  n  );
			this->var.m_n  =  n;
		}
	}
}

CQyMcObj::~CQyMcObj(  )
{
	unsigned int  i	=	0;
	for  (	i  =  0;  i  <  this->var.m_n;  i  ++  )  {
		resetQyBuf(  &this->var.m_pBufs[i]  );		
	}
	free(  this->var.m_pBufs  );

}

 int  CQyMcObj::setQyBufData(  void *  data,  unsigned int  n,  unsigned int  index  )
{
	 if  (  index >= this->var.m_n  )	return -1;
	 return ::setQyBufData( data, n, &this->var.m_pBufs[index] );
}

 void * CQyMcObj::getQyBufData(  unsigned int index  )
{
	 if  (  index >=  this->var.m_n  )  return  NULL;
	 return  this->var.m_pBufs[index].data;
}


QY_MC_WEB	*	CQyMcObj::getMcWeb(  )
{
	return	(  QY_MC_WEB  *  )this->var.m_pBufs[0].data;
}

QY_MC_SITE	*	CQyMcObj::getMcSite(  )
{
	return  (  QY_MC_SITE  *  )this->var.m_pBufs[0].data;
}

QY_MC_QUERY *	CQyMcObj::getMcQuery(  )
{
	return  (  QY_MC_QUERY  *  )this->var.m_pBufs[0].data;
}


