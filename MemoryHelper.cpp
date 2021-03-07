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

VOID* Alloc(SIZE_T usize)
{
return malloc(usize);
}

VOID Free(VOID* pbuf)
{
free(pbuf);
}
