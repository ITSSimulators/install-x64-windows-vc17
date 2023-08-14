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
#ifndef SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATAV3_H
#define SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATAV3_H

//! @file
#include "eod/intersectionoutputbasev2.h"

namespace sm
{
    namespace eod
    {
        class GazeIntersectionOutputDataV1;
        class GazeIntersectionOutputDataV2;

        //! Data representing intersections between the gaze vector and world model items
        /*!
         */
        class SM_COREDATA_API GazeIntersectionOutputDataV3 : public IntersectionOutputBaseV2
        {
            friend class GazeIntersectionOutputDataV1;
            friend class GazeIntersectionOutputDataV2;

            COREDATA_MEMORY_ALLOCATORS(GazeIntersectionOutputDataV3)

        public:

            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(44);
            COREDATA_DECLARE_NAMED_OBJECT_ID(GAZE_INTERSECTION_OUTPUT_DATA_ID, 44);
    
            //! Constructor
            /*!

             */
            GazeIntersectionOutputDataV3();

            /*! Construct a GazeIntersectionOutputDataV3 from a converted
                GazeIntersectionOutputDataV1.
                @see GazeIntersectionOutputDataV3::operator=(const GazeIntersectionOutputDataV1& rhs)
             */
            explicit GazeIntersectionOutputDataV3(const GazeIntersectionOutputDataV1& rhs);
  
            /*! Construct a GazeIntersectionOutputDataV3 from a converted
                GazeIntersectionOutputDataV2.
                @see GazeIntersectionOutputDataV3::operator=(const GazeIntersectionOutputDataV2& rhs)
             */
            explicit GazeIntersectionOutputDataV3(const GazeIntersectionOutputDataV2& rhs);
  
            GazeIntersectionOutputDataV3(const GazeIntersectionOutputDataV3& rhs);
            
            /*! Convert a GazeIntersectionOutputDataV1 to GazeIntersectionOutputDataV3 
                assigning it to this instance.  This will:
                - clear existing data
                - add a screen intersection called IntersectionOutputBase::defaultScreenName()
                  if the screen intersection world coordinate is not <0,0,0>
                - will add an intersection object called rhs.intersectionObjectName()
                  if the rhs.intersectionObjectIndex() != -1 with a world coordinate
                  of <0,0,0>
             */
            GazeIntersectionOutputDataV3& operator=(const GazeIntersectionOutputDataV1& rhs);
    
            /*! Convert a GazeIntersectionOutputDataV1 to GazeIntersectionOutputDataV3 
                assigning it to this instance.  This will:
                - clear existing data
                - add a screen intersection called IntersectionOutputBase::defaultScreenName()
                  if the screen intersection world coordinate is not <0,0,0>
                - will add an intersection object called rhs.intersectionObjectName()
                  if the rhs.intersectionObjectIndex() != -1 or gaze object intersectoin
                  coordinate is not <0,0,0> setting the world coordinate to the
                  gaze object coordinate.
             */
            GazeIntersectionOutputDataV3& operator=(const GazeIntersectionOutputDataV2& rhs);
    
            GazeIntersectionOutputDataV3& operator=(const GazeIntersectionOutputDataV3& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            virtual GazeIntersectionOutputDataV3* clone() const;
    
            /*! @see Serializable */
            virtual ObjectID objectID() const;

        };
        typedef boost::shared_ptr<GazeIntersectionOutputDataV3> GazeIntersectionOutputDataV3Ptr;
        typedef boost::shared_ptr<const GazeIntersectionOutputDataV3> ConstGazeIntersectionOutputDataV3Ptr;
    }
}

#endif

