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
#ifndef SM_COREDATA_EOD_EYECLOSUREOUTPUTDATA_H
#define SM_COREDATA_EOD_EYECLOSUREOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        //! Data class that represents eye closure related data output by the Tracking Engine
        /*!
         */
        class SM_COREDATA_API EyeClosureOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(EyeClosureOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(12);
            COREDATA_DECLARE_NAMED_OBJECT_ID(EYE_CLOSURE_OUTPUT_DATA_ID, 12);
    
            /*!
            */
            EyeClosureOutputData();
    
            //! Copies data members and calls base class copy constructor
            EyeClosureOutputData(const EyeClosureOutputData& rhs);
    
            //! Copies data members and calls base class assignent operator
            EyeClosureOutputData& operator=(const EyeClosureOutputData& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            virtual EyeClosureOutputData* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! Eye lid closure
            /*!
                The fraction of the iris currently covered
                by the upper and lower eye lid. A value of 0.0 corresponds 
                to a wide open eye, 1.0 denotes a completely closed eye. 
                The first value of the array is the measurement of the right eye of the
                person, the second value contains the measurement from the left eye.
                If the system is in search mode, the values are 0.
                @param eye_id specifies which eye to retrieve the value for (either
                    sm::eod::RIGHT_EYE  or sm::eod::LEFT_EYE)
                @pre eye_id is either sm::eod::LEFT_EYE or sm::eod::RIGHT_EYE

            */
            float eyeClosure(int eye_id) const;
    
            //! Confidence of the eye lid closure measurement [0..1]
            /*!
                The measurements for the eye closure has a confidence value 
                associated with it. A value of 1.0 corresponds to a high 
                confidence, a value of 0.0 indicates that the eye closure could 
                not be measured at all. 
                The first value of the array is the confidence of the measurement 
                from the right eye of the person, the second value contains the 
                measurement from the left eye.
                If the system is in search mode, the values are 0.
                @param eye_id specifies which eye to retrieve the value for (either 
                    sm::eod::RIGHT_EYE  or sm::eod::LEFT_EYE)
                @pre eye_id is either sm::eod::LEFT_EYE or sm::eod::RIGHT_EYE

            */
            float eyeClosureConfidence(int eye_id) const;
    
            //! The calibration status of the eye closure measure
            /*!
                The determination of the eye closure contains a part that
                requires some time to automatically calibrate itself from
                the images. The calibration is fully automatic and no 
                user actions are required. The calibration depends on a 
                number of parameters such as image brightness, distance 
                of the head from the cameras and the orientation of the head.
                If a combination of these parameters occur that has not been
                observed by the system before, the system will need to calibrate
                for this configuration. The calib_status_eye_closure parameter
                contains the calibration status of the current configuration, where
                0 means not calibrated and eye closure depended parameters 
                like blinks may be unreliable, a value of 1 indicates a fully
                calibrated configuration.
                Therefore, in the beginning of an experiment this parameter
                will show frequent fluctuations while the different parameter
                configurations are calibrated. During the experiment patches
                of low calibration status will become more rarely when all
                parameter configurations have been calibrated.

            */
            float eyeClosureCalibStatus() const;
    
            //! PERCLOS value
            /*!
                The field contains the so called PERCLOS value derived from the
                eye closure. The PERCLOS value is the percentage of measurement 
                frames in a time window, in which the eye was closed at least
                a given percentage (default is 75%)    ignoring normal blinks. 
                Typically the time window is 10000 frames = 166.66s = 2:46min.

             */
            float perclos() const;
    
            //! Frequency of blinks
            /*!
                The system records the occurrence of blinks and calculates the
                average number of blinks per second. The time window taken for
                the calculation is the same as for the two PERCLOS values.
                The measure excludes long eye closures.
                If the system is in search mode, the value is 0.

            */
            float blinkFrequency() const;
    
            //! Duration of normal blinks
            /*!
                The duration of blinks is also recorded by the system. This field 
                contains the average duration in seconds of the blinks that occurred 
                in the time window used for the calculation of the PERCLOS values. 
                The measure excludes long eye closures.
                If the system is in search mode, the value is 0.

             */
            float averageBlinkDuration() const;
    
    
            //! Eye blink state (blinking/not blinking)
            /*!
                The state of the eyes with regards to normal eye blinks is encoded 
                in this field. While the eye is open, the flag is set to false(0).
                After a normal length blink has been detected, the _blinking flag
                is set to true(1) in retrospect for all data frames in which the 
                blink has occurred. 
                The value is always false(0) when the system is in search mode.
                NOTE: The flag is NOT set to true during long eye closures!

             */
            bool blinking() const;
    
            //! Set eye closure for specified eye
            /*! @param eye_id Eye to set the closure value for 
                @param closure The eye closure fraction 0..1
                @pre eye_id is either sm::eod::LEFT_EYE or sm::eod::RIGHT_EYE
                @pre closure is in the range 0..1

             */
            void setEyeClosure(int eye_id, float closure);
    
            //! Set eye closure confidence for specified eye
            /*! @param eye_id Eye to set the confidence for 
                @param confidence Confidence of the eye closure value 0..1 
                @pre eye_id is either sm::eod::LEFT_EYE or sm::eod::RIGHT_EYE
                @pre confidence is in the range 0..1

             */
            void setEyeClosureConfidence(int eye_id, float confidence);
    
            //! Set the eye closure calibration status
            /*! @param calib_status degree of eye closure calibration value 0..1
                @pre calib_status is in the range 0..1

             */
            void setEyeClosureCalibStatus(float calib_status);
    
            //! Set the blinking flag
            /*!
                @param blinking Whether a blink is occuring or not 

              */
            void setBlinking(bool blinking);
    
            //! Set the blink frequency
            /*! @param frequency The blink frequency (blinks/secs
                @pre frequency is not less than zero

              */
            void setBlinkFrequency(float frequency);
    
            //! Set the blink duration
            /*! @param duration Average blink duration (in secs) 
                @pre duration is not less than zero

             */
            void setAverageBlinkDuration(float duration);
    
            //! Set the PERCLOS value
            /*! @param perclos New perclos value 0..1
                @pre perclos is in the range 0..1

             */
            void setPerclos(float perclos);
    
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
            void copyFrom(const EyeClosureOutputData& rhs);
    
            std::vector<float> _eye_closure_frac;
            std::vector<float> _eye_closure_confidence;
            float _eye_closure_calib_status;
            int8 _blinking;
            float _blink_frequency;
            float _avg_blink_duration;
            float _perclos;
        };
        typedef boost::shared_ptr<EyeClosureOutputData> EyeClosureOutputDataPtr;
        typedef boost::shared_ptr<const EyeClosureOutputData> ConstEyeClosureOutputDataPtr;
    }
}

#endif

