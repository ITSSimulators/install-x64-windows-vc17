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
#ifndef SM_COREDATA_EOD_FEATURELINE_H
#define SM_COREDATA_EOD_FEATURELINE_H

//! @file
#include "eod/featureoutputdata.h"

namespace sm
{
    namespace eod
    {
        //! A feature within an image that is represented by a line.
        /*!
         */
        class SM_COREDATA_API FeatureLine : public FeatureOutputData
        {
            COREDATA_MEMORY_ALLOCATORS(FeatureLine)

        public:
            /*!
                @param object_id The Serializable ID of this object

            */
            explicit FeatureLine(ObjectID object_id);
    
            FeatureLine(const FeatureLine& rhs);
    
            FeatureLine& operator=(const FeatureLine& rhs);
    
            //! Set the endpoints of the line
            /*! @param x1 X-coordinate of the start of the line in normalised image coordinates
                @param y1 Y-coordinate of the start of the line in normalised image coordinates
                @param x2 X-coordinate of the end of the line in normalised image coordinates
                @param y2 Y-coordinate of the end of the line in normalised image coordinates
                @pre x1 in range 0..1 or x1 == invalidValue()
                @pre y1 in range 0..1 or y1 == invalidValue()
                @pre x2 in range 0..1 or x2 == invalidValue()
                @pre y2 in range 0..1 or y2 == invalidValue()

             */
            void setEndPoints(float x1, float y1, float x2, float y2);
    
            /*! 
                @return x-coordinate of the start of the line.
                This is a normalised value (between 0 and 1) and is in image coordinates 
                Set to invalidValue() if this value is invalid

             */
            float x1() const;
    
            /*!
                @return y-coordinate of the start of the line
                This is a normalised value (between 0 and 1) and is in image coordinates 
                Set to invalidValue() if this value is invalid 

             */
            float y1() const;
    
            /*!
                @return x-coordinate of the end of the line
                This is a normalised value (between 0 and 1) and is in image coordinates 
                Set to invalidValue() if this value is invalid 

             */
            float x2() const;
    
            /*! 
                @return y-coordinate of the end of the line
                This is a normalised value (between 0 and 1) and is in image coordinates 
                Set to invalidValue() if this value is invalid 

             */
            float y2() const;
    
            /*! @see Serializable::clone */
            FeatureLine* clone() const;
    
            /*! @see Serializable::printLine */
            void printLine(std::ostream& s) const;
    
            /*! @see Serializable::printHeader */
            void printHeader(std::ostream& s) const;
        protected:
            /*! @see Serializable::appendBuffer */
            virtual void appendBuffer(std::vector<uint8>& buffer) const;
    
            /*! @see Serializable::readBuffer */
            virtual void readFromBuffer(const std::vector<uint8>& buffer, int& read_pos_inout);
    
            /*! @see Serializable::numDataBytes */
            virtual uint32 numDataBytes() const;
    
    
        private:
            float _x1;
            float _y1;
            float _x2;
            float _y2;
        };
        typedef boost::shared_ptr<FeatureLine> FeatureLinePtr;
        typedef boost::shared_ptr<const FeatureLine> ConstFeatureLinePtr;
    }
}

#endif

