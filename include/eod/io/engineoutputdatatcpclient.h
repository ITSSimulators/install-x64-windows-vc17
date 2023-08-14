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
#ifndef SM_COREDATA_EOD_ENGINEOUTPUTDATATCPCLIENT_H
#define SM_COREDATA_EOD_ENGINEOUTPUTDATATCPCLIENT_H

//! @file
#include "eod/engineoutputdata.h"
#include "eod/io/inetaddress.h"
#include "eod/io/tcpsocket.h"

namespace sm
{
    namespace eod
    {
        class EngineOutputData;

        namespace io
        {
            class SM_COREDATA_API EngineOutputDataTcpClient
            {
            public:
                EngineOutputDataTcpClient();
                ~EngineOutputDataTcpClient();

                //! Connects to the EngineOutputData server
                /*! 
                    @param address The address of the EngineOutputData server to which to connect
                    @throw SocketError when network error.
                    @pre !isConnected()
                */
                void connect(const InetAddress& address);

                //! @return true if connected to the EngineOutputData server
                bool connected() const;

                //! @return true if connected to the EngineOutputData server
                /*!
                    @deprecated Use connected() as it matches the naming convention
                */
                bool isConnected() const;

                //! Disconnects from the EngineOutputData server
                void disconnect();
        
                //! Returns the next EngineOutputData object through the nework connection.
                /*!
                    This function will continually read data from the network until
                    there is enough data for an EngineOutputData object to be deserialized
                    or a single read times out. If enough data is read for multiple objects
                    then the next call will return the object without reading from the network.
                    An EngineOutputData object may require multiple reads from the network to
                    receive enough data to deserialize it. This function will continue reading
                    from the network until a single network read exceeds timeout_ms.

                    Types that do not have the id EngineOutputData::THIS_OBJECT_ID are silently
                    skipped.

                    @param timeout_ms The amount of time to wait for a single network read
                        in milliseconds before returning a NULL pointer.
                    @return EngineOutputData A pointer to the EngineOutputData object received 
                        from the EngineOutputData server. The pointer will be NULL if the 
                        is server gracefully closed the connection, the client times out
                        waiting for the data.
                    @throw SocketError a network error occurred, disconnect() will have been called.
                    @throw SerializableError the data was malformed, disconnect() will have been called.
                    @pre isConnected() is true.
                */
                EngineOutputDataPtr receive(int timeout_ms = 100);

            private:
                InetAddress _address_not_used_anymore_to_be_removed_next_major_version_change;
                //! The buffer into which serialized data is read
                std::vector<uint8> _buffer;
                //! The socket through which to communicate with the EngineOutputData server
                TcpSocket _tcp_socket;
            };
        }
    }
}
#endif

