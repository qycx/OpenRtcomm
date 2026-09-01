

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu Oct 12 18:34:23 2023
 */
/* Compiler settings for PNXClient.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __PNXClient_i_h__
#define __PNXClient_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPNXDataTrans_FWD_DEFINED__
#define __IPNXDataTrans_FWD_DEFINED__
typedef interface IPNXDataTrans IPNXDataTrans;
#endif 	/* __IPNXDataTrans_FWD_DEFINED__ */


#ifndef __IGWClientTK_FWD_DEFINED__
#define __IGWClientTK_FWD_DEFINED__
typedef interface IGWClientTK IGWClientTK;
#endif 	/* __IGWClientTK_FWD_DEFINED__ */


#ifndef __IGWClient_FWD_DEFINED__
#define __IGWClient_FWD_DEFINED__
typedef interface IGWClient IGWClient;
#endif 	/* __IGWClient_FWD_DEFINED__ */


#ifndef __PNXDataTrans_FWD_DEFINED__
#define __PNXDataTrans_FWD_DEFINED__

#ifdef __cplusplus
typedef class PNXDataTrans PNXDataTrans;
#else
typedef struct PNXDataTrans PNXDataTrans;
#endif /* __cplusplus */

#endif 	/* __PNXDataTrans_FWD_DEFINED__ */


#ifndef __GWClientTK_FWD_DEFINED__
#define __GWClientTK_FWD_DEFINED__

#ifdef __cplusplus
typedef class GWClientTK GWClientTK;
#else
typedef struct GWClientTK GWClientTK;
#endif /* __cplusplus */

#endif 	/* __GWClientTK_FWD_DEFINED__ */


#ifndef __GWClient_FWD_DEFINED__
#define __GWClient_FWD_DEFINED__

#ifdef __cplusplus
typedef class GWClient GWClient;
#else
typedef struct GWClient GWClient;
#endif /* __cplusplus */

#endif 	/* __GWClient_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IPNXDataTrans_INTERFACE_DEFINED__
#define __IPNXDataTrans_INTERFACE_DEFINED__

