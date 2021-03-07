//=================
// MemoryClass.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <sys/sysinfo.h>
#include "MemoryClass.h"


//===========
// Namespace
//===========

namespace Devices {


//==================
// Con-/Destructors
//==================

Memory::Memory()
{
struct sysinfo info;
sysinfo(&info);
Available=new Int64("MemoryAvailable", info.freeram);
Total=new Int64("MemoryTotal", info.totalram);
}


//========
// Common
//========

VOID Memory::Update()
{
struct sysinfo info;
sysinfo(&info);
Available=info.freeram;
}

}
