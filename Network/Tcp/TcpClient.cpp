//===============
// TcpClient.cpp
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
#include <poll.h>
#include <unistd.h>
#include "Core/Application.h"
#include "TcpClient.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//==================
// Con-/Destructors
//==================

TcpClient::TcpClient():
iSocket(-1),
uPort(0),
uStatus(TcpClientStatus::Closed)
{}

TcpClient::~TcpClient()
{
Close();
}


//========
// Common
//========

VOID TcpClient::Close()
{
if(uStatus==TcpClientStatus::Closed)
	return;
if(iSocket!=-1)
	{
	close(iSocket);
	iSocket=-1;
	}
Application::Current->Loop.Remove(this);
hUrl=nullptr;
uPort=0;
uStatus=TcpClientStatus::Closed;
Closed(this);
}

VOID TcpClient::Connect(Handle<String> hurl, WORD uport)
{
Close();
INT isocket=socket(AF_INET, SOCK_STREAM, 0);
if(isocket<0)
	{
	DebugPrint("TcpClient - socket() failed (%i)\n", isocket);
	return;
	}
INT inoblock=1;
INT istatus=ioctl(isocket, FIONBIO, (ULONG*)&inoblock);
if(istatus!=0)
	{
	DebugPrint("TcpServer - ioctl() failed (%i)\n", istatus);
	close(isocket);
	return;
	}
hUrl=hurl;
iSocket=isocket;
uPort=uport;
uStatus=TcpClientStatus::Initializing;
Application::Current->Loop.Add(this, &TcpClient::OnLoop);
}


//================
// Common Private
//================

VOID TcpClient::OnLoop()
{
if(iSocket==-1)
	return;
if(uStatus==TcpClientStatus::Initializing)
	{
	#ifdef _UNICODE
	CHAR phost[MAX_PATH];
	StringCopy(phost, MAX_PATH, hUrl->Begin());
	#else
	LPCSTR phost=hUrl->Begin();
	#endif
	sockaddr_in addr;
	if(!ResolveHostName(phost, &addr))
		{
		Close();
		return;
		}
	addr.sin_port=htons(uPort);
	INT istatus=connect(iSocket, (sockaddr*)&addr, sizeof(addr));
	if(istatus==0)
		{
		uStatus=TcpClientStatus::ConnectionEstablished;
		}
	else
		{
		if(istatus!=EINPROGRESS)
			{
			Close();
			return;
			}
		uStatus=TcpClientStatus::Connecting;
		}
	}
if(uStatus==TcpClientStatus::Connecting)
	{
	pollfd fd;
	ZeroMemory(&fd, sizeof(pollfd));
	fd.fd=iSocket;
	fd.events=POLLOUT;
	INT istatus=poll(&fd, 1, 0);
	if(istatus!=0)
		return;
	if(fd.revents&POLLOUT)
		uStatus=TcpClientStatus::ConnectionEstablished;
	}
if(uStatus==TcpClientStatus::ConnectionEstablished)
	{
	Handle<TcpConnection> hcon=new TcpConnection(iSocket);
	hUrl=nullptr;
	iSocket=-1;
	uPort=0;
	uStatus=TcpClientStatus::Connected;
	Connected(this, hcon);
	}
}

BOOL TcpClient::ResolveHostName(LPCSTR purl, VOID* pres)
{
addrinfo addr;
ZeroMemory(&addr, sizeof(addr));
addr.ai_family=AF_INET;
addr.ai_socktype=SOCK_STREAM;
addrinfo* presult=nullptr;
getaddrinfo(purl, nullptr, &addr, &presult);
if(presult)
	{
	sockaddr_in* paddr=(sockaddr_in*)pres;
	*paddr=*(sockaddr_in*)(presult->ai_addr);
	freeaddrinfo(presult);
	return true;
	}
return false;
}

}}