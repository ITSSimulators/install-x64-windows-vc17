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
#ifndef SM_COREDATA_EOD_HEADINTERSECTIONOUTPUTBASEV2_H
#define SM_COREDATA_EOD_HEADINTERSECTIONOUTPUTBASEV2_H

//! @file
#include "eod/intersectionoutputbasev2.h"

namespace sm
{
    namespace eod
    {   
        // Forward declaration
        class HeadIntersectionOutputDataV1;

        //! Data representing intersections between the head vector and world objects       
        /*!
         */
        class SM_COREDATA_API HeadIntersectionOutputDataV2 : public IntersectionOutputBaseV2
        {
            COREDATA_MEMORY_ALLOCATORS(HeadIntersectionOutputDataV2)

            friend class HeadIntersectionOutputDataV1;

        public:

            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(45);
            COREDATA_DECLARE_NAMED_OBJECT_ID(HEADINTERSECTION_OUTPUT_DATA_V2_ID, 45);
    
            /*!
            */
             HeadIntersectionOutputDataV2();
      
            //! Conversion constructor
            explicit HeadIntersectionOutputDataV2(const HeadIntersectionOutputDataV1& rhs);

            //! Assignment
            HeadIntersectionOutputDataV2& operator=(const HeadIntersectionOutputDataV2& rhs);
    
            //! Converesion assignment from HeadIntersectionOutputDataV1
            /*! @note HeadIntersectionOutputDataV1 does not provide object intersection coordinates,                      
                      so any intersected object in \a rhs is added with the same object label,
                      and coordinates (0,0,0).
            */
            HeadIntersectionOutputDataV2& operator=(const HeadIntersectionOutputDataV1& rhs);

            /*! @return a copy of this object, allocated on the heap */
            virtual HeadIntersectionOutputDataV2* clone() const;
    
            /*! @see Serializable */
            virtual ObjectID objectID() const;
    
        };
        typedef boost::shared_ptr<HeadIntersectionOutputDataV2> HeadIntersectionOutputDataV2Ptr;
        typedef boost::shared_ptr<const HeadIntersectionOutputDataV2> ConstHeadIntersectionOutputDataV2Ptr;
    }
}

#endif

