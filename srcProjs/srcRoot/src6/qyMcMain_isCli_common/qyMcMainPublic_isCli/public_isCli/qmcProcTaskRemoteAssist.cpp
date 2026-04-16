

#include	"stdafx.h"
#include	<stdio.h>
#include	<stddef.h>
#include	<time.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture_isCli.h"
#include	"qmcAcm.h"
#include	"qyVk.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qmcDmoPublic.h"
#include	"tmpCeLib.h"
#include	"qmcCommFunc_isCli.h"




#ifdef  __SUPPORT_remoteAssist__

/*
 QY_DMITEM  CONST_recv_keyTable[] = {

  // TTY functions

  { VK_BACK, 0 },
  { VK_TAB, 0 },
  { VK_CLEAR, 0 },
  { VK_RETURN, 0 },

  { VK_PAUSE, 0 },
  { VK_ESCAPE, 0 },
  { VK_DELETE,	(  TCHAR  *  )1 },

  // Japanese stuff - almost certainly wrong...
  { VK_KANJI, 0 },
  { VK_KANA, 0 },

  // Cursor control & motion

  { VK_HOME,	(  TCHAR  *  )1 },
  { VK_LEFT,	(  TCHAR  *  )1 },
  { VK_UP,		(  TCHAR  *  )1 },
  { VK_RIGHT,	(  TCHAR  *  )1 },
  { VK_DOWN, (  TCHAR  *  )1 },
  { VK_PRIOR, (  TCHAR  *  )1 },
  { VK_NEXT, (  TCHAR  *  )1 },
  { VK_END, (  TCHAR  *  )1 },

  // Misc functions

  { VK_SELECT, 0 },
  { VK_SNAPSHOT, 0 },
  { VK_EXECUTE, 0 },
  { VK_INSERT, (  TCHAR  *  )1 },
  { VK_HELP, 0 },
  { VK_CANCEL, (  TCHAR  *  )1 },

  // Keypad Functions, keypad numbers

  { VK_SPACE, 0 },
  { VK_TAB, 0 },
  { VK_RETURN, (  TCHAR  *  )1 },
  { VK_F1, 0 },
  { VK_F2, 0 },
  { VK_F3, 0 },
  { VK_F4, 0 },
  { VK_HOME, 0 },
  { VK_LEFT, 0 },
  { VK_UP, 0 },
  { VK_RIGHT, 0 },
  { VK_DOWN, 0 },
  { VK_END, 0 },
  { VK_PRIOR, 0 },
  { VK_NEXT, 0 },
  { VK_CLEAR, 0 },
  { VK_INSERT, 0 },
  { VK_DELETE, 0 },
  // XXX XK_KP_Equal should map in the same way as ascii '='
  { VK_MULTIPLY, 0 },
  { VK_ADD, 0 },
  { VK_SEPARATOR, 0 },
  { VK_SUBTRACT, 0 },
  { VK_DECIMAL, 0 },
  { VK_DIVIDE, (  TCHAR  *  )1 },

  { VK_NUMPAD0, 0 },
  { VK_NUMPAD1, 0 },
  { VK_NUMPAD2, 0 },
  { VK_NUMPAD3, 0 },
  { VK_NUMPAD4, 0 },
  { VK_NUMPAD5, 0 },
  { VK_NUMPAD6, 0 },
  { VK_NUMPAD7, 0 },
  { VK_NUMPAD8, 0 },
  { VK_NUMPAD9, 0 },

  // Auxilliary Functions

  { VK_F1, 0 },
  { VK_F2, 0 },
  { VK_F3, 0 },
  { VK_F4, 0 },
  { VK_F5, 0 },
  { VK_F6, 0 },
  { VK_F7, 0 },
  { VK_F8, 0 },
  { VK_F9, 0 },
  { VK_F10, 0 },
  { VK_F11, 0 },
  { VK_F12, 0 },
  { VK_F13, 0 },
  { VK_F14, 0 },
  { VK_F15, 0 },
  { VK_F16, 0 },
  { VK_F17, 0 },
  { VK_F18, 0 },
  { VK_F19, 0 },
  { VK_F20, 0 },
  { VK_F21, 0 },
  { VK_F22, 0 },
  { VK_F23, 0 },
  { VK_F24, 0 },

    // Modifiers
    
  { VK_SHIFT, 0 },
  { VK_RSHIFT, 0 },
  { VK_CONTROL, 0 },
  { VK_CONTROL, (  TCHAR  *  )1 },
  { VK_MENU, 0 },
  { VK_RMENU, (  TCHAR  *  )1 },
  {	-1,			},
};
*/


 void  doKeyboardEvent(  BYTE  vkCode,  DWORD  flags  ) 
{
	keybd_event(vkCode, MapVirtualKey(vkCode, 0), flags, 0);
}


