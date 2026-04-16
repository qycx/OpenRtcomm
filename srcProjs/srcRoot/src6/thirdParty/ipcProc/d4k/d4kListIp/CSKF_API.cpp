#include <iostream>
#include <string.h>
#include "CSKF_API.h"
#include "gm3000_dll.h"
#include <tchar.h>
#include <wincrypt.h>

using namespace std;

CSKFAPI::CSKFAPI()
{
	char * szSoPIN = "admin";

	m_hDev = NULL;
	m_hApp = NULL;
	m_hCont = NULL;

	m_ulDevLen = 256;
	m_ulAppLen = 256;
	m_ulContLen = 256;

	m_ulRetryCount = 0;

	memset(m_szDevName, 0, sizeof(m_szDevName));
	memset(m_szAppName, 0, sizeof(m_szAppName));
	memset(m_szContName, 0, sizeof(m_szContName));
	memset(m_szPassword, 0, sizeof(m_szPassword));
	memset(m_szSoPin, 0, sizeof(m_szPassword));

	memcpy(m_szSoPin, szSoPIN, strlen(szSoPIN));

	m_pGmDll = &m_GmDll;
	LoadSKFAPI(_T(  "mtoken_gm3000.dll"  ), &m_GmDll);

//	this->GM_Login();
}

CSKFAPI::~CSKFAPI()
{
	if (m_hCont != NULL)
	{
		m_pGmDll->SKF_CloseContainer(m_hCont);
		m_hCont = NULL;
	}
	if (m_hApp != NULL)
	{
		m_pGmDll->SKF_CloseApplication(m_hApp);
		m_hApp = NULL;
	}
	if (m_hDev != NULL)
	{
		m_pGmDll->SKF_DisConnectDev(m_hDev);
		m_hDev = NULL;
	}
}

