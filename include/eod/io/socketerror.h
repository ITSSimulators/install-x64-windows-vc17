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
#ifndef SM_COREDATA_EOD_SOCKETERROR_H
#define SM_COREDATA_EOD_SOCKETERROR_H

//! @file
#include "eod/eoderror.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            // Class to represent exceptions thrown by sockets.
            /*!
            */
             class SM_COREDATA_API SocketError : public EODError
            {
            public:
                /*!
                */
                explicit SocketError(const std::string& message): EODError(message) 
                {
                }
                
                virtual const char* className() const 
                { 
                    return "SocketError"; 
                }
            };
        }
    }
}
#endif

