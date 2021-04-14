//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Network/Connection.h"
#include "Application.h"
#include "System.h"

using namespace Console;
using namespace Network;

extern VOID Initialize();


//=============
// Entry-Point
//=============

#ifdef _CONSOLE

INT main()
{
Initialize();
auto happ=Application::Current;
while(happ->Status==AppStatus::Running)
	{
	System::Memory->Update();
	happ->Loop(happ);
	Sleep(10);
	}
return 0;
}

#endif


//===========
// Namespace
//===========

namespace Console {


//==================
// Con-/Destructors
//==================

Application::Application(Handle<String> hname):
Core::Application(hname),
Status(AppStatus::Running)
{
Current=this;
}


//========
// Common
//========

Handle<Application> Application::Current;

VOID Application::Exit()
{
Status=AppStatus::Closed;
}

}