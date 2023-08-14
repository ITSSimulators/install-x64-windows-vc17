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
#ifndef SM_COREDATA_EOD_FEATURECIRCLE_H
#define SM_COREDATA_EOD_FEATURECIRCLE_H

//! @file
#include "eod/featureoutputdata.h"

namespace sm
{
    namespace eod
    {
        //! A feature within an image that is represented by a circle.
        /*!
         */
        class SM_COREDATA_API FeatureCircle : public FeatureOutputData
        {
            COREDATA_MEMORY_ALLOCATORS(FeatureCircle)

        public:

            /*!
                @param object_id The Serializable ID of this object

            */
            FeatureCircle(ObjectID object_id);

            FeatureCircle(const FeatureCircle& rhs);

            FeatureCircle& operator=(const FeatureCircle& rhs);

            //! Set the geometry of this circle feature
            /*! @param x X-coordinate of the circle centre point in normalised image coordinates
                @param y Y-coordinate of the circle centre point in normalised image coordinates
                @param radius Radius of the circle.

                @pre x in range 0..1 or x == invalidValue()
                @pre y in range 0..1 or y == invalidValue()
                @pre radius in range 0..1 or radius == invalidValue()

             */
            void setGeometry(float x, float y, float radius);

            /*! 
                @return x-coordinate of the centre point.
                This is a normalised value (between 0 and 1) and is in image coordinates.
                Set to invalidValue() if this value is invalid

             */
            float x() const;

            /*!
                @return y-coordinate of the centre point.
                This is a normalised value (between 0 and 1) and is in image coordinates
                Set to invalidValue() if this value is invalid 

             */
            float y() const;

            /*!
                @return radius of the circle.
                This is a normalised value (between 0 and 1) and is in image coordinates
                Set to invalidValue() if this value is invalid 

             */
            float radius() const;

            /*! @see Serializable::clone */
            FeatureCircle* clone() const;

            /*! @see Serializable::appendBuffer */
            virtual void appendBuffer(std::vector<uint8>& buffer) const;

            /*! @see Serializable::readBuffer */
            virtual void readFromBuffer(const std::vector<uint8>& buffer, int& read_pos_inout);

            /*! @see Serializable::numDataBytes */
            virtual uint32 numDataBytes() const;

            /*! @see Serializable::printLine */
            void printLine(std::ostream& s) const;

            /*! @see Serializable::printHeader */
            void printHeader(std::ostream& s) const;

        private:
            float _x;
            float _y;
            float _radius;
        };
        typedef boost::shared_ptr<FeatureCircle> FeatureCirclePtr;
        typedef boost::shared_ptr<const FeatureCircle> ConstFeatureCirclePtr;
    }
}

#endif

