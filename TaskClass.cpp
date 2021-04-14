//===============
// TaskClass.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "TaskClass.h"


//========
// Common
//========

VOID Task::Wait()
{
if(!hThis)
	return;
pthread_join(uId, nullptr);
}


//============================
// Con-/Destructors Protected
//============================

Task::Task():
uId(0)
{}
