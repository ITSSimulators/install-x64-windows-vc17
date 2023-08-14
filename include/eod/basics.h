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
#ifndef SM_COREDATA_EOD_BASICS_H
#define SM_COREDATA_EOD_BASICS_H

//! @file
#include "eod/platform_os.h"

#if defined(COREDATA_CC_MSVC)
// Allow MSVC to define M_SQRT and friends in math.h
#define _USE_MATH_DEFINES 
#endif

#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <locale>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

// These definitions are included here to prevent problems with visual studio 2003.
#ifndef M_PI
#define M_PI     3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2   1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4   0.785398163397448309616
#endif

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/static_assert.hpp>

#include "eod/coredata_export_macro.h"

#include "eod/platform_types.h"
#include "eod/platform_socket.h"
#include "eod/platform_error.h"


//-----------------------------------------------------------------------------
// OS specific includes
//-----------------------------------------------------------------------------
#if defined(COREDATA_OS_WIN32)
    #include <windows.h>
    #include <tchar.h>
    #ifndef assert
        #include <crtdbg.h>
        #define assert _ASSERTE
    #endif
#endif // OS Specific

//-----------------------------------------------------------------------------
// Compiler specific includes
//-----------------------------------------------------------------------------
#if defined(COREDATA_CC_GNU)
    #include <netinet/in.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <assert.h>
    #include <sys/time.h>
    #include <unistd.h>
    #include <errno.h>
    #include <dirent.h> 

    // Used in thread class
    #define THREAD_PRIORITY_TIME_CRITICAL 0

#endif

/*! \defgroup macros Macros */

/*! \defgroup general_macros General Macros
    \ingroup macros
*/

/*! \brief Throws an exception if an expression evaluates to false.

    Use this macro to check the documented preconditions for a function.

    \param cond The expression that should evaluate to \c true.
    \param message The message to use as the return value from std::exception::what().
    \throw std::invalid_argument
    \ingroup general_macros
    \hideinitializer
*/
#ifndef COREDATA_PRECONDITION
#define COREDATA_PRECONDITION(cond,message) {\
        if (!(cond))\
        {\
            std::stringstream s;\
            s << __FILE__ << ":" << __LINE__ << ": " << message;\
            throw std::invalid_argument(s.str());\
        }\
    }
#endif

#define COREDATA_STATIC_ASSERT BOOST_STATIC_ASSERT


/*! \brief Marks a function as not throwing a user catchable exception

	The function can still throw std::bad_alloc if a memory allocation
	failed or an exception to a failed COREDATA_PRECONDITION().
    \hideinitializer
*/
#define COREDATA_NO_THROW

/*! \brief Marks a virtual member function as being pure making the class abstract.

	Use this macro over using <code>= 0</code>.
	\code
	virtual void processData() COREDATA_PURE_METHOD;
	\endcode
    \ingroup general_macros
    \hideinitializer
*/
#define COREDATA_PURE_METHOD = 0

//-----------------------------------------------------------------------------
// Pool Allocator Hooks
//-----------------------------------------------------------------------------
#ifndef COREDATA_ALLOCATORS_INCLUDE
#include "eod/memoryutils/stdallocators.h"
#else
#include COREDATA_ALLOCATORS_INCLUDE
#endif

//-----------------------------------------------------------------------------

// typedefs to add more meaning to std::vector of float types
// These indicate how many elements are expected.
// Also, this gives us the option to use swig typemaps to map these to 
// better language types.
namespace sm
{
    namespace eod
    {
        //! A std::vector expected to contain 2 int32 elements
        /*!
            Used to represent pixel intersection.
        */
        typedef std::vector<int32> iStdVector2;
        //! A std::vector expected to contain 2 float elements
        /*!
            Used to represent screen intersection or pitch-yaw
        */
        typedef std::vector<float> fStdVector2;
        //! A std::vector expected to contain 3 float elements
        /*!
            Used to represent a point in 3D space.
        */
        typedef std::vector<float> fStdVector3;
        //! A std::vector expected to contain 2 double elements
        /*!
            Used to represent a point in 2D space or a pitch-yaw.
        */
        typedef std::vector<double> dStdVector2;
        //! A std::vector expected to contain 3 double elements
        /*!
            Used to represent a point in 3D.
        */
        typedef std::vector<double> dStdVector3;
        //! A std::vector expected to contain 4 double elements
        /*!
            Used to represent a quaternion.
        */
        typedef std::vector<double> dStdVector4;
    }
}
#endif 


