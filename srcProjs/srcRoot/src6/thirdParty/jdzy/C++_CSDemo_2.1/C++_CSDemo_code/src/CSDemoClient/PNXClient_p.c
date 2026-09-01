

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "PNXClient_i.h"

#define TYPE_FORMAT_STRING_SIZE   65                                
#define PROC_FORMAT_STRING_SIZE   2773                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _PNXClient_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } PNXClient_MIDL_TYPE_FORMAT_STRING;

typedef struct _PNXClient_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } PNXClient_MIDL_PROC_FORMAT_STRING;

typedef struct _PNXClient_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } PNXClient_MIDL_EXPR_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const PNXClient_MIDL_TYPE_FORMAT_STRING PNXClient__MIDL_TypeFormatString;
extern const PNXClient_MIDL_PROC_FORMAT_STRING PNXClient__MIDL_ProcFormatString;
extern const PNXClient_MIDL_EXPR_FORMAT_STRING PNXClient__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPNXDataTrans_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPNXDataTrans_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGWClientTK_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGWClientTK_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGWClient_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGWClient_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const PNXClient_MIDL_PROC_FORMAT_STRING PNXClient__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure GetClientVersion */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrClientVersion */

/* 24 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetupClient */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 46 */	NdrFcShort( 0x10 ),	/* 16 */
/* 48 */	NdrFcShort( 0x24 ),	/* 36 */
/* 50 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 52 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x6 ),	/* 6 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrURL */

/* 60 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrHashValue */

/* 66 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bSync */

/* 72 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 74 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 76 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bOnlySSO */

/* 78 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 80 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lRetVal */

/* 84 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 86 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 88 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 90 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 92 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 94 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetFinger */

/* 96 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 98 */	NdrFcLong( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0x9 ),	/* 9 */
/* 104 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 106 */	NdrFcShort( 0x8 ),	/* 8 */
/* 108 */	NdrFcShort( 0x8 ),	/* 8 */
/* 110 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 112 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 114 */	NdrFcShort( 0x1 ),	/* 1 */
/* 116 */	NdrFcShort( 0x5 ),	/* 5 */
/* 118 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter dwSign */

/* 120 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 122 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrGateWayIP */

/* 126 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 128 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 130 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrFinger */

/* 132 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 134 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 136 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 138 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 140 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetPolicy */

/* 144 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 146 */	NdrFcLong( 0x0 ),	/* 0 */
/* 150 */	NdrFcShort( 0xa ),	/* 10 */
/* 152 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 156 */	NdrFcShort( 0x24 ),	/* 36 */
/* 158 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 160 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0xf ),	/* 15 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrProxyPolicy */

/* 168 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 170 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 172 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrSSOPolicy */

/* 174 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 176 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 178 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrGatewayAddress */

/* 180 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 182 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 184 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter lRetVal */

/* 186 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 188 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 192 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 194 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 196 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetAuthToken */

/* 198 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 200 */	NdrFcLong( 0x0 ),	/* 0 */
/* 204 */	NdrFcShort( 0xb ),	/* 11 */
/* 206 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 210 */	NdrFcShort( 0x8 ),	/* 8 */
/* 212 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 214 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 216 */	NdrFcShort( 0x1 ),	/* 1 */
/* 218 */	NdrFcShort( 0xe ),	/* 14 */
/* 220 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrFileName */

/* 222 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 224 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 226 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrXmlData */

/* 228 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 230 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 232 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrInfo */

/* 234 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 236 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 238 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 240 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 242 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 244 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NavigateURL */

/* 246 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 248 */	NdrFcLong( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0xc ),	/* 12 */
/* 254 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 258 */	NdrFcShort( 0x24 ),	/* 36 */
/* 260 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 262 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 264 */	NdrFcShort( 0x0 ),	/* 0 */
/* 266 */	NdrFcShort( 0x1 ),	/* 1 */
/* 268 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter strUrl */

/* 270 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 272 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 274 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter lRetVal */

/* 276 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 278 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 280 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 282 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 284 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 286 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExecuteCS */

/* 288 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 290 */	NdrFcLong( 0x0 ),	/* 0 */
/* 294 */	NdrFcShort( 0xd ),	/* 13 */
/* 296 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 298 */	NdrFcShort( 0x0 ),	/* 0 */
/* 300 */	NdrFcShort( 0x24 ),	/* 36 */
/* 302 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 304 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 308 */	NdrFcShort( 0x1b ),	/* 27 */
/* 310 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGatewayAddr */

