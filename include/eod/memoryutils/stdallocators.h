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
#ifndef SM_COREDATA_EOD_MEMORYUTILS_STDALLOCATORS_H
#define SM_COREDATA_EOD_MEMORYUTILS_STDALLOCATORS_H
//! \file

#include "boost/pool/singleton_pool.hpp"

#ifdef DOXYGEN_INVOKED
/*!
\defgroup macros_memory_management Memory Management Macros
\ingroup macros

Macros controlling the memory management behaviour of coredata
objects.
*/

/*!
\brief Declares the name of the file to include for the memory allocators

Defining this macro when re-compiling coredata allows the default memory pooling
allocators to be replaced with a user defined version.

The file named by this macro should provide definition for the macro
\ref COREDATA_MEMORY_ALLOCATORS "COREDATA_MEMORY_ALLOCATORS" which needs to
define memory management operators.
An template would be
\code
#define COREDATA_MEMORY_ALLOCATORS(CLASS_TYPE)\
    public:\
        void* operator new(size_t size)    { return my_scalar_allocator(size); } \
        void* operator new [](size_t size) { return my_array_allocator(size); } \
        void  operator delete(void* p)     { my_scalar_delete(p); } \
        void  operator delete[](void* p)   { my_array_delete(p); }
\endcode

Use the following where no definition is specified
\code
#define COREDATA_MEMORY_ALLOCATORS(CLASS_TYPE)
\endcode

\ingroup macros_memory_management
*/
#define COREDATA_ALLOCATORS_INCLUDE "eod/memoryutils/stdallocator.h"
#endif

namespace sm
{
    namespace eod
    {
        namespace memoryutils
        {
            struct eod_pool_tag 
            { 
            };
        }
    }
}

/*! \brief Defines custom memory allocation member functions.

    Add this macro to all non-abstract Serializable classes to
    provide pooling versions of:
    - operator new(size_t size)
    - operator new(size_t size, int, const char*, int)
    - operator delete(void* p)
    - operator delete(void* p, int, const char *, int)

    \param CLASS_TYPE The name of the class that this macro is within.

    \see \ref coreapi_coredata_clientdefined_classes_class_eg "Example"

    \hideinitializer
    \ingroup macros_memory_management
*/
#define COREDATA_MEMORY_ALLOCATORS(CLASS_TYPE) \
    public: \
        void* operator new(size_t size) { \
            assert(size == sizeof(CLASS_TYPE)); \
            (void)size; \
            using namespace sm::eod::memoryutils; \
            typedef boost::singleton_pool<eod_pool_tag, sizeof(CLASS_TYPE)> pool; \
            return pool::malloc(); \
        } \
        void* operator new(size_t size, int, const char*, int) { \
            assert(size == sizeof(CLASS_TYPE)); \
            (void)size; \
            using namespace sm::eod::memoryutils; \
            typedef boost::singleton_pool<eod_pool_tag, sizeof(CLASS_TYPE)> pool; \
            return pool::malloc(); \
        } \
        void operator delete(void* p) { \
            using namespace sm::eod::memoryutils; \
            typedef boost::singleton_pool<eod_pool_tag, sizeof(CLASS_TYPE)> pool; \
            pool::free(p); \
        } \
        void operator delete(void* p, int, const char *, int) { \
            using namespace sm::eod::memoryutils; \
            typedef boost::singleton_pool<eod_pool_tag, sizeof(CLASS_TYPE)> pool; \
            pool::free(p); \
        }


#endif

