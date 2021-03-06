using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;

partial class Consts
{
	public const int INVALID_SOCKET = (~0);

#if DEBUG
	public const int DEFAULT_QY_ACCEPT_TIMEOUT = 5000;	//	10000;
	public const int  DEFAULT_QY_CONNECT_TIMEOUT	=	4000;
	public const int DEFAULT_QY_WRITE_TIMEOUT = 5000;   //100000;
	public const int DEFAULT_QY_READ_TIMEOUT = 5000;	//100000;
	public const int  DEFAULT_qyTo_select		=		3000;
#else
	public const int DEFAULT_QY_ACCEPT_TIMEOUT = 8000;  //  5000
	public const int DEFAULT_QY_CONNECT_TIMEOUT = 5000; //  2000
	public const int DEFAULT_QY_WRITE_TIMEOUT = 5000;   //  2000
	public const int DEFAULT_QY_READ_TIMEOUT = 20000;   //  10000
	public const int DEFAULT_qyTo_select = 5000;
#endif

}


namespace qy
{



	public struct QY_SOCK
	{
			//public int sockFd_unused;      //	第一个成员是asrSock的，应予以保持，包括成员与在结构中的位置	
			//SOCKET sockFd;      //	2014/02/07. 第一个成员是asrSock的，应予以保持，包括成员与在结构中的位置	
			public Socket	socket;
	};


		public struct SOCK_TIMEOUT
		{
			public int iAccept;
			public int iConnect;
			public int iRead;
			public int iWrite;
			public int iSelect;        //  仅在某些试探状态中使用，读写数据时使用iRead, iWrite
		}
		;

	partial class qyFuncs
	{

		public static bool isSocketInvalid(ref QY_SOCK pSock)
		{
			//return ((s) == Consts.INVALID_SOCKET); //  2013/02/08
			if (pSock.socket == null) return true;
			return false;
		}


		public static unsafe void qyDisconnect(ref QY_SOCK pSock)
		{


			//  if  (  pAsrSock->sockFd  <  0  )  return;
			if (isSocketInvalid(ref pSock)) return;  //  2014/02/08

			//closesocket(pAsrSock->sockFd);
			//pAsrSock.sockFd = -1;

			try
			{
				pSock.socket.Shutdown(SocketShutdown.Both);
				pSock.socket.Close();
			}
			catch(Exception e)
            {
				Console.WriteLine(e.ToString());
            }

			//
			pSock.socket = null;

			return;
		}


		public static unsafe int qyRecv(ref QY_SOCK pSock, byte* buf, int* pLen, int timeoutVal)
		{
			int iErr = -1;
			int nRead = -1;

			if (0==*pLen) return -1;

			/*
			
			TIMEVAL tv;
			int nRet;
			tv.tv_sec = timeoutVal / 1000;
			tv.tv_usec = (timeoutVal % 1000) * 1000;
			fd_set rfds;
			FD_ZERO(&rfds);
			FD_SET(pAsrSock->sockFd, &rfds);
			nRet = select(1, &rfds, NULL, NULL, &tv);
			if (nRet == SOCKET_ERROR) goto errLabel;
			if (nRet == 0)
			{
				iErr = 1;
				goto errLabel;
			}

			nRead = recv(pAsrSock->sockFd, buf, *pLen, 0);
			*/
			byte[] a_buf = new byte[*pLen];
			try
			{
				nRead = pSock.socket.Receive(a_buf);
			}
			catch(Exception e)
            {
				Console.WriteLine(e.ToString());
				goto errLabel;
            }
			if (nRead <= 0) goto errLabel;
			Marshal.Copy(a_buf, 0, (IntPtr)buf, nRead);

			*pLen = nRead;
			iErr = 0;

		errLabel:

			return iErr;

		}

		// 持续接收内容，将内容接收完全。
		public static unsafe int qyRecvEx(ref QY_SOCK pAsrSock, byte* buf, int len, int timeoutVal)
		{
			int nRead = 0;

			if (len <= 0) return -1;

			do
			{
				nRead = len;
				if (qyRecv(ref pAsrSock, buf, &nRead, timeoutVal)!=0) return -1;
				len -= nRead;
				buf += nRead;

			} while (len > 0);

			return 0;

		}

