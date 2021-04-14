//================
// SerialPort.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <fcntl.h>
#include <unistd.h>
#include "SerialPort.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Serial {


//==================
// Con-/Destructors
//==================

SerialPort::SerialPort(Handle<String> name):
iFile(-1)
{
iFile=open(name->Begin(), O_RDWR);
if(iFile<0)
	return;
}


//========
// Common
//========

VOID SerialPort::Listen()
{
if(iFile<0)
	return;
hListenTask=CreateTask(this, &SerialPort::DoListen);
}


//==============
// Input-Stream
//==============

SIZE_T SerialPort::Available()
{
return 0;
}

SIZE_T SerialPort::Read(VOID* buf, SIZE_T size)
{
return 0;
}


//===============
// Output-Stream
//===============

VOID SerialPort::Flush()
{
}

SIZE_T SerialPort::Write(VOID const* pbuf, SIZE_T size)
{
ScopedLock lock(cCriticalSection);
if(!pbuf||!size)
	return 0;
return write(iFile, pbuf, size);
}


//================
// Common Private
//================

VOID SerialPort::DoListen()
{
while(!hListenTask->Cancel)
	{
	}
}

}}
