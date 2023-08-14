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
#ifndef SM_COREDATA_EOD_FILEWRITER_H
#define SM_COREDATA_EOD_FILEWRITER_H

//! \file
#include "eod/serializable.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {

            /*! \brief Allows writing data toa file.
                \if SM_COREDATA_LANGUAGE_PYTHON
                class FileWriter:
                    """Reads log files.
                    """
                \endif
             */
            class SM_COREDATA_API FileWriter
            {
            public:
                /*! \brief Constructs and un-opened instance.

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def __init__(self, file_path=None):
                        """Initializes the writer"""
                        pass
                    \endif
                */
                FileWriter();

                /*! \brief Construct with opened file.

                    \param file_path The path to the log file to open.
                    \throw SerializableError Failed to open file
                    \post isOpen()
                */
                FileWriter(const std::wstring& file_path);
                FileWriter(const std::string& file_path);
        
                ~FileWriter();
        
                //! Opens a single file
                /*! 
                    \param file_path Path to file to read objects from.
                    \pre no files are open
                    \throw EngineOutputDataFileError if an error occured whilst opening the file 
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
        
                /*! \brief Writes the object to file if serializableEnabled()

                    if !object->serializableEnabled() then the file contents are
                    left unchanged.

                    \pre isOpen()
                    \throw SerializableError An error occured while writing to file.
                                             close() will have been automatically called.

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def write(self):
                        """Writes the object to file if serializableEnabled()


                        This method may raise the following exceptions:

                            - SerializableError         An error occured while writing to file.
                                                        close() will have been automatically called.
                         """
                    \endif
                */
                void write(const Serializable& object);

                /*! \brief Writes the object to file if serializableEnabled()

                    if !object->serializableEnabled() then the file contents are
                    left unchanged.

                    \param object The object to serialize.
                    \return true if no error occurred, otherwise returns false and
                        stream is closed.
                    \pre isOpen()


                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def writeNoThrow(self):
                        """Writes the object to file if serializableEnabled()

                        The arguments are:
                            - object    The Serializable derived object to write.


                        Returns True if no error occurred. If False is returned
                        the writer is automatically closed.
                        """
                    \endif
                */
                bool writeNoThrow(const Serializable& object);

                /*! \brief Returns the current size of the file */
                size_t size() const;

                /*! \brief The currently opened filepath.

                    This is the empty string if no file is open.
                */
                std::wstring filePath() const;
        
            private:
                // Ban copy construction
                FileWriter(const FileWriter&);
                // Ban assignement
                FileWriter& operator=(const FileWriter&);

                mutable std::ofstream _ofs;
                std::wstring _file_path;
            };

            /*! \brief Throws a SerializableError indicating failure to open a file

                \throw SerializableError
            */
            SM_COREDATA_API void throwFileOpenError(const std::string& filepath);
            SM_COREDATA_API void throwFileOpenError(const std::wstring& filepath);

            /*! \brief Throws a SerializableError indicating failure to write to a file

                \throw SerializableError
            */
            SM_COREDATA_API void throwFileWriteError(const std::string& filepath);
            SM_COREDATA_API void throwFileWriteError(const std::wstring& filepath);
        }
    }
}

#endif




