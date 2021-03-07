//=============
// Directory.h
//=============

#pragma once


//=======
// Using
//=======

#include "Storage/Directory.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//===========
// Directory
//===========

class Directory: public Storage::Directory
{
public:
	// Con-/Destructors
	Directory(Handle<String> Name, Handle<String> Path=nullptr, Handle<Storage::Directory> Parent=nullptr);

	// Common
	Handle<Convertible> Get(Handle<String> Path)override;

protected:
	// Common
	VOID FindClose()override;
	Handle<Convertible> FindCurrent()override;
	Handle<Convertible> FindFirst()override;
	Handle<Convertible> FindNext()override;

private:
	// Common
	Handle<Convertible> hCurrent;
	Handle<String> hPath;
	VOID* pDirectory;
};

}}