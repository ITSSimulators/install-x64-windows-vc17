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
#ifndef SM_COREDATA_EOD_ENGINEOUTPUTDATAFILEMERGER_H
#define SM_COREDATA_EOD_ENGINEOUTPUTDATAFILEMERGER_H

//! @file
#include "eod/engineoutputdata.h"
#include "eod/io/engineoutputdatafileerror.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            //! Read log files
            /*!
             */
            class SM_COREDATA_API EngineOutputDataFileReader
            {
            public:
                /*!
                */
                 EngineOutputDataFileReader();
        
                ~EngineOutputDataFileReader();
        
                //! Opens all the ".fll" files in the specified directory for reading.
                /*! 
                    @param dir The directory to read objects from
                    @param objects_to_read Vector containing the IDs of the objects to 
                    read from the files and attach to a new EngineOutputData when requested
                    @pre no files are open
                    @throw EngineOutputDataFileError if no log files are in @a dir, @a dir is
                        not a directory, a log file could not be opened for reading.

                 */
                void openFiles(const Serializable::ObjectIDVec& objects_to_read, const std::wstring& dir);

                //! Open files for merging data
                /*! Opens all the ".fll" files in the specified directory for reading. 
                    @param dir The directory to read objects from
                    @param objects_to_read Vector containing the IDs of the objects to 
                        read from the files and attach to a new EngineOutputData when requested
                    @pre no files are open
                    @throw EngineOutputDataFileError if an error occured whilst
                        opening the files */
                void openFiles(const Serializable::ObjectIDVec& objects_to_read, const std::string& dir);
        
                //! Open files for merging data
                /*! Opens all the ".fll" files in the specified directory for reading. 
                    Reads all objects within the LogFile
                    @param dir The directory to read objects from
                    @pre no files are open
                    @throw EngineOutputDataFileError if an error occured whilst opening the files */
                void openFiles(const std::wstring& dir);

                //! Open files for merging data
                /*! Opens all the ".fll" files in the specified directory for reading. 
                    Reads all objects within the LogFile
                    @param dir The directory to read objects from
                    @pre no files are open
                    @throw EngineOutputDataFileError if an error occured whilst opening the files */
                void openFiles(const std::string& dir);
       

                //! Opens a single file
                /*! 
                    @param log_file_path Path to file to read objects from.
                    @pre no files are open
                    @throw EngineOutputDataFileError if an error occured whilst opening the file 
                */
                void openFile(const std::wstring& log_file_path);
                void openFile(const std::string& log_file_path);

                //! Close any open files
                /*!
                    Never throws.

                 */
                void closeFiles();
        
                //! @return true if input files are currently open for reading
                /*!
                    Never throws

                */
                bool areFilesOpen() const;
        
                //! @return true if there is no more data to read from all files
                /*!
                    Never throws

                 */
                bool endOfData() const;
        
                //! Assemble an EngineOutputData object
                /*! Reads an EngineOutputData from each file, and attaches any sub-objects from it that
                    have a corresponding entry in the \a _objects_to_read vector to a new
                    EngineOutputData. If the ends of the files have ben reached, a NULL
                    pointer is returned.
                    @pre files are open
                    @throw SerializableError if an error occured whilst reading from the files,
                        or if duplicate object IDs were found in different files.
                        closeFiles() will be called.
                    @throw EngineOutputDataFileError if a log file did not contain an EngineOutputData
                        top level object. Required for framenumbers to be able to merge seperate log files.
                        closeFiles() will be called.

                  */
                EngineOutputDataPtr readData();
        
            private:
                class EngineOutputDataStream;

                //! Consumes non-mergable EngineOutputData objects
                /*!
                    @throw on error reading from file 
                */
                void skipNonMergable(EngineOutputDataStream&);

                //! @return the lowest frame number at the front of all streams
                EngineOutputData::FrameNumber nextMergableFrameNum();

                //! Merges the subobjects in src to dst
                void mergeSubObjects(EngineOutputData& src, EngineOutputData& dst);

                //! @return true id @a eod has a mergable subobject
                bool hasMergableSubObject(const EngineOutputData& eod) const;

                typedef std::vector<std::wstring> WStringVec;

                //! @return the full paths all the logfiles in the specified dir
                static WStringVec logFilesInDir(const std::wstring& dir);
        
                typedef Serializable::ObjectIDVec ObjectIDVec;

                //! Sorted Object IDs to read from the input files
                 ObjectIDVec _objects_to_read;

                typedef boost::shared_ptr<EngineOutputDataStream> EngineOutputDataStreamPtr;
                typedef std::vector<EngineOutputDataStreamPtr> EngineOutputDataStreamVec;
                //! Vector of input streams that we are reading data from
                EngineOutputDataStreamVec _streams;

            };
        }
    }
}

#endif


