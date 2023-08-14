/*
    Copyright (C) 2008 Seeing Machines Ltd. All rights reserved.

    This file is part of the CoreData API.

    This file may be distributed under the terms of the SM Non-Commercial License
    Agreement appearing in the file LICENSE.TXT included in the packaging
    of this file.

    This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
    WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

    Further information about the CoreData API is available at:
    http://www.seeingmachines.com/

*/
#ifndef SM_COREDATA_EOD_PLATFORM_TYPES_H
#define SM_COREDATA_EOD_PLATFORM_TYPES_H
//! @file
// Compiler dependent fixed-width integer type definitions
// (The size of an int is machine specific in C++).

// This is to prevent these from conflicting with foundationlib if used from there.
#ifndef FOUNDATION_BASICS_WINDOWS_H
    #ifdef COREDATA_CC_MSVC
            typedef unsigned __int64 uint64;
            typedef __int64 int64;
            typedef unsigned __int32 uint32;
            typedef __int32 int32;
            typedef unsigned __int16 uint16;
            typedef __int16 int16;
            typedef __int8 int8;
            typedef unsigned __int8 uint8;
    #endif

    #ifdef COREDATA_CC_GNU
    
            #include <sys/types.h>  
    
            typedef u_int64_t uint64;
            typedef int64_t int64;
            typedef u_int32_t uint32;
            typedef int32_t int32;
            typedef u_int16_t uint16;
            typedef int16_t int16;
            typedef u_int8_t uint8;
            typedef int8_t int8;

            typedef unsigned char BYTE;
            typedef unsigned long DWORD;
    #endif
#endif

#endif


