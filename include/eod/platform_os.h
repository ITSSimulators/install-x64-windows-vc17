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
#ifndef SM_COREDATA_EOD_PLATFORM_OS_H
#define SM_COREDATA_EOD_PLATFORM_OS_H

//! @file
//-----------------------------------------------------------------------------
// OS/Compiler Detect: SDK Build
//-----------------------------------------------------------------------------

#ifdef DOXYGEN_INVOKED
    /*! \defgroup operating_system_macros Operating System Macros
        \ingroup macros

        Macros to indicate the type of operating system the code is
        being compiled for.

        @{
    */

    #define COREDATA_OS_WIN32 //!< Defined when compiling 32bit or 64bit code for windows.
    #define COREDATA_OS_LINUX //!< Defined when compiling code for linux.
    #define COREDATA_OS_MAC   //!< Defined when compiling code for Mac OS X 10+.
    /*! @} - end defgroup operating_system_macros */
#else
// Detect OS
#if !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
    #define COREDATA_OS_WIN32
#elif defined(__MWERKS__) && defined(__INTEL__)
    #define COREDATA_OS_WIN32
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #define COREDATA_OS_LINUX
#elif (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__))
    #define COREDATA_OS_MAC
#endif
#endif

#ifdef DOXYGEN_INVOKED
    /*! \defgroup compiler_macros Compiler Macros
        \ingroup macros
        Macros to indicate the compiler being used.
        @{
    */

    /*! Defined when the intel compiler is being used.
        \note On windows the Intel C++ Compiler uses the headers and libraries
        from a Microsoft Visual C++ compiler.
    */
    #define COREDATA_CC_INTEL
    #define COREDATA_CC_MSVC  //!< Defined when the Microsoft Visual C++ Compiler is being used.
    #define COREDATA_CC_GNU   //!< Defined when the GNU compiler is being used.
    /*! @} - end defgroup compiler_macros */
#else
// Detect Compiler
#if defined(_MSC_VER)
    #define COREDATA_CC_MSVC
#elif defined(__GNUC__)
    #define COREDATA_CC_GNU
#elif defined(__INTEL_COMPILER)
    #define COREDATA_CC_INTEL
#endif
#endif
//-----------------------------------------------------------------------------


// Define all the possible types of WIN32 used by various win32 compilers
#ifdef COREDATA_OS_WIN32
    #ifndef __WIN32__
        #define __WIN32__
    #endif
    #ifndef WIN32
        #define WIN32
    #endif
    #ifndef _WIN32
        #define _WIN32
    #endif
#endif

//-----------------------------------------------------------------------------
// OS/Compiler Detect: special case for cygwin (emulate Linux for SDK builds)
//-----------------------------------------------------------------------------
#if defined(__CYGWIN__)
    #undef COREDATA_OS_WIN32
    #ifndef COREDATA_OS_LINUX
        #define COREDATA_OS_LINUX
    #endif
    // Cygwin does not include this function (used in serialport)
    #define cfmakeraw(x)
#endif // __CYGWIN__
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Compiler flag checks
//-----------------------------------------------------------------------------
#if defined(COREDATA_CC_MSVC)
    #define NOMINMAX
    #define VC_EXTRA_LEAN
    #define WIN32_MEAN_AND_LEAN
    // Compiler violates std::9.4.2/4
    #define COREDATA_NO_INCLASS_MEMBER_INITIALIZATION_DEFINITION

    #if (_MSC_VER >= 1400)
        // warning about throw specs not being inforced (yet)
        #pragma warning(disable : 4290) // C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
        // boost triggers these
        #pragma warning(disable : 4701) // Potentially uninitialized local variable 'name' used
        // Exporting a class that contains a datamember of STL type.
        #pragma warning(disable : 4251) // class 'some STL type' needs to have dll-interface to be used by clients of class 'classname'
        // controls STL iterator debugging options in VC8
        #ifdef _DEBUG
            #define _HAS_ITERATOR_DEBUGGING 1
        #endif
        #ifndef _SCL_SECURE_NO_WARNINGS
            // Disable message such as warning C4996: 'std::equal': Function call with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct. To disable this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how to use Visual C++ 'Checked Iterators'
            #define _SCL_SECURE_NO_WARNINGS
        #endif
    #endif

    // Disable level 4 warnings that are too frequent to be useful
    #pragma warning(disable : 4100) // 'identifier' : unreferenced formal parameter
    #pragma warning(disable : 4127) // conditional expression is constant
    #pragma warning(disable : 4505) // 'function' : unreferenced local function has been removed
    #pragma warning(disable : 4511) // 'class' : copy constructor could not be generated
    #pragma warning(disable : 4512) // 'class' : assignment operator could not be generated
    #pragma warning(disable : 4516) // 'class::symbol' : access-declarations are deprecated; member using-declarations provide a better alternative
    #pragma warning(disable : 4702) // unreachable code

    // Check that exception handling compiler option is ON
    #if (!defined(_CPPUNWIND))
        #error "Exception handling compiler option must be enabled (/GX)"
    #endif
    #if (!defined(_DLL))
        // Check memory model is multi-threaded DLL
        #error "Code generation setting must use Multithreaded DLL runtime library"
    #endif
    #if (_MSC_VER < 1300)
        // Disable debug symbol too long warning for compiler ver < 7.0
        #pragma warning(disable : 4786)
    #endif
