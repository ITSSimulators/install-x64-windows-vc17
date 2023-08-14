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
#ifndef SM_COREDATA_EOD_ENGINESTATEOUTPUTDATA_H
#define SM_COREDATA_EOD_ENGINESTATEOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"
#include "eod/headtrackerstateoutputdata.h"
#include "eod/irpodstateoutputdata.h"

namespace sm
{
    namespace eod
    {
        //! Contains status information common to all types of Seeing Machines tracking engines.
        /*!
            Different types of tracking engines are able to attach different sub-objects representing
            detailed internal state information from each processor in the pipeline. 

         */
        class SM_COREDATA_API EngineStateOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(EngineStateOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(40);
    
            //! Possible engine states.
            /*!
            */
             enum 
            {
                INVALID = -1,   //!< The engine is not created or has been destroyed or an internal error has occured.
                IDLE = 0,       //!< The engine is not running (minimumal CPU state). It is idling (consuming video) however all image processing is disabled (no tracking).
                RUNNING = 1,    //!< The engine is running. Image-processing / tracking is occuring.
            };
    
            /*!
            */
             EngineStateOutputData();

            /*!
                @param state The state of the EngineOutputData.
                @pre state is one of INVALID, IDLE or RUNNING
             */
            EngineStateOutputData(int32 state);
    
            //! Copies data members and calls base class copy constructor
            EngineStateOutputData(const EngineStateOutputData& rhs);
    
            //! Copies data members and calls base class assignent operator
            EngineStateOutputData& operator=(const EngineStateOutputData& rhs);
    
            /*! @return a deep copy of this object, allocated on the heap */
            EngineStateOutputData* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! Get the state value
            /*!

             */
            int32 state() const;

            //! Set the state value
            /*!
                @param state the new state of the EngineOutputData.
                @pre state is one of INVALID, IDLE or RUNNING

              */
            void setState(int32 state);
    
            /*!
                @return any HeadTrackerStateOutputData attached to this object, or NULL if no object is attached.
                @note Only engines that perform head-tracking will attach this type of data.
                @throw SerializableError if an object with the ID of a HeadTrackerStateOutputData was found, but 
                could not be cast into a HeadTrackerStateOutputData object 

             */
            ConstHeadTrackerStateOutputDataPtr headtrackerStateOutputData() const;
            HeadTrackerStateOutputDataPtr headtrackerStateOutputData();
    
            /*!
                @return any IRPodStateOutputData attached to this object, or NULL if no object is attached.
                @note Only engines controlling IR pods will attach this type of data.
                @throw SerializableError if an object with the ID of a IRPodStateOutputData was found, but 
                could not be cast into a IRPodStateOutputData object 

             */
            ConstIRPodStateOutputDataPtr irPodStateOutputData() const;
            IRPodStateOutputDataPtr irPodStateOutputData();
    
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
            void copyFrom(const EngineStateOutputData& rhs);
    
        private:
            int32 _state;
        };
        typedef boost::shared_ptr<EngineStateOutputData> EngineStateOutputDataPtr;
        typedef boost::shared_ptr<const EngineStateOutputData> ConstEngineStateOutputDataPtr;
    }
}
#endif

