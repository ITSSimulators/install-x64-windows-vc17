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
#ifndef SM_COREDATA_EOD_WORLDOUTPUTDATAV2_H
#define SM_COREDATA_EOD_WORLDOUTPUTDATAV2_H

//! @file
#include "eod/engineoutputbase.h"
#include "eod/worldoutputdata.h"
#include "eod/headintersectionoutputdatav2.h"
#include "eod/gazeintersectionoutputdatav3.h"

namespace sm
{
    namespace eod
    {
        //! Data class that represents world model related data
        /*!
         */
         class SM_COREDATA_API WorldOutputDataV2 : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(WorldOutputDataV2)
            
        public:

            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(43);
            COREDATA_DECLARE_NAMED_OBJECT_ID(WORLD_OUTPUT_DATA_V2_ID, 43);
    
            WorldOutputDataV2();
      
            //! Copy constructor
            WorldOutputDataV2(const WorldOutputDataV2& rhs);
            
            //! Conversion copy constructor
            /*! @see:
                - HeadIntersectionOutputDataV2 for details on conversion from HeadIntersectionOutputDataV1
                - GazeIntersectionOutputDataV3 for details on conversion from GazeIntersectionOutputDataV2
                  and GazeIntersectionOutputDataV1
            */
            WorldOutputDataV2(const WorldOutputData& rhs);

            //! Assignment operator
            WorldOutputDataV2& operator=(const WorldOutputDataV2& rhs);
    
            //! Conversion assignment operator
            WorldOutputDataV2& operator=(const WorldOutputData& rhs);

            /*! @return a copy of this object, allocated on the heap */
            virtual WorldOutputDataV2* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            /*!
                @return the HeadIntersectionOutputDataV2 attached to this object, or NULL if no head data is attached
                @throw SerializableError if an object with the ID of a HeadIntersectionOutputDataV2 was found, but
                could not be converted into a HeadIntersectionOutputDataV2 object 

             */
            ConstHeadIntersectionOutputDataV2Ptr headIntersectionOutputData() const;
            HeadIntersectionOutputDataV2Ptr headIntersectionOutputData();
    
            /*! 
                @return the GazeIntersectionOutputDataV3 attached to this object, or NULL if no gaze data is attached
                @throw SerializableError if an object with the ID of a GazeIntersectionOutputDataV2 was found, but
                could not be converted into a GazeIntersectionOutputDataV2 object 

             */
            ConstGazeIntersectionOutputDataV3Ptr gazeIntersectionOutputData() const;
            GazeIntersectionOutputDataV3Ptr gazeIntersectionOutputData();
    
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
            virtual void printOwnHeader(std::ostream& ) const;

        };
        typedef boost::shared_ptr<WorldOutputDataV2> WorldOutputDataV2Ptr;
        typedef boost::shared_ptr<const WorldOutputDataV2> ConstWorldOutputDataV2Ptr;
    }
}

#endif

