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
#ifndef SM_COREDATA_EOD_EODERROR_H
#define SM_COREDATA_EOD_EODERROR_H

//! @file
#include "eod/basics.h"

#if defined(COREDATA_CC_MSVC)
#pragma warning(push)
#pragma warning(disable : 4275) // non dll-interface class 'std::runtime_error' used as base for dll-interface class 'sm::eod::EODError'
#endif

namespace sm
{
    namespace eod
    {
        //! An abstract base class that all CoreData errors are derived from.
        /*!
        */
        class SM_COREDATA_API EODError : public std::runtime_error
        {
        public:
    
            //! Returns the name of the class as a string without any namespace qualifiers.
            /*! This function enables script wrappers to map from C++ exceptions to
                script-domain exception classes.
                It should return the name of the class (as given after the 'class' keyword.)

            */
            virtual const char* className() const COREDATA_PURE_METHOD;

        protected:
            EODError(const std::string& message):
                runtime_error(message)
                {}
        };
    }
}

#if defined(COREDATA_CC_MSVC)
#pragma warning(pop)
#endif

#endif

