

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


#ifndef __WpRootRpc_h__
#define __WpRootRpc_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __WpRootRpc_INTERFACE_DEFINED__
#define __WpRootRpc_INTERFACE_DEFINED__

/* interface WpRootRpc */
/* [implicit_handle][strict_context_handle][version][uuid] */ 

int RpcTestIncrement( 
    /* [in] */ int val);


extern handle_t WpRootRpc_IfHandle;


extern RPC_IF_HANDLE WpRootRpc_v0_1_c_ifspec;
extern RPC_IF_HANDLE WpRootRpc_v0_1_s_ifspec;
#endif /* __WpRootRpc_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


