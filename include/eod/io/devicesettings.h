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
#ifndef SM_COREDATA_EOD_DEVICESETTINGS_H
#define SM_COREDATA_EOD_DEVICESETTINGS_H

//! @file
namespace sm
{
    namespace eod
    {
        namespace io
        {
            //! Com port identifiers. The number of com-ports depends on machine architecture.
            enum ComPortID
            { 
                COM1 = 0, 
                COM2, 
                COM3, 
                COM4,
                COM5,
                COM6,
                COM7,
                COM8,
                COM9,
                COM10,
                NUM_PORTS
            };
        
            //! Baudrates
            enum BaudRate
            { 
                B110    = 110, 
                B300    = 300, 
                B600    = 600, 
                B1200   = 1200, 
                B2400   = 2400, 
                B4800   = 4800, 
                B9600   = 9600, 
                B14400  = 14000, 
                B19200  = 19200, 
                B38400  = 38400, 
                B57600  = 57600, 
                B115200 = 115200, 
                B128000 = 128000,
                B230400 = 230400,
                B460800 = 460800,
                B921600 = 921600,
                NUM_BAUD_RATES
            };

            enum Parity
            {
                NoParity = 0,
                OddParity = 1,
                EvenParity = 2,
                MarkParity = 3,
                SpaceParity = 4
            };

            enum StopBits
            {
                OneStopBit = 0,
                One5StopBits = 1,
                TwoStopBits = 2
            };
        }
    }
}
#endif

