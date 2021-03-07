//=============
// TcpClient.h
//=============

#pragma once


//=======
// Using
//=======

#include "TcpConnection.h"


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//========
// Status
//========

enum class TcpClientStatus
{
Closed,
Initializing,
Connecting,
ConnectionEstablished,
Connected
};


//============
// Tcp-Client
//============

class TcpClient: public Object
{
public:
	// Con-/Destructors
	TcpClient();
	~TcpClient();

	// Common
	VOID Close();
	Event<TcpClient> Closed;
	VOID Connect(Handle<String> Address, WORD Port);
	Event<TcpClient, Handle<TcpConnection>> Connected;

private:
	// Common
	VOID OnLoop();
	BOOL ResolveHostName(LPCSTR Url, VOID* Address);
	Handle<String> hUrl;
	INT iSocket;
	WORD uPort;
	TcpClientStatus uStatus;
};

}}