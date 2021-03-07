//================
// FileHelper.cpp
//================

#include "pch.h"


//=======
// Using
//=======

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "FileHelper.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//========
// Common
//========

UINT64 GetFileSize(LPCSTR ppath)
{
FILE* pfile=fopen(ppath, "r");
if(pfile==nullptr)
	return 0;
fseeko64(pfile, 0, SEEK_END);
UINT64 usize=ftello64(pfile);
fclose(pfile);
return usize;
}

BOOL IsDirectory(LPCSTR ppath)
{
FILE* pfile=fopen(ppath, "r+");
if(pfile)
	{
	fclose(pfile);
	return false;
	}
if(errno==EISDIR)
	return true;
return false;
}

}}