/* 312 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 314 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 316 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrAppFlag */

/* 318 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 320 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 322 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrAppPath */

/* 324 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 326 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 328 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter lRetVal */

/* 330 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 332 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 334 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 338 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetUpdatePolicy */

/* 342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0xe ),	/* 14 */
/* 350 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 352 */	NdrFcShort( 0xe ),	/* 14 */
/* 354 */	NdrFcShort( 0x24 ),	/* 36 */
/* 356 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 358 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x12 ),	/* 18 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGatewayAddress */

/* 366 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 368 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 370 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter nGatewayPort */

/* 372 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 374 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 376 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter bstrUserToken */

/* 378 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 380 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 382 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter ulUpdateDelay */

/* 384 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 386 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lRetVal */

/* 390 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 392 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 394 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 398 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetClientIP */

/* 402 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0xf ),	/* 15 */
/* 410 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 416 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 418 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 420 */	NdrFcShort( 0x1 ),	/* 1 */
/* 422 */	NdrFcShort( 0x9 ),	/* 9 */
/* 424 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ServerIP */

/* 426 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 428 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 430 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter RetVal */

/* 432 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 434 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 436 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 438 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 440 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 442 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GWLogout */

/* 444 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 446 */	NdrFcLong( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x10 ),	/* 16 */
/* 452 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */
/* 456 */	NdrFcShort( 0x24 ),	/* 36 */
/* 458 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 460 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 464 */	NdrFcShort( 0x1 ),	/* 1 */
/* 466 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrServerIP */

/* 468 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 470 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 472 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter lRetVal */

/* 474 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 476 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 480 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 482 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 484 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RunSetup */

/* 486 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 488 */	NdrFcLong( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0x11 ),	/* 17 */
/* 494 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 496 */	NdrFcShort( 0x10 ),	/* 16 */
/* 498 */	NdrFcShort( 0x24 ),	/* 36 */
/* 500 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 502 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 508 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lRunType */

/* 510 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 512 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bIsOnlySSO */

/* 516 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 518 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 520 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lRetVal */

/* 522 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 524 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 526 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 528 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 530 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 532 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDownloadProgress */

/* 534 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 536 */	NdrFcLong( 0x0 ),	/* 0 */
/* 540 */	NdrFcShort( 0x12 ),	/* 18 */
/* 542 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 546 */	NdrFcShort( 0x24 ),	/* 36 */
/* 548 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 550 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lRetVal */

/* 558 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 560 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 562 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 564 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 566 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 568 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsInstallComplete */

/* 570 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 572 */	NdrFcLong( 0x0 ),	/* 0 */
/* 576 */	NdrFcShort( 0x13 ),	/* 19 */
/* 578 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x24 ),	/* 36 */
/* 584 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 586 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lRetVal */

/* 594 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 596 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 600 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 602 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 604 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Initialize */

/* 606 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 608 */	NdrFcLong( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x14 ),	/* 20 */
/* 614 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 618 */	NdrFcShort( 0x24 ),	/* 36 */
/* 620 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 622 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 626 */	NdrFcShort( 0x16 ),	/* 22 */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrAlgType */

/* 630 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 632 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 634 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrAuxParam */

/* 636 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 638 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 640 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter Result */

/* 642 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 644 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 646 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 648 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 650 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 652 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetDigestAlg */

/* 654 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 656 */	NdrFcLong( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x15 ),	/* 21 */
/* 662 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 666 */	NdrFcShort( 0x24 ),	/* 36 */
/* 668 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 670 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0xb ),	/* 11 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrDigestAlg */

/* 678 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 680 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 682 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter Result */

/* 684 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 686 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 688 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 690 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 692 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 694 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetChooseSingleCert */

/* 696 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 698 */	NdrFcLong( 0x0 ),	/* 0 */
/* 702 */	NdrFcShort( 0x16 ),	/* 22 */
/* 704 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 706 */	NdrFcShort( 0x8 ),	/* 8 */
/* 708 */	NdrFcShort( 0x24 ),	/* 36 */
/* 710 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 712 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 716 */	NdrFcShort( 0x0 ),	/* 0 */
/* 718 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter isChoose */

