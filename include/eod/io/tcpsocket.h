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
#ifndef SM_COREDATA_EOD_TCPSOCKET_H
#define SM_COREDATA_EOD_TCPSOCKET_H

//! @file
#include "eod/basics.h"
#include "eod/io/inetaddress.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
        
            //! This class represents a socket for sending and receiving TCP packets.
            class SM_COREDATA_API TcpSocket
            {
            public:
                //! Constructs an unconnected socket.
                explicit TcpSocket(SOCKET socket = INVALID_SOCKET);
        
                //! Closes the socket.
                ~TcpSocket();
        
                //! Opens the socket.
                /*! 
                    @pre socket is not open
                    @throw SocketError on error.
                */
                void open();
                
                //! Binds the open socket to the local address.
                /*!
                    @pre socket is open
                    @pre socket is not connected
                    @throw SocketError if network error.
                */
                void bind(const InetAddress& local_address = InetAddress(0, "0.0.0.0"));
                
                //! Connects the open socket to the remote address.
                /*! 
                    If the connect fails the socket will be closed(). This matches the
                    behaviour on BSD Unix where a failed connect(2) will result in
                    all subsequent calls for the same socket returing EINVAL.

                    @pre socket is open
                    @pre socket is not connected (failure will also close the socket)
                    @throw SocketError network error.
                        TcpSocket will also be closed().
                */
                void connect(const InetAddress& remote_address);
        
                //! Closes the socket. This is safe to call on an un-opened socket.
                void close();
                
                //! Places socket into a state where it is listening for incoming connections.
                /*! @pre socket is open
                    @throw SocketError if network error.
                */
                void listen();
        
                /*! @pre socket is open
                    @throw SocketError if network error.
                 */
                TcpSocket* accept(int timeout_ms = 100);
        
                //! Returns the address the socket is connected to.
                /*! 
                    If the socket is not connected, returns the local address.
                */
                const InetAddress& getInetAddress() const;
        
                //! Sends the entire buffer of data.
                /*! 
                    Note: this method blocks the calling thread until all data has been sent.
                    @param buffer Data to send
                    @pre socket is connected
                    @throw SocketError if network error.
                */
                void send(const std::vector<uint8>& buffer);
        
                //! Sends count bytes from buffer of data.
                /*! 
                    Note: this method blocks the calling thread until all data has been sent.
                    @param buffer Data to send.
                    @param count Number of bytes to send.
                    @pre socket is connected
                    @throw SocketError if network error
                */
                void send(const uint8* buffer, unsigned int count);
        
                //! Sends count bytes from buffer of data.
                /*! 
                    This method blocks upto @ timeout_ms waiting for the socket to be
                    able to accept more data.
        
                    @param buffer Data to send.
                    @param count Number of bytes to send.
                    @param timeout_ms Number of millseconds to block.
                    @return the number of bytes actually sent.
                    @pre socket is connected
                    @throw SocketError if network error
                */
                size_t send(const uint8* buffer, size_t count, int timeout_ms);
        
                //! Receives data from this socket.
                /*! Note: this method blocks the calling thread. Use the dataReady method to
                    do a non-blocking check for data.
                    @param buffer Receives data in the datagram
                    @param timeout_ms Time to wait for the data. After this period if data
                           is not available this method returns 0
                    @param append_buffer If true, data is appended to the buffer, otherwise the
                           data overwrites 
                    @return The number of bytes read or 0 if no data was available or connection was
                        closed by other side.
                    @pre socket is connected.
                    @throw SocketError if network error.
                */
                int receive(std::vector<uint8>& buffer, int timeout_ms = 100, bool append_buffer = false);
        
                //! Returns true if data is waiting in receive buffer
                bool dataReady() const { return waitForData(0); }
        
                //! Returns true if the socket is 'connected'
                bool connected() const;
        
                //! Returns true if the socket is 'open'
                bool opened() const;
        
                //! Address used to bind.
                const InetAddress& getLocalAddress() const;
        
                //! Remote address.
                const InetAddress& getRemoteAddress() const;
        
                //! Nagle algorithm buffers smalls packets into a single send.
                /*!
                    Same as setSocketFlag(TcpNoDelay, enabled)
                */
                void enableNagleAlgortihm(bool enabled);

                enum SocketOptionFlag
                {
                    SolReuseAddr,
                    TcpNoDelay, // Send data immediately
                };

                //! Sets a socket option flag
                /*!
                    @throw SocketError socket_flag is not supported or sockets api failed.
                */
                void setSocketFlag(SocketOptionFlag socket_flag, bool value);

                //! Returns the value of the socket option
                /*!
                    @throw SocketError socket_flag is not supported or sockets api failed.
                */
                bool socketFlag(SocketOptionFlag socket_flag) const;

            private:
                // Forward declare of member class
                class Buffer;
        
                //! Banned copy constructor
                TcpSocket(const TcpSocket& rhs);
        
                //! Banned assignment operator
                TcpSocket& operator=(const TcpSocket& rhs);
        
                //! @pre socket is open
                TcpSocket(SOCKET socket, const InetAddress& local_address, const InetAddress& remote_address);
        
                //! Waits upto @a timeout_ms milliseconds for the socket to contain data to be read.
                /*!
                    @return true if data can be read.
                    @throw SocketError on error.
                */
                bool waitForData(int timeout_ms) const;
        
                //! Waits upto @a timeout_ms milliseconds for the socket to allow more data to be sent.
                /*!
                    @return true if data can be sent.
                    @throw SocketError on error.
                */
                bool waitForSend(int timeout_ms) const;
        
                void initialiseBufferSizes();
                void setBufferSize(int buffer_name, Buffer& buffer);
        
                //! Returns the underlying sockets buffer size
                /*!
                    @param buffer_name buffer name SO_SNDBUF or SO_RCVBUF
                    @return Size of buffer for socket
                    @throw SocketError on error.
                */
                size_t socketBufferSize(int buffer_name) const;
        
                //! Sends bytes on the currently connected socket.
                /*!
                    @return number of bytes sent.
                    @throw SocketError on error.
                */
                size_t sendBytes(const uint8* buffer, size_t bytes_to_send);
        
                //! A buffer of chars used for adapting vector<char> into something that the network library can use.
                class SM_COREDATA_API Buffer
                {
                public:
                    Buffer();
                    ~Buffer();
                    void setSize(int new_size);
                    char* buffer();
                    int size() const;
                private:
                    char* _buffer;
                    int _size;
                };
        
                SOCKET _socket_fd;
                bool _connected;
                InetAddress _local_address;
                InetAddress _remote_address;
                Buffer _rx_buffer;
                size_t _send_chunk_size;
            };
        }
    }
}
#endif

