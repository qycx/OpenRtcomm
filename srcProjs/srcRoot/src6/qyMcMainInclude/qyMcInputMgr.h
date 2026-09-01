

#ifndef  __QYMCINPUTMGR_H__
#define  __QYMCINPUTMGR_H__	//  {

//  这个是为了其他程序和本软件的交互的接口。用一个窗口来接受输入参数。
//  对了，要给与查询客户端是谁的方便。否则，在2个客户端一起运行的情况下，不知道该找哪个进程了
//  通常的客户端要先把bInputPermitted给设成false.窗口里，就可以用这个false把输入给拒绝了。
//  短信服务器缺省可以是 false.管理员可以设成 true.


typedef  struct  __qmInputMgr_t			{
				 HWND					hWnd;
}		 QM_INPUT_MGR;


 int  initInputMgr(  HINSTANCE  g_hInst,  QM_INPUT_MGR  *  pInputMgr  );
 void  exitInputMgr(  QM_INPUT_MGR  *  pInputMgr  );




#endif  //  }