/* 720 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 722 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 724 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Result */

/* 726 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 728 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 730 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 732 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 734 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 736 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddFilter */

/* 738 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 740 */	NdrFcLong( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0x17 ),	/* 23 */
/* 746 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 748 */	NdrFcShort( 0x8 ),	/* 8 */
/* 750 */	NdrFcShort( 0x24 ),	/* 36 */
/* 752 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 754 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 758 */	NdrFcShort( 0xb ),	/* 11 */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ulType */

/* 762 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 764 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 766 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrValue */

/* 768 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 770 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 772 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter Result */

/* 774 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 776 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 778 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 780 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 782 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 784 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ClearFilter */

/* 786 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 788 */	NdrFcLong( 0x0 ),	/* 0 */
/* 792 */	NdrFcShort( 0x18 ),	/* 24 */
/* 794 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 796 */	NdrFcShort( 0x0 ),	/* 0 */
/* 798 */	NdrFcShort( 0x24 ),	/* 36 */
/* 800 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 802 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 806 */	NdrFcShort( 0x0 ),	/* 0 */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Result */

/* 810 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 812 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 814 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 816 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 818 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 820 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure P1Sign */

/* 822 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 824 */	NdrFcLong( 0x0 ),	/* 0 */
/* 828 */	NdrFcShort( 0x19 ),	/* 25 */
/* 830 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x8 ),	/* 8 */
/* 836 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 838 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 840 */	NdrFcShort( 0x1 ),	/* 1 */
/* 842 */	NdrFcShort( 0xb ),	/* 11 */
/* 844 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrValueBase64 */

/* 846 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 848 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 850 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter Result */

/* 852 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 854 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 856 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 858 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 860 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 862 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure P1SignString */

/* 864 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 866 */	NdrFcLong( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0x1a ),	/* 26 */
/* 872 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 874 */	NdrFcShort( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0x8 ),	/* 8 */
/* 878 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 880 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 882 */	NdrFcShort( 0x1 ),	/* 1 */
/* 884 */	NdrFcShort( 0x1 ),	/* 1 */
/* 886 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrValue */

/* 888 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 890 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 892 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter Result */

/* 894 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 896 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 898 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 900 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 902 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure P7Sign */

/* 906 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 912 */	NdrFcShort( 0x1b ),	/* 27 */
/* 914 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 916 */	NdrFcShort( 0xc ),	/* 12 */
/* 918 */	NdrFcShort( 0x8 ),	/* 8 */
/* 920 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 922 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 924 */	NdrFcShort( 0x1 ),	/* 1 */
/* 926 */	NdrFcShort( 0x1 ),	/* 1 */
/* 928 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrValueBase64 */

/* 930 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 932 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 934 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter isDetach */

/* 936 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 938 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 940 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter isIncludeCert */

/* 942 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 944 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 946 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter Result */

/* 948 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 950 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 952 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 954 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 956 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 958 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure P7SignString */

/* 960 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 962 */	NdrFcLong( 0x0 ),	/* 0 */
/* 966 */	NdrFcShort( 0x1c ),	/* 28 */
/* 968 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 970 */	NdrFcShort( 0xc ),	/* 12 */
/* 972 */	NdrFcShort( 0x8 ),	/* 8 */
/* 974 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 976 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 978 */	NdrFcShort( 0x1 ),	/* 1 */
/* 980 */	NdrFcShort( 0x1 ),	/* 1 */
/* 982 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrValue */

/* 984 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 986 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 988 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter isDetach */

/* 990 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 992 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 994 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter isIncludeCert */

/* 996 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 998 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1000 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter Result */

/* 1002 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1004 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1006 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1008 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1010 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1012 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Finalize */

/* 1014 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1016 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1020 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1022 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1028 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1030 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Result */

/* 1038 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1040 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1042 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1044 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1046 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1048 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSignVersion */

/* 1050 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1052 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1056 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1058 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1060 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1062 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1064 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1066 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1068 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1070 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1072 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Result */

/* 1074 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1076 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1078 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1080 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1082 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1084 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSignCert */

/* 1086 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1088 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1092 */	NdrFcShort( 0x1f ),	/* 31 */
/* 1094 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1096 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1098 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1100 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1102 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1104 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1108 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RetCert */

