//===================
// TcpConnection.cpp
//===================

#include "pch.h"


//=======
// Using
//=======

#include <sys/socket.h>
#include <unistd.h>
#include "Core/Application.h"
#include "TcpConnection.h"

using namespace Core;


//===========
// Namespace
//===========

namespace Network {
	namespace Tcp {


//==================
// Con-/Destructors
//==================

TcpConnection::TcpConnection(INT isocket):
iSocket(isocket),
uStatus(TcpConnectionStatus::Open),
uTimeout(0)
{
InputBuffer=new PacketBuffer();
Application::Current->Loop.Add(this, &TcpConnection::OnLoop);
}

TcpConnection::~TcpConnection()
{
CloseInternal();
}


//========
// Common
//========

VOID TcpConnection::Close()
{
if(uStatus==TcpConnectionStatus::Closed)
	return;
CloseInternal();
uStatus=TcpConnectionStatus::Closed;
Closed(this);
}

VOID TcpConnection::SetTimeout(UINT utimeout)
{
UINT64 utime=GetTickCount64();
uTimeout=utime+utimeout;
}


//==============
// Input-Stream
//==============

SIZE_T TcpConnection::Available()
{
return InputBuffer->Available();
}

SIZE_T TcpConnection::Read(VOID* pbuf, SIZE_T usize)
{
return InputBuffer->Read(pbuf, usize);
}


//===============
// Output-Stream
//===============

VOID TcpConnection::Flush()
{
shutdown(iSocket, SHUT_WR);
DataSent(this);
}

SIZE_T TcpConnection::Write(VOID const* pbuf, SIZE_T usize)
{
UINT uwrite=(UINT)MIN(usize, 2048);
UINT uwritten=(UINT)write(iSocket, pbuf, uwrite);
SetTimeout(10000);
if(uwritten>uwrite)
	return 0;
return uwritten;
}


//================
// Common Private
//================

VOID TcpConnection::CloseInternal()
{
if(iSocket!=-1)
	{
	close(iSocket);
	iSocket=-1;
	}
Application::Current->Loop.Remove(this);
InputBuffer->Clear();
}

VOID TcpConnection::OnLoop()
{
Send(this);
CHAR pbuf[512];
ssize_t ilen=read(iSocket, pbuf, 512);
if(ilen==0)
	{
	if(uTimeout==0)
		return;
	UINT64 utime=GetTickCount64();
	if(utime>uTimeout)
		Close();
	return;
	}
InputBuffer->Write(pbuf, ilen);
DataReceived(this);
}

}}