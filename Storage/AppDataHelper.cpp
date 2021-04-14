//===================
// AppDataHelper.cpp
//===================

#include "pch.h"


//=======
// Using
//=======

#include <unistd.h>
#include "Core/Application.h"
#include "Storage/Filesystem/Directory.h"
#include "AppDataHelper.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Storage {


//========
// Common
//========

Handle<Directory> GetAppDataLocal()
{
auto hname=Application::Current->Name;
if(!hname)
	return nullptr;
auto login=getlogin();
Handle<String> path=new String("/home/%s/AppData/Local/%s", login, hname->Begin());
return new Filesystem::Directory("Local", path);
}

Handle<Directory> GetAppDataNetwork()
{
auto hname=Application::Current->Name;
if(!hname)
	return nullptr;
auto login=getlogin();
Handle<String> path=new String("/home/%s/AppData/Network/%s", login, hname->Begin());
return new Filesystem::Directory("Network", path);
}

}