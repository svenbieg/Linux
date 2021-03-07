//====================
// WiFiConnection.cpp
//====================

#include "pch.h"


//=======
// Using
//=======

#include "WiFiConnection.h"


//===========
// Namespace
//===========

namespace Network {
	namespace WiFi {


//==================
// Con-/Destructors
//==================

WiFiConnection::WiFiConnection()
{
Current=this;
AccessPointIp=new IpAddress("WiFiAccessPointIp", 10, 0, 1, 1);
AccessPointSubnet=new IpAddress("WiFiAccessPointSubnet", 255, 255, 255, 0);
StationIp=new IpAddress("WiFiStationIp", 0);
StationGateway=new IpAddress("WiFiStationGateway", 0);
StationSubnet=new IpAddress("WiFiStationSubnet", 0);
}


//========
// Common
//========

VOID WiFiConnection::Close()
{
}

VOID WiFiConnection::Connect()
{
}

Handle<WiFiConnection> WiFiConnection::Current=nullptr;

VOID WiFiConnection::Disconnect()
{
}

}}