class KeyStateModifier {
public:
  KeyStateModifier(int vkCode_, int flags_=0)
    : vkCode(vkCode_), flags(flags_), pressed(false), released(false)
  {}
  void press() {
    if (!(GetAsyncKeyState(vkCode) & 0x8000)) {
      doKeyboardEvent(vkCode, flags);
      //  vnclog.Print(LL_INTINFO, "fake %d down\n", vkCode);
      pressed = true;
    }
  }
  void release() {
    if (GetAsyncKeyState(vkCode) & 0x8000) {
      doKeyboardEvent(vkCode, flags | KEYEVENTF_KEYUP);
      //  vnclog.Print(LL_INTINFO, "fake %d up\n", vkCode);
      released = true;
    }
  }
  ~KeyStateModifier() {
    if (pressed) {
      doKeyboardEvent(vkCode, flags | KEYEVENTF_KEYUP);
      //  vnclog.Print(LL_INTINFO, "fake %d up\n", vkCode);
    } else if (released) {
      doKeyboardEvent(vkCode, flags);
      //  vnclog.Print(LL_INTINFO, "fake %d down\n", vkCode);
    }
  }
  int vkCode;
  int flags;
  bool pressed;
  bool released;
};




 void  keyEvent(  unsigned  int  keysym, unsigned  char  ucbDown  )
{
    if ((keysym >= 32 && keysym <= 126) ||
        (keysym >= 160 && keysym <= 255))
    {
		// ordinary Latin-1 character
		SHORT s = VkKeyScan(keysym);
		if (s == -1) {
			//  vnclog.Print(LL_INTWARN, "ignoring unrecognised Latin-1 keysym %d\n",  keysym);
			return;
		}

		BYTE vkCode = LOBYTE(s);

		KeyStateModifier ctrl(VK_CONTROL);
		KeyStateModifier alt(VK_MENU);
		KeyStateModifier shift(VK_SHIFT);
		KeyStateModifier lshift(VK_LSHIFT);
		KeyStateModifier rshift(VK_RSHIFT);

		if  (  ucbDown  )  {
			BYTE modifierState = HIBYTE(s);
			if (modifierState & 2) ctrl.press();
			if (modifierState & 4) alt.press();
			if (modifierState & 1) {
				shift.press(); 
				} 
			else {
	             lshift.release();
				 rshift.release();
			}
		}

		doKeyboardEvent(vkCode, ucbDown ? 0 : KEYEVENTF_KEYUP);

		} 
	else {
   		 // see if it's a recognised keyboard key, otherwise ignore it
		 QY_DMITEM	*  pItem;

		 for  (  pItem  =  CONST_qyKeyTable;  pItem->type  !=  -1;  pItem  ++  )  {
			  if  (  (  unsigned  int  )pItem->des  ==  keysym  )  break;
		 }
		 if  (  pItem->type  ==  -1  )  {
        	 //  vnclog.Print(LL_INTWARN, "ignoring unknown keysym %d\n",keysym);
			 return;
		 }
		 BYTE	vkCode	=	(  BYTE  )pItem->type;
		 DWORD	flags	=	0;

		 if  (  pItem->pData  )  flags |= KEYEVENTF_EXTENDEDKEY;
		 if  (  !ucbDown  )  flags |= KEYEVENTF_KEYUP;
		 //  vnclog.Print(LL_INTINFO,  "keyboard key: keysym %d(0x%x) vkCode 0x%x ext %d down %d\n",  keysym, keysym, vkCode, extendedMap[keysym], down);

		 doKeyboardEvent(vkCode, flags);
    }

	return;
}


 void  setShiftState(BYTE key, BOOL down)
{
	BOOL keystate = (GetAsyncKeyState(key) & 0x8000) != 0;

	// This routine sets the specified key to the desired value (up or down)
	if ((keystate && down) || ((!keystate) && (!down)))  return;

	// Now send a key event to set the key to the new value
	doKeyboardEvent(key, down ? 0 : KEYEVENTF_KEYUP);
	keystate = (GetAsyncKeyState(key) & 0x8000) != 0;

}


 //
 __declspec(  dllexport  )  void  clearShiftKeys()
{
	//  if (  IsWinNT())
	{
		// On NT, clear both sets of keys

		// LEFT
		setShiftState(VK_LSHIFT, FALSE);
		setShiftState(VK_LCONTROL, FALSE);
		setShiftState(VK_LMENU, FALSE);

		// RIGHT
		setShiftState(VK_RSHIFT, FALSE);
		setShiftState(VK_RCONTROL, FALSE);
		setShiftState(VK_RMENU, FALSE);
	}
	//  else
	{
		// Otherwise, we can't distinguish the keys anyway...

		// Clear the shift key states
		setShiftState(VK_SHIFT, FALSE);
		setShiftState(VK_CONTROL, FALSE);
		setShiftState(VK_MENU, FALSE);
	}
}




 __declspec(  dllexport  )  int  procTaskRemoteAssist(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  REMOTE_ASSIST_REQ  *  pReq,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask,  int  index_mems_from  )
{
	int							iErr				=	-1;
	QY_MC					*	pQyMc				=	QY_GET_GBUF(  );
	MIS_CNT					*	pMisCnt				=	(  MIS_CNT  *  )pMsgTask->pMisCnt;
	if  (  !pMisCnt  )  return  -1;
	int							tmpiRet				=	0;
	//  QY_WMBUF_COMM				wmBuf;
	char						timeBuf[32]			=	"";
	TCHAR						tHintBuf[256]		=	_T(  ""  );
	//  int							i;
	QY_SHARED_OBJ			*	pSharedObj			=	getSharedObjByIndex(  pProcInfo,  pTask->iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	CAP_procInfo_bmpU		*	pCapProcInfo		=	getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  0  );
	if  (  !pCapProcInfo  )  return  -1;
	COMPRESS_VIDEO			*	pCompressVideo		=	&pCapProcInfo->common.compressVideo;
	if  (  !pCompressVideo  )  return  -1;
	
	if  (  !pAddr  ||  !pTask->remoteAssist.maxxScreen  ||  !pTask->remoteAssist.maxyScreen  )  return  -1;

	switch  (  pReq->u.usRaType  )  {
			case  CONST_usRaType_pointerEvent:  {
				  //  Work out the flags for this event
				  DWORD		flags	=	MOUSEEVENTF_ABSOLUTE;
          		  long		data	=	0;

				  if  (  pReq->u.pointerEvent.x  !=  pTask->remoteAssist.pointerEvent.x 
					  ||  pReq->u.pointerEvent.y  !=  pTask->remoteAssist.pointerEvent.y  )
				  {
                      flags  |=  MOUSEEVENTF_MOVE;
				  }				
				  if  (  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_button1Mask  )  !=  (  pTask->remoteAssist.pointerEvent.ucButtonMask  &  CONST_button1Mask  )  )  {
					  if  (  GetSystemMetrics(  SM_SWAPBUTTON  )  )  flags  |=  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_button1Mask  )  ?  MOUSEEVENTF_RIGHTDOWN  :  MOUSEEVENTF_RIGHTUP;
					  else  flags  |=  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_button1Mask  )  ?  MOUSEEVENTF_LEFTDOWN  :  MOUSEEVENTF_LEFTUP;					
				  }				  
				  if  (  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_button2Mask  )  !=  (  pTask->remoteAssist.pointerEvent.ucButtonMask  &  CONST_button2Mask  )  )  {
					  flags  |=  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_button2Mask  )  ?  MOUSEEVENTF_MIDDLEDOWN  :  MOUSEEVENTF_MIDDLEUP;
				  }
				  if  (  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_button3Mask  )  !=  (  pTask->remoteAssist.pointerEvent.ucButtonMask  &  CONST_button3Mask  )  )  {
                      if  (  GetSystemMetrics(  SM_SWAPBUTTON  )  )  flags  |=  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_button3Mask  )  ?  MOUSEEVENTF_LEFTDOWN  :  MOUSEEVENTF_LEFTUP;
					  else  flags  |=  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_button3Mask  )  ?  MOUSEEVENTF_RIGHTDOWN  :  MOUSEEVENTF_RIGHTUP;
				  }

				  // Mouse wheel support
				  if  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_wheelUpMask  )  {
					  flags  |=  MOUSEEVENTF_WHEEL;
					  data  =  WHEEL_DELTA;
          		  }
          		  if  (  pReq->u.pointerEvent.ucButtonMask  &  CONST_wheelDownMask  )  {
					  flags  |=  MOUSEEVENTF_WHEEL;
            		  data  =  -WHEEL_DELTA;
          		  }

				  // Generate coordinate values
				  unsigned  long  x  =  (  (  pReq->u.pointerEvent.x  +  pCompressVideo->left  )  *  65535  )  /  pTask->remoteAssist.maxxScreen;
				  unsigned  long  y  =  (  (  pReq->u.pointerEvent.y  +  pCompressVideo->top  )  *  65535  )  /  pTask->remoteAssist.maxyScreen;

				  // Do the pointer event
				  ::mouse_event(  flags, (  DWORD  )x, (  DWORD  )y, data, 0  );

				  // Save the old position
				  pTask->remoteAssist.pointerEvent  =  pReq->u.pointerEvent;
				
				  //  保存此事件标识，以方便在发送图像时发送回去
