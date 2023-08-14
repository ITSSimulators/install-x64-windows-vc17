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
#ifndef SM_COREDATA_EOD_INETADDRESS_H
#define SM_COREDATA_EOD_INETADDRESS_H

//! @file
#include "eod/io/inetaddresserror.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            //! Must be called before any calls to network related routines
            SM_COREDATA_API void initNetLib();
        
            //! Makes an error string from the last network related error
            SM_COREDATA_API const std::string netLibErrorString(const std::string& context_message);

        
            //! An InetAddress consists of an IP address, and a port number.
            /*! This class is NOT thread-safe, since there is a static _address_init bool which is
                used and not protected by a mutex. This may only cause unexpected behaviour if two threads
                happen to try to construct the first InetAddress at the same time. In this case, the local
                address table may be populated twice.
                
                @todo Make this class work properly for computers with more than one network adapter,
                      especially if you are logging to the localhost. At the moment the first adapter is
                      always used. */
            class SM_COREDATA_API InetAddress
            {
            public:
                //! Constructs the internet address of the local host.
                /*! If no port number is specified, zero is used indicating
                    that the port number can be the next available.
                    @throw SocketError Error initializing networking
                */
                explicit InetAddress(int port = 0);
                //! Constructs the internet address given the address string and port number.
                //! The host string can be a hostname or a dotted IP number.
                /*! If a dotted IP address is provided, but no hostname could be resolved,
                    the hostname is set to the dotted address string.
                    If a hostname is provided but could not be resolved, the address reverts to
                    the local host.
                    @throw SocketError Error initializing networking
                */
                InetAddress(int port, const std::string& host);
        
                //! Constructs the internet address on the given port number and local adapter
                /*!
                    @throw SocketError Error initializing networking
                */
                InetAddress(int port, int adapter);
                
                //! Constructs a copy.
                InetAddress(const InetAddress& rhs);
                InetAddress(const struct sockaddr_in& rhs);
        
                //! Sets the portnum of the address
                /*! @param portnum Should be a valid unsigned short number. Negative port
                                   numbers will be set to 0. Port numbers that are too big will
                                   be truncated to the largest 16 bit port number. There may be
                                   restrictions imposed by your OS on what port numbers can be used*/
                void setPort(int portnum);

                //! Sets the address to the given host
                //! The host string can be a hostname or a dotted IP number.
                /*! If a dotted IP address is provided, but no hostname could be resolved,
                    the hostname is set to the dotted address string.
                    If a hostname is provided but could not be resolved, the address reverts to
                    the local host. 
                    @param host contains the hostname as a string containing the dns name of dotted IP number.
                    @return true if the address was ok */
                bool setHost(const std::string& host);
                //! Make this address a receiver address, which will accept packets from
                //! any host
                void setReceiverAddress();
        
                //! Sets the host address to the broadcast address.
                void setBroadcastAddress();
        
                //! @return the portnum of the address
                int getPort() const;
                //! @return the dotted network address string: eg "123.456.7.8"
                const std::string getHostIP() const;
                //! @return the Fully Qualified Domain Name of the host (not an alias).
                const std::string getHostName(bool resolve=true) const;
                //! @return the sockaddr struct for the address
                struct sockaddr *getSockAddr() const;
        
                //! Must be called if getSockAddr is used to change the hostname
                void resetHostName() const;
        
                //! @return true if the address is on the local machine.
                bool isLocal() const;
                //! Compares addresses. Note that this function compares the port
                //! numbers as well as the hostnames. If you just want to compare the
                //! hostnames, use the getHostIP() or getHostName() functions
                bool operator==(const InetAddress& a2) const;
        
                //! Return the string representation of this inet address
                std::string toString() const;
        
    #ifdef _DEBUG
                std::vector<in_addr> getLocalAddressList() const {return _local_addr;}
                static std::string ipAddrToString(in_addr& socket_addr);
    #endif
            private:
        
                //! Set the current host to be the localhost
                void setLocalHost();
                //! Set the current host to be one of the local network adapters
                void setLocalAdapter(unsigned int num);
                //! Initialise networking and set the port
                void initialise(int port);
        
                //! The address of the socket.
                /* On windows this is:
                   @code
                    struct sockaddr_in {
                        short               sin_family;
                        unsigned short      sin_port;
                        struct in_addr      sin_addr;
                        char                sin_zero[8];
                    };
        
                    struct in_addr {
                       union {
                           struct { u_char s_b1,s_b2,s_b3,s_b4; }   S_un_b;
                           struct { u_short s_w1,s_w2; }            S_un_w;
                           u_long                                   S_addr;
                       } S_un;
                    };
                    @endcode
                */
                mutable struct sockaddr_in _sock_addr;
                //! The name of the host at the address, if resolvable, otherwise dotted IP string.
                mutable std::string _hostname;
                mutable bool _hostname_resolved;
        
                //! Method that constructs a list of all addresses for the local host
                static void buildLocalAddressTable();
                //! List of local addresses
                static std::vector<in_addr> _local_addr;
                static std::string _local_hostname;
                static bool _address_init;
            };

            //! For output using standard streams
            SM_COREDATA_API std::ostream& operator<<(std::ostream& os, const InetAddress& inet_address);
        }
    }
}
#endif

