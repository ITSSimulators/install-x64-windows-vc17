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
#ifndef SM_COREDATA_EOD_HEADTRACKERSTATEOUTPUTDATA_H
#define SM_COREDATA_EOD_HEADTRACKERSTATEOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        //! Contains status information produced by all types of head-trackers. 
        /*!
            This class appears as a potential sub-object attached to EngineStateOutputData. 

         */
        class SM_COREDATA_API HeadTrackerStateOutputData: public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(HeadTrackerStateOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(41);
    
            //! Possible states for all types of head-trackers.
            /*!
            */
             enum 
            {
                INVALID = -1,           //!< The head-tracker is not created or has been destroyed or an internal error has occured.
                IDLE = 0,               //!< The head-tracker is deactivated.
                BRIGHTNESS_CONTROL = 1, //!< The head-tracker is influencing camera exposure settings
                AUTO_INIT = 2,          //!< The head-tracker is trying to acquire a new face.
                SEARCH = 3,             //!< The head-tracker is trying to recover from a tracking failure by searching for the last face tracked.
                TRACK = 4,              //!< The head-tracker is tracking a face.
            };
    
            /*!
            */
            HeadTrackerStateOutputData();

            HeadTrackerStateOutputData(int32 state);
    
            HeadTrackerStateOutputData(const HeadTrackerStateOutputData& rhs);
    
            HeadTrackerStateOutputData& operator=(const HeadTrackerStateOutputData& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            HeadTrackerStateOutputData* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! Get the state value
            /*!

             */
            int32 state() const;
    
            //! Set the state value
            /*! @pre state is in the range INVALID..TRACK

              */
            void setState(int32 state);
    
        protected:
            /*! @see EngineOutputBase */
            void appendEngineSpecificData(std::vector<uint8>& buffer) const;
    
            /*! @see EngineOutputBase */
            void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_pos);
    
            /*! @see EngineOutputBase */
            uint32 numEngineSpecificDataBytes() const;
    
            /*! @see SerializableComposite */
            void printOwnData(std::ostream& s) const;
    
            /*! @see SerializableComposite */
            void printOwnHeader(std::ostream& s) const;
    
        private:
            //! Copy the data from rhs into this object
            void copyFrom(const HeadTrackerStateOutputData& rhs);
    
        private:
            int32 _state;
        };
        typedef boost::shared_ptr<HeadTrackerStateOutputData> HeadTrackerStateOutputDataPtr;
        typedef boost::shared_ptr<const HeadTrackerStateOutputData> ConstHeadTrackerStateOutputDataPtr;
    }
}
#endif