/* 1110 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1112 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1114 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1116 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1118 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1120 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLastError */

/* 1122 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1124 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1128 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1130 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1136 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1138 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1144 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RetLong */

/* 1146 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1148 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1152 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1154 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1156 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLastErrorMessage */

/* 1158 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1160 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1164 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1166 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1170 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1172 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1174 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1176 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1180 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RetStr */

/* 1182 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1184 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1186 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1188 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1190 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1192 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DestoryAuth */

/* 1194 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1196 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1200 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1202 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1206 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1208 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1210 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1216 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lRetVal */

/* 1218 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1220 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1224 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1226 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1228 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSignCertType */

/* 1230 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1232 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1236 */	NdrFcShort( 0x23 ),	/* 35 */
/* 1238 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1242 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1244 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1246 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1248 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1252 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RetCertType */

/* 1254 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1256 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1258 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1260 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1262 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1264 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSignHash */

/* 1266 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1268 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1272 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1274 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1278 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1280 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1282 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1284 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1288 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RetSignHash */

/* 1290 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1292 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1294 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1296 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1298 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1300 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CallQueueEnable */

/* 1302 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1304 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1308 */	NdrFcShort( 0x25 ),	/* 37 */
/* 1310 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1312 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1314 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1316 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 1318 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1324 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bCallQueueEnable */

/* 1326 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1328 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1330 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bHeadInfoEnable */

/* 1332 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1334 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1336 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lRetVal */

/* 1338 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1340 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1342 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1344 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1346 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1348 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CallQueueClear */

/* 1350 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1352 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1356 */	NdrFcShort( 0x26 ),	/* 38 */
/* 1358 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1362 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1364 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1366 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1372 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lRetVal */

/* 1374 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1376 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1380 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1382 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CallQueueGet */

/* 1386 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1388 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1392 */	NdrFcShort( 0x27 ),	/* 39 */
/* 1394 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1398 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1400 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1402 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1404 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1406 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1408 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrRetVal */

/* 1410 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1412 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1414 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1416 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1418 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1420 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DoClientSecurityCheck */

/* 1422 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1424 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1428 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1430 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1432 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1434 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1436 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1438 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1442 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1444 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGatewayAddr */

/* 1446 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1448 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1450 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter shPort */

/* 1452 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1454 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1456 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter bstrSecurityPolicys */

/* 1458 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1460 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1462 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter RetVal */

/* 1464 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1466 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1468 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1470 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1472 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetProtocolVersion */

/* 1476 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1478 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1482 */	NdrFcShort( 0x29 ),	/* 41 */
/* 1484 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1488 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1490 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1492 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1494 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1498 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrProtocolVersion */

/* 1500 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1502 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1504 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1506 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1508 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1510 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ChangePinCode */

/* 1512 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1514 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1518 */	NdrFcShort( 0x2a ),	/* 42 */
/* 1520 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1522 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1524 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1526 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1528 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1532 */	NdrFcShort( 0x2b ),	/* 43 */
/* 1534 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrCertSn */

/* 1536 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1538 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1540 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter pinCodeType */

/* 1542 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1544 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1546 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrCurPinCode */

/* 1548 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1550 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1552 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrNewPinCode */

/* 1554 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1556 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1558 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter pRet */

/* 1560 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1562 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1564 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1566 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1568 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1570 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure WaitSetPolicyFinish */

/* 1572 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1574 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1578 */	NdrFcShort( 0x2b ),	/* 43 */
/* 1580 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1584 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1586 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1588 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1592 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1594 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGatewayAddress */

/* 1596 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1598 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1600 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter lRetVal */

/* 1602 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1604 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1606 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1608 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1610 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1612 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSessionToken */

/* 1614 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1616 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1620 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1622 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1626 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1628 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1630 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1632 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1634 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1636 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGWAddress */

/* 1638 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1640 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1642 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrToken */

/* 1644 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1646 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1648 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1650 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1652 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1654 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetVersion */

/* 1656 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1658 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1662 */	NdrFcShort( 0x2d ),	/* 45 */
/* 1664 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1668 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1670 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1672 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1674 */	NdrFcShort( 0x16 ),	/* 22 */
/* 1676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrRetVal */

