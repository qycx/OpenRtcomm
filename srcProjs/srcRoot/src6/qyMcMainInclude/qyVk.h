
#ifndef  __QYVK_H__
#define  __QYVK_H__		//  {


#define		CONST_qK_CANCEL         0xFF03

#define		CONST_qK_BACK           0xFF08
#define		CONST_qK_TAB            0xFF09

#define		CONST_qK_CLEAR          0xFF0C
#define		CONST_qK_RETURN         0xFF0D

#define		CONST_qK_SHIFT          0xFF10
#define		CONST_qK_CONTROL        0xFF11
#define		CONST_qK_MENU           0xFF12
#define		CONST_qK_PAUSE          0xFF13
#define		CONST_qK_CAPITAL        0xFF14

#define		CONST_qK_ESCAPE         0xFF1B

#define		CONST_qK_SPACE          0xFF20
#define		CONST_qK_PRIOR          0xFF21
#define		CONST_qK_NEXT           0xFF22
#define		CONST_qK_END            0xFF23
#define		CONST_qK_HOME           0xFF24
#define		CONST_qK_LEFT           0xFF25
#define		CONST_qK_UP             0xFF26
#define		CONST_qK_RIGHT          0xFF27
#define		CONST_qK_DOWN           0xFF28
#define		CONST_qK_SELECT         0xFF29
#define		CONST_qK_PRINT          0xFF2A
#define		CONST_qK_EXECUTE        0xFF2B
#define		CONST_qK_SNAPSHOT       0xFF2C
#define		CONST_qK_INSERT         0xFF2D
#define		CONST_qK_DELETE         0xFF2E
#define		CONST_qK_HELP           0xFF2F

#define		CONST_qK_NUMPAD0        0xFF60
#define		CONST_qK_NUMPAD1        0xFF61
#define		CONST_qK_NUMPAD2        0xFF62
#define		CONST_qK_NUMPAD3        0xFF63
#define		CONST_qK_NUMPAD4        0xFF64
#define		CONST_qK_NUMPAD5        0xFF65
#define		CONST_qK_NUMPAD6        0xFF66
#define		CONST_qK_NUMPAD7        0xFF67
#define		CONST_qK_NUMPAD8        0xFF68
#define		CONST_qK_NUMPAD9        0xFF69
#define		CONST_qK_MULTIPLY       0xFF6A
#define		CONST_qK_ADD            0xFF6B
#define		CONST_qK_SEPARATOR      0xFF6C
#define		CONST_qK_SUBTRACT       0xFF6D
#define		CONST_qK_DECIMAL        0xFF6E
#define		CONST_qK_DIVIDE         0xFF6F

#define		CONST_qK_F1             0xFF70
#define		CONST_qK_F2             0xFF71
#define		CONST_qK_F3             0xFF72
#define		CONST_qK_F4             0xFF73
#define		CONST_qK_F5             0xFF74
#define		CONST_qK_F6             0xFF75
#define		CONST_qK_F7             0xFF76
#define		CONST_qK_F8             0xFF77
#define		CONST_qK_F9             0xFF78
#define		CONST_qK_F10            0xFF79
#define		CONST_qK_F11            0xFF7A
#define		CONST_qK_F12            0xFF7B
#define		CONST_qK_F13            0xFF7C
#define		CONST_qK_F14            0xFF7D
#define		CONST_qK_F15            0xFF7E
#define		CONST_qK_F16            0xFF7F
#define		CONST_qK_F17            0xFF80
#define		CONST_qK_F18            0xFF81
#define		CONST_qK_F19            0xFF82
#define		CONST_qK_F20            0xFF83
#define		CONST_qK_F21            0xFF84
#define		CONST_qK_F22            0xFF85
#define		CONST_qK_F23            0xFF86
#define		CONST_qK_F24            0xFF87

#define		CONST_qK_NUMLOCK        0xFF90
#define		CONST_qK_SCROLL         0xFF91


#define		CONST_qK_LSHIFT         0xFFA0
#define		CONST_qK_RSHIFT         0xFFA1
#define		CONST_qK_LCONTROL       0xFFA2
#define		CONST_qK_RCONTROL       0xFFA3
#define		CONST_qK_LMENU          0xFFA4
#define		CONST_qK_RMENU          0xFFA5


extern  QY_DMITEM	CONST_qyKeyTable[];

__declspec(  dllexport  )  void  clearShiftKeys();


#endif  //  }