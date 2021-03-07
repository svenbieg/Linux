//============
// System.cpp
//============

#include "pch.h"


//=======
// Using
//=======

#include <sys/reboot.h>
#include <unistd.h>
#include "System.h"

using namespace Devices;
using namespace Physics;


//========
// Common
//========

Handle<Memory> System::Memory=new Devices::Memory();

VOID System::Reset()
{
Restart();
}

VOID System::Restart()
{
sync();
reboot(RB_AUTOBOOT);
}

Handle<TimePoint> System::Start=new TimePoint("SystemStart");

Handle<Float> System::Voltage=new Float("SystemVoltage", 3.3f);