/* 1680 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1682 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1684 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1686 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1688 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1690 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetLanguage */

/* 1692 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1694 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1698 */	NdrFcShort( 0x2e ),	/* 46 */
/* 1700 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1704 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1706 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1708 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1712 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1714 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrLanguage */

/* 1716 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1718 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1720 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter Result */

/* 1722 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1724 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1726 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1728 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1730 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1732 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetAttribute */

/* 1734 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1736 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1740 */	NdrFcShort( 0x2f ),	/* 47 */
/* 1742 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1748 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1750 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1752 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1754 */	NdrFcShort( 0x45 ),	/* 69 */
/* 1756 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter gwip */

/* 1758 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1760 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1762 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter appflag */

/* 1764 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1766 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1768 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter attributename */

/* 1770 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1772 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1774 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter attributevalue */

/* 1776 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1778 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1780 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1782 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1784 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1786 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetParentWindow */

/* 1788 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1790 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1794 */	NdrFcShort( 0x30 ),	/* 48 */
/* 1796 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1798 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1800 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1802 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1804 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1806 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1810 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ulHwnd */

/* 1812 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1814 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1816 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lRetval */

/* 1818 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1820 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1822 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1824 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1826 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1828 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPinCode */

/* 1830 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1832 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1836 */	NdrFcShort( 0x31 ),	/* 49 */
/* 1838 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1842 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1844 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1846 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1848 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1850 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1852 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Result */

/* 1854 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1856 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1858 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1860 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1862 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1864 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetPolicyByPID */

/* 1866 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1868 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1872 */	NdrFcShort( 0x32 ),	/* 50 */
/* 1874 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1876 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1878 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1880 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1882 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1884 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1886 */	NdrFcShort( 0x33 ),	/* 51 */
/* 1888 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ulPID */

/* 1890 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1892 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1894 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrProxyPolicy */

/* 1896 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1898 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1900 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrSSOPolicy */

/* 1902 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1904 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1906 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrGatewayAddress */

/* 1908 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1910 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1912 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter lRetVal */

/* 1914 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1916 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1920 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1922 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1924 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSessionTokenByPID */

/* 1926 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1928 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1932 */	NdrFcShort( 0x33 ),	/* 51 */
/* 1934 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1936 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1938 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1940 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1942 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 1944 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1946 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1948 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ulPID */

/* 1950 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1952 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1954 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrGWAddress */

/* 1956 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1958 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1960 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrToken */

/* 1962 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1964 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1966 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1968 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1970 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1972 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetForcePinDialog */

/* 1974 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1976 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1980 */	NdrFcShort( 0x34 ),	/* 52 */
/* 1982 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1984 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1986 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1988 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1990 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1996 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter isForcePinDialog */

/* 1998 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2000 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2002 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Result */

/* 2004 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2006 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2008 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2010 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2012 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2014 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MessageAuth */

/* 2016 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2018 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2022 */	NdrFcShort( 0x35 ),	/* 53 */
/* 2024 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2026 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2028 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2030 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 2032 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2034 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2036 */	NdrFcShort( 0x37 ),	/* 55 */
/* 2038 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGatewayAddress */

/* 2040 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2042 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2044 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrAttributeName */

/* 2046 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2048 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2050 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrAppID */

/* 2052 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2054 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2056 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrAttributeValue */

/* 2058 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2060 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2062 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2064 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2066 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2068 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCert */

/* 2070 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2072 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2076 */	NdrFcShort( 0x7 ),	/* 7 */
/* 2078 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 2080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2082 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2084 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x8,		/* 8 */
/* 2086 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2088 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2090 */	NdrFcShort( 0x92 ),	/* 146 */
/* 2092 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrCertType */

/* 2094 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2096 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2098 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrDN */

/* 2100 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2102 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2104 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrSN */

/* 2106 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2108 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2110 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrEmail */

/* 2112 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2114 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2116 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrDNIssuer */

/* 2118 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2120 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2122 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrCertBase64 */

/* 2124 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2126 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2128 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter pRetVal */

/* 2130 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2132 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2134 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2136 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2138 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 2140 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCertChooseType */

/* 2142 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2144 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2148 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2150 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2154 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2156 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 2158 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2164 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nType */

/* 2166 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2168 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2170 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRetVal */

