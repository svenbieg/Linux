//===================
// AppDataHelper.cpp
//===================

#include "pch.h"


//=======
// Using
//=======

#include <unistd.h>
#include "Runtime/Application.h"
#include "AppDataHelper.h"

using namespace Runtime;


//===========
// Namespace
//===========

namespace Storage {


//========
// Common
//========

Handle<String> GetAppDataLocalPath()
{
CHAR puser[32];
getlogin_r(puser, 32);
auto hname=Application::Current->Name;
if(!hname)
	return nullptr;
return new String("/home/%s/AppData/Local/%s", puser, hname->Begin());
}

Handle<String> GetAppDataNetworkPath()
{
CHAR puser[32];
getlogin_r(puser, 32);
auto hname=Application::Current->Name;
if(!hname)
	return nullptr;
return new String("/home/%s/AppData/Network/%s", puser, hname->Begin());
}

}