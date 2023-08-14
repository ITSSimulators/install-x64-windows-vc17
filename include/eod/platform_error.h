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
#ifndef SM_COREDATA_EOD_PLATFORM_ERROR_H
#define SM_COREDATA_EOD_PLATFORM_ERROR_H

//! @file
namespace sm
{
    namespace eod
    {
        /*!
            @name System Error Functions
        */
        //@{

#ifdef COREDATA_OS_WIN32        
        typedef DWORD system_error_t;
#else
        typedef int system_error_t;
#endif
        //! Returns the last system error number
        /*!
            On Windows this is the value of GetLastError().
            On Mac/Windows this is the variable errno.

            A value of 0 indicates no error.
        */
        system_error_t lastSystemErrorNumber();

        std::string systemErrorMessage(system_error_t error_number);

        /*!
            Same as return systemErrorMessage(lastSystemErrorNumber());
        */
        std::string lastSystemError();

        //@}
    }
}

#endif


