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
#ifndef SM_COREDATA_EOD_OUTPUTDATAUTILS_H
#define SM_COREDATA_EOD_OUTPUTDATAUTILS_H

//! @file
#include "eod/utils/outputdatautilserror.h"
#include "eod/engineoutputdata.h"

namespace sm
{
    namespace eod
    {
        namespace utils
        {
            /*!
                @name EngineOutputData Utility Functions
            */
            //@{

            //! Convert a binary logfile into text format
            /*! @param input_file path to the binary file
                @param output_file path to the text output file that will contain the converted data.
                If the file already exists, it is overwritten.
                @throw OutputDataUtilsError if an error occured when converting the file */
            SM_COREDATA_API void convertLogToText(const std::wstring& input_file, const std::wstring& output_file);
            SM_COREDATA_API void convertLogToText(const std::string& input_file, const std::string& output_file);
    
            //! @return true if the head is tracking
            /*!
                Note this used to also check EngineOutputData::dssOutputDataV2(). As that
                class has been split into the DSS DATA API the behaviour of this function
                has changed.
                \deprecated Use eod->headOutputData()->isTracking().
            */
            COREDATA_DEPRECATED("Use eod->headOutputData()->isTracking()") SM_COREDATA_API bool isTracking(sm::eod::EngineOutputData& eod);
            COREDATA_DEPRECATED("Use eod->headOutputData()->isTracking()") SM_COREDATA_API bool isTracking(const sm::eod::EngineOutputData& eod);
    
            //! @return the frame number of the data
            SM_COREDATA_API EngineOutputData::FrameNumber frameNumber(const EngineOutputData& data);
    
            /*! @return the vergence point of the gaze rays if they intersect,
                or the mid-point of the line joining the points where the rays are closest
                to each other
                @pre gaze data must be present and the gaze quality for both eyes must be atleast IR_GAZE level
                @throw OutputDataUtilsError if the gaze rays are parallel
             */
            SM_COREDATA_API fStdVector3 gazeVergencePoint(sm::eod::EngineOutputData& data);
            /*!  \deprecated Use non-const version */
            COREDATA_DEPRECATED("Use non-const version") SM_COREDATA_API fStdVector3 gazeVergencePoint(const sm::eod::EngineOutputData& data);
    
            /*! @return the vergence distance - distance between the HeadPose origin and vergence point
                @pre gaze data must be present and the gaze quality for both eyes must be atleast IR_GAZE level
                @throw OutputDataUtilsError if the gaze rays are parallel
             */
            SM_COREDATA_API float gazeVergenceDistance(sm::eod::EngineOutputData& data);
            /*!  \deprecated Use non-const version */
            COREDATA_DEPRECATED("Use non-const version") SM_COREDATA_API float gazeVergenceDistance(const sm::eod::EngineOutputData& data);
    
            /*! @return the vergence angle between the gaze rays
                @pre gaze data must be present and the gaze quality for both eyes must be atleast IR_GAZE level
                @throw OutputDataUtilsError if the gaze rays are parallel
             */
            SM_COREDATA_API float gazeVergenceAngle(sm::eod::EngineOutputData& data);
            /*!  \deprecated Use non-const version */
            COREDATA_DEPRECATED("Use non-const version") SM_COREDATA_API float gazeVergenceAngle(const sm::eod::EngineOutputData& data);
    
            /*! @return The cyclops (head-pose normal) vector for the output data \a data
                @pre head data must be present
             */
            SM_COREDATA_API const fStdVector3 cyclopsVector(sm::eod::EngineOutputData& data);
            /*!  \deprecated Use non-const version */
            COREDATA_DEPRECATED("Use non-const version") SM_COREDATA_API const fStdVector3 cyclopsVector(const sm::eod::EngineOutputData& data);
    
            //! Compute a merged gaze ray
            /*! @param data EngineOutputData to extract the gaze rays from
                @param ray_origin Receives the origin of the merged gaze ray in world co-ordinates [X, Y, Z].
                This is always the head-pose origin.
                @param ray_direction Receives the direction of the merged gaze ray in world co-ordinates [X, Y, Z]
                This is an angular average between the gaze vectors from each eye
                @pre gaze data must be present and at least one eye must have a gaze quality level 
                    greater than NO_TRACKING
                @throw OutputDataUtilsError if no gaze data could be computed 
             */
            SM_COREDATA_API void mergedGazeRay(sm::eod::EngineOutputData& data, 
                fStdVector3& ray_origin, fStdVector3& ray_direction);

            /*!  \deprecated Use non-const version */
            COREDATA_DEPRECATED("Use non-const version") SM_COREDATA_API void mergedGazeRay(const sm::eod::EngineOutputData& data, 
                fStdVector3& ray_origin, fStdVector3& ray_direction);
    
            //! Determine the best quality gaze ray in the EngineOutputData
            /*! Returns the gaze ray corresponding to the eye with the best Gaze Quality Level
                If both eyes have the same GQL, the gaze ray for the right eye is returned.
                @param data The EngineOutputData to extract the best gaze ray from
                @param ray_origin contains the origin of the best gaze ray after this function
                has finished executing
                @param ray_direction contains the origin of the best gaze ray after this function
                has finished executing
                @return The eye ID corresponding to the eye with the best gaze ray
                @pre gaze data must be present and the gaze quality level for at least one eye
                    must be greater than NO_TRACKING
                @throw OutputDataUtilsError if gaze ray cannot be computed
             */
            SM_COREDATA_API int bestGazeRay(sm::eod::EngineOutputData& data,
                fStdVector3& ray_origin, fStdVector3& ray_direction);

            /*!  \deprecated Use non-const version */
            COREDATA_DEPRECATED("Use non-const version") SM_COREDATA_API int bestGazeRay(const sm::eod::EngineOutputData& data,
                fStdVector3& ray_origin, fStdVector3& ray_direction);
    
            //! Maximum gaze ray vergence distance in meters.
            /*! 
                If the vergence distance is larger, gaze rays will be considered to be parallel.
            */
            const float MAX_GAZE_VERGENCE_DISTANCE = 1.5f;
            //@}
        }
    }
}

#endif

