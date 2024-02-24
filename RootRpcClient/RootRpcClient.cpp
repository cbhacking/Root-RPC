// RootRpcClient.cpp : Defines the exported functions for the DLL application.
//

#include "RootRpcClient.h"
#include "pch.h"
#include "../RootRpcDef/WpRootRpc.h"

__declspec(dllexport)
long InitializeRpc()
{
	NTSTATUS nstat;
	RPC_STATUS rstat;

	// Set up the binding handle template
	// ( https://msdn.microsoft.com/en-us/library/windows/desktop/aa378497(v=vs.85).aspx )
	RPC_BINDING_HANDLE_TEMPLATE_V1_W rbht;
	rbht.Version = 1;							// V1, as per MSDN
	rbht.Flags = 0x0;							// I don't think I need an ObjectUUID
	rbht.ProtocolSequence = RPC_PROTSEQ_LRPC;	// As per comments on MSDN; type is wrong for string
	rbht.NetworkAddress = NULL;					// LRPC, so no network address? If NULL does work, loopback
	rbht.StringEndpoint = NULL;					// Server uses a dynamic binding, so try this...
	rbht.u1.Reserved = NULL;					// Reserved, NULL as per MSDN
//	rbht.ObjectUuid								// Don't care what value it is; not using it

	// Set up the RPC security QoS. Use v5, since it new in Win8 and probably relevant to apps...
	// ( https://msdn.microsoft.com/en-us/library/windows/desktop/jj203363(v=vs.85).aspx )
	RPC_SECURITY_QOS_V5_W rsq;
	rsq.Version = 5;									// The Win8-specific one
	rsq.Capabilities = RPC_C_QOS_CAPABILITIES_DEFAULT;	// I don't *think* we need any of these?
	rsq.IdentityTracking = RPC_C_QOS_IDENTITY_DYNAMIC;	// Default for v5 and maybe LRPC, seems reasonable?
	rsq.ImpersonationType = RPC_C_IMP_LEVEL_IMPERSONATE;// Server may sometimes need to impersonate
	rsq.AdditionalSecurityInfoType = 0x0;				// Not using HTTP so don't need this
	rsq.u.HttpCredentials = NULL;						// Not using HTTP so don't need this
	rsq.Sid = NULL;										// SID of the server... LOCALSYSTEM? Will try if NULL fails
	rsq.EffectiveOnly = FALSE;							// Let server see all capabilities, not that we have much
//	rsq.ServerSecurityDescriptor						// We will set this using QueryTransientObjectSD

	// Set up the binding handle security
	// ( https://msdn.microsoft.com/en-us/library/windows/desktop/aa378496(v=vs.85).aspx )
	RPC_BINDING_HANDLE_SECURITY_V1_W rbhs;
	rbhs.Version = 1;								// V1, as per MSDN
	rbhs.ServerPrincName = NULL;					// LRPC, so no server name needed? If not NULL, localhost
	rbhs.AuthnLevel = RPC_C_AUTHN_LEVEL_PKT_PRIVACY;// According to MSDN, ncalrpc always uses this regardless
	rbhs.AuthnSvc = RPC_C_AUTHN_DEFAULT;			// Hope this works; MSDN says it's the same as AUTHN_WINNT
	rbhs.AuthIdentity = NULL;						// Hope we don't need this. If so, DefApps or InteropServices?
	rbhs.SecurityQos = (PRPC_SECURITY_QOS)&rsq;		// Use the RPC security QoS v5 defined above

	// Now, get the security descriptor for the server and add it to the RPC security QoS
	// Not sure if needed (are we doing mutual auth?) but we have it easily, so...
	nstat = ::QueryTransientObjectSecurityDescriptor(
		TransientObject_Type_Rpc,				// From policy files, \\.\rpc\...
		OBJPATH_INTEROP_RPC_SERVER,				// From policy files, INTEROPSERVICES can access this one (InteropRPC)
		&(rsq.ServerSecurityDescriptor));		// Set as the server security descriptor for the RPC Security QoS
	if (STATUS_SUCCESS != nstat)
	{
		::fprintf(
			stderr,
			"QueryTransientObjectSecurityDescriptor failed for '%S'! NTSTATUS code 0x%X\n",
			OBJPATH_INTEROP_RPC_SERVER,
			nstat);
		return nstat;
	}

	// All right, let's try creating the binding
	rstat = ::RpcBindingCreateW(
		&rbht,									// Binding handle template indicating to use LRPC
		&rbhs,									// Binding handle security including the QoS with the server SD
		NULL,									// Use the defaults on each RPC binding handle option
		&WpRootRpc_IfHandle);					// Pointer to structure that receives the newly-created binding handle
	// Decompilation suggests we always want to free the transient object SD as soon as possible
	::FreeTransientObjectSecurityDescriptor(rsq.ServerSecurityDescriptor);
	// Check RPC function result
	if (RPC_S_OK != rstat)
	{
		::fprintf(
			stderr,
			"RpcBindingCreateW failed with template, security (inc. QoS w/ SD), and no options! RPC_STATUS code %d\n",
			rstat);
		return rstat;
	}


	// Now, actually bind to the server
	rstat = ::RpcBindingBind(
		NULL,									// Not using async; should return basicall instantly
		WpRootRpc_IfHandle,						// The binding handle created above
		WpRootRpc_v0_1_c_ifspec);				// The interface's RPC_IF_HANDLE from the MIDL output
	if (RPC_S_OK != rstat)
	{
		::fprintf(
			stderr,
			"RpcBindingBind failed synchronously with binding and interface handle from MIDL! RPC_STATUS code %d\n",
			rstat);
		::RpcBindingFree(&WpRootRpc_IfHandle);
		return rstat;
	}

	// If we get here, everything should be working now!
	//RpcTryExcept
	//	rstat = ::RpcMgmtIsServerListening(WpRootRpc_IfHandle);
	//RpcExcept(TRUE)
	//RpcEndExcept
	// Test it, though...
	int res = 0;
	RpcTryExcept
		res = RpcTestIncrement(-793);
	RpcExcept(TRUE)
		return ::RpcExceptionCode();
	RpcEndExcept
	if (-792 == res)
		return 0;
	else return -1;
}

__declspec(dllexport)
int RpcIncrementTest(int valToIncrement, int *valResult)
{
	// Call a trivial RPC function and make sure it succeeds
	int res = 0;
	RpcTryExcept
		res = RpcTestIncrement(valToIncrement);
	RpcExcept(TRUE)
		return ::RpcExceptionCode();
	RpcEndExcept
	if (valResult)
	{
		*valResult = res;
	}
	return 0;
}

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
	::printf("Allocating %u (0x%X) bytes of memory in client.\n", len, len);
	void *ptr = ::malloc(len);
	::printf("Pointer returned by malloc: %p.\n", ptr);
	return ptr;
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
	::printf("Freeing memory at client address %p.\n", ptr);
	::free(ptr);
}
