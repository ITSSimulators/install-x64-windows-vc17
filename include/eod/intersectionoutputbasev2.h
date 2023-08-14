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
#ifndef SM_COREDATA_EOD_INTERSECTIONOUTPUTBASEV2_H
#define SM_COREDATA_EOD_INTERSECTIONOUTPUTBASEV2_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        //! Data representing intersections with world model items
        /*!
         */
        class SM_COREDATA_API IntersectionOutputBaseV2 : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(IntersectionOutputBaseV2)

        public:


            //! Clear all intersection data
            /*!

             */
            virtual void clearAllData();
                
            //! Is there an intersection against the specified world model item in world co-ordinates?
            /*!
             */
            virtual bool hasWorld(const std::string& label) const;

            //! Is there an intersection against the specified world model item in plane co-ordinates?
            /*!
             */
             virtual bool hasPlane(const std::string& label) const;

            //! Is there an intersection against the specified world model item in pixel co-ordinates?
            /*!
             */
             virtual bool hasPixel(const std::string& label) const;
    
            //! The intersection point against the specified world model item in world co-ordinates.
            /*!
                The co-ordinates are measured in meters relative to the world co-ordinate
                origin and will be zero if the intersection doesn't exist.
                @param label the unique text label identifying the world model item
                @return the 3D co-ordinates of the intersection or (0,0,0) if the label is unknown.

             */
            virtual const fStdVector3 world(const std::string& label) const;

            //! The intersection point against the specified world mode item in plane co-ordinates.
            /*! The co-ordinates are measured in meters relative to the centre of the 
                plane, and will be zero if the intersection doesn't exist.
                @param label the unique text label identifying the world model item
                @return the 2D co-ordinates of the intersection or (0,0) if the label is unknown.

             */
            virtual const fStdVector2 plane(const std::string& label) const;

            //! The intersection point against the specified world mode item in pixel co-ordinates.
            /*! The co-ordinates are measured in pixels will be zero if the intersection doesn't exist.
                @param label the unique text label identifying the world model item
                @return the 2D co-ordinates of the intersection or (0,0) if the label is unknown.

             */
            virtual const iStdVector2 pixel(const std::string& label) const;
      
            //! Add an intersection in world coordinates
            /*!
                @param label the text label identifying the world model item.
                    Using an existing label will overwrite the previous contents.  
                @param world the intersection point in world co-ordinates
                @pre world is a 3D point
              */
            virtual void addIntersection(const std::string& label, 
                                         const fStdVector3& world);

            //! Add an intersection in world and plane coordinates
            /*! 
                @param label the text label identifying the world model item.
                    Using an existing label will overwrite the previous contents.  
                @param world the 3D intersection point in world co-ordinates
                @param plane the 2D intersection point in plane co-ordinates
                @pre world is a 3D point
              */
            virtual void addIntersection(const std::string& label, 
                                         const fStdVector3& world,
                                         const fStdVector2& plane);

            //! Add an intersection in world, plane and pixel coordinates
            /*! 
                @param label the text label identifying the world model item.
                    Using an existing label will overwrite the previous contents.  
                @param world the 3D intersection point in world co-ordinates
                @param plane the 2D intersection point in plane co-ordinates
                @param pixel the 2D intersection point in pixel co-ordinates
                @pre world is a 3D point
                @pre pixel is a 2D point

              */
            virtual void addIntersection(const std::string& label, 
                                         const fStdVector3& world, 
                                         const fStdVector2& plane, 
                                         const iStdVector2& pixel);

            //! A vector of all valid world model item labels
            /*!
            */            
            virtual const std::vector<std::string> intersectedItems() const;

        protected:
            IntersectionOutputBaseV2();
  
            IntersectionOutputBaseV2& operator=(const IntersectionOutputBaseV2& rhs);
    
            /*! @see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8>& buffer) const;
       
            /*! @see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_position);
       
            /*! @see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;
       
            //! Prints all available co-ordinates for the first 
            //! or primary intersection.  
            /*! @see SerializableComposite */
            virtual void printOwnData(std::ostream& s) const;

            //! Prints headers for all possible co-ordinates for the 
            //! first or primary intersection. 
            /*! @see SerializableComposite */
            virtual void printOwnHeader(std::ostream& s) const;

            //! The combined length of all labels.
            //! Needed to calculate the size of this object
            virtual uint32 combinedLabelSize() const;
       
            //! Given a world model item label, returns the associated index
            //! from the _label_index_map. If there is no intersection for the 
            //! item an invalid index of -1 is returned 
            int32 labelToIndex(const std::string& label) const;

        private:
            //! Returns an existing label index or creates an new one
            /*!
                @param label the label to create an index for
                @param index output parameter to contain the added index
                @return true if new index added, false if it already existed
            */
            bool addLabelIndex(const std::string& label, int32& index);

            typedef std::map<std::string, int32> LabelIndexMap;
            typedef std::map<int32, fStdVector3> WorldCoordinatesMap;
            typedef std::map<int32, fStdVector2> PlaneCoordinatesMap;
            typedef std::map<int32, iStdVector2> PixelCoordinatesMap;           

            //! A mapping between a world model item label and an 
            //! auto-assigned index used to store the intersection co-ordinates
            LabelIndexMap _label_index_map;

            //! Intersections represented in world co-ordinates 
            WorldCoordinatesMap _world_coordinates;

            //! Intersections represented in plane co-ordinates 
            PlaneCoordinatesMap _plane_coordinates;

            //! Intersections represented in pixel co-ordinates 
            PixelCoordinatesMap _pixel_coordinates;         

        };
        typedef boost::shared_ptr<IntersectionOutputBaseV2> IntersectionOutputBaseV2Ptr;
        typedef boost::shared_ptr<const IntersectionOutputBaseV2> ConstIntersectionOutputBaseV2Ptr;
    }
}

#endif

