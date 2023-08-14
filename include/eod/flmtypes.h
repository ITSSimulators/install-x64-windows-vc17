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
#ifndef SM_COREDATA_EOD_FLMTYPES_H
#define SM_COREDATA_EOD_FLMTYPES_H

//! @file
#include "eod/basics.h"

namespace sm
{
    namespace eod
    {
        //! Identifies a face landmark according the the Face Landmark (FLM) standard.
        typedef int32 FaceLandmarkId;
    
        struct FaceCoordinate
        {
            FaceCoordinate(float x = 0, float y = 0, float z = 0)
            : x(x), y(y), z(z)
            {
            }

            // Units are in meters
            float x, y, z;
        };
    
        struct FaceTextureCoordinate
        {
            FaceTextureCoordinate(float u = 0, float v = 0) : u(u), v(v)
            {
            }

            // Normalized relative to the face-texture
            float u, v;
        };
    
        struct FaceLandmark
        {
            FaceLandmark(FaceLandmarkId id = 0, FaceCoordinate fc = FaceCoordinate(), FaceTextureCoordinate ftc = FaceTextureCoordinate())
            : id(id), fc(fc), ftc(ftc)
            {
            }

            FaceLandmarkId id;
            FaceCoordinate fc;
            FaceTextureCoordinate ftc;
        };

        //! A Vector of face landmark identifiers
        typedef std::vector<sm::eod::FaceLandmarkId> FaceLandmarkIdVec;

        //! A mapping from FaceLandmarkId to FaceLandmark.
        typedef std::map<sm::eod::FaceLandmarkId,sm::eod::FaceLandmark> FaceLandmarkMap;
    }
}

#endif

