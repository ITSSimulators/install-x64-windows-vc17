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
#ifndef SM_COREDATA_EOD_WORLDOUTPUTDATA_H
#define SM_COREDATA_EOD_WORLDOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"
#include "eod/serializablefactory.h"
#include "eod/headintersectionoutputdatav1.h"
#include "eod/gazeintersectionoutputdatabase.h"

namespace sm
{
    namespace eod
    {
        class WorldOutputDataV2;

        //! Data class that represents world model related data
        /*!
         */
        class SM_COREDATA_API WorldOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(WorldOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(19);
            COREDATA_DECLARE_NAMED_OBJECT_ID(WORLD_OUTPUT_DATA_ID, 19);
    
            /*!
            */
             WorldOutputData();
      
            //! Copy constructor
            WorldOutputData(const WorldOutputData& rhs);
            
            //! Conversion copy constructor
            /*! 
                @note rhs.gazeIntersectionData(), if it exists, is converted into an GazeIntersectionOutputDataV2 object
                @see:
                - HeadIntersectionOutputDataV1 for details on conversion from HeadIntersectionOutputDataV2
                - GazeIntersectionOutputDataV2 for details on conversion from GazeIntersectionOutputDataV3
            */
            WorldOutputData(const WorldOutputDataV2& rhs);

            //! Assignment operator
            WorldOutputData& operator=(const WorldOutputData& rhs);
    
            //! Conversion assignment operator
            /*! 
                @note rhs.gazeIntersectionData(), if it exists, is converted into an GazeIntersectionOutputDataV2 object
                @see:
                - HeadIntersectionOutputDataV1 for details on conversion from HeadIntersectionOutputDataV2
                - GazeIntersectionOutputDataV2 for details on conversion from GazeIntersectionOutputDataV3
            */
            WorldOutputData& operator=(const WorldOutputDataV2& rhs);

            /*! @return a copy of this object, allocated on the heap */
            virtual WorldOutputData* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            /*! 
                @return the HeadIntersectionOutputDataV1 attached to this object, or NULL if no Head data is attached
                @throw SerializableError if an object with the ID of a HeadIntersectionOutputDataV1 was found, but
                could not be converted into a HeadIntersectionOutputDataV1 object

             */
            ConstHeadIntersectionOutputDataV1Ptr headIntersectionOutputData() const;
            HeadIntersectionOutputDataV1Ptr headIntersectionOutputData();
    
            /*!
                @return the GazeIntersectionOutputDataBase attached to this object, or NULL if no Head data is attached
                @throw SerializableError if an object with the ID of a GazeIntersectionOutputDataBase was found, but
                could not be converted into a GazeIntersectionOutputDataBase object 

             */
            GazeIntersectionOutputDataBasePtr gazeIntersectionOutputData();
    
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
        typedef boost::shared_ptr<WorldOutputData> WorldOutputDataPtr;
        typedef boost::shared_ptr<const WorldOutputData> ConstWorldOutputDataPtr;
    }
}

#endif

