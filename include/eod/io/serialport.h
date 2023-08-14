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
#ifndef SM_COREDATA_EOD_SERIALPORT_H
#define SM_COREDATA_EOD_SERIALPORT_H

//! @file
#include "eod/io/serialporterror.h"
#include "eod/io/devicesettings.h"


namespace sm
{
    namespace eod
    {
        namespace io
        {
            //! A simple SerialPort class supporting raw I/O and also a simple transport layer protocol for reliable transmission.
            /*!
                The hardware protocol is fixed to: No flow control, no parity, 8 data bits, 1 stop bit
                Multiple SerialPort objects can use the same COM port, but only 1 object may
                have the port open.
                @note Uses the OS dependent type "BaudRate".
                @note Attempting to open non-existing com-ports will throw a SerialPortError exception.
            */
            class SM_COREDATA_API SerialPort
            {
            public:
                //! Constructs using the @a port_id, the baud-rate @a rate and the parity @a parity.
                /*! If @a open = true, attempts to open the serial port.
                    @pre port_id is in the range 0..NUMPORTS
                    @pre parity is in the range NOPARITY..SPACEPARITY
                    @pre stop_bits is in the range ONESTOPBIT..TWOSOPBITS
                    @throw SerialPortError if @a open = true, and the port failed to open.
                  */
                SerialPort(ComPortID port_id = COM1,
                           BaudRate rate = B9600,
                           bool open = true,
                           BYTE parity = NoParity,
                           BYTE stop_bits = OneStopBit);

                //! Closes the port before deletion
                virtual ~SerialPort();

                //! @return The port id used by the object
                ComPortID portId() const;

                //! @return The name-string of the port used by the object eg: "COM1", "COM2" etc
                std::string portName() const;

                //! @return true if the port @a port_id is open
                /*! @pre port_id is in the range 0..NUMPORTS
                 */
                static bool isOpen(ComPortID port_id);



                //! Attempts to open the serial port.
                /*!
                    Calls openNoThrow and maps system errors to SerialPortError exception.

                    @param rx_timeout If true, enables SerialPort::read() timeouts. 
                    @param rx_timeout_ms Number of milliseconds to block when @a rx_timeout == true
                    @throw SerialPortError if: port already open, no port or port could not support baud rate, 
                        or an operating system error occured.
                    @see SerialPort::read()
                */
                void open(bool rx_timeout = false, int rx_timeout_ms = RX_TIMEOUT_MS);

                //! @return true if the previous call to open succeeded with no intervening call to close().
                bool isOpen() const;

                //! Flush any bytes in the output buffer
                /*!
                    @pre isOpen() is true
                */
                void flush();

                //! Resets the serial-port.
                /*!
                    Clears any errors and discards any bytes in the input and output buffers.
                    @pre isOpen() is true
                */
                void reset();

                //! Closes the serial-port
                /*!
                    Can be called even if isOpen() is false.
                */
                void close();
        
                //======================================================================
                // Low Level I/O Methods
                //======================================================================
                //! Performs a blocking write.
                /*!
                    @param data The data to send.
                    @throw SerialPortError with SerialPortError::timeout() == @b true if
                        the time to send the data exceeds 500ms + 1ms * data.size().
                    @pre isOpen() is true
                    @see open()
                */
                void write(const std::vector<uint8>& data) const;

                //! Performs a blocking read until a specified number of bytes have been read or a timeout occurs.
                /*!
                    @param data Received bytes are placed into this vector
                    @param num_to_read The number of bytes that are received into @a data before the
                        function returns.
                    @param append If true, appends @a data with the received bytes, otherwise
                        clears @a data before reading.
                    @throw SerialPortError with SerialPortError::timeout() == @b true if
                        port is opended with the @a rx_timeout flag set to @b true
                        and the time-period between the arrival of any two characters
                        exceeds 2 seconds or the total time 
                        exceeds @a rx_timeout_ms + 100ms * @a num_to_read.
                    @pre isOpen() is true
                */
                void read(std::vector<uint8>& data, int num_to_read, bool append = false) const;

