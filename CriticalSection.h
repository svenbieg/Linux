//===================
// CriticalSection.h
//===================

#pragma once


//=======
// Using
//=======

#include <pthread.h>
#include "TypeHelper.h"


//======================
// Forward-Declarations
//======================

class Signal;


//==================
// Critical Section
//==================

class CriticalSection
{
public:
	// Friends
	friend Signal;

	// Con-/Destructors
	CriticalSection() { pthread_mutex_init(&cMutex, nullptr); }
	~CriticalSection() { pthread_mutex_destroy(&cMutex); }

	// Common
	inline BOOL IsLocked() { if(pthread_mutex_trylock(&cMutex)){ pthread_mutex_unlock(&cMutex); return false; } return true; }
	inline VOID Lock() { pthread_mutex_lock(&cMutex); }
	inline BOOL TryLock() { return pthread_mutex_trylock(&cMutex); }
	inline VOID Unlock() { pthread_mutex_unlock(&cMutex); }

private:
	// Common
	pthread_mutex_t cMutex;
};
