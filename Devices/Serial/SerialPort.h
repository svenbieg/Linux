//==============
// SerialPort.h
//==============

#pragma once


//=======
// Using
//=======

#include "Storage/Streams/RandomAccessStream.h"


//===========
// Namespace
//===========

namespace Devices {
	namespace Serial {


//=============
// Serial-Port
//=============

class SerialPort: public ::Storage::Streams::RandomAccessStream
{
public:
	// Con-/Destructors
	SerialPort(Handle<String> Name="/dev/ttyS0");

	// Common
	Event<SerialPort> DataReceived;
	VOID Listen();

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Common
	VOID DoListen();
	CriticalSection cCriticalSection;
	Handle<Task> hListenTask;
	INT iFile;
};

}}