                //! Read a single byte, blocking the calling thread until the byte is received or a timeout occurs.
                /*!
                    @return The next character read from the serial-port hardware buffer
                    @throw SerialPortError with SerialPortError::timeout() == @b true if
                        port is opended with the @a rx_timeout flag set to @b true
                        and the time-period between the arrival of any two characters
                        exceeds 2 seconds or the total time 
                        exceeds @a rx_timeout_ms + 100ms * @a num_to_read.

                    @pre isOpen() is true
                    @see open()
                */
                char read() const;

        
                //======================================================================
                // Datagram I/O methods 
                //======================================================================
                //! Constructs a datagram frame from a buffer of data and writes it to the serial port.
                /*!
                    @param data The data to send.
                    @return 0 on success, otherwise system error number.
                    @throw SerialPortError with SerialPortError::timeout() == @b true if
                        the time to send the data exceeds 500ms + 1ms * data.size().
                    @pre isOpen() is true.
                    @see write()
                    @see @ref coreapi_coredata_serialprotocol
                */
                void sendDatagram(const std::vector<uint8>& data) const;

                //! Receives a datagram over the serial-port.
                /*!
                    @param data Data from frame is read into this vector
                    @param append If true, existing bytes in @a data vector are unchanged, otherwise
                        old bytes are cleared.
                    @return The number of bytes read.
                    @throw SerialPortError with SerialPortError::timeout() == @b true if
                        port is opended with the @a rx_timeout flag set to @b true
                        and the time-period between the arrival of any two characters
                        exceeds 2 seconds or the total time 
                        exceeds @a rx_timeout_ms + 100ms * @a num_to_read.
                    @pre isOpen() is true.
                    @see read()
                    @see @ref coreapi_coredata_serialprotocol
                */
                int receiveDatagram(std::vector<uint8>& data, bool append = false) const;

                //======================================================================
                // Non-Throwing I/O methods 
                //======================================================================

                //! @return true if the error number indicates a timeout
                static bool isTimeout(system_error_t error_number);

                //! Attempts to open the serial port.
                /*!
                    @param rx_timeout If true, enables SerialPort::read() timeouts. 
                    @param rx_timeout_ms Number of milliseconds to block when @a rx_timeout == true
                    @return system error code if serial port failed to open. The @a rx_timeout parameter
                        must be false for non-windows systems as the timeout code is not implemented yet.
                        
                    @todo Implement the timeout behaviour under Linux
                */
                system_error_t openNoThrow(bool rx_timeout = false, int rx_timeout_ms = RX_TIMEOUT_MS);

                //! Receives a datagram over the serial-port.
                /*!
                    Does not throw.

                    @param data Data from frame is read into this vector
                    @param append If true, existing bytes in @a data vector are unchanged, otherwise
                        old bytes are cleared.
                    @param data_size_out The number of data bytes appended to @a data
                    @return 0 on success, otherwise system error number.
                        When SerialPortError::timeout() == @b true and the 
                        port is opended with the @a rx_timeout flag set to @b true
                        and the time-period between the arrival of any two characters
                        exceeds 2 seconds or the total time 
                        exceeds @a rx_timeout_ms + 100ms * @a num_to_read then the isTimeout()
                        function will return true when passed the return value.
                    @pre isOpen() is true.
                    @see readNoThrow
                    @see @ref coreapi_coredata_serialprotocol
                */
                system_error_t receiveDatagramNoThrow(std::vector<uint8>& data, bool append, int& data_size_out) const;

                //! Constructs a datafram from a buffer of data and writes it to the serial port.
                /*!
                    @param data The data to send.
                    @return 0 on success, otherwise system error number.
                    @pre isOpen() is true.
                    @see writeNoThrow()
                    @see @ref coreapi_coredata_serialprotocol
                */
                system_error_t sendDatagramNoThrow(const std::vector<uint8>& data) const;
        