/* 2172 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2174 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2180 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCertInfo */

/* 2184 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2190 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2192 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2194 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2196 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2198 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 2200 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2202 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2204 */	NdrFcShort( 0x3a ),	/* 58 */
/* 2206 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrCertType */

/* 2208 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2210 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2212 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter lInfoType */

/* 2214 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2216 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2218 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrOID */

/* 2220 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2222 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2224 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter pRetCerInfo */

/* 2226 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2228 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2230 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2232 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2234 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2236 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AttachSign */

/* 2238 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2240 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2244 */	NdrFcShort( 0xa ),	/* 10 */
/* 2246 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2248 */	NdrFcShort( 0x21 ),	/* 33 */
/* 2250 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2252 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 2254 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2256 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2258 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2260 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrDN */

/* 2262 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2264 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2266 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter pszSrcData */

/* 2268 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2270 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2272 */	0x1,		/* FC_BYTE */
			0x0,		/* 0 */

	/* Parameter lSrcDataLen */

/* 2274 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2276 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2278 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pbstrSignedData */

/* 2280 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2282 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2284 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2286 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2288 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2290 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DetachSign */

/* 2292 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2294 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2298 */	NdrFcShort( 0xb ),	/* 11 */
/* 2300 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2302 */	NdrFcShort( 0x21 ),	/* 33 */
/* 2304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2306 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 2308 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2310 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2312 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2314 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrDN */

/* 2316 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2318 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2320 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter pszSrcData */

/* 2322 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 2324 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2326 */	0x1,		/* FC_BYTE */
			0x0,		/* 0 */

	/* Parameter lSrcDataLen */

/* 2328 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2330 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pbstrSignedData */

/* 2334 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2336 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2338 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2340 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2342 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetErrorCode */

/* 2346 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2352 */	NdrFcShort( 0xc ),	/* 12 */
/* 2354 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2358 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2360 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2362 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2368 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pRetVal */

/* 2370 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2372 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2376 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2378 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2380 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetErrorMessage */

/* 2382 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2384 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2388 */	NdrFcShort( 0xd ),	/* 13 */
/* 2390 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2394 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2396 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2398 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2400 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2404 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lErrorCode */

/* 2406 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2408 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2410 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pErrorMessage */

/* 2412 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2414 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2416 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2418 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2420 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2422 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure JITGetVersion */

/* 2424 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2426 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2430 */	NdrFcShort( 0xe ),	/* 14 */
/* 2432 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2434 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2436 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2438 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2440 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2442 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2444 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2446 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrVersion */

/* 2448 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2450 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2452 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2454 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2456 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2458 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure P1SignStr */

/* 2460 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2462 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2466 */	NdrFcShort( 0xf ),	/* 15 */
/* 2468 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2472 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2474 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2476 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2478 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2480 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2482 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrDN */

/* 2484 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2486 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2488 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrSrc */

/* 2490 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2492 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2494 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter pbstrSignedData */

/* 2496 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2498 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2500 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2502 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2504 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2506 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GWInit */

/* 2508 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2510 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2514 */	NdrFcShort( 0x7 ),	/* 7 */
/* 2516 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2520 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2522 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2524 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2528 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2530 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGWAddr */

/* 2532 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2534 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2536 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter lnRetVal */

/* 2538 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2540 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2542 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2544 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2546 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2548 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GWGetCertList */

/* 2550 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2552 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2556 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2558 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2562 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2564 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2566 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2568 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2572 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrCertList */

/* 2574 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2576 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2578 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2580 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2582 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2584 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GWLogin */

/* 2586 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2588 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2592 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2594 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2596 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2598 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2600 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 2602 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 2604 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2606 */	NdrFcShort( 0x28 ),	/* 40 */
/* 2608 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lnType */

/* 2610 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2612 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2614 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrUsr */

/* 2616 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2618 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2620 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrPwd */

/* 2622 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2624 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2626 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter bstrAppList */

/* 2628 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2630 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2632 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2634 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2636 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GWGetLastError */

/* 2640 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2642 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2646 */	NdrFcShort( 0xa ),	/* 10 */
/* 2648 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2652 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2654 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2656 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2662 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lnErrorCode */

/* 2664 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2666 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2668 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2670 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2672 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2674 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GWGetLastErrorMsg */

