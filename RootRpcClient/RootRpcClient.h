#pragma once

__declspec(dllexport)
long InitializeRpc();

__declspec(dllexport)
int RpcIncrementTest(int valToIncrement, int *valResult);
