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
#ifndef SM_COREDATA_EOD_SOCK_TYPES_H
#define SM_COREDATA_EOD_SOCK_TYPES_H

//! @file
#if defined(COREDATA_CC_GNU)
    // BSD SOCKETS
    #include <sys/ioctl.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>

    #define INVALID_SOCKET -1
    #define ERROR -1
    #define SOCKET_ERROR -1
    #define SOCKET int
    #define closesocket(x) close((x))
    #define ADDR(x) (x).sin_addr.s_addr

    namespace sm
    {
        namespace eod
        {
            inline int ioctlsocket (SOCKET s, long cmd, u_long *argp) { return ::ioctl(s,cmd,argp); }
        }
    }
#endif

#if defined(COREDATA_OS_WIN32)
    #include <winsock2.h>
    #include <ws2tcpip.h>

    // WINDOWS SOCKETS
    #define ADDR(x) (x).sin_addr.S_un.S_addr
#endif // COREDATA_OS_WIN32

#endif

