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
#ifndef SM_COREDATA_EOD_DATAGRAMSOCKET_H
#define SM_COREDATA_EOD_DATAGRAMSOCKET_H

//! @file
// From networkLib
#include "eod/io/inetaddress.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
        
            //! This class represents a socket for sending and receiving UDP packets.
            class SM_COREDATA_API DatagramSocket
            {
            public:
                //! Constructs a datagram socket and binds it to the specified port on the local host machine.
                /*!
                    @param port_num The port number to bind to. Ports below 1024 usually require special
                        privileges to create.  The default value of 0 chooses an unused port.
                    @param rcv_buff_len The maximum size UDP packet that can be recieved.
                    @param send_buff_len The maximum size UDP packet that can be sent.
                */
                explicit DatagramSocket(int port_num = 0, int rcv_buff_len = 4096, int send_buff_len = 4096);
        
                //! Constructs a datagram socket and binds it to the specified
                //! multicast ip address on the specified port.
                explicit DatagramSocket(std::vector<std::string> multicast, int port_num);
        
                //! Closes the socket.
                ~DatagramSocket();
        
                //! Returns a file descriptor handle to the socket
                int getSocket() const { return static_cast<int>(_socket_fd); }
        
                //! Gets the local address to which the socket is bound.
                const InetAddress& getLocalAddress() const;
        
                //! Connects the socket to the remote address.
                /*! Connecting the DatagramSocket to a specific address
                    ensures that the socket can only send to or receive from
                    that address.
                    @note Since these are UDP sockets, there is no "connection" made with any other process on any other host,
                    so connected here means just connecting to an address (UDP port on a host). */
                void connectSocket(const InetAddress& address);
        
                //! Disconnects the socket from any remote address
                /*! Resets the remote address to the local address */
                void disconnectSocket();
        
                //! Returns the address the socket is connected to.
                //! If the socket is not connected, returns the local address.
                const InetAddress& getInetAddress() const;
        
                //! Sets the SO_RCVBUF option to the specified value for this DatagramSocket.
                /*!
                    @param size The maximum size UDP packet that can be recieved. Datagrams
                        larger than this value will be dropped.
                */
                void setReceiveBufferSize(int size);
        
                //! Get the value of the SO_RCVBUF option for this socket.
                //! This is the buffer size used for input on this socket.
                int getReceiveBufferSize() const { return _rx_buff_len; }
        
                //! Sets the SO_SENDBUF option to the specified value for this DatagramSocket.
                /*!
                    @param size The maximum size UDP packet that can be sent.
                */
                void setSendBufferSize(int size);
        
                //! Get the value of the SO_SNDBUF option for this socket.
                //! This is the buffer size used for output on this socket.
                int getSendBufferSize() const { return _tx_buff_len; }
        
                //! Sends a datagram packet from this socket.
                /*! 
                    If you have connected the socket to a remote address using connect(), then you can
                    call Send without an address.
                    If @a buffer is larger than getSendBufferSize() then multiple datagrams will be
                    sent of send buffer size with a final datagram with the remainder. This behaviour
                    should not be relied on as it may change in the future.
        
                    @param buffer the buffer of data to send.
                    @pre buffer.size() <= max datagram size of 64KB
                    @throw SocketError if buffer.size() > 64KB, socket not connected or network failure.
                */
                void sendDatagram(const std::vector<uint8>& buffer) const;
        
                //! Explicit send: sends to the address specified.
                /*!
                    Warning: If the socket has already been connected to an address using connectSocket,
                    the address argument will be ignored and the datagram will be sent to the connected address
                    instead.
                   If @a buffer is larger than getSendBufferSize() then multiple datagrams will be
                    sent of send buffer size with a final datagram with the remainder. This behaviour
                    should not be relied on as it may change in the future.
                */
                void sendDatagram(const std::vector<uint8>& buffer, const InetAddress& to) const;
        
                //! Receives a datagram packet for this socket.
                /*! Note: this method blocks the calling thread. Use the dataReady method to
                    do a non-blocking check for data.
                    @param buffer Receives data in the datagram
                    @param from Address data is to be received from
                    @param timeout_ms Time to wait for the data. After this period if data
                           is not available this method returns 0
                    @param append_buffer If true, data is appended to the buffer, otherwise the
                           data overwrites 
                    @return The number of bytes read or 0 if no data was available.
                    @throw SocketError operating system reported an error.
                */
                int receiveDatagram(std::vector<uint8>& buffer, const InetAddress& from, int timeout_ms = 100, const bool append_buffer = false) const;
        
                //! @return true if data is waiting in receive buffer
                bool dataReady() const { return waitForData(0); }
        
                //! @return true if the socket is 'connected'
                bool connected() const { return _connected; }
        
                //! Enables broadcast packets to be sent
                void enabledBroadcast(bool enabled);
        
                SOCKET _socket_fd;
            private:
                void subscribeMulticast(std::string address);
                void unsubscribeMulticast(std::string address);
        
                std::vector<std::string> _multicast_addresses;
        
                //! Banned copy constructor
                DatagramSocket(const DatagramSocket& rhs);
        
                //! Banned assignment operator
                DatagramSocket& operator=(const DatagramSocket& rhs);
        
                bool waitForData(int timeout_ms) const;
        
                int _rx_buff_len;
                int _tx_buff_len;
                char *_rx_buffer;
                char *_tx_buffer;
                InetAddress _local_address;
                InetAddress _remote_address;
                bool _connected;
                bool _blocking_on;
            };
        }
    }
}
#endif

