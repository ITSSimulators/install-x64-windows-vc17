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
#ifndef SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATAV1_H
#define SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATAV1_H

//! @file
#include "eod/gazeintersectionoutputdatabase.h"

namespace sm
{
    namespace eod
    {
        // Forward Declarations
        class GazeIntersectionOutputDataV2;
        class GazeIntersectionOutputDataV3;

        //! Data class that represents intersections between gaze vector and world objects
        /*!
            Used in faceLab 4.0

         */
        class SM_COREDATA_API GazeIntersectionOutputDataV1 : public GazeIntersectionOutputDataBase
        {
            COREDATA_MEMORY_ALLOCATORS(GazeIntersectionOutputDataV1)

            friend class GazeIntersectionOutputDataV2;

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(18);
            COREDATA_DECLARE_NAMED_OBJECT_ID(GAZE_INTERSECTION_OUTPUT_DATA_ID, 18);

            virtual ~GazeIntersectionOutputDataV1();

            /*!
            */
             GazeIntersectionOutputDataV1();

            GazeIntersectionOutputDataV1(const GazeIntersectionOutputDataV1& rhs);

            /*! Construct a GazeIntersectionOutputDataV1 instance by converting a
                GazeIntersectionOutputDataV2 object, copying all elements of rhs
                ignoring the gaze intersection world coordinate.
             */
            explicit GazeIntersectionOutputDataV1(const GazeIntersectionOutputDataV2& rhs);

            /*! Construct a GareIntersectionOutputDataV1 instance by converting a
                GazeIntersectionOutputDataV3 object.
                @see GazeIntersectionOutputDataV1::operator=(const GazeIntersectionOutputDataV3& rhs)
             */
            explicit GazeIntersectionOutputDataV1(const GazeIntersectionOutputDataV3& rhs);

            GazeIntersectionOutputDataV1& operator=(const GazeIntersectionOutputDataBase& rhs);

            GazeIntersectionOutputDataV1& operator=(const GazeIntersectionOutputDataV1& rhs);

            /*! Convert a GazeIntersectionOutputDataV3 to an GazeIntersectionOutputDataV1
                assigning it to this instance.  The conversion will:
                - Set the world, screen and pixel coordinates from the first screen intersection
                  object found in GazeIntersectionOutputDataV3 passed in.  If no screen intersection
                  is found then world, screen and pixel intersection values are zeroed.
                - Set the intersectionObjectName and intersectionObjectIndex to that of the
                  first intersection found which only contains a world coordinate.
             */
            GazeIntersectionOutputDataV1& operator=(const GazeIntersectionOutputDataV3& rhs);

            /*! @return a copy of this object, allocated on the heap */
            virtual GazeIntersectionOutputDataV1* clone() const;

            /*! @see Serializable */
            virtual ObjectID objectID() const;

            /*! @see IntersectionOutputBase */
            virtual int32 intersectionObjectIndex() const;

            /*! @see IntersectionOutputBase */
            virtual const std::string intersectionObjectName() const;

            /*! @see IntersectionOutputBase */
            virtual bool intersectsScreen() const;

            /*! @see IntersectionOutputBase */
            virtual const fStdVector3& screenIntersectionWorldCoordinates() const;

            /*! @see IntersectionOutputBase */
            virtual const fStdVector2& screenIntersectionScreenCoordinates() const;

            /*! @see IntersectionOutputBase */
            virtual const iStdVector2& screenIntersectionPixelCoordinates() const;

            /*! @see IntersectionOutputBase
                @pre screen_intersection is a 3D point
             */
            virtual void setScreenIntersectionWorldCoordinates(const fStdVector3& screen_intersection);

            /*! @see IntersectionOutputBase
                @pre screen_intersection is a 2D point
             */
            virtual void setScreenIntersectionScreenCoordinates(const fStdVector2& screen_intersection);

            /*! @see IntersectionOutputBase
                @pre screen_intersection is a 2D point
             */
            virtual void setScreenIntersectionPixelCoordinates(const iStdVector2& screen_intersection);

            /*! @see IntersectionOutputBase */
            virtual void setIntersectionObjectIndex(int32 index);

            /*! @see IntersectionOutputBase */
            virtual void setIntersectionObjectName(const std::string& name);

            /*! @see IntersectionOutputBase */
            virtual void setIntersectsScreen(bool intersects);

        protected:
            /*! @see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8>& ) const;

            /*! @see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8>& , int& );

            /*! @see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;

            /*! @see SerializableComposite */
            virtual void printOwnData(std::ostream& ) const;

            /*! @see SerializableComposite */
            virtual void printOwnHeader(std::ostream& s) const;

            /*! @see GazeIntersectionOutputDataBase */
            virtual void assignData(const GazeIntersectionOutputDataBase& src);
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
        typedef boost::shared_ptr<GazeIntersectionOutputDataV1> GazeIntersectionOutputDataV1Ptr;
        typedef boost::shared_ptr<const GazeIntersectionOutputDataV1> ConstGazeIntersectionOutputDataV1Ptr;
    }
}

#endif


