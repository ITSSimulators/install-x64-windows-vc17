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
#ifndef SM_COREDATA_EOD_INERTIAOUTPUTDATA_H
#define SM_COREDATA_EOD_INERTIAOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        //! Data class that represents intertia data.
        /*!
         */
        class SM_COREDATA_API InertiaOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(InertiaOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(32);
            COREDATA_DECLARE_NAMED_OBJECT_ID(OUTPUT_DATA_ID, 32);
    
            //! All members zeroed
            /*!
            */
            InertiaOutputData();
            
            InertiaOutputData(const InertiaOutputData& rhs);
            
            InertiaOutputData& operator=(const InertiaOutputData& rhs);

            /*! @return a copy of this object, allocated on the heap */
            virtual InertiaOutputData* clone() const;

            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! @return Angular rate along X-axis in rads/sec
            /*!
             */
            float angularRateX() const;

            //! @return Angular rate along Y-axis in rads/sec
            /*!
            */
            float angularRateY() const;

            //! @return Angular rate along Z-axis in rads/sec
            /*!
            */
            float angularRateZ() const;

            //! Set angular rate along X-axis in rads/sec
            /*!
            */
            void setAngularRateX(float rate);

            //! Set angular rate along Y-axis in rads/sec
            /*!
            */
             void setAngularRateY(float rate);

            //! Set angular rate along Z-axis in rads/sec
            /*!
            */
             void setAngularRateZ(float rate);
    
            //! @return Acceleration along X-axis in Gs
            /*!
            */
            float accelX() const;

            //! @return Acceleration along Y-axis in Gs
            /*!
            */
            float accelY() const;

            //! @return Acceleration along Z-axis in Gs
            /*!
            */
            float accelZ() const;

            //! Set acceleration along X-axis in Gs
            /*!
            */
            void setAccelX(float);

            //! Set acceleration along Y-axis in Gs
            /*!
            */
            void setAccelY(float);

            //! Set acceleration along Z-axis in Gs
            /*!
             */
             void setAccelZ(float);
    
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
            void copyFrom(const InertiaOutputData& rhs);
    
        private:
            //! Angular rates in radians / sec
            float _x_ang_rate;
            float _y_ang_rate;
            float _z_ang_rate;
            //! Linear accellerations in Gs
            float _x_accel;
            float _y_accel;
            float _z_accel;
        };
        typedef boost::shared_ptr<InertiaOutputData> InertiaOutputDataPtr;
        typedef boost::shared_ptr<const InertiaOutputData> ConstInertiaOutputDataPtr;
    }
}

#endif

