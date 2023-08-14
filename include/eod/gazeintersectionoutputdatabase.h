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
#ifndef SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATABASE_H
#define SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATABASE_H

//! @file
#include "eod/intersectionoutputbase.h"

namespace sm
{
    namespace eod
    {
        //! Data class that represents intersections between gaze vector and world objects
        /*!
        */
        class SM_COREDATA_API GazeIntersectionOutputDataBase : public IntersectionOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(GazeIntersectionOutputDataBase)

        public:

            virtual ~GazeIntersectionOutputDataBase() COREDATA_PURE_METHOD;

            //! Assignment operator supports copying different versions of GazeIntersectionOutputDataBase
            GazeIntersectionOutputDataBase& operator=(const GazeIntersectionOutputDataBase& rhs);

            //! Returns ID of the latest faceLAB GazeIntersectionOutputDataObject
            /*!
             */
            static ObjectID latestGazeIntersectionObjectID();

            //! Point in world coordinates where the gaze vector intersects world model object (in meters)
            /*
                The field contains the 3D point in world coordinates in meters at which the
                gaze vector intersects world model object. The gaze used for intersections is the Unified Gaze Ray.
                Intersection values are only logged if the GQL=3 for at least 1 eye.
                Intersection coordinates are logged for both planes and spheres.
                Zero coordinates represent that no possible intersection could be computed.

             */
            virtual const fStdVector3& gazeObjectIntersection() const;

            /*! Set the world model object intersection point in world co-ordinates
                @param object_intersection vector of length 3 containing the [X, Y, Z] co-ordinates of the
                world model object intersection
                @throw std::invalid_argument if an attempt to add an object_intersection is made
                    to GazeIntersectionOutputDataBase

              */
            virtual void setGazeObjectIntersection(const fStdVector3& object_intersection);

        protected:
             GazeIntersectionOutputDataBase();

            //! Assigns private data members to src private members
            virtual void assignData(const GazeIntersectionOutputDataBase& src) COREDATA_PURE_METHOD;
        };
        typedef boost::shared_ptr<GazeIntersectionOutputDataBase> GazeIntersectionOutputDataBasePtr;
        typedef boost::shared_ptr<const GazeIntersectionOutputDataBase> ConstGazeIntersectionOutputDataBasePtr;
    }
}

#endif

