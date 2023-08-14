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
#ifndef SM_COREDATA_EOD_IO_PORTNUMBERVALIDATORCONSTS_H
#define SM_COREDATA_EOD_IO_PORTNUMBERVALIDATORCONSTS_H

//! @file
namespace sm
{
    namespace eod
    {
    
       namespace io
        {
            /* 
                Constants for setting range of ports available for
                opening. This is an extra security feature and also stops
                people accidentally sending data to a different service
            */
             /*
            */
            const int MAXIMUM_PORT_NUMBER = 5000;
            const int MINIMUM_PORT_NUMBER = 2000;
            const int DEFAULT_PORT_NUMBER = 2001;
            const int DEFAULT_TCP_PORT_NUMBER = 3000;
        };
    }
}

#endif

