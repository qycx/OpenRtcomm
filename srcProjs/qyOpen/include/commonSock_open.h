
#ifndef  __commonSock_open_h__
#define  __commonSock_open_h__	//  {

//
typedef  struct  __sock_timeout_t  {
				 int				iAccept;
				 int				iConnect;
				 int				iRead;
				 int				iWrite;
				 int				iSelect;		//  仅在某些试探状态中使用，读写数据时使用iRead, iWrite
}		 SOCK_TIMEOUT;
//




//
#endif  //  }


