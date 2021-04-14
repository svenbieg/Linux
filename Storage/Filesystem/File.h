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

	// Storage.File
	VOID Close()override;
	BOOL Create(FileCreateMode Create=FileCreateMode::OpenExisting, FileAccessMode Access=FileAccessMode::ReadOnly, FileShareMode Share=FileShareMode::ShareRead)override;
	BOOL SetSize(UINT64 Size)override;

	// Container
	FileSize GetSize()override;
	BOOL Seek(UINT64 Position)override;

	// Input-Stream
	SIZE_T Available()override;
	SIZE_T Read(VOID* Buffer, SIZE_T Size)override;

	// Output-Stream
	VOID Flush()override;
	SIZE_T Write(VOID const* Buffer, SIZE_T Size)override;

private:
	// Common
	VOID DoClose();
	BOOL DoCreate(FileCreateMode Create, FileAccessMode Access, FileShareMode Share);
	FILE* pFile;
	UINT64 uPosition;
	UINT64 uSize;
};

}}