/* 2676 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2678 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2682 */	NdrFcShort( 0xb ),	/* 11 */
/* 2684 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2688 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2690 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2692 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2694 */	NdrFcShort( 0x28 ),	/* 40 */
/* 2696 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2698 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrErrorMsg */

/* 2700 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2702 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2704 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2706 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2708 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2710 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GWLogout */

/* 2712 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2714 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2718 */	NdrFcShort( 0xc ),	/* 12 */
/* 2720 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2724 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2726 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2728 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2734 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2736 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2738 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2740 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GWOpenPortal */

/* 2742 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2744 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2748 */	NdrFcShort( 0xd ),	/* 13 */
/* 2750 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2754 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2756 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2758 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2764 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2766 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2768 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2770 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const PNXClient_MIDL_TYPE_FORMAT_STRING PNXClient__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1c ),	/* Offset= 28 (32) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (10) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffde ),	/* Offset= -34 (6) */
/* 42 */	
			0x12, 0x0,	/* FC_UP */
/* 44 */	NdrFcShort( 0xffea ),	/* Offset= -22 (22) */
/* 46 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x4 ),	/* 4 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (42) */
/* 56 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 58 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 60 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 62 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IPNXDataTrans, ver. 0.0,
   GUID={0xDAC3A59C,0x8541,0x400D,{0x91,0xB9,0x2F,0xEF,0x97,0xE5,0xBA,0xA0}} */

#pragma code_seg(".orpc")
static const unsigned short IPNXDataTrans_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    36,
    96,
    144,
    198,
    246,
    288,
    342,
    402,
    444,
    486,
    534,
    570,
    606,
    654,
    696,
    738,
    786,
    822,
    864,
    906,
    960,
    1014,
    1050,
    1086,
    1122,
    1158,
    1194,
    1230,
    1266,
    1302,
    1350,
    1386,
    1422,
    1476,
    1512,
    1572,
    1614,
    1656,
    1692,
    1734,
    1788,
    1830,
    1866,
    1926,
    1974,
    2016
    };

