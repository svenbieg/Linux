//===============
// Application.h
//===============

#pragma once


//=======
// Using
//=======

#include "Runtime/Application.h"


//===========
// Namespace
//===========

namespace Console {


//========
// Status
//========

enum class AppStatus
{
Closed=0,
Running=1,
};


//=============
// Application
//=============

class Application: public Runtime::Application
{
public:
	// Con-/Destructors
	Application(Handle<String> Name);

	// Common
	static Handle<Application> Current;
	VOID Exit();
	AppStatus Status;
};

}