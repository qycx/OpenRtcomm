
#ifndef  __remoteAssistPublic_h__
#define  __remoteAssistPublic_h__	//  {


#define		CONST_maxKeysPerKey			4
#define		CONST_voidKeyCode			-1

// keycodes contains the keysyms terminated by an VoidKeyCode.
// The releaseModifiers is a set of ORed flags indicating whether 
// particular modifier-up messages should be sent before the keys 
// and modifier-down after.

#define		CONST_KEYMAP_LCONTROL		0x0001
#define		CONST_KEYMAP_RCONTROL		0x0002
#define		CONST_KEYMAP_LALT			0x0004
#define		CONST_KEYMAP_RALT			0x0008

typedef  struct  __key2Send_t			{
				 unsigned  int			keycodes[CONST_maxKeysPerKey];
				 unsigned  int			releaseModifiers;
}		 KEY_2_SEND;

//
 KEY_2_SEND  vk2Send(  UINT  virtkey,  DWORD  keyData  );


#endif  //  }


