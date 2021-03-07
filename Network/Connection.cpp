//================
// Connection.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <unistd.h>
#include "Connection.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Details {


//==================
// Con-/Destructors
//==================

Connection::Connection()
{
Current=this;
CHAR phostname[32];
gethostname(phostname, 32);
HostName=phostname;
}


//========
// Common
//========

Handle<Connection> Connection::Current=new Connection();

}}