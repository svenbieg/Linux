//===============
// Application.h
//===============

#pragma once


//=======
// Using
//=======

#include "Core/Application.h"


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

class Application: public Core::Application
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