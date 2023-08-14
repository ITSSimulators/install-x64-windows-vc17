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
#ifndef SM_COREDATA_EOD_FLMIDS_H
#define SM_COREDATA_EOD_FLMIDS_H

//! @file
#include "eod/flmtypes.h"

namespace sm
{
    namespace eod
    {
        /*
            Here we define names and id values for the face landmarks.
            Refer to the FLM Standard.
            NOTE: Once defined, these values never change - they coincide with the externally released FLM standard.
            ALSO NOTE: This is not a comprehensive list of all the landmarks that may be produced by a tracking engine.
            Rather, these are landmarks commonly referred to in the tracking code. 
            The only way to list all the landmarks getting created by the engine is to enumerate a FaceOutputData produced by the engine.
            SM Internal link: <file:\\sm.local\dfs\FLIB\Doc\FLM Standard.pdf>

        */
        enum FixedFaceLandmarkId 
        {
            // These are the facial landmarks that are commonly referred to as "Reference" points in the code.
            RIGHT_EYE_OUTER_CORNER = 0,
            RIGHT_EYE_INNER_CORNER = 1,
            LEFT_EYE_INNER_CORNER = 2,
            LEFT_EYE_OUTER_CORNER = 3,
            RIGHT_MOUTH_CORNER = 4,
            LEFT_MOUTH_CORNER =5,
            RIGHT_NOSTRIL = 6,
            LEFT_NOSTRIL = 7,
    
            // Lip points
            OUTER_LIP_0 = 100,
            OUTER_LIP_1 = 101,
            OUTER_LIP_2 = 102,
            OUTER_LIP_3 = 103,
            OUTER_LIP_4 = 104,
            OUTER_LIP_5 = 105,
            INNER_LIP_0 = 200,
            INNER_LIP_1 = 201,
            INNER_LIP_2 = 202,
            INNER_LIP_3 = 203,
            INNER_LIP_4 = 204,
            INNER_LIP_5 = 205,
            INNER_LIP_6 = 206,
            INNER_LIP_7 = 207,
    
            // Eyebrow points
            RIGHT_EYEBROW_0 = 300,
            RIGHT_EYEBROW_1 = 301,
            RIGHT_EYEBROW_2 = 302,
            LEFT_EYEBROW_0 = 400,
            LEFT_EYEBROW_1 = 401,
            LEFT_EYEBROW_2 = 402,
    
            // Nose points
            NOSE_0 = 500,
            NOSE_1 = 501,
            NOSE_2 = 502,
            NOSE_3 = 503,
    
            // Eye points
            RIGHT_PUPIL_CENTRE = 600,
            RIGHT_UPPER_EYELID = 601,
            RIGHT_LOWER_EYELID = 602,
            LEFT_PUPIL_CENTRE = 700,
            LEFT_UPPER_EYELID = 701,
            LEFT_LOWER_EYELID = 702,
        };
    
        /*!
            @name Landmark Groups

            The following functions define landmark ids related to different facial features.
        */
        //@{
    
        //! @return The set of all fixed face landmark IDs (there may be more IDs than this set)
        /*!
         */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_ALL_FIXED();

        //! @return The "reference" set of landmark IDs
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_REFERENCE();

        //! @return The set of four eye corners
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_EYE_CORNERS();

        //! @return The set of all face landmark IDs that are on the outer lips.
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_OUTER_LIP();

        //! @return The set of all face landmark IDs that are on the inner lips.
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_INNER_LIP();

        //! @return The set of all face landmark IDs that are on the lips - includes mouth corners.
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_LIPS();

        //! @return The set of all face landmark IDs that are on the nose - includes nostrils.
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_NOSE();

        //! @return The set of all face landmark IDs that are on the left eye - includes eye corners, eyelids and pupil
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_LEFT_EYE();

        //! @return The set of all face landmark IDs that are on the right eye - includes eye corners, eyelids and pupil
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_RIGHT_EYE();

        //! @return The set of all face landmark IDs that are on the left eyebrow
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_LEFT_EYEBROW();

        //! @return The set of all face landmark IDs that are on the right eyebrow
        /*!
        */
        SM_COREDATA_API const sm::eod::FaceLandmarkIdVec& FLM_IDS_RIGHT_EYEBROW();
        //@}
    }
}
#endif