/* interface IPNXDataTrans */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPNXDataTrans;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DAC3A59C-8541-400D-91B9-2FEF97E5BAA0")
    IPNXDataTrans : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetClientVersion( 
            /* [retval][out] */ BSTR *bstrClientVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetupClient( 
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrHashValue,
            /* [in] */ BOOL bSync,
            /* [in] */ BOOL bOnlySSO,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFinger( 
            /* [in] */ ULONG dwSign,
            /* [in] */ BSTR bstrGateWayIP,
            /* [retval][out] */ BSTR *bstrFinger) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolicy( 
            /* [in] */ BSTR bstrProxyPolicy,
            /* [in] */ BSTR bstrSSOPolicy,
            /* [in] */ BSTR bstrGatewayAddress,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAuthToken( 
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrXmlData,
            /* [retval][out] */ BSTR *bstrInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NavigateURL( 
            /* [in] */ BSTR strUrl,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecuteCS( 
            /* [in] */ BSTR bstrGatewayAddr,
            /* [in] */ BSTR bstrAppFlag,
            /* [in] */ BSTR bstrAppPath,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUpdatePolicy( 
            /* [in] */ BSTR bstrGatewayAddress,
            /* [in] */ SHORT nGatewayPort,
            /* [in] */ BSTR bstrUserToken,
            /* [in] */ ULONG ulUpdateDelay,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetClientIP( 
            /* [in] */ BSTR ServerIP,
            /* [retval][out] */ BSTR *RetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GWLogout( 
            /* [in] */ BSTR bstrServerIP,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunSetup( 
            /* [in] */ LONG lRunType,
            /* [in] */ BOOL bIsOnlySSO,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDownloadProgress( 
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsInstallComplete( 
            /* [retval][out] */ BOOL *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ BSTR bstrAlgType,
            /* [in] */ BSTR bstrAuxParam,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDigestAlg( 
            /* [in] */ BSTR bstrDigestAlg,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetChooseSingleCert( 
            /* [in] */ ULONG isChoose,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddFilter( 
            /* [in] */ ULONG ulType,
            /* [in] */ BSTR bstrValue,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearFilter( 
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE P1Sign( 
            /* [in] */ BSTR bstrValueBase64,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE P1SignString( 
            /* [in] */ BSTR bstrValue,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE P7Sign( 
            /* [in] */ BSTR bstrValueBase64,
            /* [in] */ VARIANT_BOOL isDetach,
            /* [in] */ VARIANT_BOOL isIncludeCert,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE P7SignString( 
            /* [in] */ BSTR bstrValue,
            /* [in] */ VARIANT_BOOL isDetach,
            /* [in] */ VARIANT_BOOL isIncludeCert,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Finalize( 
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSignVersion( 
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSignCert( 
            /* [retval][out] */ BSTR *RetCert) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastError( 
            /* [retval][out] */ ULONG *RetLong) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastErrorMessage( 
            /* [retval][out] */ BSTR *RetStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DestoryAuth( 
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSignCertType( 
            /* [retval][out] */ BSTR *RetCertType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSignHash( 
            /* [retval][out] */ BSTR *RetSignHash) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallQueueEnable( 
            /* [in] */ BOOL bCallQueueEnable,
            /* [in] */ BOOL bHeadInfoEnable,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallQueueClear( 
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallQueueGet( 
            /* [retval][out] */ BSTR *bstrRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoClientSecurityCheck( 
            /* [in] */ BSTR bstrGatewayAddr,
            /* [in] */ SHORT shPort,
            /* [in] */ BSTR bstrSecurityPolicys,
            /* [retval][out] */ BOOL *RetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProtocolVersion( 
            /* [retval][out] */ BSTR *bstrProtocolVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangePinCode( 
            /* [in] */ BSTR bstrCertSn,
            /* [in] */ LONG pinCodeType,
            /* [in] */ BSTR bstrCurPinCode,
            /* [in] */ BSTR bstrNewPinCode,
            /* [retval][out] */ LONG *pRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitSetPolicyFinish( 
            /* [in] */ BSTR bstrGatewayAddress,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSessionToken( 
            /* [in] */ BSTR bstrGWAddress,
            /* [retval][out] */ BSTR *bstrToken) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVersion( 
            /* [retval][out] */ BSTR *bstrRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLanguage( 
            /* [in] */ BSTR bstrLanguage,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAttribute( 
            /* [in] */ BSTR gwip,
            /* [in] */ BSTR appflag,
            /* [in] */ BSTR attributename,
            /* [retval][out] */ BSTR *attributevalue) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetParentWindow( 
            /* [in] */ ULONG ulHwnd,
            /* [retval][out] */ LONG *lRetval) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPinCode( 
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPolicyByPID( 
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrProxyPolicy,
            /* [in] */ BSTR bstrSSOPolicy,
            /* [in] */ BSTR bstrGatewayAddress,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSessionTokenByPID( 
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrGWAddress,
            /* [retval][out] */ BSTR *bstrToken) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetForcePinDialog( 
            /* [in] */ ULONG isForcePinDialog,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MessageAuth( 
            /* [in] */ BSTR bstrGatewayAddress,
            /* [in] */ BSTR bstrAttributeName,
            /* [in] */ BSTR bstrAppID,
            /* [retval][out] */ BSTR *bstrAttributeValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPhoto( 
            /* [in] */ BSTR bstrSvrIP,
            /* [in] */ USHORT usSvrPort,
            /* [in] */ BSTR bstrID,
            /* [retval][out] */ BSTR *bstrBase64) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCertList( 
            /* [retval][out] */ BSTR *pbstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE P1SignWithPin( 
            /* [in] */ BSTR bstrSN,
            /* [in] */ BSTR bstrPIN,
            /* [in] */ BSTR bstrOrg,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearFilterEx( 
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSessionToken( 
            /* [in] */ BSTR bstrGwAddr,
            /* [in] */ BSTR bstrToken,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSessionTokenByPID( 
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrGwAddr,
            /* [in] */ BSTR bstrToken,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GWLogoutByPID( 
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrGatewayAddress,
            /* [retval][out] */ LONG *lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE P1SignAndGetPubKey( 
            /* [in] */ BSTR bstrSrcData,
            /* [in] */ BSTR bstrKeyDriver,
            /* [in] */ BSTR bstrUserPin,
            /* [in] */ int nType,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSessionTokenEx( 
            /* [in] */ BSTR bstrGWAddress,
            /* [in] */ USHORT usPort,
            /* [retval][out] */ BSTR *bstrToken) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSessionTokenExByPID( 
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrGWAddress,
            /* [in] */ USHORT usPort,
            /* [retval][out] */ BSTR *bstrToken) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_CheckCertStatus( 
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_GetDeviceInfo( 
            /* [in] */ BSTR deviceFingerRule,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_GetCertManufactureInfo( 
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_UpdateCertManufactureInfo( 
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_ImportCert( 
            /* [in] */ BSTR b64Cert,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_UpdateCert( 
            /* [in] */ BSTR b64Cert,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_GetSignInfo( 
            /* [in] */ BSTR original,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_SetDeviceID( 
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_GetDeviceID( 
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_CheckCertStatusEx( 
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_GetDeviceInfoEx( 
            /* [in] */ BSTR deviceFingerRule,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_GetCertManufactureInfoEx( 
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_UpdateCertManufactureInfoEx( 
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_ImportCertEx( 
            /* [in] */ BSTR b64Cert,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_UpdateCertEx( 
            /* [in] */ BSTR b64Cert,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_GetSignInfoEx( 
            /* [in] */ BSTR original,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_SetDeviceIDEx( 
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CM_GetDeviceIDEx( 
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAppToken( 
            /* [in] */ BSTR serverIP,
            /* [in] */ BSTR userToken,
            /* [in] */ BSTR appId,
            /* [retval][out] */ BSTR *csToken) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAppToken( 
            /* [in] */ BSTR serverIP,
            /* [in] */ BSTR appId,
            /* [in] */ BSTR appToken,
            /* [in] */ BSTR bstrExpTime,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCertLists( 
            /* [retval][out] */ BSTR *pbstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSDPInfo( 
            BSTR sdpInfo,
            /* [retval][out] */ BSTR *bstrResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTokensByURL( 
            /* [in] */ BSTR appUrl,
            /* [retval][out] */ BSTR *bstrToken) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckKeyExist( 
            /* [in] */ ULONG ulType,
            /* [retval][out] */ LONG *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE P7SignWithPin( 
            /* [in] */ BSTR bstrSN,
            /* [in] */ BSTR bstrPIN,
            /* [in] */ BSTR bstrValueBase64,
            /* [in] */ VARIANT_BOOL isDetach,
            /* [in] */ VARIANT_BOOL isIncludeCert,
            /* [retval][out] */ BSTR *Result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPNXDataTransVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPNXDataTrans * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPNXDataTrans * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPNXDataTrans * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPNXDataTrans * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPNXDataTrans * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPNXDataTrans * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPNXDataTrans * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetClientVersion )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *bstrClientVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetupClient )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrURL,
            /* [in] */ BSTR bstrHashValue,
            /* [in] */ BOOL bSync,
            /* [in] */ BOOL bOnlySSO,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFinger )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG dwSign,
            /* [in] */ BSTR bstrGateWayIP,
            /* [retval][out] */ BSTR *bstrFinger);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolicy )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrProxyPolicy,
            /* [in] */ BSTR bstrSSOPolicy,
            /* [in] */ BSTR bstrGatewayAddress,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAuthToken )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrFileName,
            /* [in] */ BSTR bstrXmlData,
            /* [retval][out] */ BSTR *bstrInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NavigateURL )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR strUrl,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExecuteCS )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrGatewayAddr,
            /* [in] */ BSTR bstrAppFlag,
            /* [in] */ BSTR bstrAppPath,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUpdatePolicy )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrGatewayAddress,
            /* [in] */ SHORT nGatewayPort,
            /* [in] */ BSTR bstrUserToken,
            /* [in] */ ULONG ulUpdateDelay,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetClientIP )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR ServerIP,
            /* [retval][out] */ BSTR *RetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GWLogout )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrServerIP,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RunSetup )( 
            IPNXDataTrans * This,
            /* [in] */ LONG lRunType,
            /* [in] */ BOOL bIsOnlySSO,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDownloadProgress )( 
            IPNXDataTrans * This,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsInstallComplete )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BOOL *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrAlgType,
            /* [in] */ BSTR bstrAuxParam,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDigestAlg )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrDigestAlg,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetChooseSingleCert )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG isChoose,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddFilter )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG ulType,
            /* [in] */ BSTR bstrValue,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearFilter )( 
            IPNXDataTrans * This,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *P1Sign )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrValueBase64,
            /* [retval][out] */ BSTR *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *P1SignString )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrValue,
            /* [retval][out] */ BSTR *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *P7Sign )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrValueBase64,
            /* [in] */ VARIANT_BOOL isDetach,
            /* [in] */ VARIANT_BOOL isIncludeCert,
            /* [retval][out] */ BSTR *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *P7SignString )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrValue,
            /* [in] */ VARIANT_BOOL isDetach,
            /* [in] */ VARIANT_BOOL isIncludeCert,
            /* [retval][out] */ BSTR *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Finalize )( 
            IPNXDataTrans * This,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSignVersion )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSignCert )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *RetCert);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLastError )( 
            IPNXDataTrans * This,
            /* [retval][out] */ ULONG *RetLong);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLastErrorMessage )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *RetStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DestoryAuth )( 
            IPNXDataTrans * This,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSignCertType )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *RetCertType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSignHash )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *RetSignHash);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CallQueueEnable )( 
            IPNXDataTrans * This,
            /* [in] */ BOOL bCallQueueEnable,
            /* [in] */ BOOL bHeadInfoEnable,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CallQueueClear )( 
            IPNXDataTrans * This,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CallQueueGet )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *bstrRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoClientSecurityCheck )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrGatewayAddr,
            /* [in] */ SHORT shPort,
            /* [in] */ BSTR bstrSecurityPolicys,
            /* [retval][out] */ BOOL *RetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetProtocolVersion )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *bstrProtocolVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangePinCode )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrCertSn,
            /* [in] */ LONG pinCodeType,
            /* [in] */ BSTR bstrCurPinCode,
            /* [in] */ BSTR bstrNewPinCode,
            /* [retval][out] */ LONG *pRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitSetPolicyFinish )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrGatewayAddress,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSessionToken )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrGWAddress,
            /* [retval][out] */ BSTR *bstrToken);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVersion )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *bstrRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLanguage )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrLanguage,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAttribute )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR gwip,
            /* [in] */ BSTR appflag,
            /* [in] */ BSTR attributename,
            /* [retval][out] */ BSTR *attributevalue);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetParentWindow )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG ulHwnd,
            /* [retval][out] */ LONG *lRetval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPinCode )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPolicyByPID )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrProxyPolicy,
            /* [in] */ BSTR bstrSSOPolicy,
            /* [in] */ BSTR bstrGatewayAddress,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSessionTokenByPID )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrGWAddress,
            /* [retval][out] */ BSTR *bstrToken);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetForcePinDialog )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG isForcePinDialog,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MessageAuth )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrGatewayAddress,
            /* [in] */ BSTR bstrAttributeName,
            /* [in] */ BSTR bstrAppID,
            /* [retval][out] */ BSTR *bstrAttributeValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPhoto )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrSvrIP,
            /* [in] */ USHORT usSvrPort,
            /* [in] */ BSTR bstrID,
            /* [retval][out] */ BSTR *bstrBase64);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCertList )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *pbstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *P1SignWithPin )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrSN,
            /* [in] */ BSTR bstrPIN,
            /* [in] */ BSTR bstrOrg,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearFilterEx )( 
            IPNXDataTrans * This,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSessionToken )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrGwAddr,
            /* [in] */ BSTR bstrToken,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSessionTokenByPID )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrGwAddr,
            /* [in] */ BSTR bstrToken,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GWLogoutByPID )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrGatewayAddress,
            /* [retval][out] */ LONG *lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *P1SignAndGetPubKey )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrSrcData,
            /* [in] */ BSTR bstrKeyDriver,
            /* [in] */ BSTR bstrUserPin,
            /* [in] */ int nType,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSessionTokenEx )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrGWAddress,
            /* [in] */ USHORT usPort,
            /* [retval][out] */ BSTR *bstrToken);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetSessionTokenExByPID )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG ulPID,
            /* [in] */ BSTR bstrGWAddress,
            /* [in] */ USHORT usPort,
            /* [retval][out] */ BSTR *bstrToken);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_CheckCertStatus )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_GetDeviceInfo )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR deviceFingerRule,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_GetCertManufactureInfo )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_UpdateCertManufactureInfo )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_ImportCert )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR b64Cert,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_UpdateCert )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR b64Cert,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_GetSignInfo )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR original,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_SetDeviceID )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_GetDeviceID )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_CheckCertStatusEx )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_GetDeviceInfoEx )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR deviceFingerRule,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_GetCertManufactureInfoEx )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_UpdateCertManufactureInfoEx )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_ImportCertEx )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR b64Cert,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_UpdateCertEx )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR b64Cert,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_GetSignInfoEx )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR original,
            /* [in] */ BSTR serverIP,
            /* [in] */ USHORT serverPort,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_SetDeviceIDEx )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR deviceId,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CM_GetDeviceIDEx )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAppToken )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR serverIP,
            /* [in] */ BSTR userToken,
            /* [in] */ BSTR appId,
            /* [retval][out] */ BSTR *csToken);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAppToken )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR serverIP,
            /* [in] */ BSTR appId,
            /* [in] */ BSTR appToken,
            /* [in] */ BSTR bstrExpTime,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCertLists )( 
            IPNXDataTrans * This,
            /* [retval][out] */ BSTR *pbstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSDPInfo )( 
            IPNXDataTrans * This,
            BSTR sdpInfo,
            /* [retval][out] */ BSTR *bstrResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTokensByURL )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR appUrl,
            /* [retval][out] */ BSTR *bstrToken);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CheckKeyExist )( 
            IPNXDataTrans * This,
            /* [in] */ ULONG ulType,
            /* [retval][out] */ LONG *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *P7SignWithPin )( 
            IPNXDataTrans * This,
            /* [in] */ BSTR bstrSN,
            /* [in] */ BSTR bstrPIN,
            /* [in] */ BSTR bstrValueBase64,
            /* [in] */ VARIANT_BOOL isDetach,
            /* [in] */ VARIANT_BOOL isIncludeCert,
            /* [retval][out] */ BSTR *Result);
        
        END_INTERFACE
    } IPNXDataTransVtbl;

    interface IPNXDataTrans
    {
        CONST_VTBL struct IPNXDataTransVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPNXDataTrans_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPNXDataTrans_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPNXDataTrans_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPNXDataTrans_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPNXDataTrans_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPNXDataTrans_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPNXDataTrans_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPNXDataTrans_GetClientVersion(This,bstrClientVersion)	\
    ( (This)->lpVtbl -> GetClientVersion(This,bstrClientVersion) ) 

#define IPNXDataTrans_SetupClient(This,bstrURL,bstrHashValue,bSync,bOnlySSO,lRetVal)	\
    ( (This)->lpVtbl -> SetupClient(This,bstrURL,bstrHashValue,bSync,bOnlySSO,lRetVal) ) 

#define IPNXDataTrans_GetFinger(This,dwSign,bstrGateWayIP,bstrFinger)	\
    ( (This)->lpVtbl -> GetFinger(This,dwSign,bstrGateWayIP,bstrFinger) ) 

#define IPNXDataTrans_SetPolicy(This,bstrProxyPolicy,bstrSSOPolicy,bstrGatewayAddress,lRetVal)	\
    ( (This)->lpVtbl -> SetPolicy(This,bstrProxyPolicy,bstrSSOPolicy,bstrGatewayAddress,lRetVal) ) 

#define IPNXDataTrans_GetAuthToken(This,bstrFileName,bstrXmlData,bstrInfo)	\
    ( (This)->lpVtbl -> GetAuthToken(This,bstrFileName,bstrXmlData,bstrInfo) ) 

#define IPNXDataTrans_NavigateURL(This,strUrl,lRetVal)	\
    ( (This)->lpVtbl -> NavigateURL(This,strUrl,lRetVal) ) 

#define IPNXDataTrans_ExecuteCS(This,bstrGatewayAddr,bstrAppFlag,bstrAppPath,lRetVal)	\
    ( (This)->lpVtbl -> ExecuteCS(This,bstrGatewayAddr,bstrAppFlag,bstrAppPath,lRetVal) ) 

#define IPNXDataTrans_SetUpdatePolicy(This,bstrGatewayAddress,nGatewayPort,bstrUserToken,ulUpdateDelay,lRetVal)	\
    ( (This)->lpVtbl -> SetUpdatePolicy(This,bstrGatewayAddress,nGatewayPort,bstrUserToken,ulUpdateDelay,lRetVal) ) 

#define IPNXDataTrans_GetClientIP(This,ServerIP,RetVal)	\
    ( (This)->lpVtbl -> GetClientIP(This,ServerIP,RetVal) ) 

#define IPNXDataTrans_GWLogout(This,bstrServerIP,lRetVal)	\
    ( (This)->lpVtbl -> GWLogout(This,bstrServerIP,lRetVal) ) 

#define IPNXDataTrans_RunSetup(This,lRunType,bIsOnlySSO,lRetVal)	\
    ( (This)->lpVtbl -> RunSetup(This,lRunType,bIsOnlySSO,lRetVal) ) 

#define IPNXDataTrans_GetDownloadProgress(This,lRetVal)	\
    ( (This)->lpVtbl -> GetDownloadProgress(This,lRetVal) ) 

#define IPNXDataTrans_IsInstallComplete(This,lRetVal)	\
    ( (This)->lpVtbl -> IsInstallComplete(This,lRetVal) ) 

#define IPNXDataTrans_Initialize(This,bstrAlgType,bstrAuxParam,Result)	\
    ( (This)->lpVtbl -> Initialize(This,bstrAlgType,bstrAuxParam,Result) ) 

#define IPNXDataTrans_SetDigestAlg(This,bstrDigestAlg,Result)	\
    ( (This)->lpVtbl -> SetDigestAlg(This,bstrDigestAlg,Result) ) 

#define IPNXDataTrans_SetChooseSingleCert(This,isChoose,Result)	\
    ( (This)->lpVtbl -> SetChooseSingleCert(This,isChoose,Result) ) 

#define IPNXDataTrans_AddFilter(This,ulType,bstrValue,Result)	\
    ( (This)->lpVtbl -> AddFilter(This,ulType,bstrValue,Result) ) 

#define IPNXDataTrans_ClearFilter(This,Result)	\
    ( (This)->lpVtbl -> ClearFilter(This,Result) ) 

#define IPNXDataTrans_P1Sign(This,bstrValueBase64,Result)	\
    ( (This)->lpVtbl -> P1Sign(This,bstrValueBase64,Result) ) 

#define IPNXDataTrans_P1SignString(This,bstrValue,Result)	\
    ( (This)->lpVtbl -> P1SignString(This,bstrValue,Result) ) 

#define IPNXDataTrans_P7Sign(This,bstrValueBase64,isDetach,isIncludeCert,Result)	\
    ( (This)->lpVtbl -> P7Sign(This,bstrValueBase64,isDetach,isIncludeCert,Result) ) 

#define IPNXDataTrans_P7SignString(This,bstrValue,isDetach,isIncludeCert,Result)	\
    ( (This)->lpVtbl -> P7SignString(This,bstrValue,isDetach,isIncludeCert,Result) ) 

#define IPNXDataTrans_Finalize(This,Result)	\
    ( (This)->lpVtbl -> Finalize(This,Result) ) 

#define IPNXDataTrans_GetSignVersion(This,Result)	\
    ( (This)->lpVtbl -> GetSignVersion(This,Result) ) 

#define IPNXDataTrans_GetSignCert(This,RetCert)	\
    ( (This)->lpVtbl -> GetSignCert(This,RetCert) ) 

#define IPNXDataTrans_GetLastError(This,RetLong)	\
    ( (This)->lpVtbl -> GetLastError(This,RetLong) ) 

#define IPNXDataTrans_GetLastErrorMessage(This,RetStr)	\
    ( (This)->lpVtbl -> GetLastErrorMessage(This,RetStr) ) 

#define IPNXDataTrans_DestoryAuth(This,lRetVal)	\
    ( (This)->lpVtbl -> DestoryAuth(This,lRetVal) ) 

#define IPNXDataTrans_GetSignCertType(This,RetCertType)	\
    ( (This)->lpVtbl -> GetSignCertType(This,RetCertType) ) 

#define IPNXDataTrans_GetSignHash(This,RetSignHash)	\
    ( (This)->lpVtbl -> GetSignHash(This,RetSignHash) ) 

#define IPNXDataTrans_CallQueueEnable(This,bCallQueueEnable,bHeadInfoEnable,lRetVal)	\
    ( (This)->lpVtbl -> CallQueueEnable(This,bCallQueueEnable,bHeadInfoEnable,lRetVal) ) 

#define IPNXDataTrans_CallQueueClear(This,lRetVal)	\
    ( (This)->lpVtbl -> CallQueueClear(This,lRetVal) ) 

#define IPNXDataTrans_CallQueueGet(This,bstrRetVal)	\
    ( (This)->lpVtbl -> CallQueueGet(This,bstrRetVal) ) 

#define IPNXDataTrans_DoClientSecurityCheck(This,bstrGatewayAddr,shPort,bstrSecurityPolicys,RetVal)	\
    ( (This)->lpVtbl -> DoClientSecurityCheck(This,bstrGatewayAddr,shPort,bstrSecurityPolicys,RetVal) ) 

#define IPNXDataTrans_GetProtocolVersion(This,bstrProtocolVersion)	\
    ( (This)->lpVtbl -> GetProtocolVersion(This,bstrProtocolVersion) ) 

#define IPNXDataTrans_ChangePinCode(This,bstrCertSn,pinCodeType,bstrCurPinCode,bstrNewPinCode,pRet)	\
    ( (This)->lpVtbl -> ChangePinCode(This,bstrCertSn,pinCodeType,bstrCurPinCode,bstrNewPinCode,pRet) ) 

#define IPNXDataTrans_WaitSetPolicyFinish(This,bstrGatewayAddress,lRetVal)	\
    ( (This)->lpVtbl -> WaitSetPolicyFinish(This,bstrGatewayAddress,lRetVal) ) 

#define IPNXDataTrans_GetSessionToken(This,bstrGWAddress,bstrToken)	\
    ( (This)->lpVtbl -> GetSessionToken(This,bstrGWAddress,bstrToken) ) 

#define IPNXDataTrans_GetVersion(This,bstrRetVal)	\
    ( (This)->lpVtbl -> GetVersion(This,bstrRetVal) ) 

#define IPNXDataTrans_SetLanguage(This,bstrLanguage,Result)	\
    ( (This)->lpVtbl -> SetLanguage(This,bstrLanguage,Result) ) 

#define IPNXDataTrans_GetAttribute(This,gwip,appflag,attributename,attributevalue)	\
    ( (This)->lpVtbl -> GetAttribute(This,gwip,appflag,attributename,attributevalue) ) 

#define IPNXDataTrans_SetParentWindow(This,ulHwnd,lRetval)	\
    ( (This)->lpVtbl -> SetParentWindow(This,ulHwnd,lRetval) ) 

#define IPNXDataTrans_GetPinCode(This,Result)	\
    ( (This)->lpVtbl -> GetPinCode(This,Result) ) 

#define IPNXDataTrans_SetPolicyByPID(This,ulPID,bstrProxyPolicy,bstrSSOPolicy,bstrGatewayAddress,lRetVal)	\
    ( (This)->lpVtbl -> SetPolicyByPID(This,ulPID,bstrProxyPolicy,bstrSSOPolicy,bstrGatewayAddress,lRetVal) ) 

#define IPNXDataTrans_GetSessionTokenByPID(This,ulPID,bstrGWAddress,bstrToken)	\
    ( (This)->lpVtbl -> GetSessionTokenByPID(This,ulPID,bstrGWAddress,bstrToken) ) 

#define IPNXDataTrans_SetForcePinDialog(This,isForcePinDialog,Result)	\
    ( (This)->lpVtbl -> SetForcePinDialog(This,isForcePinDialog,Result) ) 

#define IPNXDataTrans_MessageAuth(This,bstrGatewayAddress,bstrAttributeName,bstrAppID,bstrAttributeValue)	\
    ( (This)->lpVtbl -> MessageAuth(This,bstrGatewayAddress,bstrAttributeName,bstrAppID,bstrAttributeValue) ) 

#define IPNXDataTrans_GetPhoto(This,bstrSvrIP,usSvrPort,bstrID,bstrBase64)	\
    ( (This)->lpVtbl -> GetPhoto(This,bstrSvrIP,usSvrPort,bstrID,bstrBase64) ) 

#define IPNXDataTrans_GetCertList(This,pbstrResult)	\
    ( (This)->lpVtbl -> GetCertList(This,pbstrResult) ) 

#define IPNXDataTrans_P1SignWithPin(This,bstrSN,bstrPIN,bstrOrg,bstrResult)	\
    ( (This)->lpVtbl -> P1SignWithPin(This,bstrSN,bstrPIN,bstrOrg,bstrResult) ) 

#define IPNXDataTrans_ClearFilterEx(This,Result)	\
    ( (This)->lpVtbl -> ClearFilterEx(This,Result) ) 

#define IPNXDataTrans_SetSessionToken(This,bstrGwAddr,bstrToken,Result)	\
    ( (This)->lpVtbl -> SetSessionToken(This,bstrGwAddr,bstrToken,Result) ) 

#define IPNXDataTrans_SetSessionTokenByPID(This,ulPID,bstrGwAddr,bstrToken,Result)	\
    ( (This)->lpVtbl -> SetSessionTokenByPID(This,ulPID,bstrGwAddr,bstrToken,Result) ) 

#define IPNXDataTrans_GWLogoutByPID(This,ulPID,bstrGatewayAddress,lRetVal)	\
    ( (This)->lpVtbl -> GWLogoutByPID(This,ulPID,bstrGatewayAddress,lRetVal) ) 

#define IPNXDataTrans_P1SignAndGetPubKey(This,bstrSrcData,bstrKeyDriver,bstrUserPin,nType,bstrResult)	\
    ( (This)->lpVtbl -> P1SignAndGetPubKey(This,bstrSrcData,bstrKeyDriver,bstrUserPin,nType,bstrResult) ) 

#define IPNXDataTrans_GetSessionTokenEx(This,bstrGWAddress,usPort,bstrToken)	\
    ( (This)->lpVtbl -> GetSessionTokenEx(This,bstrGWAddress,usPort,bstrToken) ) 

#define IPNXDataTrans_GetSessionTokenExByPID(This,ulPID,bstrGWAddress,usPort,bstrToken)	\
    ( (This)->lpVtbl -> GetSessionTokenExByPID(This,ulPID,bstrGWAddress,usPort,bstrToken) ) 

#define IPNXDataTrans_CM_CheckCertStatus(This,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_CheckCertStatus(This,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_GetDeviceInfo(This,deviceFingerRule,bstrResult)	\
    ( (This)->lpVtbl -> CM_GetDeviceInfo(This,deviceFingerRule,bstrResult) ) 

#define IPNXDataTrans_CM_GetCertManufactureInfo(This,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_GetCertManufactureInfo(This,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_UpdateCertManufactureInfo(This,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_UpdateCertManufactureInfo(This,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_ImportCert(This,b64Cert,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_ImportCert(This,b64Cert,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_UpdateCert(This,b64Cert,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_UpdateCert(This,b64Cert,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_GetSignInfo(This,original,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_GetSignInfo(This,original,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_SetDeviceID(This,deviceId,bstrResult)	\
    ( (This)->lpVtbl -> CM_SetDeviceID(This,deviceId,bstrResult) ) 

#define IPNXDataTrans_CM_GetDeviceID(This,bstrResult)	\
    ( (This)->lpVtbl -> CM_GetDeviceID(This,bstrResult) ) 

#define IPNXDataTrans_CM_CheckCertStatusEx(This,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_CheckCertStatusEx(This,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_GetDeviceInfoEx(This,deviceFingerRule,bstrResult)	\
    ( (This)->lpVtbl -> CM_GetDeviceInfoEx(This,deviceFingerRule,bstrResult) ) 

#define IPNXDataTrans_CM_GetCertManufactureInfoEx(This,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_GetCertManufactureInfoEx(This,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_UpdateCertManufactureInfoEx(This,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_UpdateCertManufactureInfoEx(This,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_ImportCertEx(This,b64Cert,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_ImportCertEx(This,b64Cert,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_UpdateCertEx(This,b64Cert,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_UpdateCertEx(This,b64Cert,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_GetSignInfoEx(This,original,serverIP,serverPort,bstrResult)	\
    ( (This)->lpVtbl -> CM_GetSignInfoEx(This,original,serverIP,serverPort,bstrResult) ) 

#define IPNXDataTrans_CM_SetDeviceIDEx(This,deviceId,bstrResult)	\
    ( (This)->lpVtbl -> CM_SetDeviceIDEx(This,deviceId,bstrResult) ) 

#define IPNXDataTrans_CM_GetDeviceIDEx(This,bstrResult)	\
    ( (This)->lpVtbl -> CM_GetDeviceIDEx(This,bstrResult) ) 

#define IPNXDataTrans_GetAppToken(This,serverIP,userToken,appId,csToken)	\
    ( (This)->lpVtbl -> GetAppToken(This,serverIP,userToken,appId,csToken) ) 

#define IPNXDataTrans_SetAppToken(This,serverIP,appId,appToken,bstrExpTime,Result)	\
    ( (This)->lpVtbl -> SetAppToken(This,serverIP,appId,appToken,bstrExpTime,Result) ) 

#define IPNXDataTrans_GetCertLists(This,pbstrResult)	\
    ( (This)->lpVtbl -> GetCertLists(This,pbstrResult) ) 

#define IPNXDataTrans_SetSDPInfo(This,sdpInfo,bstrResult)	\
    ( (This)->lpVtbl -> SetSDPInfo(This,sdpInfo,bstrResult) ) 

#define IPNXDataTrans_GetTokensByURL(This,appUrl,bstrToken)	\
    ( (This)->lpVtbl -> GetTokensByURL(This,appUrl,bstrToken) ) 

#define IPNXDataTrans_CheckKeyExist(This,ulType,Result)	\
    ( (This)->lpVtbl -> CheckKeyExist(This,ulType,Result) ) 

#define IPNXDataTrans_P7SignWithPin(This,bstrSN,bstrPIN,bstrValueBase64,isDetach,isIncludeCert,Result)	\
    ( (This)->lpVtbl -> P7SignWithPin(This,bstrSN,bstrPIN,bstrValueBase64,isDetach,isIncludeCert,Result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPNXDataTrans_INTERFACE_DEFINED__ */


#ifndef __IGWClientTK_INTERFACE_DEFINED__
#define __IGWClientTK_INTERFACE_DEFINED__

/* interface IGWClientTK */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGWClientTK;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4DD1C6CC-9243-426C-949F-D03FDC7D1089")
    IGWClientTK : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCert( 
            /* [in] */ BSTR bstrCertType,
            /* [in] */ BSTR bstrDN,
            /* [in] */ BSTR bstrSN,
            /* [in] */ BSTR bstrEmail,
            /* [in] */ BSTR bstrDNIssuer,
            /* [in] */ BSTR bstrCertBase64,
            /* [retval][out] */ ULONG *pRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCertChooseType( 
            /* [in] */ LONG nType,
            /* [retval][out] */ ULONG *pRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCertInfo( 
            /* [in] */ BSTR bstrCertType,
            /* [in] */ LONG lInfoType,
            /* [in] */ BSTR bstrOID,
            /* [retval][out] */ BSTR *pRetCerInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AttachSign( 
            /* [in] */ BSTR bstrDN,
            /* [in] */ const BYTE *pszSrcData,
            /* [in] */ ULONG lSrcDataLen,
            /* [retval][out] */ BSTR *pbstrSignedData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DetachSign( 
            /* [in] */ BSTR bstrDN,
            /* [in] */ const BYTE *pszSrcData,
            /* [in] */ ULONG lSrcDataLen,
            /* [retval][out] */ BSTR *pbstrSignedData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorCode( 
            /* [retval][out] */ ULONG *pRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorMessage( 
            /* [in] */ ULONG lErrorCode,
            /* [retval][out] */ BSTR *pErrorMessage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE JITGetVersion( 
            /* [retval][out] */ BSTR *pbstrVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE P1SignStr( 
            /* [in] */ BSTR bstrDN,
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR *pbstrSignedData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGWClientTKVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGWClientTK * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGWClientTK * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGWClientTK * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGWClientTK * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGWClientTK * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGWClientTK * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGWClientTK * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCert )( 
            IGWClientTK * This,
            /* [in] */ BSTR bstrCertType,
            /* [in] */ BSTR bstrDN,
            /* [in] */ BSTR bstrSN,
            /* [in] */ BSTR bstrEmail,
            /* [in] */ BSTR bstrDNIssuer,
            /* [in] */ BSTR bstrCertBase64,
            /* [retval][out] */ ULONG *pRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCertChooseType )( 
            IGWClientTK * This,
            /* [in] */ LONG nType,
            /* [retval][out] */ ULONG *pRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCertInfo )( 
            IGWClientTK * This,
            /* [in] */ BSTR bstrCertType,
            /* [in] */ LONG lInfoType,
            /* [in] */ BSTR bstrOID,
            /* [retval][out] */ BSTR *pRetCerInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AttachSign )( 
            IGWClientTK * This,
            /* [in] */ BSTR bstrDN,
            /* [in] */ const BYTE *pszSrcData,
            /* [in] */ ULONG lSrcDataLen,
            /* [retval][out] */ BSTR *pbstrSignedData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DetachSign )( 
            IGWClientTK * This,
            /* [in] */ BSTR bstrDN,
            /* [in] */ const BYTE *pszSrcData,
            /* [in] */ ULONG lSrcDataLen,
            /* [retval][out] */ BSTR *pbstrSignedData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetErrorCode )( 
            IGWClientTK * This,
            /* [retval][out] */ ULONG *pRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetErrorMessage )( 
            IGWClientTK * This,
            /* [in] */ ULONG lErrorCode,
            /* [retval][out] */ BSTR *pErrorMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *JITGetVersion )( 
            IGWClientTK * This,
            /* [retval][out] */ BSTR *pbstrVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *P1SignStr )( 
            IGWClientTK * This,
            /* [in] */ BSTR bstrDN,
            /* [in] */ BSTR bstrSrc,
            /* [retval][out] */ BSTR *pbstrSignedData);
        
        END_INTERFACE
    } IGWClientTKVtbl;

    interface IGWClientTK
    {
        CONST_VTBL struct IGWClientTKVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGWClientTK_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGWClientTK_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGWClientTK_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGWClientTK_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGWClientTK_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGWClientTK_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGWClientTK_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGWClientTK_SetCert(This,bstrCertType,bstrDN,bstrSN,bstrEmail,bstrDNIssuer,bstrCertBase64,pRetVal)	\
    ( (This)->lpVtbl -> SetCert(This,bstrCertType,bstrDN,bstrSN,bstrEmail,bstrDNIssuer,bstrCertBase64,pRetVal) ) 

#define IGWClientTK_SetCertChooseType(This,nType,pRetVal)	\
    ( (This)->lpVtbl -> SetCertChooseType(This,nType,pRetVal) ) 

#define IGWClientTK_GetCertInfo(This,bstrCertType,lInfoType,bstrOID,pRetCerInfo)	\
    ( (This)->lpVtbl -> GetCertInfo(This,bstrCertType,lInfoType,bstrOID,pRetCerInfo) ) 

#define IGWClientTK_AttachSign(This,bstrDN,pszSrcData,lSrcDataLen,pbstrSignedData)	\
    ( (This)->lpVtbl -> AttachSign(This,bstrDN,pszSrcData,lSrcDataLen,pbstrSignedData) ) 

#define IGWClientTK_DetachSign(This,bstrDN,pszSrcData,lSrcDataLen,pbstrSignedData)	\
    ( (This)->lpVtbl -> DetachSign(This,bstrDN,pszSrcData,lSrcDataLen,pbstrSignedData) ) 

#define IGWClientTK_GetErrorCode(This,pRetVal)	\
    ( (This)->lpVtbl -> GetErrorCode(This,pRetVal) ) 

#define IGWClientTK_GetErrorMessage(This,lErrorCode,pErrorMessage)	\
    ( (This)->lpVtbl -> GetErrorMessage(This,lErrorCode,pErrorMessage) ) 

#define IGWClientTK_JITGetVersion(This,pbstrVersion)	\
    ( (This)->lpVtbl -> JITGetVersion(This,pbstrVersion) ) 

#define IGWClientTK_P1SignStr(This,bstrDN,bstrSrc,pbstrSignedData)	\
    ( (This)->lpVtbl -> P1SignStr(This,bstrDN,bstrSrc,pbstrSignedData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGWClientTK_INTERFACE_DEFINED__ */


#ifndef __IGWClient_INTERFACE_DEFINED__
#define __IGWClient_INTERFACE_DEFINED__

/* interface IGWClient */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGWClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("048B8480-28E7-49F9-A5ED-C736752943D8")
    IGWClient : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GWInit( 
            BSTR bstrGWAddr,
            /* [retval][out] */ LONG *lnRetVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GWGetCertList( 
            /* [retval][out] */ BSTR *bstrCertList) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GWLogin( 
            LONG lnType,
            BSTR bstrUsr,
            BSTR bstrPwd,
            /* [retval][out] */ BSTR *bstrAppList) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GWGetLastError( 
            /* [retval][out] */ LONG *lnErrorCode) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GWGetLastErrorMsg( 
            /* [retval][out] */ BSTR *bstrErrorMsg) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GWLogout( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GWOpenPortal( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGWClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGWClient * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGWClient * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGWClient * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGWClient * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGWClient * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGWClient * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGWClient * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GWInit )( 
            IGWClient * This,
            BSTR bstrGWAddr,
            /* [retval][out] */ LONG *lnRetVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GWGetCertList )( 
            IGWClient * This,
            /* [retval][out] */ BSTR *bstrCertList);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GWLogin )( 
            IGWClient * This,
            LONG lnType,
            BSTR bstrUsr,
            BSTR bstrPwd,
            /* [retval][out] */ BSTR *bstrAppList);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GWGetLastError )( 
            IGWClient * This,
            /* [retval][out] */ LONG *lnErrorCode);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GWGetLastErrorMsg )( 
            IGWClient * This,
            /* [retval][out] */ BSTR *bstrErrorMsg);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GWLogout )( 
            IGWClient * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GWOpenPortal )( 
            IGWClient * This);
        
        END_INTERFACE
    } IGWClientVtbl;

    interface IGWClient
    {
        CONST_VTBL struct IGWClientVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGWClient_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGWClient_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGWClient_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGWClient_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGWClient_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGWClient_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGWClient_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGWClient_GWInit(This,bstrGWAddr,lnRetVal)	\
    ( (This)->lpVtbl -> GWInit(This,bstrGWAddr,lnRetVal) ) 

#define IGWClient_GWGetCertList(This,bstrCertList)	\
    ( (This)->lpVtbl -> GWGetCertList(This,bstrCertList) ) 

#define IGWClient_GWLogin(This,lnType,bstrUsr,bstrPwd,bstrAppList)	\
    ( (This)->lpVtbl -> GWLogin(This,lnType,bstrUsr,bstrPwd,bstrAppList) ) 

#define IGWClient_GWGetLastError(This,lnErrorCode)	\
    ( (This)->lpVtbl -> GWGetLastError(This,lnErrorCode) ) 

#define IGWClient_GWGetLastErrorMsg(This,bstrErrorMsg)	\
    ( (This)->lpVtbl -> GWGetLastErrorMsg(This,bstrErrorMsg) ) 

#define IGWClient_GWLogout(This)	\
    ( (This)->lpVtbl -> GWLogout(This) ) 

#define IGWClient_GWOpenPortal(This)	\
    ( (This)->lpVtbl -> GWOpenPortal(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGWClient_INTERFACE_DEFINED__ */



#ifndef __PNXClientLib_LIBRARY_DEFINED__
#define __PNXClientLib_LIBRARY_DEFINED__

/* library PNXClientLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_PNXClientLib;

EXTERN_C const CLSID CLSID_PNXDataTrans;

#ifdef __cplusplus

class DECLSPEC_UUID("9DD991F7-6FB0-4004-95A4-0A55006A8C42")
PNXDataTrans;
#endif

EXTERN_C const CLSID CLSID_GWClientTK;

#ifdef __cplusplus

class DECLSPEC_UUID("444BDD41-57B8-4907-B337-BE45E6724982")
GWClientTK;
#endif

EXTERN_C const CLSID CLSID_GWClient;

#ifdef __cplusplus

class DECLSPEC_UUID("1D507C40-9080-4241-9A3C-B2B2448714B8")
GWClient;
#endif
#endif /* __PNXClientLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


