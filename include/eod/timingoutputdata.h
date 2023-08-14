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
#ifndef SM_COREDATA_EOD_TIMINGOUTPUTDATA_H
#define SM_COREDATA_EOD_TIMINGOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"
#include "eod/serializablefactory.h"

namespace sm
{
    namespace eod
    {
        //! Data class that represents timing related data output by the Tracking Engine
        /*!
         */
        class SM_COREDATA_API TimingOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(TimingOutputData)

        public:
            // Annotation Label Constants
            /*
            */
            enum { INVALID_ANNOTATION_LABEL = -1 };
    
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(10);
            COREDATA_DECLARE_NAMED_OBJECT_ID(TIMING_OUTPUT_DATA_ID, 10);

            //! Constructor
            /*!

             */
            TimingOutputData();
    
            TimingOutputData(const TimingOutputData& rhs);
    
            TimingOutputData& operator=(const TimingOutputData& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            virtual TimingOutputData* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! Time since tracking started in seconds
            /*
                This time value represents the time in seconds since the 
                tracking was started, that is, since the start button was 
                pushed. The time gets reset when the stop button is pushed
                and the start button is pushed again. However, this will 
                also create a new logfile, and therefore, this time
                will always start with 0 in each logfile. 

            */
            double experimentTime() const;
    
            //! Time in seconds since 1.1.1970 universal GMT time.
            /*!
                This value is a convenient and standardized way to encode 
                the global date and time and can be easily converted into 
                all standard date/time formats. The accuracy of the values
                depends on the correct setting of the system clock.
            */
            int32 frameTimeSecs() const;
    
            //! Additional milliseconds in universal GMT time.
            /*!
                The frame_time_s parameter only encodes full seconds but no 
                fractions of seconds. To record the time more precisely the
                additional number of milliseconds is recorded in the 
                frame_time_ms field. The accuracy of the values depends on 
                the correct setting of the system clock.
            */
            uint16 frameTimeMSecs() const;
    
            //! Approximate delay in seconds between image generation and logger data release
            /*!
                The system estimates the delay between the image capture time and the
                disk/network logging time. This value can help to synchronise 
                the output of the system with other data streams taken in 
                parallel by other systems. The measured delay accounts for the image
                processing and data logger induced delays (particularly the 
                buffering required for the correction of the eye gaze based on
                eye blink events). 
                @par
    
                ***NOTE***
                This value does NOT account for the time required to transfer the data via 
                the network to another machine. This is non-deterministic.
    
                approxDelay() is only an estimate provided for convenience in 
                cases where the delay caused by the network delay can be neglected.
    
                For accurate data alignment use the GMT parameters (frameTimeSecs() and
                frameTimeMSecs()) and synchronize PC clocks using NTP to within 16 ms.
            */
            float approxDelay() const;
    
            //! User defined tag id, marking the beginning or end of an event.
            /*
                This field contains a user defined id that can be triggered by 
                events such as pressing function keys etc. The operator can use
                these tags to mark the point in time when certain events occurred
                during the experiment. No event is marked by value 0.
            */
            int32 annotationLabelID() const;
    
            //! Set the experiment time
            void setExperimentTime(double experiment_time);
            //! Set the seconds portion of the frame time time
            void setFrameTimeSeconds(int32 frame_time_s);
            //! Set the milliseconds portion of the frame time time
            void setFrameTimeMilliseconds(uint16 frame_time_ms);
            //! Set the approximate logging delay
            void setApproxDelay(float delay);
            //! Set the annotation label for this frame
            void setAnnotationLabelID(int32 label_id);
    
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
            void copyFrom(const TimingOutputData& rhs);
    
            double _experiment_time;
            int32 _frame_time_s;
            uint16 _frame_time_ms;
            float _approx_delay;
            int32 _annotation_label_id;
        };

        typedef boost::shared_ptr<TimingOutputData> TimingOutputDataPtr;
        typedef boost::shared_ptr<const TimingOutputData> ConstTimingOutputDataPtr;
    }
}

#endif

