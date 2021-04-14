//=============
// TaskClass.h
//=============

#pragma once


//=======
// Using
//=======

#include <functional>
#include <pthread.h>
#include "Handle.h"


//======
// Task
//======

class Task: public Object
{
public:
	// Common
	volatile BOOL Cancel;
	VOID Wait();

protected:
	// Con-/Destructors
	Task();

	// Common
	Handle<Task> hThis;
	pthread_t uId;
};


//============
// Task Typed
//============

template <class _owner_t, class... _args_t>
class TaskTyped: public Task
{
public:
	// Using
	typedef VOID (_owner_t::*TaskProc)(_args_t...);

	// Con-/Destructors
	TaskTyped(_owner_t* Owner, TaskProc Procedure):
		hOwner(Owner),
		pProcedure(Procedure)
		{}

	// Common
	VOID Run(_args_t... Arguments)
		{
		if(hThis)
			return;
		hThis=this;
		cProcedure=[this, Arguments...](){ (hOwner->*pProcedure)(Arguments...); };
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		pthread_create(&uId, &attr, DoTask, this);
		pthread_attr_destroy(&attr);
		}

private:
	// Common
	static VOID* DoTask(VOID* Param)
		{
		Handle<TaskTyped> task=(TaskTyped*)Param;
		task->cProcedure();
		task->hThis=nullptr;
		return nullptr;
		}
	std::function<VOID()> cProcedure;
	Handle<_owner_t> hOwner;
	TaskProc pProcedure;
};
