//===============
// Directory.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include <dirent.h>
#include "Directory.h"
#include "File.h"
#include "FileHelper.h"
#include "PathHelper.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//==================
// Con-/Destructors
//==================

Directory::Directory(Handle<String> hname, Handle<String> hpath, Handle<Storage::Directory> hparent):
Storage::Directory(hname, "Storage.Filesystem.Directory", hparent),
hPath(hpath),
pDirectory(nullptr)
{}


//========
// Common
//========

Handle<Convertible> Directory::Get(Handle<String> hpath)
{
if(!hpath)
	return nullptr;
ScopedLock lock(cCriticalSection);
auto ppath=hpath->Begin();
UINT upos=0;
while(PathIsSeparator(ppath[upos]))
	upos++;
UINT uclen=PathGetComponentLength(&ppath[upos]);
if(!uclen)
	return this;
Handle<String> hname=new String(uclen, &ppath[upos]);
upos+=uclen;
Handle<String> hitempath=new String("%s/%s", hPath->Begin(), hname->Begin());
FILE* pfile=fopen(hitempath->Begin(), "r+");
if(pfile)
	{
	fseeko64(pfile, 0, SEEK_END);
	UINT64 usize=ftello64(pfile);
	fclose(pfile);
	return new File(hitempath, usize);
	}
if(errno==EISDIR)
	{
	Handle<Directory> hsub=new Directory(hname, hitempath, this);
	if(ppath[upos]==0)
		return hsub;
	return hsub->Get(&ppath[upos]);
	}
return nullptr;
}


//==================
// Common Protected
//==================

VOID Directory::FindClose()
{
if(pDirectory)
	{
	closedir((DIR*)pDirectory);
	pDirectory=nullptr;
	}
hCurrent=nullptr;
cCriticalSection.Unlock();
}

Handle<Convertible> Directory::FindCurrent()
{
return hCurrent;
}

Handle<Convertible> Directory::FindFirst()
{
cCriticalSection.TryLock();
hCurrent=nullptr;
if(pDirectory)
	{
	closedir((DIR*)pDirectory);
	pDirectory=nullptr;
	}
DIR* pdir=opendir(hPath->Begin());
if(!pdir)
	return nullptr;
pDirectory=pdir;
while(1)
	{
	auto pent=readdir(pdir);
	if(!pent)
		break;
	if(pent->d_name[0]=='.')
		continue;
	Handle<String> hpath=new String("%s/%s", hPath->Begin(), pent->d_name);
	if(IsDirectory(hpath->Begin()))
		{
		hCurrent=new Directory(pent->d_name, hpath, this);
		break;
		}
	UINT64 usize=GetFileSize(hpath->Begin());
	hCurrent=new File(hpath, usize);
	break;
	}
if(!hCurrent)
	{
	if(pDirectory)
		{
		closedir((DIR*)pDirectory);
		pDirectory=nullptr;
		}
	}
return hCurrent;
}

Handle<Convertible> Directory::FindNext()
{
if(!pDirectory)
	return nullptr;
auto pent=readdir((DIR*)pDirectory);
if(!pent)
	{
	closedir((DIR*)pDirectory);
	pDirectory=nullptr;
	hCurrent=nullptr;
	return nullptr;
	}
Handle<String> hpath=new String("%s/%s", hPath->Begin(), pent->d_name);
if(IsDirectory(hpath->Begin()))
	{
	hCurrent=new Directory(pent->d_name, hpath, this);
	return hCurrent;
	}
UINT64 usize=GetFileSize(hpath->Begin());
hCurrent=new File(hpath, usize);
return hCurrent;
}

}}