ULONG CSKFAPI::GM_Login()
{
	ULONG      ulRslt = SAR_OK;

	ulRslt = m_pGmDll->SKF_EnumDev(TRUE, m_szDevName, &m_ulDevLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ConnectDev(m_szDevName, &m_hDev);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_EnumApplication(m_hDev, m_szAppName, &m_ulAppLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_OpenApplication(m_hDev, m_szAppName, &m_hApp);
	ERROR_THROW(ulRslt);

	printf("Please enter the USBKey password:\n");
	cin >> m_szPassword;
	ulRslt = m_pGmDll->SKF_VerifyPIN(m_hApp, USER_TYPE, m_szPassword, &m_ulRetryCount);
	if (ulRslt != SAR_OK)
	{
		printf("User PIN error!!!\n");
		goto END_OF_FUN;
	}	

	//printf("Please enter the container name: \n");
	//cin >> m_szContName;

	//ulRslt = m_pGmDll->SKF_OpenContainer(m_hApp, m_szContName, &m_hCont);
	//ERROR_THROW(ulRslt);

	printf("Login successful !!!\n");

END_OF_FUN:
	return ulRslt;
}

void CSKFAPI::SetContName( char * szContName )
{
	strcpy(m_szContName, szContName);
}

void CSKFAPI::SetPassword( char * szPassword )
{
	strcpy(m_szPassword, szPassword);
}

ULONG CSKFAPI::GM_EnumDev()
{
	ULONG ulRslt = SAR_OK;

	char * pDevNameList = m_szDevName;
	int index = 1;

	ulRslt = m_pGmDll->SKF_EnumDev(TRUE, m_szDevName, &m_ulDevLen);
	ERROR_THROW(ulRslt);

	printf("\nDevice Name: \n");
	while(strlen(pDevNameList) > 0)
	{
		printf("	%d.: %s\n", index++, pDevNameList);
		pDevNameList += (strlen(pDevNameList) + 1);
	}

	printf("\nEnumDev successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_GetDevState()
{
	ULONG ulRslt = SAR_OK;
	ULONG  ulState = 0;

	ulRslt = m_pGmDll->SKF_GetDevState(m_szDevName, &ulState);
	ERROR_THROW(ulRslt);

	if (ulState)
	{
		printf("\nDevice exists!\n");
	}
	else
	{
		printf("Device does not exist!\n");
	}

	printf("\nGetDevState successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_SetDevLable()
{
	ULONG ulRslt = SAR_OK;
	char  szLabel[32] = {0};

	printf("Please enter the set Device Label\n");
	cin >> szLabel;

	ulRslt = m_pGmDll->SKF_SetLabel(m_hDev, szLabel);
	ERROR_THROW(ulRslt);

	printf("\nSet Device Label successful!!!\n");
	printf("Device Label: %s\n\n", szLabel);

END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_GetDevInfo()
{
	ULONG ulRslt = SAR_OK;

	ulRslt = m_pGmDll->SKF_GetDevInfo(m_hDev, &m_DevInfo);
	ERROR_THROW(ulRslt);

	printf("\nDevice info: \n");
	printf("\tManufacturer:              %s\n", m_DevInfo.Manufacturer);
	printf("\tVersion:                   %hhu.%hhu\n", m_DevInfo.Version.major, m_DevInfo.Version.minor);
	printf("\tIssuer:                    %s\n", m_DevInfo.Issuer);
	printf("\tLabel:                     %s\n", m_DevInfo.Label);
	printf("\tSerialNumber:              %s\n", m_DevInfo.SerialNumber);
	printf("\tHWVersion:                 %hhu.%hhu\n", m_DevInfo.HWVersion.major, m_DevInfo.HWVersion.minor);
	printf("\tFirmwareVersion:           %hhu.%hhu\n", m_DevInfo.FirmwareVersion.major, m_DevInfo.FirmwareVersion.minor);
	printf("\tAlgSymCap:                 %d\n", m_DevInfo.AlgSymCap);
	printf("\tAlgAsymCap:                %d\n", m_DevInfo.AlgAsymCap);
	printf("\tAlgHashCap:                %d\n", m_DevInfo.AlgHashCap);
	printf("\tDevAuthAlgId:              %d\n", m_DevInfo.DevAuthAlgId);
	printf("\tTotalSpace:                %d\n", m_DevInfo.TotalSpace);
	printf("\tFreeSpace:                 %d\n", m_DevInfo.FreeSpace);
	printf("\tReserved:                  ");
	PrintByteStr(m_DevInfo.Reserved);
	//printf("\tCspName:                   %s\n", m_DevInfo.CspName);

	printf("\nGet Device info successful !!!\n\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_DevAuth()
{
	ULONG	ulRslt = SAR_OK;
	HANDLE	hkey = NULL;

	BYTE    byKey[32] = {0};
	BYTE    byRandom[16] = {0};
	BYTE    byEnData[16] = {0};
	BYTE    byEnCryptData[256] = {0};

	ULONG   ulEnDataLen = 32;
	ULONG   ulEnCryptDataLen = 256;

	BLOCKCIPHERPARAM bp = {0};

	memcmp(bp.IV, "12345678", 8);
	bp.IVLen = 16;
	bp.PaddingType = 0;

	printf("Please enter the device authentication key: \n");
	cin >> byKey;

	ulRslt = m_pGmDll->SKF_GenRandom(m_hDev, byRandom, 16);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_SetSymmKey(m_hDev, byKey, SGD_SM4_ECB, &hkey);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_EncryptInit(hkey, bp);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_Encrypt(hkey, byRandom, 16, byEnCryptData, &ulEnCryptDataLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_DevAuth(m_hDev, byEnCryptData, ulEnCryptDataLen);
	ERROR_THROW(ulRslt);

	printf("\nDevice Auth successful !!!\n\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_ChangeDevAuthKey()
{
	ULONG	ulRslt = SAR_OK;

	BYTE    byKey[32] = {0};
	BYTE    byNewKey[32] = {0};

	ULONG   ulKeyLen = sizeof(byNewKey);

	ulRslt = this->GM_DevAuth();
	ERROR_THROW(ulRslt);

	printf("Please enter the new device authentication key: \n");
	cin >> byNewKey;

	ulRslt = m_pGmDll->SKF_ChangeDevAuthKey(m_hDev, byNewKey, ulKeyLen);
	ERROR_THROW(ulRslt);

	printf("\nChange device Auth successful !!!\n\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_VerifyPIN()
{
	ULONG	ulPINType = 0;
	ULONG	ulRslt = SAR_OK;

PIN:
	printf("Please select the login mode: \n");
	printf("\t1. USER_TYPE\n");
	printf("\t2. ADMIN_TYPE\n");
	cin >> ulPINType;

	if (ulPINType == 1)
	{
		printf("\nPlease enter the user PIN: \n");
		cin >> m_szPassword;
		ulRslt = m_pGmDll->SKF_VerifyPIN(m_hApp, USER_TYPE, m_szPassword, &m_ulRetryCount);
		ERROR_THROW(ulRslt);
	}
	else if (ulPINType == 2)
	{
		printf("Please enter the admin PIN: \n");
		cin >> m_szSoPin;
		ulRslt = m_pGmDll->SKF_VerifyPIN(m_hApp, ADMIN_TYPE, m_szSoPin, &m_ulRetryCount);
		ERROR_THROW(ulRslt);
	}
	else
	{
		printf("Please enter a valid command!\n\n");
		goto PIN;
	}

	printf("\nVerify PIN successful !!!\n\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_GetPINInfo()
{	
	ULONG	ulRslt = SAR_OK;
	ULONG	ulPINType = 0;
	ULONG   ulMaxRetryCount = 0;
	ULONG   ulRemainRetryCount = 0;

	int    bDefaultPin = false;

	printf("Please select the login mode: \n");
	printf("\t1. USER_TYPE\n");
	printf("\t2. ADMIN_TYPE\n");
	cin >> ulPINType;

	if (ulPINType == 1)
		ulPINType = USER_TYPE;
	else if (ulPINType == 2)
		ulPINType = ADMIN_TYPE;
	else
		printf("Instruction is invalid\n");

	ulRslt = m_pGmDll->SKF_GetPINInfo(m_hApp, ulPINType, &ulMaxRetryCount, &ulRemainRetryCount, &bDefaultPin);
	ERROR_THROW(ulRslt);

	printf("PIN info: \n");
	printf("\tMaxRetryCount:        %d\n", ulMaxRetryCount);
	printf("\tRemainRetryCount:     %d\n", ulRemainRetryCount);
	printf("\tDefaultPin:           %d\n", bDefaultPin);

	printf("\nGet PIN info successful !!!\n\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_ChangePIN()
{
	ULONG	ulRslt = SAR_OK;
	ULONG	ulPINType = 0;

	char    szNewPin[32] = {0};

	printf("Please select the login mode: \n");
	printf("\t1. USER_TYPE\n");
	printf("\t2. ADMIN_TYPE\n");
	cin >> ulPINType;

	if (ulPINType == 1)
		ulPINType = USER_TYPE;
	else if (ulPINType == 2)
		ulPINType = ADMIN_TYPE;
	else
		printf("Instruction is invalid\n");

	printf("Please enter the old PIN: \n");
	cin >> m_szPassword;

	printf("Please enter the New PIN: \n");
	cin >> szNewPin;

	ulRslt = m_pGmDll->SKF_ChangePIN(m_hApp, ulPINType, m_szPassword, szNewPin, &m_ulRetryCount);
	ERROR_THROW(ulRslt);

	printf("\nChange PIN successful !!!\n\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_UnblockPIN()
{
	ULONG	ulRslt = SAR_OK;

	printf("Please enter the soPIN: \n");
	cin >> m_szSoPin;

	printf("Please enter the new PIN: \n");
	cin >> m_szPassword;

	ulRslt = m_pGmDll->SKF_UnblockPIN(m_hApp, m_szSoPin, m_szPassword, &m_ulRetryCount);
	ERROR_THROW(ulRslt);

	printf("\nChange PIN successful !!!\n\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_EnumApplication()
{
	ULONG ulRslt = SAR_OK;

	char * pAppNameList = m_szAppName;
	int index = 1;

	ulRslt = m_pGmDll->SKF_EnumApplication(m_hDev, m_szAppName, &m_ulAppLen);
	ERROR_THROW(ulRslt);

	printf("\nApplication Name: \n");
	while(strlen(pAppNameList) > 0)
	{
		printf("	%d.: %s\n", index++, pAppNameList);
		pAppNameList += (strlen(pAppNameList) + 1);
	}

	printf("\nEnumApp successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_CreatApplication()
{
	ULONG	ulRslt = SAR_OK;
	ULONG	ulAdminPinRetryCount = 10;
	ULONG	ulUserPinRetryCount = 10;
	char	szAppName[256] = {0};
	HANDLE  happ = NULL;

	ulRslt = this->GM_DevAuth();
	ERROR_THROW(ulRslt);

	printf("Please enter the App name: \n");
	cin >> szAppName;

	printf("Please enter the SoPin: \n");
	cin >> m_szSoPin;

	printf("Please enter the user Pin: \n");
	cin >> m_szSoPin;

	ulRslt = m_pGmDll->SKF_CreateApplication(m_hDev, szAppName, m_szSoPin, ulAdminPinRetryCount, m_szPassword, ulUserPinRetryCount, SECURE_ANYONE_ACCOUNT, &happ);
	ERROR_THROW(ulRslt);

	printf("App Name: %s\n", szAppName);
	printf("\nEnumApp successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_DeleteAppliction()
{
	ULONG	ulRslt = SAR_OK;
	char	szAppName[256] = {0};

	ulRslt = this->GM_DevAuth();
	ERROR_THROW(ulRslt);

	printf("Please enter the App name: \n");
	cin >> szAppName;

	ulRslt = m_pGmDll->SKF_DeleteApplication(m_hDev, szAppName);
	ERROR_THROW(ulRslt);

	printf("\nDelete App successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_OpenApplication()
{
	ULONG	ulRslt = SAR_OK;
	char	szAppName[256] = {0};

	printf("Please enter the App name: \n");
	cin >> szAppName;

	ulRslt = m_pGmDll->SKF_OpenApplication(m_hDev, szAppName, &m_hApp);
	ERROR_THROW(ulRslt);

	printf("\nOpen App successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_CloseApplication()
{
	ULONG	ulRslt = SAR_OK;

	ulRslt = m_pGmDll->SKF_CloseApplication(m_hApp);
	ERROR_THROW(ulRslt);

	printf("\nClose App successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_CreatFile()
{
	ULONG	ulRslt = SAR_OK;

	char    szFileName[32] = {0};
	ULONG   ulFileLen = 1024;

	printf("Please enter the file name: \n");
	cin >> szFileName;

	printf("Please enter the file size: \n");
	cin >> ulFileLen;

	ulRslt = m_pGmDll->SKF_CreateFile(m_hApp, szFileName, ulFileLen, SECURE_ANYONE_ACCOUNT, SECURE_ANYONE_ACCOUNT);
	ERROR_THROW(ulRslt);

	printf("file name: %s\n", szFileName);
	printf("\nCreat File successful !!!\n");

END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_DeleteFile()
{
	ULONG	ulRslt = SAR_OK;

	char    szFileName[32] = {0};

	printf("Please enter the file name: \n");
	cin >> szFileName;

	ulRslt = m_pGmDll->SKF_DeleteFile(m_hApp, szFileName);
	ERROR_THROW(ulRslt);

	printf("\nDelete File successful !!!\n");

END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_EnumFile()
{
	ULONG ulRslt = SAR_OK;
	ULONG ulFileSize = 256;

	char   szFileName[256] = {0};
	char * pFileNameList = szFileName;
	int index = 1;

	ulRslt = m_pGmDll->SKF_EnumFiles(m_hApp, szFileName, &ulFileSize);
	ERROR_THROW(ulRslt);

	printf("\nFile Name: \n");
	while(strlen(pFileNameList) > 0)
	{
		printf("	%d.: %s\n", index++, pFileNameList);
		pFileNameList += (strlen(pFileNameList) + 1);
	}

	printf("\nEnum File successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_EnumContainer()
{
	ULONG ulRslt = SAR_OK;
	ULONG ulContSize = 256;

	char   szContName[256] = { 0 };
	char*  pContNameList = szContName;
	int index = 1;

	ulRslt = m_pGmDll->SKF_EnumContainer(m_hApp, szContName, &ulContSize);
	ERROR_THROW(ulRslt);

	printf("\nContainer Name: \n");
	while (strlen(pContNameList) > 0)
	{
		printf("	%d.: %s\n", index++, pContNameList);
		pContNameList += (strlen(pContNameList) + 1);
	}

	printf("\nEnum successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_GetFileInfo()
{
	ULONG ulRslt = SAR_OK;
	FILEATTRIBUTE fileInfo = {0};

	char    szFileName[32] = {0};

	printf("Please enter the file name: \n");
	cin >> szFileName;

	ulRslt = m_pGmDll->SKF_GetFileInfo(m_hApp, szFileName, &fileInfo);
	ERROR_THROW(ulRslt);

	printf("FileName:            %s\n", fileInfo.FileName);
	printf("FileSize:            %d\n", fileInfo.FileSize);
	printf("ReadRights:          %d\n", fileInfo.ReadRights);
	printf("WriteRights:         %d\n", fileInfo.WriteRights);

	printf("\nGet File info successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_ReadFile()
{
	ULONG	ulRslt = SAR_OK;

	char    szFileName[256] = {0};
	char    szOutData[256] = {0};
	ULONG   ulFileLen = 256;
	ULONG   ulOutLen = 256;

	printf("Please enter the file name: \n");
	cin >> szFileName;

	ulRslt = m_pGmDll->SKF_ReadFile(m_hApp, szFileName, 0, ulFileLen, (BYTE*)szOutData, &ulOutLen);
	ERROR_THROW(ulRslt);

	printf("szOutData: %s\n", szOutData);

	printf("\nRead File successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_WriteFile()
{
	ULONG	ulRslt = SAR_OK;

	char    szFileName[256] = {0};
	char    szInData[256] = {0};
	char    szOutData[256] = {0};
	ULONG   ulFileLen = 256;
	ULONG   ulInLen = 0;
	ULONG   ulOutLen = 256;

	printf("Please enter the file name: \n");
	cin >> szFileName;

	printf("Please enter the data to be write: \n");
	cin >> szInData;

	ulInLen = strlen(szInData);

	ulRslt = m_pGmDll->SKF_WriteFile(m_hApp, szFileName, 0, (BYTE*)szInData, ulInLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ReadFile(m_hApp, szFileName, 0, ulInLen, (BYTE*)szOutData, &ulOutLen);
	ERROR_THROW(ulRslt);

	printf("szOutData: %s\n", szOutData);

	printf("\nWrite File successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_CreateContainer()
{
	ULONG	ulRslt = SAR_OK;

	char    szContName[256] = {0};
	HANDLE  hcont = NULL;

	printf("Please enter the container name: \n");
	cin >> szContName;

	ulRslt = m_pGmDll->SKF_CreateContainer(m_hApp, szContName, &hcont);
	ERROR_THROW(ulRslt);

	printf("Cont Name: %s\n", szContName);
	printf("\nCreate Container successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_DeleteContainer()
{
	ULONG	ulRslt = SAR_OK;

	char    szContName[256] = {0};
	HANDLE  hcont = NULL;

	printf("Please enter the container name: \n");
	cin >> szContName;

	ulRslt = m_pGmDll->SKF_DeleteContainer(m_hApp, szContName);
	ERROR_THROW(ulRslt);

	printf("\nDelete Container successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_OpenContainer()
{
	ULONG	ulRslt = SAR_OK;

	char    szContName[256] = {0};
	printf("Please enter the container name: \n");
	cin >> szContName;

	ulRslt = m_pGmDll->SKF_OpenContainer(m_hApp, szContName, &m_hCont);
	ERROR_THROW(ulRslt);

	printf("\nOpen Container successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_CloseContainer()
{
	ULONG	ulRslt = SAR_OK;

	if (m_hCont != NULL)
	{
		ulRslt = m_pGmDll->SKF_CloseContainer(m_hCont);
		ERROR_THROW(ulRslt);
	}

	printf("\nOpen Container successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_GetContainerType()
{
	ULONG	ulRslt = SAR_OK;
	ULONG  ulContType = 0;

	ulRslt = GM_OpenContainer();
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_GetContainerType(m_hCont, &ulContType);
	ERROR_THROW(ulRslt);

	switch (ulContType)
	{
	case 0 :
		printf("The container has not been assigned a type or is empty\n");
		break;
	case 1:
		printf("The container is an RSA container!\n");
		break;
	case 2:
		printf("The container is an ECC container!\n");
		break;
	default:
		break;
	}

	printf("\nGet Container Type successful !!!\n");
END_OF_FUN:
	return ulRslt;
}



BOOL get_SN(PCCERT_CONTEXT pCert, LPSTR lptcSN, ULONG* pulLen)
{
	CHAR scSN[512] = { 0 };

	if (!pCert)
	{
		return FALSE;
	}
	if (!pulLen)
	{
		return FALSE;
	}

	PCRYPT_INTEGER_BLOB pSn = &(pCert->pCertInfo->SerialNumber);
	for (int n = (int)(pSn->cbData - 1); n >= 0; n--)
	{
		CHAR szHex[32] = { 0 };
		sprintf_s(szHex, "%02X", (pSn->pbData)[n]);
		strcat_s(scSN, 512, szHex);
	}

	if (!lptcSN)
	{
		*pulLen = strlen(scSN) + 1;
		return FALSE;
	}

	if (*pulLen <= strlen(scSN) + 1)
	{
		return FALSE;
	}
	strcpy_s(lptcSN, *pulLen, scSN);
	*pulLen = strlen(scSN);

	return TRUE;
}

std::string CSKFAPI::GM_GetSignCertSN()
{
	std::string strSN = "";

	ULONG ulRslt = SAR_OK;
	ULONG ulContSize = 256;
	char  szContName[256] = { 0 };
	char* pContNameList = szContName;
	BYTE    byCertData[4096] = { 0 };
	BOOL    bSignFlag = TRUE;
	ULONG   ulCertLen = 4096;

	ulRslt = m_pGmDll->SKF_EnumDev(TRUE, m_szDevName, &m_ulDevLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ConnectDev(m_szDevName, &m_hDev);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_EnumApplication(m_hDev, m_szAppName, &m_ulAppLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_OpenApplication(m_hDev, m_szAppName, &m_hApp);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_EnumContainer(m_hApp, szContName, &ulContSize);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_OpenContainer(m_hApp, szContName, &m_hCont);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ExportCertificate(m_hCont, bSignFlag, byCertData, &ulCertLen);
	ERROR_THROW(ulRslt);

	PCCERT_CONTEXT pCert = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, byCertData, ulCertLen);
	if (pCert)
	{
		CHAR szSNBuf[128] = { 0 };
		DWORD dwLen = 128;

		get_SN(pCert, szSNBuf, &dwLen);

		strSN = szSNBuf;

		CertFreeCertificateContext(pCert);
	}

END_OF_FUN:
	return strSN;
}

ULONG CSKFAPI::GM_ExportCertificate()
{
	ULONG	ulRslt = SAR_OK;

	BYTE    byCertData[4096] = {0};
	BOOL    bSignFlag = TRUE;
	ULONG   ulCertLen = 4096;

	printf("Please enter the certificate type: \n");
	printf("0: Encrypt Cert\n");
	printf("1: Sign Cert\n");

	cin >> bSignFlag;

	ulRslt = GM_OpenContainer();
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ExportCertificate(m_hCont, bSignFlag, byCertData, &ulCertLen);
	ERROR_THROW(ulRslt);
	
	FILE* fp = NULL;

	fp = fopen("cert.cer", "wb+");
	fwrite(byCertData, ulCertLen, 1, fp);

	//for (int i = 1; i < ulCertLen; i++)
	//{
	//	printf("0x%02x ", byCertData[i]);
	//	if (i % 16 == 0)
	//	{
	//		printf("\n");
	//	}
	//}

	fclose(fp);
	printf("\n\nExport Certificate successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_ImportCertificate()
{
	ULONG	ulRslt = SAR_OK;
	ULONG   ulCertLen = 1024;
	BOOL    bSignFlag = TRUE;
	BYTE    byCertData[1024] = {0};

	printf("Please enter the certificate type: \n");
	printf("0: Encrypt Cert\n");
	printf("1: Sign Cert\n");

	cin >> bSignFlag;

	ulRslt = GM_OpenContainer();
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ExportCertificate(m_hCont, bSignFlag, byCertData, &ulCertLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ImportCertificate(m_hCont, bSignFlag, byCertData, ulCertLen);
	ERROR_THROW(ulRslt);

	printf("\n");
	for (int i = 1; i < ulCertLen; i++)
	{
		printf("0x%02x ", byCertData[i]);
		if (i % 16 == 0)
		{
			printf("\n");
		}
	}

	printf("\n\nImport Certificate successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_GenRandom()
{
	ULONG	ulRslt = SAR_OK;
	BYTE    byRandom[2048] = {0};
	ULONG   ulRanLen = 0;

	printf("Please enter random number length: \n");
	cin >> ulRanLen;

	ulRslt = m_pGmDll->SKF_GenRandom(m_hDev, byRandom, ulRanLen);
	ERROR_THROW(ulRslt);

	printf("Random Data: \n\n");

	for (int i = 1; i < ulRanLen; i++)
	{
		printf("0x%02x ", byRandom[i]);
		if (i % 16 == 0)
		{
			printf("\n");
		}
	}	

	printf("\n\nGen Random successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_Digest()
{
	ULONG	ulRslt = SAR_OK;
	HANDLE  hHash = NULL;

	BYTE    byInputData[256] = {0};
	BYTE    byOutData[256] = {0};

	ULONG   ulInputLen = 256;
	ULONG   ulOutputLen = 256;

	for (int i = 0; i < ulInputLen; i++)
	{
		byInputData[i] = i;
	}

	ulRslt = m_pGmDll->SKF_DigestInit(m_hDev, SGD_SM3, NULL, NULL, 0, &hHash);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_Digest(hHash, byInputData, ulInputLen, byOutData, &ulOutputLen);
	ERROR_THROW(ulRslt);

	printf("Digest Data: \n");
	for (int i = 0; i < ulOutputLen; i++)
	{
		printf("0x%02x ", byOutData[i]);
		if (i % 16 == 0)
		{
			printf("\n");
		}
	}

	printf("\n\nDigest test successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_GroupDigest()
{
	ULONG	ulRslt = SAR_OK;

	HANDLE  hHash = NULL;

	BYTE    byInputData[8192] = {0};
	BYTE    byOutData[256] = {0};

	ULONG   ulInputLen = 7192;
	ULONG   ulOutputLen = 256;

	long	nCount = ulInputLen / DECPRY_DATA_SIZE;
	long	nLast = ulInputLen % DECPRY_DATA_SIZE;
	long	offset = 0;

	int		index = 0;

	for (int i = 0; i < ulInputLen; i++)
	{
		byInputData[i] = i;
	}

	ulRslt = m_pGmDll->SKF_LockDev(m_hDev, 0xFFFFFFFF);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_DigestInit(m_hDev, SGD_SM3, NULL, NULL, 0, &hHash);
	ERROR_THROW(ulRslt);

	for(int i = 0; i < nCount; i++)
	{
		ulRslt = m_pGmDll->SKF_DigestUpdate(hHash, byInputData + offset, DECPRY_DATA_SIZE);
		ERROR_THROW(ulRslt);

		offset += DECPRY_DATA_SIZE;
	}
	if (nLast > 0)
	{
		ulRslt = m_pGmDll->SKF_DigestUpdate(hHash, byInputData + offset, DECPRY_DATA_SIZE);
		ERROR_THROW(ulRslt);
	}

	ulRslt = m_pGmDll->SKF_DigestFinal(hHash, byOutData, &ulOutputLen);
	ERROR_THROW(ulRslt);

	cout << "Digest Data: " << endl;
	for (int i = 0; i < ulOutputLen; i++)
	{
		printf("0x%02x ", byOutData[i]);
		if (i == 15 && i != 0)
		{
			printf("\n");
		}
	}

	ulRslt = m_pGmDll->SKF_UnlockDev(m_hDev);
	ERROR_THROW(ulRslt);

	printf("\n\nGroup digest test successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_RSASignAndVerify()
{
	ULONG	ulRslt = SAR_OK;

	char szContName[256] = {0};

	BYTE    byInData[117] = {0};
	BYTE    byOutData[1024] = {0};
	BYTE	byRSAPubBlob[1024] = {0};

	ULONG	ulBlobLen = 1024;
	ULONG   ulInputLen = 117;
	ULONG   ulOutputLen = 1024;

	for (int i = 0; i < ulInputLen; i++)
	{
		byInData[i] = i;
	}

	ulRslt = this->GM_OpenContainer();
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_RSASignData(m_hCont, byInData, ulInputLen, byOutData, &ulOutputLen);
	ERROR_THROW(ulRslt);

	printf("RSASign Data:\n");
	for (int i = 1; i < ulOutputLen; i++)
	{
		printf("0x%02x ", byOutData[i]);
		if (i % 16 == 0)
		{
			printf("\n");
		}
	}

	printf("\nRSA Sign successful!\n");

	ulRslt = m_pGmDll->SKF_ExportPublicKey(m_hCont, TRUE, byRSAPubBlob, &ulBlobLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_RSAVerify(m_hDev, (PRSAPUBLICKEYBLOB)byRSAPubBlob, byInData, ulInputLen, byOutData, ulOutputLen);
	ERROR_THROW(ulRslt);

	printf("\n\nRSA Verify successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_ECCSignAndVerify()
{
	ULONG	ulRslt = SAR_OK;
	BYTE	byEccPubBlob[1024] = {0};
	BYTE    byInData[32] = {0};

	ULONG   ulInputLen = 32;
	ULONG	ulBlobLen = sizeof(byEccPubBlob);

	ECCSIGNATUREBLOB	stSignature = {0};

	for (int i = 0; i < ulInputLen; i++)
	{
		byInData[i] = i;
	}

	ulRslt = this->GM_OpenContainer();
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ECCSignData(m_hCont, byInData, ulInputLen, &stSignature);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ExportPublicKey(m_hCont, TRUE, byEccPubBlob, &ulBlobLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_ECCVerify(m_hDev, (PECCPUBLICKEYBLOB)byEccPubBlob, byInData, ulInputLen, &stSignature);
	ERROR_THROW(ulRslt);

	printf("\n\nECC Verify successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_EnCryptAndDeCryptData()
{
	ULONG	ulRslt = 0;
	HANDLE	hEnKey = NULL;
	HANDLE  hDeKey = NULL;

	BYTE	iv[16] = {0};
	BYTE    byInData[32] = {0};
	BYTE    byEnCryptData[1024] = {0};
	BYTE    byDeCryptData[1024] = {0};

	ULONG   ulEnCryptLen = 1024;
	ULONG   ulDeCryptLen = 1024;
	ULONG   ulInputLen = 32;

	BLOCKCIPHERPARAM bp;

	UINT8	key[16] = {0xD9,0x45,0xFA,0x61,0x4A,0x25,0xFF,0xA3,0xCC,0x03,0x74,0x50,0xE2,0xA7,0x18,0xF8};

	for (int i = 0; i < ulInputLen; i++)
	{
		byInData[i] = i;
	}

	ulRslt = m_pGmDll->SKF_SetSymmKey(m_hDev, key, SGD_SM4_ECB, &hEnKey);
	ERROR_THROW(ulRslt);

	bp.PaddingType = 0;
	memcpy(bp.IV, iv, 16);
	bp.IVLen = 16;

	ulRslt = m_pGmDll->SKF_EncryptInit(hEnKey, bp);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_Encrypt(hEnKey, byInData, ulInputLen, byEnCryptData, &ulEnCryptLen);
	ERROR_THROW(ulRslt);

	printf("Data Encrypt successful!\n\n");

	cout << "EnCrypt Data: " << endl;
	for (int i = 0; i < ulEnCryptLen; i++)
	{
		printf("0x%02x ", byEnCryptData[i]);
		if (i == 15)
		{
			printf("\n");
		}
	}

	ulRslt = m_pGmDll->SKF_SetSymmKey(m_hDev, key, SGD_SM4_ECB, &hDeKey);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_DecryptInit(hDeKey, bp);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_Decrypt(hDeKey, byEnCryptData, ulEnCryptLen, byDeCryptData, &ulDeCryptLen);
	ERROR_THROW(ulRslt);

	printf("\n\nInput Data:\n");
	for (int i = 0; i < ulDeCryptLen; i++)
	{
		printf("0x%02x ", byDeCryptData[i]);
		if (i == 15)
		{
			printf("\n");
		}
	}
	printf("\n\n");

	printf("DeCrypt Data:\n");
	for (int i = 0; i < ulDeCryptLen; i++)
	{
		printf("0x%02x ", byDeCryptData[i]);
		if (i == 15)
		{
			printf("\n");
		}
	}

	printf("\n\nData Decrypt successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_GroupEnCryptAndDeCryptData()
{
	ULONG	ulRslt = 0;
	HANDLE	hEnKey = NULL;
	HANDLE  hDeKey = NULL;

	BYTE    byInData[8192] = {0};
	BYTE    byEnCryptData[8192] = {0};
	BYTE    byDeCryptData[8192] = {0};
	BYTE	*pbEncrypted_ptr = byEnCryptData;
	BYTE	*pbDecrypted_ptr = byDeCryptData;

	ULONG   ulEnCryptLen = 0;
	ULONG   ulDeCryptLen = 0;
	ULONG   ulInputLen = 1024;

	BLOCKCIPHERPARAM bp;

	UINT8	key[16] = {0xD9,0x45,0xFA,0x61,0x4A,0x25,0xFF,0xA3,0xCC,0x03,0x74,0x50,0xE2,0xA7,0x18,0xF8};

	long	nCount = ulInputLen / DECPRY_DATA_SIZE;
	long	nLast = ulInputLen % DECPRY_DATA_SIZE;
	long	offset = 0;

	int		index = 0;

	ULONG nEnOutDataLen = 0;
	ULONG nDeOutDataLen = 0;

	for (int i = 0; i < ulInputLen; i++)
	{
		byInData[i] = i;
	}

	ulRslt = m_pGmDll->SKF_SetSymmKey(m_hDev, key, SGD_SM4_ECB, &hEnKey);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_LockDev(m_hDev, 0xFFFFFFFF);
	ERROR_THROW(ulRslt);

	bp.PaddingType = 1;
	memcpy(bp.IV, "1234567812345678" ,16);
	bp.IVLen = 16;

	ulRslt = m_pGmDll->SKF_EncryptInit(hEnKey, bp);
	ERROR_THROW(ulRslt);

	for (index = 0; index < nCount; index++)
	{
		nEnOutDataLen = DECPRY_DATA_SIZE;

		ulRslt = m_pGmDll->SKF_EncryptUpdate(hEnKey, byInData + offset, DECPRY_DATA_SIZE, pbEncrypted_ptr, &nEnOutDataLen);
		ERROR_THROW(ulRslt);

		offset += DECPRY_DATA_SIZE;
		pbEncrypted_ptr += nEnOutDataLen;
		ulEnCryptLen += nEnOutDataLen;
	}

	if (nLast > 0)
	{
		ulRslt = m_pGmDll->SKF_EncryptUpdate(hEnKey, byInData + offset, nLast, pbEncrypted_ptr, &nEnOutDataLen);
		ERROR_THROW(ulRslt);

		pbEncrypted_ptr += nEnOutDataLen;
		ulEnCryptLen += nEnOutDataLen;
	}

	nEnOutDataLen = DECPRY_DATA_SIZE;
	ulRslt = m_pGmDll->SKF_EncryptFinal(hEnKey, pbEncrypted_ptr, &nEnOutDataLen);
	ERROR_THROW(ulRslt);

	printf("Group Encrypt successful \n\n");
	printf("EnCrypt Data:\n");
	for (int i = 1; i < ulEnCryptLen; i++)
	{
		printf("0x%02x ", byEnCryptData[i]);
		if (i % 15 == 0 )
		{
			printf("\n");
		}
	}
	printf("\n");

	ulRslt = m_pGmDll->SKF_UnlockDev(m_hDev);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_LockDev(m_hDev, 0xFFFFFFFF);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_SetSymmKey(m_hDev, key, SGD_SM4_ECB, &hDeKey);
	ERROR_THROW(ulRslt);

	bp.PaddingType = 1;
	memcpy(bp.IV, "1234567812345678", 16);
	bp.IVLen = 16;

	ulRslt = m_pGmDll->SKF_DecryptInit(hDeKey, bp);
	ERROR_THROW(ulRslt);

	nCount =  ulEnCryptLen / DECPRY_DATA_SIZE;
	nLast  =  ulEnCryptLen % DECPRY_DATA_SIZE;
	offset = 0;

	pbEncrypted_ptr = byEnCryptData;
	for (index = 0; index < nCount; index++)
	{
		nDeOutDataLen = DECPRY_DATA_SIZE;
		ulRslt = m_pGmDll->SKF_DecryptUpdate(hDeKey, pbEncrypted_ptr + offset, DECPRY_DATA_SIZE, pbDecrypted_ptr, &nDeOutDataLen);
		ERROR_THROW(ulRslt);

		offset +=  DECPRY_DATA_SIZE;
		pbDecrypted_ptr += nDeOutDataLen;
		ulDeCryptLen += nDeOutDataLen;
	}

	if (nLast > 0)
	{
		nDeOutDataLen = nLast;
		ulRslt = m_pGmDll->SKF_DecryptUpdate(hDeKey, pbEncrypted_ptr + offset, nLast, pbDecrypted_ptr, &nDeOutDataLen);
		ERROR_THROW(ulRslt);

		pbDecrypted_ptr += nDeOutDataLen;
		ulDeCryptLen += nDeOutDataLen;
	}

	nDeOutDataLen = DECPRY_DATA_SIZE;

	ulRslt = m_pGmDll->SKF_DecryptFinal(hDeKey, pbDecrypted_ptr, &nDeOutDataLen);
	ERROR_THROW(ulRslt);

	ulDeCryptLen += nDeOutDataLen;

	cout << "Decrypt Data: " << endl;
	for (int i = 0; i < ulDeCryptLen; i++)
	{
		printf("0x%02x ", byDeCryptData[i]);
		if (i % 15 == 0 )
		{
			printf("\n");
		}
	}

	printf("\n");

	ulRslt = m_pGmDll->SKF_UnlockDev(m_hDev);
	ERROR_THROW(ulRslt);

	printf("\n\nGroup Data Decrypt successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_MacData()
{
	ULONG	ulRslt = 0;

	HANDLE	hKey = NULL;
	HANDLE  hMac = NULL;

	BYTE    byInData[256] = {0};
	BYTE    byMacData[256] = {0};

	ULONG   ulInputLen = 256;
	ULONG   ulMacDataLen = 256;

	BLOCKCIPHERPARAM pMacParam;
	UINT8	key[16] = {0xD9,0x45,0xFA,0x61,0x4A,0x25,0xFF,0xA3,0xCC,0x03,0x74,0x50,0xE2,0xA7,0x18,0xF8};

	for (int i = 0; i < ulInputLen; i++)
	{
		byInData[i] = i;
	}

	ulRslt = m_pGmDll->SKF_SetSymmKey(m_hDev, key, SGD_SM4_ECB, &hKey);
	ERROR_THROW(ulRslt);

	memset(&pMacParam, 0, sizeof(pMacParam));
	ulRslt = m_pGmDll->SKF_MacInit(hKey, &pMacParam, &hMac);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_Mac(hMac, byInData, ulInputLen, byMacData, &ulMacDataLen);
	ERROR_THROW(ulRslt);

	printf("\nMac Data successful:\n");
	printf("Mac Data:\n");
	for (int i = 0; i < ulMacDataLen; i++)
	{
		printf("0x%02x ", byMacData[i]);
	}

	printf("\n\nMac Data successful !!!\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_GroupMacData()
{
	ULONG	ulRslt = 0;

	HANDLE	hKey = NULL;
	HANDLE  hMac = NULL;

	BYTE    byInData[4096] = {0};
	BYTE    byMacData[256] = {0};
	BYTE	*pbMacData_ptr = byMacData;

	ULONG   ulInputLen = 4096;
	ULONG   ulMacDataLen = 256;
	ULONG   nMacDataLen = 0;

	BLOCKCIPHERPARAM pMacParam;
	UINT8	key[16] = {0xD9,0x45,0xFA,0x61,0x4A,0x25,0xFF,0xA3,0xCC,0x03,0x74,0x50,0xE2,0xA7,0x18,0xF8};

	long	nCount = ulInputLen / DECPRY_DATA_SIZE;
	long	nLast = ulInputLen % DECPRY_DATA_SIZE;
	long	offset = 0;

	int		index = 0;

	for (int i = 0; i < ulInputLen; i++)
	{
		byInData[i] = i;
	}

	ulRslt = m_pGmDll->SKF_SetSymmKey(m_hDev, key, SGD_SM4_ECB, &hKey);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_LockDev(m_hDev, 0xFFFFFFFF);
	ERROR_THROW(ulRslt);

	memset(&pMacParam, 0, sizeof(pMacParam));
	ulRslt = m_pGmDll->SKF_MacInit(hKey, &pMacParam, &hMac);
	ERROR_THROW(ulRslt);

	for (index = 0; index < nCount; index++)
	{
		ulRslt = m_pGmDll->SKF_MacUpdate(hMac, byInData + offset, DECPRY_DATA_SIZE);
		ERROR_THROW(ulRslt);

		offset += DECPRY_DATA_SIZE;
	}

	if (nLast > 0)
	{
		ulRslt = m_pGmDll->SKF_MacUpdate(hMac, byInData + offset, DECPRY_DATA_SIZE);
		ERROR_THROW(ulRslt);
	}

	ulRslt = m_pGmDll->SKF_MacFinal(hMac, byMacData, &ulMacDataLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_UnlockDev(m_hDev);
	ERROR_THROW(ulRslt);
	
	printf("\n\nMac Data:\n");
	for (int i = 0; i < ulMacDataLen; i++)
	{
		printf("0x%02x ", byMacData[i]);
	}

	printf("\n\nGroup Mac Data successful:\n");
END_OF_FUN:
	return ulRslt;
}

ULONG CSKFAPI::GM_ECCKeyAgreement()
{
	ULONG	ulRslt = 0;

	char    szSendContName[256] = {0};
	char    szRecvContName[256] = {0};

	BYTE    bSendID[18] = "1234567812345678";
	BYTE	bRecvID[18] = "8765432187654321";
	BYTE	iv[16] = {0};
	BYTE    byInData[32] = {0};
	BYTE    byEnCryptData[1024] = {0};
	BYTE    byDeCryptData[1024] = {0};

	ULONG   ulEnCryptLen = 1024;
	ULONG   ulDeCryptLen = 1024;
	ULONG   ulInputLen = 32;
	ULONG   ulSendIdLen = sizeof(bSendID);
	ULONG	ulRecvIdLen = sizeof(bRecvID);
	
	HANDLE  hSendCont = NULL;
	HANDLE  hRecvCont = NULL;
	HANDLE  hKeyAgreement = NULL;
	HANDLE  hSendKey = NULL;
	HANDLE  hRecvKey = NULL;

	ECCPUBLICKEYBLOB sendTmpEccPub = {0};
	ECCPUBLICKEYBLOB recvTmpEccPub = {0};
	ECCPUBLICKEYBLOB sendBlob = {0};
	ECCPUBLICKEYBLOB recvBlob = {0};

	BLOCKCIPHERPARAM bp = {0};

	printf("Please enter the name of the send container: \n");
	cin >> szSendContName;

	ulRslt = m_pGmDll->SKF_OpenContainer(m_hApp, szSendContName, &hSendCont);
	if (ulRslt != SAR_OK)
	{
		if (ulRslt == SAR_CONTAINER_NOT_FOUND)
		{
			ulRslt = m_pGmDll->SKF_CreateContainer(m_hApp, szSendContName, &hSendCont);
			ERROR_THROW(ulRslt);
		}
	}

	ulRslt = m_pGmDll->SKF_GenECCKeyPair(hSendCont, SGD_SM2_1, &sendBlob);
	ERROR_THROW(ulRslt);

	printf("Please enter the name of the recv container: \n");
	cin >> szRecvContName;

	ulRslt = m_pGmDll->SKF_OpenContainer(m_hApp, szRecvContName, &hRecvCont);
	if (ulRslt != SAR_OK)
	{
		if (ulRslt == SAR_CONTAINER_NOT_FOUND)
		{
			ulRslt = m_pGmDll->SKF_CreateContainer(m_hApp, szRecvContName, &hRecvCont);
			ERROR_THROW(ulRslt);
		}
	}

	ulRslt = m_pGmDll->SKF_GenECCKeyPair(hRecvCont, SGD_SM2_1, &recvBlob);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_GenerateAgreementDataWithECC(hSendCont, SGD_SM1_ECB, &sendTmpEccPub, bSendID, ulSendIdLen, &hKeyAgreement);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_GenerateAgreementDataAndKeyWithECC(hRecvCont, SGD_SM1_ECB, &sendBlob, &sendTmpEccPub, &recvTmpEccPub, bRecvID, ulRecvIdLen, bSendID, ulSendIdLen, &hRecvKey);
	ERROR_THROW(ulRslt);


	ulRslt = m_pGmDll->SKF_GenerateKeyWithECC(hKeyAgreement, &recvBlob, &recvTmpEccPub, bRecvID, ulRecvIdLen, &hSendKey);
	ERROR_THROW(ulRslt);

	for (int i = 0; i < ulInputLen; i++)
	{
		byInData[i] = i;
	}
	
	ulRslt = m_pGmDll->SKF_EncryptInit(hSendKey, bp);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_Encrypt(hSendKey, byInData, ulInputLen, byEnCryptData, &ulEnCryptLen);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_DecryptInit(hRecvKey, bp);
	ERROR_THROW(ulRslt);

	ulRslt = m_pGmDll->SKF_Decrypt(hRecvKey, byEnCryptData, ulEnCryptLen, byDeCryptData, &ulDeCryptLen);
	ERROR_THROW(ulRslt);

	if (memcmp(byInData, byDeCryptData, ulInputLen) == 0)
	{
		printf("Key agreement successful!!!");
	}

END_OF_FUN:
	return ulRslt;
}