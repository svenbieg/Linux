//================
// TimeHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <time.h>
#include <unistd.h>
#include "TimeHelper.h"


//========
// Common
//========

UINT GetTickCount()
{
timespec ts;
clock_gettime(CLOCK_REALTIME, &ts);
UINT uticks=(UINT)(ts.tv_nsec/1000000);
uticks+=(UINT)(ts.tv_sec*1000);
return uticks;
}

UINT64 GetTickCount64()
{
timespec ts;
clock_gettime(CLOCK_REALTIME, &ts);
UINT64 uticks=ts.tv_nsec/1000000;
uticks+=ts.tv_sec*1000;
return uticks;
}

VOID Sleep(UINT ums)
{
usleep(ums);
}
