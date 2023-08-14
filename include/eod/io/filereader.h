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
#ifndef SM_COREDATA_EOD_FILEREADER_H
#define SM_COREDATA_EOD_FILEREADER_H

//! \file
#include "eod/serializable.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {

            /*! \brief Allows sequential access to a log file.
                \if SM_COREDATA_LANGUAGE_PYTHON
                class FileReader:
                    """Reads log files.
                    """
                \endif
             */
            class SM_COREDATA_API FileReader
            {
            public:
                /*! \brief Constructs and un-opened instance.

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def __init__(self, file_path=None):
                        """Initializes the reader"""
                        pass
                    \endif
                */
                FileReader();

                /*! \brief Construct with opened file.

                    \param file_path The path to the log file to open.
                    \throw SerializableError Failed to open file
                    \post isOpen()
                */
                FileReader(const std::wstring& file_path);
                FileReader(const std::string& file_path);
        
                ~FileReader();
        
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
        
                //! \return true if there is no more data to read from all files
                /*!
                    Never throws

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def atEnd(self):
                        """Returns True if there is no more data to be read.
                        """
                    \endif
                 */
                bool atEnd() const;
        
                /*! \brief Reads the next Serializable object from the file.

                    \param status_out Status flags indicating the status of the deserialization.
                    \return A pointer to the deserialized object.

                    \pre isOpen()
                    \pre !atEnd()

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def read(self):
                        """Reads the next Serializable object from the file.

                        Returns a 2-tuple of (Serialiable,int)
                         """
                    \endif
                  */
                SerializablePtr read(sm::eod::DeserializationStatusFlags& status_out);
        
                /*! \brief Returns the current read position within the file */
                size_t position() const;

            private:
                // Ban copy construction
                FileReader(const FileReader&);
                // Ban assignement
                FileReader& operator=(const FileReader&);

                void throwFileOpenError(const std::string& filepath);
                // mutable as _stream.peek() is not const and we use it for determinig eof()
                mutable std::ifstream _ifs;
            };
        }
    }
}

#endif



