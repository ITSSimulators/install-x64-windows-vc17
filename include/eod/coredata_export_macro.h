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
#ifndef SM_COREDATA_EXPORT_MACRO_H
#define SM_COREDATA_EXPORT_MACRO_H
//! @file
#if defined(SM_COREDATA_BUILD_DLL)
#elif defined(SM_COREDATA_BUILD_LIB)
#elif defined(SM_COREDATA_USE_DLL)
#elif defined(SM_COREDATA_USE_LIB)
#else
// If not defined default to shared library
#       define SM_COREDATA_USE_DLL
#endif

#ifdef COREDATA_CC_MSVC
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SM_COREDATA_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SM_COREDATA_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#	if defined(SM_COREDATA_BUILD_DLL)
#		define SM_COREDATA_API __declspec(dllexport)
#	elif defined(SM_COREDATA_USE_DLL)
#		define SM_COREDATA_API __declspec(dllimport)
#   else
#	    define SM_COREDATA_API 
#	endif

#else
// For gcc
#	if defined(SM_COREDATA_BUILD_DLL) || defined(SM_COREDATA_USE_DLL)
#	define SM_COREDATA_API __attribute__ ((visibility ("default")))
#	else
#	define SM_COREDATA_API 
#   endif
#endif


#endif


