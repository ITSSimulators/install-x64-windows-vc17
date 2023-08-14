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
#ifndef SM_COREDATA_EOD_NETINITIALISER_H
#define SM_COREDATA_EOD_NETINITIALISER_H

//! @file
namespace sm
{
    namespace eod
    {
        namespace io
        {
            //! Handles initialisation and destruction of networking API.
            /*! For windows this means initialising and then cleaning up the windows
                sockets API. */
            class SM_COREDATA_API NetInitialiser
            {
            public:
                NetInitialiser();
                ~NetInitialiser();
        
            private:
                void init() const;
                void cleanup() const;
            };
        }
    }
}
#endif

