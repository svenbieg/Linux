//==========
// File.cpp
//==========

#include "pch.h"


//=======
// Using
//=======

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "File.h"
#include "PathHelper.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//==================
// Con-/Destructors
//==================

File::File(Handle<String> hpath, UINT64 usize):
Storage::File(PathGetName(hpath), "Storage.Filesystem.File"),
hPath(hpath),
pFile(nullptr),
uPosition(0),
uSize(usize)
{}

File::~File()
{
DoClose();
}

VOID File::Close()
{
ScopedLock lock(cCriticalSection);
DoClose();
}

BOOL File::Create(BOOL boverwrite)
{
ScopedLock lock(cCriticalSection);
return DoCreate(boverwrite);
}

BOOL File::Open(BOOL breadonly, BOOL bcreate)
{
ScopedLock lock(cCriticalSection);
return DoOpen(breadonly, bcreate);
}


//=========================
// Con-/Destructors Static
//=========================

Handle<File> File::Create(Handle<String> hpath, BOOL boverwrite)
{
Handle<File> hfile=new File(hpath);
if(hfile->Create(boverwrite))
	return hfile;
return nullptr;
}

Handle<File> File::Open(Handle<String> hpath, BOOL breadonly, BOOL bcreate)
{
Handle<File> hfile=new File(hpath);
if(hfile->Open(breadonly, bcreate))
	return hfile;
return nullptr;
}


//========
// Access
//========

SIZE_T File::Available()
{
ScopedLock lock(cCriticalSection);
return uSize-uPosition;
}

SIZE_T File::Read(VOID* pbuf, SIZE_T usize)
{
if(!pbuf||!usize)
	return 0;
ScopedLock lock(cCriticalSection);
if(!pFile)
	{
	if(!DoOpen(true, false))
		return 0;
	}
return fread(pbuf, 1, usize, pFile);
}

BOOL File::Seek(UINT64 uoffset)
{
ScopedLock lock(cCriticalSection);
if(!pFile)
	{
	if(!DoOpen(true, false))
		return 0;
	}
if(uoffset>uSize)
	return false;
fseeko64(pFile, uoffset, SEEK_SET);
uPosition=ftello64(pFile);
return true;
}


//==============
// Modification
//==============

VOID File::Flush()
{
if(pFile)
	fflush(pFile);
}

SIZE_T File::Write(VOID const* pbuf, SIZE_T usize)
{
if(!pbuf||!usize)
	return 0;
ScopedLock lock(cCriticalSection);
if(pFile==nullptr)
	return 0;
SIZE_T uwritten=fwrite(pbuf, 1, usize, pFile);
uPosition+=uwritten;
if(uPosition>uSize)
	uSize=uPosition;
return uwritten;
}


//================
// Common Private
//================

VOID File::DoClose()
{
if(pFile!=nullptr)
	{
	fclose(pFile);
	pFile=nullptr;
	}
uPosition=0;
}

BOOL File::DoCreate(BOOL boverwrite)
{
DoClose();
CHAR pacc[3];
pacc[0]='r';
pacc[1]=0;
pacc[2]=0;
FILE* pfile=fopen(hPath->Begin(), pacc);
if(pfile)
	{
	fclose(pfile);
	if(!boverwrite)
		return false;
	}
pacc[0]='w';
pacc[1]='+';
pfile=fopen(hPath->Begin(), pacc);
if(!pfile)
	return false;
pFile=pfile;
uSize=0;
return true;
}

BOOL File::DoOpen(BOOL breadonly, BOOL bcreate)
{
DoClose();
CHAR pacc[3];
pacc[0]='r';
pacc[1]=breadonly? 0: '+';
pacc[2]=0;
FILE* pfile=fopen(hPath->Begin(), pacc);
if(pfile==nullptr)
	{
	if(!bcreate)
		return false;
	pacc[0]='w';
	pacc[1]='+';
	pfile=fopen(hPath->Begin(), pacc);
	if(!pfile)
		return false;
	}
pFile=pfile;
fseeko64(pFile, 0, SEEK_END);
uSize=ftello64(pFile);
fseeko64(pFile, 0, SEEK_SET);
return true;
}

}}