		public static unsafe int qySend(ref QY_SOCK pSock, byte* buf, int len, int timeoutVal)
		{
			int iErr = -1;
			int nSent = -1;

			if (0==len) return -1;

			/*
			int ret;
			TIMEVAL tm;
			fd_set wfds;
			FD_ZERO(&wfds);
			FD_SET(pAsrSock->sockFd, &wfds);
			tm.tv_sec = timeoutVal / 1000;
			tm.tv_usec = (timeoutVal % 1000) * 1000;
			if ((ret = select(0, NULL, &wfds, NULL, &tm)) <= 0)
			{
				qyDisplayLastError("asrSend: select failed"); goto errLabel;
			}

			nSent = send(pAsrSock->sockFd, buf, len, 0);
			if (nSent != len)
			{
				qyDisplayLastError("asrSend: send failed"); goto errLabel;
			}
			*/
			byte[] a_buf = new byte[len];
			Marshal.Copy((IntPtr)buf, a_buf, 0, len);
			try
			{
				nSent = pSock.socket.Send(a_buf);
			}
			catch(Exception e)
            {
				Console.WriteLine(e.ToString());
				goto errLabel;
            }
			if (nSent != len) goto errLabel;

			iErr = 0;

		errLabel:

			return iErr;


		}


	public static int qyConnect(string ipaddr, int port, ref SOCK_TIMEOUT to, ref QY_SOCK pSock)
	{

			int iErr = -1;
			int tmp;



			/*
	 struct sockaddr_in server;
		uint arg;

*/	
	 //  if ( pAsrSock->sockFd >= 0 ) return -1;
	 if  (  !isSocketInvalid(ref pSock  )  )  return  -1;   //  2014/02/08


			/*
			pAsrSock->sockFd = socket(AF_INET, SOCK_STREAM, 0 );
			//  if ( pAsrSock->sockFd < 0 ) goto errLabel;
			if  (isSocketInvalid(pAsrSock->sockFd  )  )  goto  errLabel;	//  2014/02/08

			// traceLog2( "asrConnect( ): now call setsockopt( )", "" );

			BOOL sopt;
			   sopt=TRUE;
			setsockopt(pAsrSock->sockFd, IPPROTO_TCP, TCP_NODELAY, (char*)&sopt,sizeof(BOOL));
			   sopt=TRUE;
			setsockopt(pAsrSock->sockFd, SOL_SOCKET, SO_DONTLINGER, (char*)&sopt,sizeof(BOOL));


			   arg = 1;
			tmp = ioctlsocket(pAsrSock->sockFd, FIONBIO, &arg );
			if (tmp ) goto errLabel;


			server.sin_family =	AF_INET; 
			server.sin_addr.S_un.S_addr = inet_addr(ipaddr );
			   server.sin_port = htons((u_short ) port);

			   tmp = connect(pAsrSock->sockFd, ( struct sockaddr * )&server, sizeof(server ) );

			if (tmp != 0 ) {
				tmp = WSAGetLastError();
				if (tmp != WSAEWOULDBLOCK ) goto errLabel;

				int ret;
			   TIMEVAL tm;
			   fd_set wfds;

			   FD_ZERO(&wfds);
			   FD_SET(pAsrSock->sockFd, &wfds );
			   tm.tv_sec = timeoutVal / 1000;
				tm.tv_usec = (timeoutVal % 1000 ) * 1000;
				if ((ret = select( 0, NULL, &wfds, NULL, &tm ) ) <= 0 ) 
					goto errLabel;

			}

		   arg = 0;
			tmp = ioctlsocket(pAsrSock->sockFd, FIONBIO, &arg );
			if (tmp ) goto errLabel;
				   */

			try
			{
				//
				pSock.socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
				if (pSock.socket == null) goto errLabel;

				//


#if true
				//
				IAsyncResult result = pSock.socket.BeginConnect(ipaddr, port, null, null);

				bool success = result.AsyncWaitHandle.WaitOne(to.iConnect, true);

				if (pSock.socket.Connected)
				{
					pSock.socket.EndConnect(result);
				}
				else
				{
					// NOTE, MUST CLOSE THE SOCKET
					goto errLabel;

				}
#else
				pSock.socket.Connect(ipaddr, port);
#endif

				//
				pSock.socket.SendTimeout = to.iWrite;
				pSock.socket.ReceiveTimeout = to.iRead;
			}
			catch (Exception e )
            {
				Console.WriteLine("qyConnect failed, " + e.ToString());
				goto errLabel;
            }


			iErr = 0;

errLabel:

	 if (0!=iErr ) {
		//  if ( pAsrSock->sockFd >= 0 ) 
		 if  (  !isSocketInvalid(ref pSock  )  )
		{
			//closesocket(pAsrSock->sockFd ); pAsrSock->sockFd = -1;
					pSock.socket.Close();
					pSock.socket = null;

		}
	 }

			return iErr;

}

		public static unsafe int setSockTimeout(SOCK_TIMEOUT* p)
		{
			p->iAccept = Consts.DEFAULT_QY_ACCEPT_TIMEOUT;
			p->iConnect = Consts.DEFAULT_QY_CONNECT_TIMEOUT;
			p->iRead = Consts.DEFAULT_QY_READ_TIMEOUT;
			p->iWrite = Consts.DEFAULT_QY_WRITE_TIMEOUT;
			p->iSelect = Consts.DEFAULT_qyTo_select;

			return 0;
		}


	}
}
