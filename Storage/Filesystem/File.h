//========
// File.h
//========

#pragma once


//=======
// Using
//=======

#include "Storage/File.h"


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//======
// File
//======

class File: public Storage::File
{
public:
	// Con-/Destructors
	File(Handle<String> Path, UINT64 Size=0);
	~File();
	VOID Close();
	BOOL Create(BOOL Overwrite=false);
	BOOL Open(BOOL ReadOnly=true, BOOL Create=false);

	// Con-/Destructors Static
	static Handle<File> Create(Handle<String> Path, BOOL Overwrite=false);
	static Handle<File> Open(Handle<String> Path, BOOL ReadOnly=true, BOOL Create=false);

	// Access
	SIZE_T Available()override;
	Handle<String> GetPath() { return hPath; }
	FileSize GetSize()override { return uSize; }
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;
	BOOL Seek(UINT64 Position)override;

	// Modification
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Common
	VOID DoClose();
	BOOL DoCreate(BOOL Overwrite);
	BOOL DoOpen(BOOL ReadOnly, BOOL Create);
	CriticalSection cCriticalSection;
	Handle<String> hPath;
	FILE* pFile;
	UINT64 uPosition;
	UINT64 uSize;
};

}}