

/* this ALWAYS GENERATED file contains the RPC server stubs */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Fri Jul 03 16:14:11 2015
 */
/* Compiler settings for WpRootRpc.idl:
    Oicf, W4, Zp8, env=Win32 (32b run), target_arch=ARM 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/

#include <string.h>
#include "WpRootRpc.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   41                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _WpRootRpc_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } WpRootRpc_MIDL_TYPE_FORMAT_STRING;

typedef struct _WpRootRpc_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } WpRootRpc_MIDL_PROC_FORMAT_STRING;

typedef struct _WpRootRpc_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } WpRootRpc_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};

extern const WpRootRpc_MIDL_TYPE_FORMAT_STRING WpRootRpc__MIDL_TypeFormatString;
extern const WpRootRpc_MIDL_PROC_FORMAT_STRING WpRootRpc__MIDL_ProcFormatString;
extern const WpRootRpc_MIDL_EXPR_FORMAT_STRING WpRootRpc__MIDL_ExprFormatString;

/* Standard interface: WpRootRpc, ver. 0.1,
   GUID={0x2b68b4d0,0xa756,0x41c9,{0x9c,0x75,0x91,0x0d,0x8d,0x0e,0x54,0x57}} */


extern const MIDL_SERVER_INFO WpRootRpc_ServerInfo;

extern const RPC_DISPATCH_TABLE WpRootRpc_v0_1_DispatchTable;

static const RPC_SERVER_INTERFACE WpRootRpc___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x2b68b4d0,0xa756,0x41c9,{0x9c,0x75,0x91,0x0d,0x8d,0x0e,0x54,0x57}},{0,1}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    (RPC_DISPATCH_TABLE*)&WpRootRpc_v0_1_DispatchTable,
    0,
    0,
    0,
    &WpRootRpc_ServerInfo,
    0x04000000
    };
RPC_IF_HANDLE WpRootRpc_v0_1_s_ifspec = (RPC_IF_HANDLE)& WpRootRpc___RpcServerInterface;

extern const MIDL_STUB_DESC WpRootRpc_StubDesc;


#if !defined(__RPC_ARM32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const WpRootRpc_MIDL_PROC_FORMAT_STRING WpRootRpc__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure RpcTestIncrement */

			0x32,		/* FC_BIND_PRIMITIVE */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x8 ),	/* ARM Stack size/offset = 8 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0xc,		/* 12 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x1 ),	/* 1 */
/* 26 */	0x1,		/* 1 */
			0x80,		/* 128 */

	/* Parameter val */

/* 28 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 30 */	NdrFcShort( 0x0 ),	/* ARM Stack size/offset = 0 */
/* 32 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 34 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 36 */	NdrFcShort( 0x4 ),	/* ARM Stack size/offset = 4 */
/* 38 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const WpRootRpc_MIDL_TYPE_FORMAT_STRING WpRootRpc__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };

static const unsigned short WpRootRpc_FormatStringOffsetTable[] =
    {
    0
    };


static const MIDL_STUB_DESC WpRootRpc_StubDesc = 
    {
    (void *)& WpRootRpc___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    0,
    WpRootRpc__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x8000253, /* MIDL Version 8.0.595 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

static const RPC_DISPATCH_FUNCTION WpRootRpc_table[] =
    {
    NdrServerCall2,
    0
    };
static const RPC_DISPATCH_TABLE WpRootRpc_v0_1_DispatchTable = 
    {
    1,
    (RPC_DISPATCH_FUNCTION*)WpRootRpc_table
    };

static const SERVER_ROUTINE WpRootRpc_ServerRoutineTable[] = 
    {
    (SERVER_ROUTINE)RpcTestIncrement
    };

static const MIDL_SERVER_INFO WpRootRpc_ServerInfo = 
    {
    &WpRootRpc_StubDesc,
    WpRootRpc_ServerRoutineTable,
    WpRootRpc__MIDL_ProcFormatString.Format,
    WpRootRpc_FormatStringOffsetTable,
    0,
    0,
    0,
    0};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* if defined(_ARM_) */

