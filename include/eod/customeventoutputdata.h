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
#ifndef SM_COREDATA_EOD_CUSTOMEVENTOUTPUTDATA_H
#define SM_COREDATA_EOD_CUSTOMEVENTOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        /*! A container of 32 bit flags.
            The flags are specific to the application generating them.

        */
        class SM_COREDATA_API CustomEventOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(CustomEventOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(36);
    
            //! All members zeroed
            /*!
            */
            CustomEventOutputData();

            //! Copies data members and calls base class copy constructor
            CustomEventOutputData(const CustomEventOutputData& rhs);

            /*! Copies data members and calls base class assignent operator
                @param rhs The CustomEventOutputData to replicate.
             */
            CustomEventOutputData& operator=(const CustomEventOutputData& rhs);
            /*! 
                @return a copy of this object, allocated on the heap
             */
            virtual CustomEventOutputData* clone() const;
            /*!
                @see EngineOutputBase 
            */
            virtual ObjectID objectID() const;
    
            //! Returns the 32 bit flags as a number
            /*!
            */
            uint32 flags() const;
    
            //! Sets flags using a value and mask
            /*!
                The value is bit-ANDed with the mask and bit-ORed with the value.

            */
            void setFlags(uint32 value, uint32 mask = 0);

            //! Sets the value of a single bit flag
            /*!
                @pre bit_pos >= 0 and <= 31

            */
            void setFlag(int bit_pos, bool value);
    
            //! Returns true if a bit is set
            /*!
                @pre bit_pos >= 0 and <= 31

            */
            bool isSet(int bit_pos) const;
    
        protected:
            /*! @see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8>& buffer) const;
            /*! @see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_pos);
            /*! @see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;
            /*! @see SerializableComposite */
            virtual void printOwnData(std::ostream& s) const;
            /*! @see SerializableComposite */
            virtual void printOwnHeader(std::ostream& s) const;
    
        private:
            //! Copy the data from rhs into this object
            void copyFrom(const CustomEventOutputData& rhs);
    
        private:
            //! 32 bit-flags
            uint32 _flags;
        };

        typedef boost::shared_ptr<CustomEventOutputData> CustomEventOutputDataPtr;
        typedef boost::shared_ptr<const CustomEventOutputData> ConstCustomEventOutputDataPtr;
    }
}
#endif

