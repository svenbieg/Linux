//=================
// ClockHelper.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include <time.h>
#include "ClockHelper.h"

using namespace Physics;


//===========
// Namespace
//===========

namespace Devices {


//========
// Common
//========

BOOL ClockGetTime(TIMEPOINT& tp, UINT udelta)
{
time_t tnow;
time(&tnow);
tnow-=udelta;
tm* ptmnow=localtime(&tnow);
if(ptmnow->tm_year+1900<2000)
	return false;
tp.Second=(BYTE)ptmnow->tm_sec;
tp.Minute=(BYTE)ptmnow->tm_min;
tp.Hour=(BYTE)ptmnow->tm_hour;
tp.DayOfWeek=(BYTE)ptmnow->tm_wday;
tp.DayOfMonth=(BYTE)ptmnow->tm_mday;
tp.Month=(BYTE)ptmnow->tm_mon;
tp.Year=(WORD)ptmnow->tm_year;
return true;
}

}