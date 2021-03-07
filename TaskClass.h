//=============
// TaskClass.h
//=============

#pragma once


//=======
// Using
//=======

/*#include <pthread.h>
#include "Handle.h"
#include "TaskHelper.h"


//========
// Status
//========

enum class TaskStatus
{
Running,
Done,
Cancel
};


//======
// Task
//======

template <class RET>
class Task: public Object
{
public:
	// Con-/Destructors
	Task(Function<RET()> Function): Task([Function](Task<RET>* ptask){ return Function(); }) {}
	Task(Function<RET(Task<RET>*)> Function):
		cFunction(Function),
		hThis(this),
		uException(Exception::None),
		uStatus(TaskStatus::Running)
		{
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		pthread_create(&uId, &attr, RunAsync, this);
		pthread_attr_destroy(&attr);
		}

	// Common
	VOID Cancel()
		{
		if(uStatus==TaskStatus::Running)
			uStatus=TaskStatus::Cancel;
		}
	RET Get()
		{
		if(hThis==nullptr)
			return tReturnValue;
		pthread_join(uId, nullptr);
		if(uException!=Exception::None)
			Throw(uException);
		return tReturnValue;
		}
	TaskStatus GetStatus()const { return uStatus; }
	VOID Wait()
		{
		if(hThis==nullptr)
			return;
		pthread_join(uId, nullptr);
		if(uException!=Exception::None)
			Throw(uException);
		}

private:
	// Allgemein
	static VOID* RunAsync(VOID* TaskPtr)
		{
		Task<RET>* ptask=(Task<RET>*)TaskPtr;
		try
			{
			ptask->tReturnValue=ptask->cFunction(ptask);
			}
		catch(Exception exc)
			{
			ptask->uException=exc;
			}
		ptask->uStatus=TaskStatus::Done;
		ptask->hThis=nullptr;
		return nullptr;
		}
	Function<RET(Task<RET>*)> cFunction;
	Handle<Task<RET>> hThis;
	RET tReturnValue;
	Exception uException;
	pthread_t uId;
	TaskStatus uStatus;
};

template <>
class Task<VOID>: public Object
{
public:
	// Con-/Destructors
	Task(Function<VOID()> Function): Task([Function](Task<VOID>* ptask){ Function(); }) {}
	Task(Function<VOID(Task<VOID>*)> Function):
		cFunction(Function),
		hThis(this),
		uException(Exception::None),
		uStatus(TaskStatus::Running)
		{
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		pthread_create(&uId, &attr, RunAsync, this);
		pthread_attr_destroy(&attr);
		}

	// Common
	VOID Cancel()
		{
		if(uStatus==TaskStatus::Running)
			uStatus=TaskStatus::Cancel;
		}
	TaskStatus GetStatus()const { return uStatus; }
	VOID Wait()
		{
		if(hThis==nullptr)
			return;
		pthread_join(uId, nullptr);
		if(uException!=Exception::None)
			Throw(uException);
		}

private:
	// Allgemein
	static VOID* RunAsync(VOID* TaskPtr)
		{
		Task<VOID>* ptask=(Task<VOID>*)TaskPtr;
		try
			{
			ptask->cFunction(ptask);
			}
		catch(Exception exc)
			{
			ptask->uException=exc;
			}
		ptask->uStatus=TaskStatus::Done;
		ptask->hThis=nullptr;
		return nullptr;
		}
	Function<VOID(Task<VOID>*)> cFunction;
	Handle<Task<VOID>> hThis;
	Exception uException;
	pthread_t uId;
	TaskStatus uStatus;
};
*/