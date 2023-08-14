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
#ifndef SM_COREDATA_EOD_GPSOUTPUTDATAV2_H
#define SM_COREDATA_EOD_GPSOUTPUTDATAV2_H

//! @file
#include "eod/engineoutputbase.h"

#include "eod/gpscoordinate.h"

namespace sm
{
    namespace eod
    {
        //! Data class that represents public head-pose related engine data
        //! A data class for GPS data.
        /*!
        */
         class SM_COREDATA_API GPSOutputDataV2 : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(GPSOutputDataV2)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(35);
            COREDATA_DECLARE_NAMED_OBJECT_ID(GPS_OUTPUT_DATA_ID, 35);
    
            //! All members zeroed
            /*!
            */
             GPSOutputDataV2();

            GPSOutputDataV2(const GPSOutputDataV2& rhs);
    
            virtual ~GPSOutputDataV2();

            GPSOutputDataV2& operator=(const GPSOutputDataV2& rhs);

            /*! @return a copy of this object, allocated on the heap */
            virtual GPSOutputDataV2* clone() const;
            
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! @return true if the GPS data is valid.
            /*!
             */
             bool isDataValid() const;
            
            //! Time in seconds since 1.1.1970 universal GMT time.
            /*!
                This value is a convenient and standardized way to encode 
                the global date and time and can be easily converted into 
                all standard date/time formats. The accuracy of the values
                depends on the correct setting of the system clock.

             */
            uint32 gmtTime() const;

            //! @return latitude 
            /*!
             */
             const sm::eod::GPSCoordinateV2 latitude() const;

            //! @return longitude 
            /*!
             */
             const sm::eod::GPSCoordinateV2 longitude() const;

            //! @return speed detected by the GPS device measured in km/h
            /*!
             */
             float speed() const;

            //! @return travelling course (direction) measured in degrees
            /*!
             */
             float course() const;
    
            //! Set GPS data validity
            /*!
             */
             void setDataValid(bool valid);

            //! Set GMT time of this GPS data set in seconds since 00:00:00 01.01.1970 (UTC)
            /*!
             */
             void setGMTTime(uint32 gmt_time);

            //! Set latitude
            /*!
             */
             void setLatitude(const sm::eod::GPSCoordinateV2& latitude);

            //! Set longitude
            /*!
            */
             void setLongitude(const sm::eod::GPSCoordinateV2& longitude);

            //! Set speed in km/h
            /*!
            */
             void setSpeed(float speed_km_h);

            //! Set the travelling course angle in degrees
            /*!
            */
             void setCourse(float course);
    
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
            void copyFrom(const GPSOutputDataV2& rhs);
    
        private:
            int8 _data_valid;
            uint32 _gmt_time;       
            sm::eod::GPSCoordinateV2 _latitude;
            sm::eod::GPSCoordinateV2 _longitude;
            //! Speed Over Ground in km/h
            float _speed_km_h;
            //! Course Over Ground in degrees
            float _course;
        };
        typedef boost::shared_ptr<GPSOutputDataV2> GPSOutputDataV2Ptr;
        typedef boost::shared_ptr<const GPSOutputDataV2> ConstGPSOutputDataV2Ptr;
    }
}

#endif

