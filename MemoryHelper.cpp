//==================
// MemoryHelper.cpp
//==================

#include "pch.h"


//=======
// Using
//=======

#include <malloc.h>
#include "MemoryHelper.h"


//============
// Allocation
//============

VOID* Alloc(SIZE_T size)
{
return malloc(size);
}

VOID* DeviceAlloc(SIZE_T size)
{
return memalign(16, size);
}

VOID DeviceFree(VOID* buf)
{
free(buf);
}

VOID Free(VOID* buf)
{
free(buf);
}
