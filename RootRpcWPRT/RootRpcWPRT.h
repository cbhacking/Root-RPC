#pragma once

#include "../RootRpcClient/RootRpcClient.h"

using namespace Platform;

namespace RootRpcWPRT
{
    public ref class RootRpc sealed
    {
        RootRpc();
    public:
		static int InititializeRpc();
		static int TestRpc(int toIncrement, int *result);
    };
}