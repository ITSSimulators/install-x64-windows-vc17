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
#ifndef SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATAV41_H
#define SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATAV41_H

//! @file
#include "eod/gazeintersectionoutputdatav1.h"

namespace sm
{
    namespace eod
    {
        class GazeIntersectionOutputDataV3;

        //! Data class that represents intersections between gaze vector and world objects
        /*!
            Used from faceLab 4.1

         */
         class SM_COREDATA_API GazeIntersectionOutputDataV2 : public GazeIntersectionOutputDataBase
        {
            COREDATA_MEMORY_ALLOCATORS(GazeIntersectionOutputDataV2)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(29);
            COREDATA_DECLARE_NAMED_OBJECT_ID(GAZE_INTERSECTION_OUTPUT_DATA_ID, 29);
    
            /*!
            */
             GazeIntersectionOutputDataV2();

            /*! Construct a GareIntersectionOutputDataV2 instance by converting a
                GazeIntersectionOutputDataV3 object. 
                @see GazeIntersectionOutputDataV2::operator=(const GazeIntersectionOutputDataV1& rhs)
             */
            explicit GazeIntersectionOutputDataV2(const GazeIntersectionOutputDataV1& rhs);

            GazeIntersectionOutputDataV2(const GazeIntersectionOutputDataV2& rhs);

            /*! Construct a GareIntersectionOutputDataV2 instance by converting a
                GazeIntersectionOutputDataV3 object. 
                @see GazeIntersectionOutputDataV2::operator=(const GazeIntersectionOutputDataV3& rhs)
             */
            explicit GazeIntersectionOutputDataV2(const GazeIntersectionOutputDataV3& rhs);

            virtual ~GazeIntersectionOutputDataV2();

            /*! Convert a GazeIntersectionOutputDataV1 instance to a
                GazeIntersectionOutputDataV2 object, copying all elements of rhs
                and setting the gaze intersection world coordinate to <0,0,0>.
             */
            GazeIntersectionOutputDataV2& operator=(const GazeIntersectionOutputDataV1& rhs);

            GazeIntersectionOutputDataV2& operator=(const GazeIntersectionOutputDataV2& rhs);
    
            /*! Convert a GazeIntersectionOutputDataV3 to an GazeIntersectionOutputDataV1
                assigning it to this instance.  The conversion will:
                - Set the world, screen and pixel coordinates from the first screen intersection
                  object found in GazeIntersectionOutputDataV3 passed in.  If no screen intersection
                  is found then world, screen and pixel intersection values are zeroed.
                - Set the intersectionObjectName and intersectionObjectIndex and world coordinate
                  to that of the first intersection found which only contains a world coordinate.
             */
            GazeIntersectionOutputDataV2& operator=(const GazeIntersectionOutputDataV3& rhs);
    
            GazeIntersectionOutputDataV2& operator=(const GazeIntersectionOutputDataBase& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            virtual GazeIntersectionOutputDataV2* clone() const;
    
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
    
            /*! @see GazeIntersectionOutputDataBase */
            virtual const fStdVector3& gazeObjectIntersection() const;
    
            /*! @see GazeIntersectionOutputDataBase */
            virtual void setGazeObjectIntersection(const fStdVector3& object_intersection);
    
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
            //! 3D gaze intersection with World Model objects. Zero coordinates represent that no possible intersection could be computed.
            fStdVector3 _gaze_object_intersection;
            
            //! Previous version data
            GazeIntersectionOutputDataV1 _base_data;
        };
        typedef boost::shared_ptr<GazeIntersectionOutputDataV2> GazeIntersectionOutputDataV2Ptr;
        typedef boost::shared_ptr<const GazeIntersectionOutputDataV2> ConstGazeIntersectionOutputDataV2Ptr;
    }
}

#endif

