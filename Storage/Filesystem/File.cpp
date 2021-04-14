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
Storage::File(hpath, "Storage.Filesystem.File"),
pFile(nullptr),
uPosition(0),
uSize(usize)
{}

File::~File()
{
DoClose();
}


//==============
// Storage.File
//==============

VOID File::Close()
{
ScopedLock lock(cCriticalSection);
DoClose();
}

BOOL File::Create(FileCreateMode create, FileAccessMode access, FileShareMode share)
{
ScopedLock lock(cCriticalSection);
return DoCreate(create, access, share);
}

BOOL File::SetSize(UINT64 size)
{
ScopedLock lock(cCriticalSection);
if(!pFile)
	return false;
if(uSize==size)
	return true;
if(ftruncate64(fileno(pFile), size)<0)
	return false;
return true;
}


//===========
// Container
//===========

FileSize File::GetSize()
{
return uSize;
}

BOOL File::Seek(UINT64 uoffset)
{
ScopedLock lock(cCriticalSection);
if(!pFile)
	return 0;
if(uoffset>uSize)
	return false;
fseeko64(pFile, uoffset, SEEK_SET);
uPosition=ftello(pFile);
return true;
}


//==============
// Input-Stream
//==============

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
	return 0;
return fread(pbuf, 1, usize, pFile);
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

BOOL File::DoCreate(FileCreateMode create, FileAccessMode access, FileShareMode share)
{
DoClose();
CHAR pacc[3];
pacc[0]='r';
pacc[1]=(access==FileAccessMode::ReadOnly? 0: '+');
pacc[2]=0;
FILE* pfile=fopen(hPath->Begin(), pacc);
if(pfile)
	{
	if(create==FileCreateMode::CreateNew)
		{
		fclose(pfile);
		return false;
		}
	if(access==FileAccessMode::ReadWrite)
		{
		fclose(pfile);
		pfile=nullptr;
		}
	}
else
	{
	if(create==FileCreateMode::OpenExisting)
		return false;
	if(access==FileAccessMode::ReadOnly)
		return false;
	}
if(!pfile)
	{
	pacc[0]='w';
	pacc[1]='+';
	pfile=fopen(hPath->Begin(), pacc);
	if(!pfile)
		return false;
	}
if(create==FileCreateMode::CreateAlways)
	{
	if(ftruncate64(fileno(pfile), 0)<0)
		return false;
	}
else
	{
	fseeko64(pfile, 0, SEEK_END);
	uSize=ftello64(pfile);
	fseeko64(pfile, 0, SEEK_SET);
	}
pFile=pfile;
return true;
}

}}