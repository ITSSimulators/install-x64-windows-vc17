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
#ifndef SM_COREDATA_EOD_ENGINEOUTPUTDATAFILEWRITER_H
#define SM_COREDATA_EOD_ENGINEOUTPUTDATAFILEWRITER_H

//! \file
#include "eod/engineoutputdata.h"
#include "eod/io/engineoutputdatafileerror.h"
#include "eod/io/bufferedoutputfilestream.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            //! Writes log files
            /*!
                \if SM_COREDATA_LANGUAGE_PYTHON
                class EngineOutputDataFileWriter:
                    """Writes log files.
                    """
                \endif
             */
            class SM_COREDATA_API EngineOutputDataFileWriter
            {
            public:
                /*!
                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def __init__(self):
                        """Initializes the writer."""
                    \endif
                */
                 EngineOutputDataFileWriter();

                ~EngineOutputDataFileWriter();

                /*! \brief Open some new logfiles for writing

                    \param ids_to_log Vector of object IDs that we want to log. Each ID in 
                        this vector will have its own logfile that objects with a 
                        corresponding ID will be written to.
                    \param logging_dir The directory to create the new logfiles in
                    \param suffix A string that will be appended to the log file filename, before
                        the file extension.
                        This can be used to append a date and time to the logfile, for example.
                    \param file_buffer_size Buffer file size.
                    \pre no files are open
                    \throw EngineOutputDataFileError if an error occured in opening the files
                    \see objectIDToFileName
                    \deprecated Use newFile().

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def newFiles(self, ids_to_log, logging_dir, suffix = "", file_buffer_size = 32768):
                        """Open some new logfiles for writing.

                        The arguments are:
                            - ids_to_log        A tuple of objectIDs that are to be logged.
                                                Each ID in this vector will have its own
                                                logfile that objects with a corresponding ID will
                                                be written to. The tuple cannot be empty.
                            - logging_dir       The directory to create the new logfiles in.
                            - suffix            A string that will be appended to the log file
                                                filename, before the file extension.
                            - file_buffer_size  The size of the file buffer.

                        This method may raise the following exceptions:

                            - EngineOutputDataFileError An error occurred while opening the files, or
                                                        the object ID is not known to objectIDToFileName().
                         """
                    \endif
                  */
                COREDATA_DEPRECATED("Use newFile()") void newFiles(const Serializable::ObjectIDVec& ids_to_log,
                              const std::wstring& logging_dir,
                              const std::wstring& suffix = L"",
                              int file_buffer_size = 32768);

                /*! \brief Open some new logfiles for writing

                    \param ids_to_log Vector of object IDs that we want to log. Each ID in this vector will have its own
                        logfile that objects with a corresponding ID will be written to
                    \param logging_dir The directory to create the new logfiles in
                    \param suffix A string that will be appended to the log file filename, before
                        the file extension.
                        This can be used to append a date and time to the logfile, for example.
                    \param file_buffer_size Buffer file size.

                    \pre no files are open
                    \throw EngineOutputDataFileError if an error occured in opening the files 
                    \see objectIDToFileName
                    \deprecated Use newFile().
                */
                COREDATA_DEPRECATED("Use newFile()") void newFiles(const Serializable::ObjectIDVec& ids_to_log,
                              const std::string& logging_dir,
                              const std::string& suffix = "",
                              int file_buffer_size = 32768);

                //! Open a new logfile for writing.
                /*! \param object_id The object ID that we want to log. 
                    \param log_file_path The path to a file to write to. The path must exist.
                    \param file_buffer_size Buffer file size.
                    \pre no files are open
                    \throw EngineOutputDataFileError if an error occured in opening the files

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def newFiles(self, object_id, log_file_path, file_buffer_size = 32768):
                        """Open a new logfile for writing.

                        The arguments are:
                            - object_id         The ObjectID to log.
                            - log_file_path     The path to a file to write to.
                            - file_buffer_size  The size of the file buffer.

                        This method may raise the following exceptions:

                            - EngineOutputDataFileError An error occurred while opening the files.
                         """
                    \endif
                  */
                void newFile(Serializable::ObjectID object_id,
                              const std::wstring& log_file_path,
                              int file_buffer_size = 32768);

                //! Open a new logfile for writing.
                /*! \param object_id The object ID that we want to log. 
                    \param log_file_path The path to a file to write to. The path must exist.
                    \param file_buffer_size Buffer file size.
                    \pre no files are open
                    \throw EngineOutputDataFileError if an error occured in opening the files
                */
                void newFile(Serializable::ObjectID object_id,
                              const std::string& log_file_path,
                              int file_buffer_size = 32768);

                //! Open a new logfile for writing.
                /*!
                    \param log_file_path The path to a file to write to. The path must exist.
                    \param file_buffer_size Buffer file size.
                    \pre no files are open
                    \throw EngineOutputDataFileError if an error occured in opening the files

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def newFiles(self, log_file_path, file_buffer_size = 32768):
                        """Open a new logfile for writing.

                        The arguments are:
                            - log_file_path     The path to a file to write to.
                            - file_buffer_size  The size of the file buffer.

                        This method may raise the following exceptions:

                            - EngineOutputDataFileError An error occurred while opening the files.
                         """
                    \endif
                  */
                void newFile(const std::wstring& log_file_path,
                             int file_buffer_size = 32768);

                //! Open a new logfile for writing.
                /*!
                    \param log_file_path The path to a file to write to. The path must exist.
                    \param file_buffer_size Buffer file size.
                    \pre no files are open
                    \throw EngineOutputDataFileError if an error occured in opening the files
                */
                void newFile(const std::string& log_file_path,
                             int file_buffer_size = 32768);

                //! Close the open logfiles
                /*!
                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def closeFiles(self):
                        """Closes any open files.
                        """
                    \endif
                 */
                void closeFiles();

                //! \return true if the logfiles are currently open and can be written to
                /*!
                    Never throws

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def areFilesOpen(self):
                        """Returns True if files are currently opened.
                        """
                    \endif
                */
                bool areFilesOpen() const;

                //! Write \a data to the open logfiles
                /*! 
                    Each top-level sub object that has serializeEnabled() == true and
                    corresponds to an open logfile is extracted from \a data and written to file.
                    Nothing is done if data->serializeEnabled() == false.
                    If the top-level sub object is not found it is also looked for under the
                    first FaceSetOutputDataLatest object.

                    \param data The engine output data to write to files.
                    \pre files are open
                    \throw EngineOutputDataFileError Failed to write file.
                    \deprecated Use non-shared pointer version.

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def writeData(self, label):
                        """Writes data to the open logfiles.

                        The arguments are:
                            - data  The EngineOutputData instance to write.
                                    Each top-level sub object that has serializeEnabled() == True 
                                    and corresponds to an open logfile is extracted 
                                    from data and written to file.
                        """
                    \endif
                  */
                COREDATA_DEPRECATED("Use non-shared pointer version") void writeData(const ConstEngineOutputDataPtr& data);
                void writeData(const EngineOutputData& data);

                //! Map between a Serializable object ID and a filename
                /*! \return the filename that represents the data specified by object_id.
                    For example "Head" for HeadOutputData objects.
                    \throw EngineOutputDataFileError If the ID is unrecognised
                    
                    The default mappings are:
                    <ul>
                        <li>TimingOutputData "Timing"
                        <li>HeadOutputData "Head"
                        <li>HeadOutputDataV2 "HeadV2"
                        <li>EyeOutputData "Eye"
                        <li>FeatureSetsByCamera "Features"
                        <li>FaceOutputData "Face"
                        <li>FaceOutputDataV2 "FaceV2"
                        <li>WorldOutputData "World"
                        <li>WorldOutputDataV2 "WorldV2"
                        <li>EngineStateOutputData "EngineState"
                        <li>InertiaOutputData "Inertia"
                        <li>CustomEventOutputData "Custom_Events"
                        <li>GPSOutputData "GPS"
                        <li>GPSOutputDataV2 "GPSV2"
                    </ul>

                    \if SM_COREDATA_LANGUAGE_PYTHON
                    def objectIDToFileName(object_id):
                        """Returns the filename that represents the data specified by object_id.

                        The arguments are:
                            - object_id     The object ID to get the filename for.

                        The currently known object IDs are:
                          - TimingOutputData "Timing"
                          - HeadOutputData "Head"
                          - HeadOutputDataV2 "HeadV2"
                          - EyeOutputData "Eye"
                          - FeatureSetsByCamera "Features"
                          - FaceOutputData "Face"
                          - FaceOutputDataV2 "FaceV2"
                          - WorldOutputData "World"
                          - WorldOutputDataV2 "WorldV2"
                          - EngineStateOutputData "EngineState"
                          - InertiaOutputData "Inertia"
                          - CustomEventOutputData "Custom_Events"
                          - GPSOutputData "GPS"
                          - GPSOutputDataV2 "GPSV2"

                        This method may raise the following exceptions:

                            - EngineOutputDataFileError The object ID is not recognized.
                        """
                    \endif
                 */
                static std::wstring objectIDToFileName(Serializable::ObjectID object_id);

                //! Registers a mapping between a Serializable object ID and a filename.
                static void registerObjectIDFileName(Serializable::ObjectID object_id,std::wstring filename);

            private:
                //! Log object to stream if serializeEnabled()
                /*!
                    \throw EngineOutputDataFileError Failure to write to stream.
                */
                void serializeObject(const Serializable& object, std::ostream& stream);

                //! Log the sub-object of \a output_data that has the object_id \a sub_object_id
                void writeSubObject(const EngineOutputData& output_data, Serializable::ObjectID sub_object_id);

                typedef std::map<Serializable::ObjectID, sm::eod::io::BufferedOutputFileStream*> StreamMap;
                /*! Map of the output streams this logger is writing to. The key here is the Serializable
                    ID of the particular data sub-object we are writing */
                StreamMap _output_files;
                bool _log_all;

                //! Banned Copy Constructor
                EngineOutputDataFileWriter(const EngineOutputDataFileWriter&);
                //! Banned assignment operator
                const EngineOutputDataFileWriter& operator=(const EngineOutputDataFileWriter&);
            };
        }
    }
}

#endif