#if  0  //2016/12/26
				  if  (  pReq->u.pointerEvent.uiEventId  )  {	
					  pCompressVideo->uiEventId_lastRecvd  =  pReq->u.pointerEvent.uiEventId;
				  }
#endif

				  }
				  break;
			case  CONST_usRaType_keyEvent:  {
				  /*
				  DWORD		flags	=	0;
				  SHORT		s		=	VkKeyScan(  pReq->u.keyEvent.key  );
				  if  (  s  ==  -1  ) {
					  traceLogA(  "VkKeyScan failed."  );  goto  errLabel;
				  }
				  BYTE vkCode;	vkCode  =  LOBYTE(  s  );

				  if  (  pReq->u.keyEvent.ucbDown  )  flags  |=  KEYEVENTF_KEYUP;

				  keybd_event(  vkCode,  MapVirtualKey(  vkCode,  0  ),  flags,  0  );
				  */
				  keyEvent(  pReq->u.keyEvent.key,  pReq->u.keyEvent.ucbDown  );

				  }				  
				  break;
			default:
					break;
	}
											 

	iErr  =  0;  

//  errLabel:

	if  (  iErr  ||  tHintBuf[0]  )  qyShowInfo1(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tn %d, procTaskRemoteAssist %s. %s"  ),  pMsgTask->uiTranNo,  (  iErr  ?  _T(  "failed."  )  :  _T(  "OK"  )  ),  tHintBuf  );
	
	return  iErr;

}

#else

__declspec(  dllexport  )  int  procTaskRemoteAssist(  MC_VAR_isCli  *  pProcInfo,  MSGR_ADDR  *  pAddr,  int  iTaskId,  MIS_MSG_TASK  *  pMsgTask,  REMOTE_ASSIST_REQ  *  pReq,  AV_TRAN_INFO  *  pTranInfo,  PROC_TASK_AV  *  pTask,  int  index_mems_from  )
{
#ifdef  __DEBUG__
		traceLog(  _T(  "procTaskRemoteAssist not supported."  )  );
#endif
	  return  -1;
}

#endif


