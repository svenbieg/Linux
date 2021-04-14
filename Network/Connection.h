//==============
// Connection.h
//==============

#pragma once


//=======
// Using
//=======

#include "Common/Network/Connection.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Details {


//============
// Connection
//============

class Connection: public Network::Connection
{
public:
	// Con-/Destructors
	Connection();

	// Common
	VOID Connect()override {}
	static Handle<Connection> Current;
	VOID Disconnect()override {}
	BOOL IsConnected()override { return true; }
};

}}