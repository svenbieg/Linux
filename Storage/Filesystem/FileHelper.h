//==============
// FileHelper.h
//==============

#pragma once


//===========
// Namespace
//===========

namespace Storage {
	namespace Filesystem {


//========
// Common
//========

UINT64 GetFileSize(LPCSTR Path);
BOOL IsDirectory(LPCSTR Path);

}}