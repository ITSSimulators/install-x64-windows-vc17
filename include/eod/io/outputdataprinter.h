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
#ifndef SM_COREDATA_EOD_FACESTATEPRINTER_H
#define SM_COREDATA_EOD_FACESTATEPRINTER_H

//! @file
#include "eod/io/inetaddress.h"
#include "eod/engineoutputdata.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            //! Display FacState and EngineOutputData objects
            class SM_COREDATA_API OutputDataPrinter
            {
            public:
        
                //! Display face states from a given network host
                /*! 60 Hz data is displayed by continuously overwriting previous frame data.
                    NOTE: this method is not intended to be used for more than one host at the
                    same time, since it is a static method. */
                template <typename SpecificFaceState>
                static void displayFaceStateFromNet(const SpecificFaceState& face_state, const InetAddress& from)
                {
                    if ((_num_received == 0) || (_host_ip != from.getHostIP()))
                    {
                        _host_ip = from.getHostIP();
                        resetCounters();
                        std::cout << std::endl << "Receiving FaceState ID " <<
                            static_cast<int>(face_state.objectID()) << " data from " << 
                            from.getHostIP() << std::endl;
                    }
                    
                    FrameDataInfo display_info = getInfoFromFaceState(face_state);
                    processData(display_info);
                }
        
                static void displayEngineOutputDataFromNet(EngineOutputData& engine_output_data, const InetAddress& from);
        
            private:
                //! Used to hold the data that should be printed on the screen
                struct FrameDataInfo
                {
                    unsigned long _frame_num;
                    bool _tracking;
                    unsigned long _num_data_bytes;
                };
        
                static FrameDataInfo getInfoFromEngineData(EngineOutputData& output_data);
        
                template <typename SpecificFaceState>
                static FrameDataInfo getInfoFromFaceState(const SpecificFaceState& face_state)
                {
                    FrameDataInfo retval;
                    retval._frame_num = face_state._data.frame_num;
                    retval._tracking = face_state._data.is_tracking;
                    retval._num_data_bytes = face_state.numDataBytes();
        
                    return retval;
                }
        
                //! Process an OutputDataDisplayInfo object.
                /*! Updates the counters and writes the details to the screen */
                static void processData(FrameDataInfo& display_info);
        
                static std::ostream&  fld(std::ostream& o, int width);
        
                //! Print the frame information to screen, including the given frame number and tracking state
                static void printInfo(int frame_num, bool tracking);
        
                //! Reset the static counters associated with this object
                static void resetCounters();
        
                static unsigned long _num_received;
                static unsigned long _num_dropped;
                static unsigned long _total_size;
                static unsigned long _last_frame_num;
                static bool _last_was_tracking;
                static std::string _host_ip;
            };
        }
    }
}
#endif