#endif
//-----------------------------------------------------------------------------

// Macros for compiler dependent code
#ifdef COREDATA_OS_WIN32
    #define WINDOWS_ONLY(x) x
    #define LINUX_ONLY(x)
#elif defined(COREDATA_OS_LINUX) || defined(COREDATA_OS_MAC)
    #define WINDOWS_ONLY(x) 
    #define LINUX_ONLY(x) x
#else
    #error "Only Windows, Linux, and Mac builds are supported!"
#endif // OS Specific

/*! \brief Marks mark classes and/or functions as no longer being supported.

	\param text_message The message to be displayed by the compiler when code
		uses the deprecated function. It should indicate an alternative.

	The macro should be placed before the return type for functions and 
	between the class/struct keyword and identifier.
	\code
	class COREDATA_DEPRECATED("Use class Radio instead.") Wireless
	{
	};
	COREDATA_DEPRECATED("Wrong naming, use turnOn().") void turn_on(Wireless&);
	\endcode
    \hideinitializer
    \ingroup general_macros
*/
#if defined(COREDATA_CC_MSVC) && _MSC_VER >= 1400
// 1400 is VC8
#	define COREDATA_DEPRECATED(text_message) __declspec(deprecated(text_message))
#elif defined(COREDATA_CC_GNU) 
#	define COREDATA_DEPRECATED(text_message) __attribute__ ((deprecated))
#else
#define COREDATA_DEPRECATED(text_message) 
#endif

/*! \brief Declares an object id named \a constant_name

    \param constant_name The name of the object
    \param value the ObjectID
    \ingroup general_macros
    \hideinitializer
*/
#define COREDATA_DECLARE_NAMED_OBJECT_ID(constant_name, value) \
    BOOST_STATIC_CONSTANT(ObjectID, constant_name = value)

/*! \brief Provides the definition for the objectid named \a constant_name.

    \param fully_qualified_class_name The fully qualified class name
    \param constant_name The name of the object
    \ingroup general_macros
    \hideinitializer
*/
#ifndef COREDATA_NO_INCLASS_MEMBER_INITIALIZATION_DEFINITION
#   define COREDATA_DEFINE_NAMED_OBJECT_ID(fully_qualified_class_name, constant_name) \
        const ::sm::eod::Serializable::ObjectID fully_qualified_class_name::constant_name
#else
#   define COREDATA_DEFINE_NAMED_OBJECT_ID(fully_qualified_class_name, constant_name)
#endif

/*! \brief Declares an object id named THIS_OBJECT_ID

    \param value the ObjectID
    \see COREDATA_DECLARE_NAMED_OBJECT_ID
    \ingroup general_macros
    \hideinitializer
*/
#define COREDATA_DECLARE_THIS_OBJECT_ID(value) \
    COREDATA_DECLARE_NAMED_OBJECT_ID(THIS_OBJECT_ID, value)

/*! \brief Provides the definition for the objectid THIS_OBJECT_ID
    \param fully_qualified_class_name The fully qualified class name
    \ingroup general_macros
    \hideinitializer
*/
#define COREDATA_DEFINE_THIS_OBJECT_ID(fully_qualified_class_name) \
    COREDATA_DEFINE_NAMED_OBJECT_ID(fully_qualified_class_name, THIS_OBJECT_ID)
#endif


