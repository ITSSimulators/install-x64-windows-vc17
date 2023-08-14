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
#ifndef SM_COREDATA_EOD_DECOMPRESSINGFILEREADER_H
#define SM_COREDATA_EOD_DECOMPRESSINGFILEREADER_H

//! \file
#include "eod/io/filereader.h"
#include "eod/io/compressingfilewriter.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {


            /*! \brief Allows sequential access to a log file containing compressed objects.

                \see \ref coreapi_coredata_cpp_exampleapps_eodcompressor "Example - eodcompressor"
                \see \ref coreapi_coredata_binarystandard_compression "Compression Binary Format"

                \if SM_COREDATA_LANGUAGE_PYTHON
                class DecompressingFileReader:
                    """Allows sequential access to a log file containing compressed objects.
                    """
                \endif
             */
            class SM_COREDATA_API DecompressingFileReader
            {
            public:
                /*! \brief Constructs and un-opened instance with default decoder factory.

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def __init__(self, arg=None):
                        """Initializes the reader
                        
                        The arguments are:
                            - arg   If None then the reader is un-opened.
                                    If a string then the file is opened and if
                                    that fails a SerializationError is raised.
                                    If it is a SerializableCompressorDecoderFactory object
                                    then the reader is un-opened but will use the decoder factory
                                    for deserialization.

                        This method may raise the following exceptions:

                            - SerializableError Failed to open file for reading.
                        """
                        pass
                    \endif
                */
                DecompressingFileReader();

                /*! \brief Construct with opened file and default decoder factory.

                    \param file_path The path to the log file to open.
                    \throw SerializableError Failed to open file
                    \post isOpen()
                */
                DecompressingFileReader(const std::wstring& file_path);
                DecompressingFileReader(const std::string& file_path);

                /*! \brief Constructs and un-opened instance using a copy of the decoder factory.

                    \param decoder_factory The decoder factory, a copy of which is used
                        for decoding compressed objects.
                */
                DecompressingFileReader(const SerializableCompressorDecoderFactory& decoder_factory);

        
                ~DecompressingFileReader();
        
                //! Opens a single file
                /*! 
                    \param file_path Path to file to read objects from.
                    \pre !isOpen()
                    \throw SerializableError if an error occured whilst opening the file 
                */
                bool open(const std::wstring& file_path);
                bool open(const std::string& file_path);

                //! Closes the file if open.
                /*!
                    Never throws.

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def close(self):
                        """Close the file if open.
                        """
                    \endif
                 */
                void close();
        
                //! \return true if input file is currently open.
                /*!
                    Never throws

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def isOpen(self):
                        """Returns True if file is currently opened.
                        """
                    \endif
                */
                bool isOpen() const;
        
                //! \return true if there is no more data to read the file.
                /*!
                    Never throws

                    \pre isOpen()

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def atEnd(self):
                        """Returns True if there is no more data to be read.
                        """
                    \endif
                 */
                bool atEnd() const;
        
                /*! \brief Reads the next Serializable object from the file.

                    \param status_out DeserializationStatus enumeration indicating the state of the object.
                    \return The serializable object constructed from
                                            the file contents.
                    \pre isOpen()
                    \throw SerializableError End of file or an error occured whilst reading from the file.
                        close() will be called.

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def read(self):
                        """Reads the next Serializable object from the file.

                        This method may raise the following exceptions:

                            - SerializableError         An error occured while reading from the file.
                                                        close() will have been automatically called.
                         """
                    \endif
                  */
                SerializablePtr read(sm::eod::DeserializationStatusFlags& status_out);
        
                /*! \brief Sets the decoder factory to use for decompressing data.

                    \pre !isOpen()

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def setDecoderFactory(self, decoder_factory):
                        """Sets the decoder factory to use for decompressing data.

                        The arguments are:
                            - decoder_factory   The decoder factory to use for decompresing.

                        This method may raise the following exceptions:

                            - invalid_argument  self.isOpen() is not False.
                        """
                    \endif
                */
                void setDecoderFactory(const SerializableCompressorDecoderFactory& decoder_factory);

            private:
                class Decompressor;

                // Ban copy construction
                DecompressingFileReader(const DecompressingFileReader&);
                // Ban assignment
                DecompressingFileReader& operator=(const DecompressingFileReader&);

                FileReader _reader;
                boost::scoped_ptr<Decompressor> _decompressor;
            };
        }
    }
}

#endif

