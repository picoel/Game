/**
  * @file	String.h
  * @brief	tcharå^ÇÃstringÉNÉâÉXÅB
  * @date 2015/05/02 01:16:34
  */

#ifndef INCLUDE_TSTRING_H
#define INCLUDE_TSTRING_H

#include <string>
#include <tchar.h>
#include "Lib/Memory/Allocator/Allocator.h"

typedef std::basic_string< S8, std::char_traits<S8>, CAllocator<S8> > CString;
typedef std::basic_string< S16, std::char_traits<S16>, CAllocator<S16> > CWString;
typedef std::basic_string< TChar, std::char_traits<TCHAR>, CAllocator<TCHAR> > CTString;

#endif // #ifndef INCLUDE_TSTRING_H
