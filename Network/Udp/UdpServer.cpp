//===============
// UdpServer.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "Core/Application.h"
#include "UdpServer.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Network {
	namespace Udp {


//==================
// Con-/Destructors
//==================

UdpServer::UdpServer():
iSocket(-1)
{}

UdpServer::~UdpServer()
{
Close();
}


//========
// Common
//========

VOID UdpServer::Close()
{
if(iSocket!=-1)
	{
	close(iSocket);
	iSocket=-1;
	Application::Current->Loop.Remove(this);
	}
}

VOID UdpServer::Listen(WORD uport)
{
if(iSocket!=-1)
	Close();
addrinfo addr;
ZeroMemory(&addr, sizeof(addr));
addr.ai_family=AF_INET;
addr.ai_socktype=SOCK_DGRAM;
addr.ai_protocol=IPPROTO_UDP;
addr.ai_flags=AI_PASSIVE;
addrinfo* paddr=nullptr;
CHAR pport[8];
StringPrint(pport, 8, "%u", (UINT)uport);
INT istatus=getaddrinfo(NULL, pport, &addr, &paddr);
if(istatus!=0)
	{
	DebugPrint("UdpServer - getaddrinfo failed (%i)\n", istatus);
	return;
	}
INT isocket=socket(paddr->ai_family, paddr->ai_socktype, paddr->ai_protocol);
if(isocket<0)
	{
	DebugPrint("UdpServer - socket() failed (%i)\n", isocket);
	freeaddrinfo(paddr);
	return;
	}
istatus=bind(isocket, paddr->ai_addr, (INT)paddr->ai_addrlen);
if(istatus!=0)
	{
	DebugPrint("UdpServer - bind() failed (%i)\n", istatus);
	close(isocket);
	freeaddrinfo(paddr);
	return;
	}
freeaddrinfo(paddr);
iSocket=isocket;
Application::Current->Loop.Add(this, &UdpServer::OnLoop);
}


//================
// Common Private
//================

VOID UdpServer::OnLoop()
{
CHAR pbuf[512];
SIZE_T ilen=recv(iSocket, pbuf, 512, 0);
if(ilen<=0)
	return;
WORD usize=(WORD)ilen;
Handle<UdpMessage> hmsg=new UdpMessage(pbuf, usize);
MessageReceived(this, hmsg);
}

}}