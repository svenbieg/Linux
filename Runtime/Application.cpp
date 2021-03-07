//=================
// Application.cpp
//=================

#include "pch.h"


//=======
// Using
//=======

#include "Application.h"


//===========
// Namespace
//===========

namespace Runtime {


//========
// Common
//========

Handle<Application> Application::Current;


//============================
// Con-/Destructors Protected
//============================

Application::Application(Handle<String> hname, Handle<String> hurl):
Core::Application(hname)
{
Current=this;
AppData=new Storage::AppData();
Log=new Storage::Storables::Log();
Settings=new Storage::Storables::Settings();
UpdateStatus=new StringVariable("UpdateStatus");
}

}