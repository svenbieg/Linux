//==================
// WiFiConnection.h
//==================

#pragma once


//=======
// Using
//=======

#include "Network/Http/HttpServer.h"
#include "Network/Connection.h"
#include "Network/IpAddress.h"
#include "Web/WebPage.h"


//===========
// Namespace
//===========

namespace Network {
	namespace WiFi {


//=================
// WiFi-Connection
//=================

class WiFiConnection: public Connection
{
private:
	// Using
	using HttpServer=Network::Http::HttpServer;
	using IpAddress=Network::IpAddress;
	using _WebPage=Web::WebPage;

public:
	// Con-/Destructors
	WiFiConnection();

	// Common
	Handle<IpAddress> AccessPointIp;
	Handle<String> AccessPointNetwork;
	Handle<String> AccessPointPassword;
	Handle<IpAddress> AccessPointSubnet;
	VOID Close();
	VOID Connect()override;
	Event<WiFiConnection> Connected;
	static Handle<WiFiConnection> Current;
	VOID Disconnect()override;
	Event<WiFiConnection> Disconnected;
	BOOL IsConnected()override { return StationIp->Get()!=0; }
	Handle<IpAddress> StationIp;
	Handle<IpAddress> StationGateway;
	Handle<StringVariable> StationNetwork;
	Handle<StringVariable> StationPassword;
	Handle<IpAddress> StationSubnet;
	Handle<_WebPage> WebPage;
};

}}
