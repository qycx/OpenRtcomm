
#ifndef __QYHOTKEYS_H__
#define __QYHOTKEYS_H__	/* { */


#define	QY_HOTKEY_ENABLED			0x80000000
#define QY_HOTKEY_ALTMODIFIER		0x08000000
#define QY_HOTKEY_CTRLMODIFIER		0x04000000
#define QY_HOTKEY_EXTMODIFIER		0x02000000
#define QY_HOTKEY_SHIFTMODIFIER		0x01000000

typedef struct __qyHotKeys {
	unsigned int hotkeyPurgePassphraseCache;
	unsigned int hotkeyEncrypt;
	unsigned int hotkeyDecrypt;	
	unsigned int hotkeySign;

} QY_HOTKEYS;

static const QY_HOTKEYS sDefaultHotKeys = 
				{
					QY_HOTKEY_CTRLMODIFIER|VK_F12,
					QY_HOTKEY_CTRLMODIFIER|QY_HOTKEY_SHIFTMODIFIER|'E',
					QY_HOTKEY_CTRLMODIFIER|QY_HOTKEY_SHIFTMODIFIER|'D',
					0x00
				};


#endif /* } */

