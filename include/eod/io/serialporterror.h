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
#ifndef SM_COREDATA_EOD_SERIALPORTERROR_H
#define SM_COREDATA_EOD_SERIALPORTERROR_H

//! @file
#include "eod/eoderror.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            //! SerialPortError is a type of exception that is thrown when a serial port
            //! operation produces an error.
            /*!
            */
            class SM_COREDATA_API SerialPortError: public EODError
            {
            public:
                //! Indicate timeout = true when the port has timed out for tx/rx.
                /*!

                */
                SerialPortError(const std::string& message, bool timeout = false):
                    EODError(message),
                    _timeout(timeout)
                    {}
        
                //! @return true if Error was due to timeout on read or write
                /*!

                */
                bool timeout() const 
                { 
                    return _timeout; 
                }

                virtual const char* className() const 
                { 
                    return "SerialPortError"; 
                }

            private:
                const bool _timeout;
            };
        }
    }
}
#endif

