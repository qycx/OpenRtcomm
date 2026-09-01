#include "skfapi_dll.h"
#include "gm3000_dll.h"

class CSKFAPI
{
public:
	CSKFAPI(bool jitSafeModule);

	~CSKFAPI();

	void    SetContName(char * szContName);

	void    SetPassword(char * szPassword);

public:
	ULONG   GM_Login();

	ULONG   GM_EnumDev();

	ULONG   GM_GetDevState();

	ULONG   GM_SetDevLable();

	ULONG   GM_GetDevInfo();

	ULONG   GM_DevAuth();

	ULONG   GM_ChangeDevAuthKey();

	ULONG   GM_VerifyPIN();

	ULONG   GM_GetPINInfo();

	ULONG   GM_ChangePIN();

	ULONG   GM_UnblockPIN();

	ULONG   GM_EnumApplication();

	ULONG   GM_CreatApplication();

	ULONG   GM_DeleteAppliction();

	ULONG   GM_OpenApplication();

	ULONG   GM_CloseApplication();

	ULONG   GM_CreatFile();

	ULONG   GM_DeleteFile();

	ULONG   GM_EnumFile();

	ULONG   GM_EnumContainer();

	ULONG   GM_GetFileInfo();

	ULONG   GM_ReadFile();

	ULONG   GM_WriteFile();

	ULONG   GM_CreateContainer();

	ULONG   GM_DeleteContainer();

	ULONG   GM_OpenContainer();

	ULONG   GM_CloseContainer();

	ULONG   GM_GetContainerType();

	ULONG   GM_ExportCertificate();

	ULONG   GM_ImportCertificate();

	ULONG   GM_GenRandom();

	ULONG   GM_Digest();

	ULONG   GM_GroupDigest();

	ULONG   GM_RSASignAndVerify();

	ULONG   GM_ECCSignAndVerify();

	ULONG   GM_EnCryptAndDeCryptData();

	ULONG   GM_GroupEnCryptAndDeCryptData();

	ULONG   GM_MacData();

	ULONG   GM_GroupMacData();

	ULONG   GM_ECCKeyAgreement();

	std::string GM_GetSignCertSN();

private:

	HANDLE		m_hDev;
	HANDLE      m_hApp;
	HANDLE      m_hCont;

	char		m_szDevName[256];
	char		m_szContName[256];
	char        m_szAppName[256];
	char        m_szPassword[32];
	char        m_szSoPin[32];	

	DEVINFO     m_DevInfo;

	GmDll		m_GmDll;
	pGmDll      m_pGmDll;

	ULONG       m_ulRetryCount;
	ULONG       m_ulDevLen;
	ULONG       m_ulAppLen;
	ULONG       m_ulContLen;
};