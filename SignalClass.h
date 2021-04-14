//===============
// SignalClass.h
//===============

#pragma once


//=======
// Using
//=======

#include "CriticalSection.h"


//========
// Signal
//========

class Signal
{
public:
	// Con-/Destructors
	Signal() { pthread_cond_init(&cCondition, nullptr); }
	~Signal() { pthread_cond_destroy(&cCondition); }

	// Common
	VOID Broadcast() { pthread_cond_broadcast(&cCondition); }
	VOID Wait(CriticalSection& CriticalSection) { pthread_cond_wait(&cCondition, &CriticalSection.cMutex); }

private:
	// Common
	pthread_cond_t cCondition;
};