static const MIDL_STUBLESS_PROXY_INFO IPNXDataTrans_ProxyInfo =
    {
    &Object_StubDesc,
    PNXClient__MIDL_ProcFormatString.Format,
    &IPNXDataTrans_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPNXDataTrans_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    PNXClient__MIDL_ProcFormatString.Format,
    &IPNXDataTrans_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(54) _IPNXDataTransProxyVtbl = 
{
    &IPNXDataTrans_ProxyInfo,
    &IID_IPNXDataTrans,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetClientVersion */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::SetupClient */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetFinger */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::SetPolicy */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetAuthToken */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::NavigateURL */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::ExecuteCS */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::SetUpdatePolicy */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetClientIP */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GWLogout */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::RunSetup */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetDownloadProgress */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::IsInstallComplete */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::Initialize */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::SetDigestAlg */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::SetChooseSingleCert */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::AddFilter */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::ClearFilter */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::P1Sign */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::P1SignString */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::P7Sign */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::P7SignString */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::Finalize */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetSignVersion */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetSignCert */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetLastError */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetLastErrorMessage */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::DestoryAuth */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetSignCertType */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetSignHash */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::CallQueueEnable */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::CallQueueClear */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::CallQueueGet */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::DoClientSecurityCheck */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetProtocolVersion */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::ChangePinCode */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::WaitSetPolicyFinish */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetSessionToken */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetVersion */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::SetLanguage */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetAttribute */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::SetParentWindow */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetPinCode */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::SetPolicyByPID */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::GetSessionTokenByPID */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::SetForcePinDialog */ ,
    (void *) (INT_PTR) -1 /* IPNXDataTrans::MessageAuth */
};


static const PRPC_STUB_FUNCTION IPNXDataTrans_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IPNXDataTransStubVtbl =
{
    &IID_IPNXDataTrans,
    &IPNXDataTrans_ServerInfo,
    54,
    &IPNXDataTrans_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IGWClientTK, ver. 0.0,
   GUID={0x4DD1C6CC,0x9243,0x426C,{0x94,0x9F,0xD0,0x3F,0xDC,0x7D,0x10,0x89}} */

#pragma code_seg(".orpc")
static const unsigned short IGWClientTK_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    2070,
    2142,
    2184,
    2238,
    2292,
    2346,
    2382,
    2424,
    2460
    };

static const MIDL_STUBLESS_PROXY_INFO IGWClientTK_ProxyInfo =
    {
    &Object_StubDesc,
    PNXClient__MIDL_ProcFormatString.Format,
    &IGWClientTK_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGWClientTK_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    PNXClient__MIDL_ProcFormatString.Format,
    &IGWClientTK_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _IGWClientTKProxyVtbl = 
{
    &IGWClientTK_ProxyInfo,
    &IID_IGWClientTK,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IGWClientTK::SetCert */ ,
    (void *) (INT_PTR) -1 /* IGWClientTK::SetCertChooseType */ ,
    (void *) (INT_PTR) -1 /* IGWClientTK::GetCertInfo */ ,
    (void *) (INT_PTR) -1 /* IGWClientTK::AttachSign */ ,
    (void *) (INT_PTR) -1 /* IGWClientTK::DetachSign */ ,
    (void *) (INT_PTR) -1 /* IGWClientTK::GetErrorCode */ ,
    (void *) (INT_PTR) -1 /* IGWClientTK::GetErrorMessage */ ,
    (void *) (INT_PTR) -1 /* IGWClientTK::JITGetVersion */ ,
    (void *) (INT_PTR) -1 /* IGWClientTK::P1SignStr */
};


static const PRPC_STUB_FUNCTION IGWClientTK_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IGWClientTKStubVtbl =
{
    &IID_IGWClientTK,
    &IGWClientTK_ServerInfo,
    16,
    &IGWClientTK_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IGWClient, ver. 0.0,
   GUID={0x048B8480,0x28E7,0x49F9,{0xA5,0xED,0xC7,0x36,0x75,0x29,0x43,0xD8}} */

#pragma code_seg(".orpc")
static const unsigned short IGWClient_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    2508,
    2550,
    2586,
    2640,
    2676,
    2712,
    2742
    };

static const MIDL_STUBLESS_PROXY_INFO IGWClient_ProxyInfo =
    {
    &Object_StubDesc,
    PNXClient__MIDL_ProcFormatString.Format,
    &IGWClient_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGWClient_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    PNXClient__MIDL_ProcFormatString.Format,
    &IGWClient_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _IGWClientProxyVtbl = 
{
    &IGWClient_ProxyInfo,
    &IID_IGWClient,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IGWClient::GWInit */ ,
    (void *) (INT_PTR) -1 /* IGWClient::GWGetCertList */ ,
    (void *) (INT_PTR) -1 /* IGWClient::GWLogin */ ,
    (void *) (INT_PTR) -1 /* IGWClient::GWGetLastError */ ,
    (void *) (INT_PTR) -1 /* IGWClient::GWGetLastErrorMsg */ ,
    (void *) (INT_PTR) -1 /* IGWClient::GWLogout */ ,
    (void *) (INT_PTR) -1 /* IGWClient::GWOpenPortal */
};


static const PRPC_STUB_FUNCTION IGWClient_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IGWClientStubVtbl =
{
    &IID_IGWClient,
    &IGWClient_ServerInfo,
    14,
    &IGWClient_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    PNXClient__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x70001f4, /* MIDL Version 7.0.500 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * _PNXClient_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IGWClientProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPNXDataTransProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGWClientTKProxyVtbl,
    0
};

const CInterfaceStubVtbl * _PNXClient_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IGWClientStubVtbl,
    ( CInterfaceStubVtbl *) &_IPNXDataTransStubVtbl,
    ( CInterfaceStubVtbl *) &_IGWClientTKStubVtbl,
    0
};

PCInterfaceName const _PNXClient_InterfaceNamesList[] = 
{
    "IGWClient",
    "IPNXDataTrans",
    "IGWClientTK",
    0
};

const IID *  _PNXClient_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _PNXClient_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _PNXClient, pIID, n)

int __stdcall _PNXClient_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _PNXClient, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _PNXClient, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _PNXClient, 3, *pIndex )
    
}

const ExtendedProxyFileInfo PNXClient_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _PNXClient_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _PNXClient_StubVtblList,
    (const PCInterfaceName * ) & _PNXClient_InterfaceNamesList,
    (const IID ** ) & _PNXClient_BaseIIDList,
    & _PNXClient_IID_Lookup, 
    3,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

