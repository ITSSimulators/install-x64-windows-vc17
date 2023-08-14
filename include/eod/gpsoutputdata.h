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
#ifndef SM_COREDATA_EOD_GPSOUTPUTDATA_H
#define SM_COREDATA_EOD_GPSOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"

#include "eod/gpscoordinate.h"

namespace sm
{
    namespace eod
    {
        //! A data class for GPS data.
        /*!
        */
        class SM_COREDATA_API GPSOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(GPSOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(34);
            COREDATA_DECLARE_NAMED_OBJECT_ID(GPS_OUTPUT_DATA_ID, 34);
    
            //! All members zeroed
            /*!
            */
            GPSOutputData();

            GPSOutputData(const GPSOutputData& rhs);
    
            virtual ~GPSOutputData();

            GPSOutputData& operator=(const GPSOutputData& rhs);

            /*! @return a copy of this object, allocated on the heap */
            virtual GPSOutputData* clone() const;
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
            const sm::eod::GPSCoordinateV1 latitude() const;

            //! @return longitude 
            /*!
             */
            const sm::eod::GPSCoordinateV1 longitude() const;

            //! @return speed detected by the GPS device measured in km/h
            /*!
             */
            int16 speed() const;
    
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
            void setLatitude(const sm::eod::GPSCoordinateV1& latitude);

            //! Set longitude
            /*!
            */
            void setLongitude(const sm::eod::GPSCoordinateV1& longitude);

            //! Set speed in km/h
            /*!
            */
            void setSpeed(int16 speed_km_h);
    
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
            void copyFrom(const GPSOutputData& rhs);
    
        private:
            int8 _data_valid;
            uint32 _gmt_time;       
            sm::eod::GPSCoordinateV1 _latitude;
            sm::eod::GPSCoordinateV1 _longitude;
            int16 _speed_km_h;
        };
        typedef boost::shared_ptr<GPSOutputData> GPSOutputDataPtr;
        typedef boost::shared_ptr<const GPSOutputData> ConstGPSOutputDataPtr;
    }
}

#endif

