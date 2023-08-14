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
#ifndef SM_COREDATA_EOD_TCPENDPOINT_H
#define SM_COREDATA_EOD_TCPENDPOINT_H

//! @file
#include "eod/io/inetaddress.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            class TcpSocket;
        
            //! TcpEndPoint is an abstract base class encapsulating the sending and receiving of
            //! data to a TCP endpoint.
            class SM_COREDATA_API TcpEndPoint
            {
            public:
                //! Closes down endpoint and releases resources.
                virtual ~TcpEndPoint() COREDATA_PURE_METHOD;
        
                //! Sends the entire buffer of data.
                /*! Note: this method blocks the calling thread until all data has been sent.
                    @param buffer Data to send
                    @pre socket is open
                    @throw SocketError if f network error.
                */
                void send(const std::vector<uint8>& buffer);
                
                //! Blocking sends of a buffer of data.
                /*! Note: this method blocks the calling thread until all data has been sent.
                    @param buffer Data to send
                    @param num_bytes The number of bytes to send
                    @pre socket is open
                    @throw SocketError if network error.
                */
                void send(const uint8* buffer, size_t num_bytes);
        
                //! Non-blocking sends of a buffer of data.
                /*! Note: this method blocks the calling thread until all data has been sent.
                    @param buffer Data to send
                    @param num_bytes The number of bytes to send
                    @param timeout_ms Number of milliseconds to wait for ability to send data.
                    @return number of bytes sent.
                    @pre socket is open
                    @throw SocketError if network error.
                */
                size_t send(const uint8* buffer, size_t num_bytes, int timeout_ms);
        
                //! Receives data from this socket.
                /*! Note: this method blocks the calling thread. Use the dataReady method to
                    do a non-blocking check for data.
                    @param buffer Receives data in the datagram
                    @param append_buffer If true, data is appended to the buffer, otherwise the
                           data overwrites 
                    @return The number of bytes read or 0 if no data was available or connection was
                        closed by other side. 
                    @pre socket is open
                    @throw SocketError if network error.
                */
                int receive(std::vector<uint8>& buffer, bool append_buffer = false);
        
                //! @return true if data is waiting in receive buffer
                bool dataReady() const;
        
                //! Closes the socket. This is safe to call on an un-opened socket.
                void close();
        
                //! @return true if the socket is 'connected'
                bool opened() const;
        
                //! Time to wait for the receiving of data.
                void setReceiveTimeoutMillis(int timeout_ms);
                //! Time to wait for the receiving of data.
                int receiveTimeoutMillis() const;
        
                //! Nagle algorithm buffers smalls packets into a single send.
                void enableNagleAlgortihm(bool enabled);
        
                //! Returns the address of the local side of the endpoint.
                InetAddress localAddress() const;
        
            protected:
                TcpEndPoint();
        
                //! Construct endpoint attached to an already opened socket.
                TcpEndPoint(TcpSocket* socket);
        
                //! Construct a disconected endpoint bound to a local address.
                TcpEndPoint(const InetAddress& local_address);
            
                //! Underlying TcpSocket.
                TcpSocket& socket();
                //! Underlying TcpSocket.
                const TcpSocket& socket() const;
            private:
                // Copy construction not allowed.
                TcpEndPoint(const TcpEndPoint&);
                // Assignment operator not allowed.
                TcpEndPoint& operator=(const TcpEndPoint&);
                //! The socket.
                std::auto_ptr<TcpSocket> _socket;
                //! Timeout in milliseconds for all receive calls.
                int _rx_timeout;
            };
        }
    }
}
#endif

