//===============
// Application.h
//===============

#pragma once


//=======
// Using
//=======

#include "Core/Application.h"
#include "Storage/Storables/Log.h"
#include "Storage/Storables/Settings.h"
#include "Storage/AppData.h"


//===========
// Namespace
//===========

namespace Runtime {


//=============
// Application
//=============

class Application: public Core::Application
{
public:
	// Common
	Handle<Storage::AppData> AppData;
	static Handle<Application> Current;
	Handle<Storage::Storables::Log> Log;
	Handle<Storage::Storables::Settings> Settings;
	VOID Update() {}
	Handle<StringVariable> UpdateStatus;

protected:
	// Con-/Destructors
	Application(Handle<String> Name, Handle<String> UpdateUrl=nullptr);
};

}