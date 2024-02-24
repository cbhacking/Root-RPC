// RootRpcWPRT.cpp
#include "pch.h"
#include "RootRpcWPRT.h"

using namespace RootRpcWPRT;

RootRpc::RootRpc()
{
}

int RootRpc::InititializeRpc()
{
	return ::InitializeRpc();
}

int RootRpc::TestRpc(int toIncrement, int *result)
{
	return ::RpcIncrementTest(toIncrement, result);
}