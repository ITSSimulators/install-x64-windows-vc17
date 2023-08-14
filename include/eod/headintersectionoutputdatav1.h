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
#ifndef SM_COREDATA_EOD_HEADINTERSECTIONOUTPUTDATAV1_H
#define SM_COREDATA_EOD_HEADINTERSECTIONOUTPUTDATAV1_H

//! @file
#include "eod/intersectionoutputbase.h"

namespace sm
{
    namespace eod
    {
        // Forward declaration
        class HeadIntersectionOutputDataV2;

        //! Data class that represents intersections between head vector and world objects
        /*!
            @note this class has been renamed from CyclopsIntersectionOutputData 

         */
        class SM_COREDATA_API HeadIntersectionOutputDataV1 : public IntersectionOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(HeadIntersectionOutputDataV1)
            
        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(17);
            COREDATA_DECLARE_NAMED_OBJECT_ID(HEADINTERSECTION_OUTPUT_DATA_V1_ID, 17);
    
            /*!
            */
            HeadIntersectionOutputDataV1();
      
            //! Copy constructor
            HeadIntersectionOutputDataV1(const HeadIntersectionOutputDataV1& rhs);
      
            //! Conversion constructor
            /*! @see conversion assignment operator for details on conversion */
            HeadIntersectionOutputDataV1(const HeadIntersectionOutputDataV2& rhs);

            /*! @param rhs The value to assign to this HeadIntersectionOutputDataV1 instance
                @return this CyclopsIntersecionOutputData
             */
            HeadIntersectionOutputDataV1& operator=(const HeadIntersectionOutputDataV1& rhs);
    
            //! Conversion assignment operator
            /*! HeadIntersectionOutputDataV2 supports [0..N-1] object intersections,including
                possibly multiple screen and non-screen objects.

                HeadIntersectionOutputDataV1, on the other hand, supports only 0 or 1 screen intersections,
                and 0 or 1 (non-screen) object intersections.

                This conversion is defined as:
                - the screen intersection data for this HeadIntersectionOutputDataV1 is set from the last screen intersection added
                  to the \a rhs HeadIntersectionOutputDataV2
                - if the \a rhs HeadIntersectionOutputDataV2 has no screen intersection, then this->intersectsScreen() will return false, 
                  and all the HeadIntersectionOutputDataV1 screen intersection member functions will return zero ([0,0,0]) vectors 
                - the (non-screen) intersection for this HeadIntersectionOutputDataV1 is set from the last non-screen intersection
                  added to the \a rhs object
                - if the \a rhs HeadIntersectionOutputDataV2 has non-screen intersection objects, then this->intersectionObjectIndex()
                  will return false
            */
            HeadIntersectionOutputDataV1& operator=(const HeadIntersectionOutputDataV2& rhs);

            /*! @return a copy of this object, allocated on the heap */
            virtual HeadIntersectionOutputDataV1* clone() const;
    
            /*! @see Serializable */
            virtual ObjectID objectID() const;
    
            /*! @see IntersectionOutputBase */
            int32 intersectionObjectIndex() const;
    
            /*! @see IntersectionOutputBase */
            const std::string intersectionObjectName() const;
    
            /*! @see IntersectionOutputBase */
            bool intersectsScreen() const;
    
            /*! @see IntersectionOutputBase */
            const fStdVector3& screenIntersectionWorldCoordinates() const;
    
            /*! @see IntersectionOutputBase */
            const fStdVector2& screenIntersectionScreenCoordinates() const;
    
            /*! @see IntersectionOutputBase */
            const iStdVector2& screenIntersectionPixelCoordinates() const;
    
            /*! @see IntersectionOutputBase */
            void setScreenIntersectionWorldCoordinates(const fStdVector3& screen_intersection);
            
            /*! @see IntersectionOutputBase */
            void setScreenIntersectionScreenCoordinates(const fStdVector2& screen_intersection);
            
            /*! @see IntersectionOutputBase */
            void setScreenIntersectionPixelCoordinates(const iStdVector2& screen_intersection);
    
            /*! @see IntersectionOutputBase */
            void setIntersectionObjectIndex(int32 index);
    
            /*! @see IntersectionOutputBase */
            void setIntersectionObjectName(const std::string& name);
    
            /*! @see IntersectionOutputBase */
            void setIntersectsScreen(bool intersects);
   
        protected:
            /*! @see SerializableComposite */
            void printOwnHeader(std::ostream& s) const;
            
            /*! @see EngineOutputBase */
            void appendEngineSpecificData(std::vector<uint8>& buffer) const;
    
            /*! @see EngineOutputBase */
            void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_pos);
    
            /*! @see EngineOutputBase */
            uint32 numEngineSpecificDataBytes() const;
    
            /*! @see SerializableComposite */
            void printOwnData(std::ostream& s) const;
    
            /*! @see IntersectionOutputBase */
            void copyFrom(const IntersectionOutputBase& rhs);
    
        private:
            //! Index of the object that is being intersected
            int32 _intersection_object_index;
            //! Name of the object that is being intersected
            std::string _intersection_object_name;
            //! True if intersects the screen
            int8 _screen_intersect;
            //! Intersection of the screen in world coordinates
            fStdVector3 _screen_intersection_world_coords;
            //! Intersection of the screen in screen coordinates
            fStdVector2 _screen_intersection_screen_coords;
            //! Intersection of the screen in pixel coordinates
            iStdVector2 _screen_intersection_pixel_coords;
        };
        typedef boost::shared_ptr<HeadIntersectionOutputDataV1> HeadIntersectionOutputDataV1Ptr;
        typedef boost::shared_ptr<const HeadIntersectionOutputDataV1> ConstHeadIntersectionOutputDataV1Ptr;
    }
}

#endif

