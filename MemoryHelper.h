//================
// MemoryHelper.h
//================

#pragma once


//=======
// Using
//=======

#include "TypeHelper.h"


//==============
// Architecture
//==============

#if(defined(_M_AMD64)||defined(_M_ARM64))
#define _BITS64
#define IF32(x)
#define IF64(x) x
#else
#define _BITS32
#define IF32(x) x
#define IF64(x)
#endif


//============
// Allocation
//============

VOID* Alloc(SIZE_T Size);
VOID* DeviceAlloc(SIZE_T Size);
VOID DeviceFree(VOID* Buffer);
VOID Free(VOID* Buffer);
