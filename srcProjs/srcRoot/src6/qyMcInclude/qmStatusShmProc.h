
#ifndef  __QMSTATUSSHMPROC_H__
#define  __QMSTATUSSHMPROC_H__	//  {

typedef  struct  __statusShm_is_t	{
				 int				iType;
				 TCHAR				tBuf[256];

}				 STATUS_SHM_is;


typedef  struct  __statusShm_netMc_t	{
				 int					iType;
}		 STATUS_SHM_netMc;
#endif

