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
#ifndef SM_COREDATA_EOD_GPSCOORDINATE_H
#define SM_COREDATA_EOD_GPSCOORDINATE_H

//! @file
#include "eod/basics.h"

namespace sm
{
    namespace eod
    {
        /*!
        */
         struct GPSCoordinateV1
        {
            int16 degrees;
            int8 minutes;
            int8 seconds;
            char hemisphere;

            GPSCoordinateV1():
            degrees(0),
            minutes(0),
            seconds(0),
            hemisphere('N')
            {
            };
        };
        /*!
        */
         struct GPSCoordinateV2
        {
            int16 degrees;
            int8 minutes;
            float seconds;
            char hemisphere;

            GPSCoordinateV2():
            degrees(0),
            minutes(0),
            seconds(0.0f),
            hemisphere('N')
            {
            };
        };
        typedef GPSCoordinateV2 GPSCoordinate;
    }
}

#endif

