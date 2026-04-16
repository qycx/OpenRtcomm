#include "gm3000_dll.h"
#include <stdio.h>

HMODULE LoadSKFAPI(LPCTSTR lpSKFLibPath, GmDll * pGmLib)
{
	HMODULE hMod = LoadLibrary(lpSKFLibPath);
	if (!hMod)
	{
		return NULL;
	}

	//SKF API
	pGmLib->SKF_WaitForDevEvent							= (SKF_WaitForDevEventPtr)GetProcAddress(hMod, "SKF_WaitForDevEvent");
	pGmLib->SKF_CancelWaitForDevEvent					= (SKF_CancelWaitForDevEventPtr)GetProcAddress(hMod, "SKF_CancelWaitForDevEvent");
	pGmLib->SKF_EnumDev									= (SKF_EnumDevPtr)GetProcAddress(hMod, "SKF_EnumDev");
	pGmLib->SKF_ConnectDev								= (SKF_ConnectDevPtr)GetProcAddress(hMod, "SKF_ConnectDev");
	pGmLib->SKF_DisConnectDev							= (SKF_DisConnectDevPtr)GetProcAddress(hMod, "SKF_DisConnectDev");
	pGmLib->SKF_GetDevState								= (SKF_GetDevStatePtr)GetProcAddress(hMod, "SKF_GetDevState");
	pGmLib->SKF_SetLabel								= (SKF_SetLabelPtr)GetProcAddress(hMod, "SKF_SetLabel");
	pGmLib->SKF_GetDevInfo								= (SKF_GetDevInfoPtr)GetProcAddress(hMod, "SKF_GetDevInfo");
	pGmLib->SKF_LockDev									= (SKF_LockDevPtr)GetProcAddress(hMod, "SKF_LockDev");
	pGmLib->SKF_UnlockDev								= (SKF_UnlockDevPtr)GetProcAddress(hMod, "SKF_UnlockDev");
	pGmLib->SKF_ChangeDevAuthKey						= (SKF_ChangeDevAuthKeyPtr)GetProcAddress(hMod, "SKF_ChangeDevAuthKey");
	pGmLib->SKF_DevAuth									= (SKF_DevAuthPtr)GetProcAddress(hMod, "SKF_DevAuth");
	pGmLib->SKF_ChangePIN								= (SKF_ChangePINPtr)GetProcAddress(hMod, "SKF_ChangePIN");
	pGmLib->SKF_GetPINInfo								= (SKF_GetPINInfoPtr)GetProcAddress(hMod, "SKF_GetPINInfo");
	pGmLib->SKF_VerifyPIN								= (SKF_VerifyPINPtr)GetProcAddress(hMod, "SKF_VerifyPIN");
	pGmLib->SKF_UnblockPIN								= (SKF_UnblockPINPtr)GetProcAddress(hMod, "SKF_UnblockPIN");
	pGmLib->SKF_ClearSecureState						= (SKF_ClearSecureStatePtr)GetProcAddress(hMod, "SKF_ClearSecureState");
	pGmLib->SKF_CreateApplication						= (SKF_CreateApplicationPtr)GetProcAddress(hMod, "SKF_CreateApplication");
	pGmLib->SKF_EnumApplication							= (SKF_EnumApplicationPtr)GetProcAddress(hMod, "SKF_EnumApplication");
	pGmLib->SKF_DeleteApplication						= (SKF_DeleteApplicationPtr)GetProcAddress(hMod, "SKF_DeleteApplication");
	pGmLib->SKF_OpenApplication							= (SKF_OpenApplicationPtr)GetProcAddress(hMod, "SKF_OpenApplication");
	pGmLib->SKF_CloseApplication						= (SKF_CloseApplicationPtr)GetProcAddress(hMod, "SKF_CloseApplication");
	pGmLib->SKF_CreateFile								= (SKF_CreateFilePtr)GetProcAddress(hMod, "SKF_CreateFile");
	pGmLib->SKF_DeleteFile								= (SKF_DeleteFilePtr)GetProcAddress(hMod, "SKF_DeleteFile");
	pGmLib->SKF_EnumFiles								= (SKF_EnumFilesPtr)GetProcAddress(hMod, "SKF_EnumFiles");
	pGmLib->SKF_GetFileInfo								= (SKF_GetFileInfoPtr)GetProcAddress(hMod, "SKF_GetFileInfo");
	pGmLib->SKF_ReadFile								= (SKF_ReadFilePtr)GetProcAddress(hMod, "SKF_ReadFile");
	pGmLib->SKF_WriteFile								= (SKF_WriteFilePtr)GetProcAddress(hMod, "SKF_WriteFile");
	pGmLib->SKF_CreateContainer							= (SKF_CreateContainerPtr)GetProcAddress(hMod, "SKF_CreateContainer");
	pGmLib->SKF_DeleteContainer							= (SKF_DeleteContainerPtr)GetProcAddress(hMod, "SKF_DeleteContainer");
	pGmLib->SKF_OpenContainer							= (SKF_OpenContainerPtr)GetProcAddress(hMod, "SKF_OpenContainer");
	pGmLib->SKF_CloseContainer							= (SKF_CloseContainerPtr)GetProcAddress(hMod, "SKF_CloseContainer");
	pGmLib->SKF_EnumContainer							= (SKF_EnumContainerPtr)GetProcAddress(hMod, "SKF_EnumContainer");
	pGmLib->SKF_GetConProperty							= (SKF_GetConPropertyPtr)GetProcAddress(hMod, "SKF_GetConProperty");
	pGmLib->SKF_GenRandom								= (SKF_GenRandomPtr)GetProcAddress(hMod, "SKF_GenRandom");
	pGmLib->SKF_GenExtRSAKey							= (SKF_GenExtRSAKeyPtr)GetProcAddress(hMod, "SKF_GenExtRSAKey");
	pGmLib->SKF_GenRSAKeyPair							= (SKF_GenRSAKeyPairPtr)GetProcAddress(hMod, "SKF_GenRSAKeyPair");
	pGmLib->SKF_ImportRSAKeyPair						= (SKF_ImportRSAKeyPairPtr)GetProcAddress(hMod, "SKF_ImportRSAKeyPair");
	pGmLib->SKF_RSASignData								= (SKF_RSASignDataPtr)GetProcAddress(hMod, "SKF_RSASignData");
	pGmLib->SKF_RSAVerify								= (SKF_RSAVerifyPtr)GetProcAddress(hMod, "SKF_RSAVerify");
	pGmLib->SKF_RSAExportSessionKey						= (SKF_RSAExportSessionKeyPtr)GetProcAddress(hMod, "SKF_RSAExportSessionKey");
	pGmLib->SKF_ExtRSAPubKeyOperation					= (SKF_ExtRSAPubKeyOperationPtr)GetProcAddress(hMod, "SKF_ExtRSAPubKeyOperation");
	pGmLib->SKF_ExtRSAPriKeyOperation					= (SKF_ExtRSAPriKeyOperationPtr)GetProcAddress(hMod, "SKF_ExtRSAPriKeyOperation");
	pGmLib->SKF_RSADecrypt								= (SKF_RSADecryptPtr)GetProcAddress(hMod, "SKF_RSADecrypt");
	pGmLib->SKF_GenECCKeyPair							= (SKF_GenECCKeyPairPtr)GetProcAddress(hMod, "SKF_GenECCKeyPair");
	pGmLib->SKF_ImportECCKeyPair						= (SKF_ImportECCKeyPairPtr)GetProcAddress(hMod, "SKF_ImportECCKeyPair");
	pGmLib->SKF_ECCSignData								= (SKF_ECCSignDataPtr)GetProcAddress(hMod, "SKF_ECCSignData");
	pGmLib->SKF_ECCVerify								= (SKF_ECCVerifyPtr)GetProcAddress(hMod, "SKF_ECCVerify");
	pGmLib->SKF_ECCExportSessionKey						= (SKF_ECCExportSessionKeyPtr)GetProcAddress(hMod, "SKF_ECCExportSessionKey");
	pGmLib->SKF_ExtECCEncrypt							= (SKF_ExtECCEncryptPtr)GetProcAddress(hMod, "SKF_ExtECCEncrypt");
	pGmLib->SKF_ExtECCDecrypt							= (SKF_ExtECCDecryptPtr)GetProcAddress(hMod, "SKF_ExtECCDecrypt");
	pGmLib->SKF_ExtECCSign								= (SKF_ExtECCSignPtr)GetProcAddress(hMod, "SKF_ExtECCSign");
	pGmLib->SKF_ExtECCVerify							= (SKF_ExtECCVerifyPtr)GetProcAddress(hMod, "SKF_ExtECCVerify");
	pGmLib->SKF_GenerateAgreementDataWithECC			= (SKF_GenerateAgreementDataWithECCPtr)GetProcAddress(hMod, "SKF_GenerateAgreementDataWithECC");
	pGmLib->SKF_GenerateKeyWithECC						= (SKF_GenerateKeyWithECCPtr)GetProcAddress(hMod, "SKF_GenerateKeyWithECC");
	pGmLib->SKF_GenerateAgreementDataAndKeyWithECC		= (SKF_GenerateAgreementDataAndKeyWithECCPtr)GetProcAddress(hMod, "SKF_GenerateAgreementDataAndKeyWithECC");
	pGmLib->SKF_ExportPublicKey							= (SKF_ExportPublicKeyPtr)GetProcAddress(hMod, "SKF_ExportPublicKey");
	pGmLib->SKF_ImportSessionKey						= (SKF_ImportSessionKeyPtr)GetProcAddress(hMod, "SKF_ImportSessionKey");
	pGmLib->SKF_SetSymmKey								= (SKF_SetSymmKeyPtr)GetProcAddress(hMod, "SKF_SetSymmKey");
	pGmLib->SKF_EncryptInit								= (SKF_EncryptInitPtr)GetProcAddress(hMod, "SKF_EncryptInit");
	pGmLib->SKF_Encrypt									= (SKF_EncryptPtr)GetProcAddress(hMod, "SKF_Encrypt");
	pGmLib->SKF_EncryptUpdate							= (SKF_EncryptUpdatePtr)GetProcAddress(hMod, "SKF_EncryptUpdate");
	pGmLib->SKF_EncryptFinal							= (SKF_EncryptFinalPtr)GetProcAddress(hMod, "SKF_EncryptFinal");
	pGmLib->SKF_DecryptInit								= (SKF_DecryptInitPtr)GetProcAddress(hMod, "SKF_DecryptInit");
	pGmLib->SKF_Decrypt									= (SKF_DecryptPtr)GetProcAddress(hMod, "SKF_Decrypt");
	pGmLib->SKF_DecryptUpdate							= (SKF_DecryptUpdatePtr)GetProcAddress(hMod, "SKF_DecryptUpdate");
	pGmLib->SKF_DecryptFinal							= (SKF_DecryptFinalPtr)GetProcAddress(hMod, "SKF_DecryptFinal");
	pGmLib->SKF_DigestInit								= (SKF_DigestInitPtr)GetProcAddress(hMod, "SKF_DigestInit");
	pGmLib->SKF_Digest									= (SKF_DigestPtr)GetProcAddress(hMod, "SKF_Digest");
	pGmLib->SKF_DigestUpdate							= (SKF_DigestUpdatePtr)GetProcAddress(hMod, "SKF_DigestUpdate");
	pGmLib->SKF_DigestFinal								= (SKF_DigestFinalPtr)GetProcAddress(hMod, "SKF_DigestFinal");
	pGmLib->SKF_MacInit									= (SKF_MacInitPtr)GetProcAddress(hMod, "SKF_MacInit");
	pGmLib->SKF_Mac										= (SKF_MacPtr)GetProcAddress(hMod, "SKF_Mac");
	pGmLib->SKF_MacUpdate								= (SKF_MacUpdatePtr)GetProcAddress(hMod, "SKF_MacUpdate");
	pGmLib->SKF_MacFinal								= (SKF_MacFinalPtr)GetProcAddress(hMod, "SKF_MacFinal");
	pGmLib->SKF_CloseHandle								= (SKF_CloseHandlePtr)GetProcAddress(hMod, "SKF_CloseHandle");
	pGmLib->SKF_Transmit								= (SKF_TransmitPtr)GetProcAddress(hMod, "SKF_Transmit");
	pGmLib->SKF_ImportCertificate						= (SKF_ImportCertificatePtr)GetProcAddress(hMod, "SKF_ImportCertificate");
	pGmLib->SKF_ExportCertificate						= (SKF_ExportCertificatePtr)GetProcAddress(hMod, "SKF_ExportCertificate");
	pGmLib->SKF_PrvKeyDecrypt							= (SKF_PrvKeyDecryptPtr)GetProcAddress(hMod, "SKF_PrvKeyDecrypt");
	pGmLib->SKF_RSAPrvKeyDecrypt						= (SKF_RSAPrvKeyDecryptPtr)GetProcAddress(hMod, "SKF_RSAPrvKeyDecrypt");
	pGmLib->SKF_GenerateKey								= (SKF_GenerateKeyPtr)GetProcAddress(hMod,"SKF_GenerateKey");
	pGmLib->SKF_RSADecrypt                  			= (SKF_RSADecryptPtr)GetProcAddress(hMod,"SKF_RSADecryptPtr");
	pGmLib->SKF_GenRemoteUnblockRequest     			= (SKF_GenRemoteUnblockRequestPtr)GetProcAddress(hMod,"SKF_GenRemoteUnblockRequest");
	pGmLib->SKF_RemoteUnblockPIN						= (SKF_RemoteUnblockPINPtr)GetProcAddress(hMod,"SKF_RemoteUnblockPIN");
	pGmLib->SKF_GetContainerType						= (SKF_GetContainerTypePtr)GetProcAddress(hMod,"SKF_GetContainerType");
	pGmLib->SKF_ExtRSAEncrypt							= (SKF_ExtRSAEncryptPtr)GetProcAddress(hMod,"SKF_ExtRSAEncrypt");

	return hMod;
}

void PrintByteStr( BYTE *str )
{
	for (int i = 0; i < strlen((char*)str); i++)
	{
		printf("%hhu", str[i]);
	}
	printf("\n");
}
