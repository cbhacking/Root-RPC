//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "targetver.h"

// Deal with the stupid API partitioning
#include <winapifamily.h>
#ifdef WINAPI_PARTITION_DESKTOP
#undef WINAPI_PARTITION_DESKTOP
#endif
#define WINAPI_PARTITION_DESKTOP 1

// Windows Header Files:
#include <windows.h>
#include <rpc.h>
#include <ntstatus.h>

#include <SecurityRuntime.h>

#include <stdio.h>
