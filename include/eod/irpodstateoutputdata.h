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
#ifndef SM_COREDATA_EOD_IRPODSTATEOUTPUTDATA_H
#define SM_COREDATA_EOD_IRPODSTATEOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        //! Contains status information produced by a software controlled IR pod 
        /*!
            This class appears as a potential sub-object attached to EngineStateOutputData. 

         */
        class SM_COREDATA_API IRPodStateOutputData: public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(IRPodStateOutputData)

        public:
            //! The ID that identifies an object of this type
            /*!
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(42);
    
            //! Possible states for the IR pod
            /*!
            */
             enum 
            {
                OFF = 0, 
                ON = 1,        
            };
    
            IRPodStateOutputData();
            /*! @pre state is eitherr OFF or ON
                @pre position is a 3D vector

            */
            IRPodStateOutputData(int32 state, const fStdVector3& position);
    
            IRPodStateOutputData(const IRPodStateOutputData& rhs);
    
            IRPodStateOutputData& operator=(const IRPodStateOutputData& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            IRPodStateOutputData* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! Get the state value
            /*!

             */
            int32 state() const;
    
            //! Set the state value
            /*!
                @pre state is eitherr OFF or ON

             */
            void setState(int32 state);
    
            //! Get the position of the IR pod in the world coordinate frame
            /*!

             */
            const fStdVector3& position() const;
    
            //! Set the position of the IR pod in the world coordinate frame
            /*! @pre position is a 3D vector

              */
            void setPosition(const fStdVector3& position);
    
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
            void copyFrom(const IRPodStateOutputData& rhs);
    
        private:
            int32 _state;
            fStdVector3 _position;
        };
        typedef boost::shared_ptr<IRPodStateOutputData> IRPodStateOutputDataPtr;
        typedef boost::shared_ptr<const IRPodStateOutputData> ConstIRPodStateOutputDataPtr;
    }
}
#endif

