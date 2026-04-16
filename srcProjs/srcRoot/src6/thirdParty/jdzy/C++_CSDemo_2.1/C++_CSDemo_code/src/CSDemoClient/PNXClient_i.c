

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Jan 23 18:14:05 2019
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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IPNXDataTrans,0xDAC3A59C,0x8541,0x400D,0x91,0xB9,0x2F,0xEF,0x97,0xE5,0xBA,0xA0);


MIDL_DEFINE_GUID(IID, IID_IGWClientTK,0x4DD1C6CC,0x9243,0x426C,0x94,0x9F,0xD0,0x3F,0xDC,0x7D,0x10,0x89);


MIDL_DEFINE_GUID(IID, IID_IGWClient,0x048B8480,0x28E7,0x49F9,0xA5,0xED,0xC7,0x36,0x75,0x29,0x43,0xD8);


MIDL_DEFINE_GUID(IID, LIBID_PNXClientLib,0x678B1D22,0xAFE6,0x4FE0,0x9A,0x47,0x6A,0xF4,0x5E,0xB8,0x24,0x6F);


MIDL_DEFINE_GUID(CLSID, CLSID_PNXDataTrans,0x9DD991F7,0x6FB0,0x4004,0x95,0xA4,0x0A,0x55,0x00,0x6A,0x8C,0x42);


MIDL_DEFINE_GUID(CLSID, CLSID_GWClientTK,0x444BDD41,0x57B8,0x4907,0xB3,0x37,0xBE,0x45,0xE6,0x72,0x49,0x82);


MIDL_DEFINE_GUID(CLSID, CLSID_GWClient,0x1D507C40,0x9080,0x4241,0x9A,0x3C,0xB2,0xB2,0x44,0x87,0x14,0xB8);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



