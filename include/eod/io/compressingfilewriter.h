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
#ifndef SM_COREDATA_EOD_COMPRESSINGFILEWRITER_H
#define SM_COREDATA_EOD_COMPRESSINGFILEWRITER_H

//! \file
#include "eod/io/compressionprofileregistry.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {

            /*! \brief Filter applied to sub objects for writing a partial object tree

                \see EngineOutputBase::setSerialableSubObjectsEnabled
            */
            struct SubObjectFilter
            {
                sm::eod::Serializable::ObjectIDVec object_ids;
                bool recursive;
            };

            /*! \brief Allows writing compressed data to a log file.

                \see \ref coreapi_coredata_cpp_exampleapps_eodcompressor "Example eodcompressor"
                \see \ref coreapi_coredata_binarystandard_compression "Compression Binary Format"

                \if SM_COREDATA_LANGUAGE_PYTHON
                class CompressingFileWriter:
                    """Allows writing compressed data to a log file.
                    """
                \endif
             */
            class SM_COREDATA_API CompressingFileWriter
            {
            public:
                /*! \brief Constructs and un-opened instance.

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def __init__(self, file_path=None):
                        """Constructs and optionally opens a log file for writing.

                        This method may raise the following exceptions:

                            - SerializableError         An error occured while trying to open the file.

                        """
                        pass
                    \endif
                */
                CompressingFileWriter();

                /*! \brief Construct with opened file.

                    \param file_path The path to the log file to open.
                    \throw SerializableError Failed to open file
                    \post isOpen()
                */
                explicit CompressingFileWriter(const std::wstring& file_path);
                explicit CompressingFileWriter(const std::string& file_path);
        
                ~CompressingFileWriter();
        
                //! Opens a single file
                /*! 
                    Calls close() to close any already opened file and then tries
                    to open a new file for writing.

                    \param file_path Path to file to write to. Any existing data is truncated.
                    \return \c true if the file was opened successfully.
                */
                bool openNoThrow(const std::wstring& file_path);
                bool openNoThrow(const std::string& file_path);

                //! Opens a single file
                /*! 
                    Calls close() to close any already opened file and then tries
                    to open a new file for writing.

                    \param file_path Path to file to write to. Any existing data is truncated.
                    \throw SerializableError Failed to open file
                */
                void open(const std::wstring& file_path);
                void open(const std::string& file_path);

                //! Flushes any data and closes the file if open.
                /*!
                    \throw SerializableError Failed to write to file, file will have been closed.

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
        
        
                /*! \brief Writes the object to the file.

                    \pre isOpen()
                    \throw SerializableError Failed to write to file, file will have been closed.

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def write(self):
                        """Writes the object to the file.

                        This method may raise the following exceptions:

                            - SerializableError         An error occured while writing to file.
                                                        close() will have been automatically called.
                         """
                    \endif
                  */
                void write(SerializablePtr object);


                /*! \brief Writes the object to file

                    The filter is applied to the object and then any nodes
                    enabled for serializable will be written using the current
                    compression profile.

                    \pre isOpen()
                    \throw SerializableError Failed to write to file, file will have been closed.
                */
                void write(SerializablePtr object, SubObjectFilter& filter);

                /*! \brief Returns the number of bytes written to disk so far.

                    This does not include any unflushed data.
                */
                size_t bytesWrittenToDisk() const;

                /*! \brief Flushes any data in memory to disk 
                
                    Can be called even if isOpen() is false.
                    \throw SerializableError Failed to write to file, file will have been closed.
                */
                void flush();


                /*! \brief Flushes any existing data and changes the compression profile

                    Subsequent calls to write will use the supplied compression profile.

                    \throw SerializableError Failed to write to file, file will have been closed.
                */
                void setCompressionProfile(CompressionProfileValue profile);
        
                /*! \brief Returns the current compression profile */
                CompressionProfileValue compressionProfile() const;

                /*! \brief Sets the compression profile registry to use.

                    \param profile_registry Registry used for encoding serializable objects.
                    \pre !isOpen()
                    \see defaultCompressionProfileRegistry()
                */
                void setProfileRegistry(const CompressionProfileRegistry& profile_registry);

                /*! \brief The currently opened filepath.

                    This is the empty string if no file is open.
                */
                std::wstring filePath() const;

            private:
                // Ban copy construction
                CompressingFileWriter(const CompressingFileWriter&);
                // Ban assignment
                CompressingFileWriter& operator=(const CompressingFileWriter&);

                //! @return true if profile calls for writing data uncompressed.
                bool isCompressionDisabled() const;

                //! Resets
                void resetCompressor();

                bool flushNoThrow();
                void writeObjectToFile(const sm::eod::Serializable& object);

                class Compressor;

                FileWriter _writer;
                CompressionProfileRegistry _profile_registry;

                CompressionProfileValue _compression_profile;
                boost::scoped_ptr<Compressor> _compressor;
                sm::eod::io::PTS _presentation_time_stamp;
            };
        }
    }
}

#endif




