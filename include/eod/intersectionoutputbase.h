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
#ifndef SM_COREDATA_EOD_INTERSECTIONOUTPUTBASE_H
#define SM_COREDATA_EOD_INTERSECTIONOUTPUTBASE_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        /*!
            Data class that represents world intersection related data output by the Tracking Engine
            This is a base class and all its derived classes will share this interface. 

         */
        class SM_COREDATA_API IntersectionOutputBase : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(IntersectionOutputBase)

        public:
            //! Maximum length of a world model object name 
            /*
            */
            BOOST_STATIC_CONSTANT(size_t, MAX_OBJ_NAME_LENGTH = 7);
    
            //! Index of the world-model object intersected by the direction vector
            /*!
                The world model contains a number of indexed objects. The field 
                contains the index of the object that is intersected,
                or -1 if no object is intersected or the tracking failed. The value
                is only valid if >=1.
    
                Note that this does not include the screen, which is a special
                world model object.

             */
            virtual int32 intersectionObjectIndex() const COREDATA_PURE_METHOD;
    
            //! Name of the world-model object intersected by the direction vector
            /*!
                The world model contains a number of indexed objects. The field 
                contains the name of the object that is intersected,
                or "nothing" if no object is intersected or "notrack" if the 
                tracking failed.
    
                @note This name can be any length, but when this object is serialized,
                the name will be truncated/padded to ensure it is exactly MAX_OBJ_NAME_LENGTH

             */
            virtual const std::string intersectionObjectName() const COREDATA_PURE_METHOD;
    
            //! Flag indicating that the direction vector intersects with the screen
            /*
                The flag is true when the vector intersects the
                special world object "screen". In this case, the intersection 
                coordinates presented in following data members are coordinates within 
                the region defined as the screen area.

             */
            virtual bool intersectsScreen() const COREDATA_PURE_METHOD;
    
            //! Point in world coordinates where the vector intersects the screen plane (in meters)
            /*
                The field contains the 3D point in world coordinates in meters at which the 
                vector intersects the screen plane defined by the special
                screen object in the world model. The values are valid even when the
                vector does not intersect the screen. In this case the 3D point will be
                outside the region defined as the screen. If the head tracking 
                fails the values are 0.

             */
            virtual const fStdVector3& screenIntersectionWorldCoordinates() const COREDATA_PURE_METHOD;
    
            //! Point in screen coordinates where the vector intersects the screen plane (in meters)
            /*
                The field contains the 2D point in screen coordinates in meters at which the 
                vector intersects the screen plane defined by the special
                screen object in the world model. The values are valid even when the
                cyclops vector does not intersect the screen. In this case the 2D point will be
                outside the region defined as the screen. If the head tracking 
                fails the values are 0.

             */
            virtual const fStdVector2& screenIntersectionScreenCoordinates() const COREDATA_PURE_METHOD;
    
            //! Pixel coordinates of screen intersection point of the cyclops vector
            /*
                The field contains the 2D point in pixels at which the 
                vector intersects the screen plane defined by the special
                screen object in the world model. The values are valid even when the
                vector does not intersect the screen. In this case the pixel coordinates
                will be outside the region defined as the screen. If the head
                tracking fails the values are 0.

             */
            virtual const iStdVector2& screenIntersectionPixelCoordinates() const COREDATA_PURE_METHOD;
    
            /*!
                Set the the screen-intersection point in world co-ordinates
                @param screen_intersection vector of length 3 containing the [X, Y, Z] co-ordinates of the 
                screen intersection
                @throw std::invalid_argument If the coordinate is not a 3D coordinate. 

             */
            virtual void setScreenIntersectionWorldCoordinates(const fStdVector3& screen_intersection) COREDATA_PURE_METHOD;
            /*!
                Set the the screen-intersection point in screen co-ordinates
                @param screen_intersection vector of length 2 containing the [X, Y] co-ordinates of the 
                screen intersection.
                @throw std::invalid_argument If the coordinate is not a 2D coordinate. 

             */
            virtual void setScreenIntersectionScreenCoordinates(const fStdVector2& screen_intersection) COREDATA_PURE_METHOD;
            /*!
                Set the the screen-intersection point in pixel co-ordinates
                @param screen_intersection vector of length 2 containing the [X, Y] co-ordinates of the 
                screen intersection. 
                @throw std::invalid_argument If the coordinate is not a 2D coordinate. 

             */
            virtual void setScreenIntersectionPixelCoordinates(const iStdVector2& screen_intersection) COREDATA_PURE_METHOD;
    
            //! Set the index of the currently intersected world-model object
            /*!
             */
            virtual void setIntersectionObjectIndex(int32 index) COREDATA_PURE_METHOD;
    
            //! Set the name of the currently intersected world-model object
            /*! 
                @note This name can be any length, but when this object is serialized,
                the name will be truncated/padded to ensure it is exactly MAX_OBJ_NAME_LENGTH

             */
            virtual void setIntersectionObjectName(const std::string& name) COREDATA_PURE_METHOD;
    
            //! Set the screen intersection flag
            /*!
             */
            virtual void setIntersectsScreen(bool intersects) COREDATA_PURE_METHOD;
    
            //! Name of the screen label when upgrading objects to later versions
            static const char* defaultScreenName();

        protected:
            //! Default name of object.
            static const char* defaultObjectName();
        };
        typedef boost::shared_ptr<IntersectionOutputBase> IntersectionOutputBasePtr;
        typedef boost::shared_ptr<const IntersectionOutputBase> ConstIntersectionOutputBasePtr;
    }
}

#endif


