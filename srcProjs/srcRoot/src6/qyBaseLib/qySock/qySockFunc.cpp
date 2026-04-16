
#include	"qyPrecomp.h"
#include	<Winsock2.h>
#include	<windows.h>
#include	"qyCommon.h"


 extern  "C"  int  qyBufSend(  void  *  pQySockParam,  QY_BUF * pQyBuf, int  timeout  )
{
	 int	len	=	htonl(  pQyBuf->len  );

	 if  (  asrSend(  pQySockParam,  (  char  *  )&len,  sizeof(  len  ),  timeout  )  )	return  -1;
	 if  (  pQyBuf->len  )  { 
		 if  (  asrSend(  pQySockParam,  (  char  *  )pQyBuf->data,  pQyBuf->len,  timeout  )  )	 {
		 	 return  -1;
	 	 }
	 }
	 
	 return  0;

}

#if  0
 extern  "C"  int  qyBufRecv(  void  *  pQySockParam,  QY_BUF * pQyBuf,  int  timeout )
{
	 int		iErr  =  -1;
	 int		len;

	 if  (  asrRecvX(  pQySockParam,  (  char  *  )&len,  sizeof(  len  ),  timeout  )  )  return  -1;
	 len  =  ntohl(  len  );
	 
	 if  (  len  )  {
		 if  (  qyBufAllocData(  pQyBuf,  len  )  )	 return  -1;
	 }

	 if  (  asrRecvX(  pQySockParam,  (  char  *  )pQyBuf->data,  len,  timeout  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 qyBufFree(  pQyBuf  );
	 }

	 return  iErr;
	 
}
#endif


 
 extern  "C"  BOOL  bQyIpLocal(  unsigned  long  ulAddr  )
{
	BOOL				bRet	=	FALSE;
	char				ac[256];
	int					i		=	0;
	struct  hostent  *  phe		=	NULL;
    
	if  (  gethostname(  ac,  sizeof(  ac  )  )  ==  SOCKET_ERROR  )  {
        goto  errLabel;
    }
	
    phe  =  gethostbyname(  ac  );
    if  (  phe  ==  0  )  {
        goto  errLabel;
    }
    
    for  (  i  =  0;  phe->h_addr_list[i]  !=  0;  ++  i  )  {
         struct  in_addr  addr;
         
		 memcpy( &addr,  phe->h_addr_list[i],  sizeof(  struct  in_addr  )  );

		 if  (  addr.s_addr  ==  ulAddr  )  {
			 bRet  =  TRUE;	
			 goto  errLabel;
		 }

    }
    	
errLabel:

    return  bRet;

}


 int iidoit(int, char**)
{
    char ac[80];
    if  (  gethostname(ac, sizeof(ac))  ==  SOCKET_ERROR  )  {
        //  cerr << "Error " << WSAGetLastError() << " when getting local host name." << endl;
        return 1;
    }
    //  cout << "Host name is " << ac << "." << endl;

    struct hostent* phe = gethostbyname(ac);
    if  (  phe  ==  0  )  {
        //  cerr << "Yow!  Bad host lookup." << endl;
        return  1;
    }
    
    for  (  int i = 0; phe->h_addr_list[i] != 0; ++i) {
         struct in_addr addr;
         memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        //  cout << "Address " << i << ": " << inet_ntoa(addr) << endl;
    }
    
    return  0;

}


 