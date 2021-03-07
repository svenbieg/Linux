//===================
// CriticalSection.h
//===================

#pragma once


//=======
// Using
//=======

#include <mutex>


//==================
// Critical Section
//==================

class CriticalSection
{
public:
	// Con-/Destructors
	CriticalSection() {}

	// Common
	inline BOOL IsLocked() { if(cMutex.try_lock()){ cMutex.unlock(); return false; } return true; }
	inline VOID Lock() { cMutex.lock(); }
	inline BOOL TryLock() { return cMutex.try_lock(); }
	inline VOID Unlock() { cMutex.unlock(); }

private:
	// Common
	std::mutex cMutex;
};
