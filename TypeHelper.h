//==============
// TypeHelper.h
//==============

#pragma once


//=======
// Using
//=======

#include <cstddef>


//==================
// Integrated Types
//==================

typedef void VOID;

typedef int BOOL;

// Memory-Types
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef unsigned long long int QWORD;
typedef size_t SIZE_T;

// Numeric Types
typedef short int SHORT;
typedef unsigned short int USHORT;
typedef int INT;
typedef unsigned int UINT;
typedef long int LONG;
typedef unsigned long int ULONG;
typedef long long int INT64;
typedef unsigned long long int UINT64;
typedef float FLOAT;

// Characters
typedef char CHAR;
typedef char TCHAR;
typedef wchar_t WCHAR;

// Strings
typedef char* LPSTR;
typedef char const* LPCSTR;
typedef char* LPTSTR;
typedef char const* LPCTSTR;
typedef wchar_t* LPWSTR;
typedef wchar_t const* LPCWSTR;

typedef unsigned short int WORD;
typedef double DOUBLE;


//========
// Limits
//========

#define MAX_UINT 0xFFFFFFFF
#define MAX_SIZE_T 0xFFFFFFFF