                //! Performs a block reading of a single byte.
                /*!
                    Does not throw.

                    @param value_out Result of read if successfull.
                    @return 0 on success, otherwise system error number.
                        When SerialPortError::timeout() == @b true and the 
                        port is opended with the @a rx_timeout flag set to @b true
                        and the time-period between the arrival of any two characters
                        exceeds 2 seconds or the total time 
                        exceeds @a rx_timeout_ms + 100ms * @a num_to_read then the isTimeout()
                        function will return true when passed the return value.
                    @pre isOpen() is true.
                */
                system_error_t readNoThrow(uint8& value_out) const;

                //! Performs a block reading of a single byte.
                /*!
                    Does not throw.

                    @param data Result of read if successfull.
                    @param num_to_read
                    @param append When true, read data will be append
                    @return 0 on success, otherwise system error number.
                        When SerialPortError::timeout() == @b true and the 
                        port is opended with the @a rx_timeout flag set to @b true
                        and the time-period between the arrival of any two characters
                        exceeds 2 seconds or the total time 
                        exceeds @a rx_timeout_ms + 100ms * @a num_to_read then the isTimeout()
                        function will return true when passed the return value.
                    @pre isOpen() is true.
                */
                system_error_t readNoThrow(std::vector<uint8> &data, int num_to_read, bool append) const;

                //! Performs a blocking write.
                /*!
                    Does not throw.

                    @param data The data to send.
                    @return 0 if read successful and @a data has been updated, otherwise
                        system error number. If the time to send the data exceeds 
                        500ms + 1ms * data.size() then passing the returned error number
                        to isTimeout() will return true.
                    @pre isOpen() is true.
                */
                system_error_t writeNoThrow(const std::vector<uint8>& data) const;

                //! The timeout period for a read operation
                BOOST_STATIC_CONSTANT(int, RX_TIMEOUT_MS = 10000);
        
            private:
                //! Banned copy constructor
                SerialPort(const SerialPort& copy_from);

                //! Banned assignment operator
                SerialPort& operator=(const SerialPort& copy_from);

                //! Reads the serial-port until the frame flag sequence is detected.
                //! Received bytes are placed into @a data
                system_error_t readUntilFrameMarker(std::vector<uint8>& data) const;
                system_error_t skipUntilFrameMarker() const;

                system_error_t saveSystemErrorAndClose();
        
                //! The COM port used by the class's methods
                const ComPortID _port_id;
                //! The baud-rate the port is opened with
                const BaudRate _rate;
                //! The parity the port is opened with
                const BYTE _parity;
                //! The stop bits the port is opened with
                const BYTE _stop_bits;
        
                // OS specific handles to the serial port.
            
    #ifdef COREDATA_CC_GNU      
                int _serport_handle;
    #endif

    #ifdef COREDATA_OS_WIN32
                HANDLE _serport_handle;
                HANDLE _write_event_handle;
                HANDLE _read_event_handle;
    #endif      
        
                //======================================================================
                // Static Methods 
                //======================================================================
                //! Generate a two-byte CRC value, for the bytes in @a data.
                static unsigned short makeCRC(const std::vector<uint8>& data);
                //! @return true if the last two bytes in @a data is the correct CRC for the preceding bytes.
                static bool checkCRC(const std::vector<uint8>& data);

                //! Converts OS independent BaudRate type into OS specific flag value
                static unsigned int baudRateFlag(BaudRate rate);
                //! Uses OS specific calls to confirm that the values in _open_ports match the actual
                //! state of the COM ports.
                static void updateOpenPorts();
                //! Array of flags - if true, associated port is considered to be open.
                static bool _open_ports[NUM_PORTS];
            };
        }
    }
}
#endif

