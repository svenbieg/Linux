//===============
// TcpServer.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include "Core/Application.h"
#include "TcpServer.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//==================
// Con-/Destructors
//==================

TcpServer::TcpServer():
iSocket(-1)
{}

TcpServer::~TcpServer()
{
Close();
}


//========
// Common
//========

VOID TcpServer::Close()
{
if(iSocket!=-1)
	{
	close(iSocket);
	iSocket=-1;
	}
Application::Current->Loop.Remove(this);
Closed(this);
}

VOID TcpServer::Listen(WORD uport)
{
if(iSocket!=-1)
	Close();
addrinfo addr;
ZeroMemory(&addr, sizeof(addr));
addr.ai_family=AF_INET;
addr.ai_socktype=SOCK_STREAM;
addr.ai_protocol=IPPROTO_TCP;
addr.ai_flags=AI_PASSIVE;
addrinfo* paddr=nullptr;
if(uport==80) // iptables -t nat -A PREROUTING -p tcp --dport 80 -j REDIRECT --to-port 8000
	uport=8000;
CHAR pport[8];
StringPrint(pport, 8, "%u", (UINT)uport);
INT istatus=getaddrinfo(NULL, pport, &addr, &paddr);
if(istatus!=0)
	{
	DebugPrint("TcpServer - getaddrinfo failed (%i)\n", istatus);
	return;
	}
INT isocket=socket(paddr->ai_family, paddr->ai_socktype, paddr->ai_protocol);
if(isocket<0)
	{
	DebugPrint("TcpServer - socket() failed (%i)\n", isocket);
	freeaddrinfo(paddr);
	return;
	}
INT inoblock=1;
istatus=ioctl(isocket, FIONBIO, (ULONG*)&inoblock);
if(istatus!=0)
	{
	DebugPrint("TcpServer - ioctl() failed (%i)\n", istatus);
	close(isocket);
	freeaddrinfo(paddr);
	return;
	}
INT ireuse=1;
if(setsockopt(isocket, SOL_SOCKET, SO_REUSEADDR, &ireuse, sizeof(INT))<0)
	{
	DebugPrint("TcpServer - setsockopt() failed (%i)\n", errno);
	close(isocket);
	freeaddrinfo(paddr);
	return;
	}
istatus=bind(isocket, paddr->ai_addr, (INT)paddr->ai_addrlen);
if(istatus!=0)
	{
	DebugPrint("TcpServer - bind() failed (%i)\n", errno);
	close(isocket);
	freeaddrinfo(paddr);
	return;
	}
freeaddrinfo(paddr);
istatus=listen(isocket, SOMAXCONN);
if(istatus!=0)
	{
	DebugPrint("TcpServer - listen() failed (%i)\n", istatus);
	close(isocket);
	return;
	}
iSocket=isocket;
Application::Current->Loop.Add(this, &TcpServer::OnLoop);
}


//================
// Common Private
//================

VOID TcpServer::OnLoop()
{
INT isocket=accept(iSocket, nullptr, nullptr);
if(isocket<0)
	{
	INT ierr=errno;
	if(ierr==EWOULDBLOCK)
		return;
	DebugPrint("TcpServer- accept() failed (%i)\n", ierr);
	return;
	}
Handle<TcpConnection> hcon=new TcpConnection(isocket);
ConnectionReceived(this, hcon);
}

}}