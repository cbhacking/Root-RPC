#pragma once

#include "../RootRpcDef/WpRootRpc.h"
#include "pch.h"

RPC_STATUS CALLBACK RpcInterfaceCallback(
  _In_ RPC_IF_HANDLE Interface,
  _In_ void          *Context
);
