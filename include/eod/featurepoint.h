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
#ifndef SM_COREDATA_EOD_FEATUREPOINT_H
#define SM_COREDATA_EOD_FEATUREPOINT_H

//! @file
#include "eod/featureoutputdata.h"

namespace sm
{
    namespace eod
    {
        //! A feature within an image that is represented by a point.
        /*! 
         */
        class SM_COREDATA_API FeaturePoint : public FeatureOutputData
        {
            COREDATA_MEMORY_ALLOCATORS(FeaturePoint)

        public:
            /*
            */
            //! The ID that identifies the FeaturePoint representing the right pupil
            COREDATA_DECLARE_NAMED_OBJECT_ID(RIGHT_PUPIL_ID, 23);
            //! The ID that identifies the FeaturePoint representing the left pupil
            COREDATA_DECLARE_NAMED_OBJECT_ID(LEFT_PUPIL_ID, 24);
    
            //! @param object_id The Serializable ID of this object
            /*!
                Sets the name of this object to be that returned by IDToHeaderPrefix for
                the supplied object_id 

            */
            explicit FeaturePoint(ObjectID object_id);
    
            FeaturePoint(const FeaturePoint& rhs);
    
            FeaturePoint& operator=(const FeaturePoint& rhs);
    
            //! Set the position of this feature
            /*! @param x X-coordinate of the feature point in normalised image coordinates
                @param y Y-coordinate of the feature point in normalised image coordinates
                @pre x is invalidValue() or in the range 0..1
                @pre y is invalidValue() or in the range 0..1

            */
            void setPosition(float x, float y);
    
            /*! @return x-coordinate of the feature point.
                This is a normalised value (between 0 and 1) and is in image coordinates.
                Set to invalidPosition() if this value is invalid

             */
            float x() const;
    
            /*! @return y-coordinate of the feature point.
                This is a normalised value (between 0 and 1) and is in image coordinates 
                Set to invalidPosition() if this value is invalid

             */
            float y() const;
    
            /*! @see Serializable::clone */
            FeaturePoint* clone() const;
    
            /*! @see Serializable::printLine */
            void printLine(std::ostream& s) const;
    
            /*! @see Serializable::printLine */
            void printHeader(std::ostream& s) const;
        protected:
            /*! @see Serializable::appendBuffer */
            virtual void appendBuffer(std::vector<uint8>& buffer) const;
    
            /*! @see Serializable::readBuffer */
            virtual void readFromBuffer(const std::vector<uint8>& buffer, int& read_pos_inout);
    
            /*! @see Serializable::numDataBytes */
            virtual uint32 numDataBytes() const;
    
    
            /*! @return a string representing a text header prefix, based on _object_id
                For example, returns "L_PUPILPOS" if object_id is LEFT_PUPIL_POS */
            static std::string IDToName(ObjectID object_id);
    
        private:
            float _x;
            float _y;
        };
        typedef boost::shared_ptr<FeaturePoint> FeaturePointPtr;
        typedef boost::shared_ptr<const FeaturePoint> ConstFeaturePointPtr;
    }
}

#endif

