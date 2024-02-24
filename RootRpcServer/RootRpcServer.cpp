// RootRpcServer.cpp : Defines the exported functions for the DLL application.
//

#include "pch.h"
#include "RootRpcServer.h"

int wmain (int argc, wchar_t* argv[])
{
	NTSTATUS nstat = 0x0;
	RPC_STATUS rstat = 0;
	PSECURITY_DESCRIPTOR psd = nullptr;
	RPC_BINDING_VECTOR *prbv;

	// Get a security descriptor that allows InteropServices apps to access the server
	nstat = ::QueryTransientObjectSecurityDescriptor(
		TransientObject_Type_Rpc,
		OBJPATH_INTEROP_RPC_SERVER,
		&psd);
	if (STATUS_SUCCESS != nstat)
	{
		::printf(
			"QueryTransientObjectSecurityDescriptor failed for type 'Rpc' and path %S! NTSTATUS code 0x%X\n",
			OBJPATH_INTEROP_RPC_SERVER,
			nstat);
		return (int)nstat;
	}
	::printf("QueryTransientObjectSecurityDescriptor succeeded!\n");

	// Specify the protocol sequence, but don't bind an endpoint or interface
	rstat = ::RpcServerUseProtseqW(
		(RPC_WSTR)L"ncalrpc",
		RPC_C_PROTSEQ_MAX_REQS_DEFAULT,
		psd);
	// Free the descriptor immediately, regardless of result
	::FreeTransientObjectSecurityDescriptor(psd);
	if (RPC_S_OK != rstat)
	{
		::printf(
			"RpcServerUseProtseqW failed for 'ncalrpc' with default maxreqs and queried SD! RPC_STATUS code %d\n",
			rstat);
		return (int)rstat;
	}
	::printf("RpcServerUseProtseqW succeeded!\n");

	// Get the binding handles usable by this server (from example)
	// Not sure why we're doing this now, I guess it minimizes time with allocated SD?
	rstat = ::RpcServerInqBindings(&prbv);
	if (RPC_S_OK != rstat)
	{
		::printf(
			"RpcServerInqBindings failed! RPC_STATUS code %d\n",
			rstat);
		return (int)rstat;
	}
	::printf("RpcServerInqBindings succeeded!\n");

	// Get a security descriptor that allows InteropServices apps to access the interface
	nstat = ::QueryTransientObjectSecurityDescriptor(
		TransientObject_Type_Rpc,
		OBJPATH_INTEROP_RPC_INTERFACE,
		&psd);
	if (STATUS_SUCCESS != nstat)
	{
		::printf(
			"QueryTransientObjectSecurityDescriptor failed for type 'Rpc' and path %S! NTSTATUS code 0x%X\n",
			OBJPATH_INTEROP_RPC_INTERFACE,
			nstat);
		::RpcBindingVectorFree(&prbv);
		return (int)nstat;
	}
	::printf("QueryTransientObjectSecurityDescriptor succeeded!\n");

	// Register the RPC interface, with the variant that permits specifying a SD that permits apps.
	// Also specifies to use a callback function, and to auto-listen.
	rstat = ::RpcServerRegisterIf3(
		WpRootRpc_v0_1_s_ifspec,		// Server-side RPC interface handle
		NULL,							// No UUID because not using MgrEpv
		NULL,							// No manager entry point vector, using EPV from MIDL
		RPC_IF_AUTOLISTEN |				// Begin listening automatically (from example)
		RPC_IF_ALLOW_SECURE_ONLY |		// Require at least some degree of authorization (from example)
		RPC_IF_ALLOW_LOCAL_ONLY,		// NCALRPC is already local-only... (from example)
		RPC_C_LISTEN_MAX_CALLS_DEFAULT,	// Not worried about number of concurrent callers
		0xFFFFFFFF,						// No max size, doens't matter for this protseq anyhow
		RpcInterfaceCallback,			// Callback function for when a client connects
		psd);							// Security descriptor that allows ID_CAP_INTEROPSERVICES apps
	// Free the descriptor immediately, regardless of result
	::FreeTransientObjectSecurityDescriptor(psd);
	if (RPC_S_OK != rstat)
	{
		::printf(
			"RpcServerRegisterIf3 failed for flags '41', callback, and queried SD! RPC_STATUS code %d\n",
			rstat);
		::RpcBindingVectorFree(&prbv);
		return (int)rstat;
	}
	::printf("RpcServerUseProtseqW succeeded!\n");

	// Register the dynamically-created endpoint so we can use it from other apps (from example).
	rstat = ::RpcEpRegisterW(
		WpRootRpc_v0_1_s_ifspec,		// Server-side RPC interface handle
		prbv,							// All the binding handles we can receive on (from example)
		NULL,							// No object UUIDs, apparently (from example)
		NULL);							// No annotation (from example)
	if (RPC_S_OK != rstat)
	{
		::printf(
			"RpcEpRegisterW failed with the binding handles and no UUIDs! RPC_STATUS code %d\n",
			rstat);
		::RpcBindingVectorFree(&prbv);
		return (int)rstat;
	}
	::printf("RpcEpRegisterW succeeded!\n");

	// Free the binding vector; I think we don't need it anymore (from example)
	rstat = ::RpcBindingVectorFree(&prbv);
	if (RPC_S_OK != rstat)
	{
		::printf(
			"RpcBindingVectorFree failed to free the binding handles! RPC_STATUS code %d\n",
			rstat);
		return (int)rstat;
	}
	::printf("RpcBindingVectorFree succeeded!\n");

	// Example just returns here, implying this is non-blocking. We'll put in a blocking call...
	::printf("Server should now be running. Press Enter to exit...\n\n");
	::getc(stdin);
	// Input received; let's shut it down!
	::printf("Server is now exiting...\n");

	// Unregister the interface
	rstat = ::RpcServerUnregisterIfEx(
		WpRootRpc_v0_1_s_ifspec,		// Server-side RPC interface handle
		NULL,							// Remove for all previously registered UUIDs (from example)
		TRUE);							// Call context handle run-downs once all calls complete (from example)
	if (RPC_S_OK != rstat)
	{
		::printf(
			"RpcServerUnregisterIfEx failed with NULL UUIDs and rundown enabled! RPC_STATUS code %d\n",
			rstat);
		return (int)rstat;
	}
	::printf("RpcServerUnregisterIfEx succeeded!\n");

	::printf("Main is returning cleanly.\n");
	return 0;
}

RPC_STATUS CALLBACK RpcInterfaceCallback(RPC_IF_HANDLE Interface, void *Context)
{
	::printf("\nRPC interface security callback invoked.\n");
	return RPC_S_OK;
}

int RpcTestIncrement(int val)
{
	::printf("\nRpcTestIncrement called with input value %d.\n", val);
	return (val + 1);
}

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
	::printf("Allocating %u (0x%X) bytes of memory in server.\n", len, len);
	void *ptr = ::malloc(len);
	::printf("Pointer returned by malloc: %p.\n", ptr);
	return ptr;
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
	::printf("Freeing memory at server address %p.\n", ptr);
	::free(ptr);
}
