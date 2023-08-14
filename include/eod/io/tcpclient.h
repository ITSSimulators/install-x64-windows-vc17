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
#ifndef SM_COREDATA_EOD_TCPCLIENT_H
#define SM_COREDATA_EOD_TCPCLIENT_H

//! @file
#include "eod/io/inetaddress.h"
#include "eod/io/tcpendpoint.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
        
            //! A simple TCP stream.
            /*!
                Typical usage:
                @code
                TcpClient client;
                client.open(InetAddress(HTTP_PORT, WEB_SITE_URL));
                std::vector<uint8> data;
                client.send(data);
                client.receive(data);
                client.close();
                @endcode
             */
            class SM_COREDATA_API TcpClient : public TcpEndPoint
            {
            public:
                //! Opens a client connection bound to the local address.
                /*!
                    @throw SocketError on error.
                */
                TcpClient();
        
                //! Opens a connection to the remote address.
                /*! 
                    @param remote_address remote address to connect to
                    @throw SocketError on error.
                */
                void open(const InetAddress& remote_address);
            };
        }
    }
}
#endif

