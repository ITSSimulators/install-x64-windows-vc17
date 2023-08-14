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
#ifndef SM_COREDATA_EOD_GAZEOUTPUTDATA_H
#define SM_COREDATA_EOD_GAZEOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        /*
        */
         enum GazeQualityLevel
        {
            NO_TRACKING = 0,        //!< The head is not tracked, no gaze data available.
            HEAD_DIRECTION,         //!< The eyes could not be tracked, gaze is computed from head orientation only.
            NON_IR_GAZE,            //!< The gaze is computed from the head pose and the iris location.
            IR_GAZE,                //!< The gaze is computed from the infrared reflections and the iris location.
            NUM_GAZE_QUALITY_LEVELS //!< The number of gaze quality levels defined.
        };
    
    
        //! Data class that represents gaze related data output by the Tracking Engine
        /*!
        */
         class SM_COREDATA_API GazeOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(GazeOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(13);
            COREDATA_DECLARE_NAMED_OBJECT_ID(GAZE_OUTPUT_DATA_ID, 13);
    
            /*!
            */
             GazeOutputData();
    
            //! Copies data members and calls base class copy constructor
            GazeOutputData(const GazeOutputData& rhs);
    
            GazeOutputData& operator=(const GazeOutputData& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            virtual GazeOutputData* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! Quality of gaze output for a given eye
            /*!
                This is a value between 0 and 4 which indicates how accurate the gaze direction is.
                The gaze quality levels are:
                0: No Gaze Available - No gaze direction value could be measured
                1: Head-Pose Gaze - The gaze direction is the same as the head-direction
                2: Non-IR Gaze - Gaze direction calculated when Infra-Red data is not available
                   This is the gaze quality that was produced by faceLAB 3 and earlier
                3: IR Gaze - Gaze direction estimated using IR data
                @param eye_id Specifies which eye the Gaze Quality Level is for (sm::eod::RIGHT_EYE
                or sm::eod::LEFT_EYE)
                @throw std::invalid_argument if eye_id is neither LEFT_EYE nor RIGHT_EYE

             */
            GazeQualityLevel gazeQualityLevel(int eye_id) const;
    
            //! Gaze direction in world coordinate space around [x,y]
            /*!
                The orientation of the eye gaze with respect to the world coordinate
                system is encoded in these fields. The values are the Euler angles in
                radians for rotations around the x- and y-axis to align the z-axes
                of the world coordinate system with the eye gaze direction.
                The eye gaze direction defined in this way represents the direction
                of a vector originating from the eyeball centre.
                If the system is in search mode, the values are 0. These values are
                filtered with the internal faceLAB saccade filter.
                @param eye_id Specifies which gaze direction is returned (sm::eod::RIGHT_EYE
                or sm::eod::LEFT_EYE)
                @throw std::invalid_argument if eye_id is neither LEFT_EYE nor RIGHT_EYE

             */
            const fStdVector2& gazeRotation(int eye_id) const;
    
            //! Positions of the eye balls in world coordinates
            /*!
                The positions of the centre of the eye balls in world coordinates. If the system is
                not using IR-based gaze, these are derived from the calibrated, or if not available,
                from the uncalibrated eye ball positions relative to the head model features. If the
                system is able to track IR-gaze, a more accurate value is logged 
                If the system is in search mode, the value is 0.
                @param eye_id Specifies which eyeball centre is returned (sm::eod::RIGHT_EYE 
                or sm::eod::LEFT_EYE) 
                @throw std::invalid_argument if eye_id is neither LEFT_EYE nor RIGHT_EYE

             */
            const fStdVector3& eyeballCentre(int eye_id) const;
    
            //! Flag indicating a saccade
            /*!
                The flag is set during saccades of the eye gaze as detected by
                the internal faceLAB saccade filter. This signal is the basis
                for the eye gaze filter.

             */
            bool saccade() const;
    
            //! Flag indicating whether or not gaze has been calibrated
            /*!
                Calibrated gaze is more accurate than uncalibrated gaze.

             */
            bool gazeCalibrated() const;
    
            //! Set the saccade flag
            /*!
                @param saccade true if a saccade is occuring, false otherwise 

             */
            void setSaccade(bool saccade);
    
            //! Set whether the gaze has been calibrated
            /*!
                @param calibrated true if the gaze has been calibrated, false otherwise 

             */
            void setGazeCalibrated(bool calibrated);
    
            //! Set the gaze quality level for a given eye
            /*!
                @param eye_id The eye to set the Gaze Quality Level for
                @param gql The Gaze Quality Level 
                @pre eye_id is either LEFT_EYE or RIGHT_EYE
                @pre gql must be in the range NO_TRACKING..NUM_GAZE_QUALITY_LEVELS-1

              */
            void setGazeQualityLevel(int eye_id, GazeQualityLevel gql);
    
            //! Set the position of the eyeball centre for a given eye
            /*!
                @param eye_id The eye to set the eyeball centre for
                @param eyeball_centre vector of length 3 ([x, y, z]) representing the 3D position 
                of the eyeball centre (in world coordinates)
                @pre eye_id is either LEFT_EYE or RIGHT_EYE
                @pre eyeball_centre is a 3D point

              */
            void setEyeballCentre(int eye_id, const fStdVector3& eyeball_centre);
    
            //! Set the gaze rotation for a given eye
            /*!
                @param eye_id The eye to set the gaze rotation for
                @param gaze_rot Vector of length 2 [Pitch, Yaw] represnting the gaze rotation. 
                @pre eye_id is either LEFT_EYE or RIGHT_EYE
                @pre eyeball_centre is a 2D rotation vector

              */
            void setGazeRotationPitchYaw(int eye_id, const fStdVector2& gaze_rot);

            /*!
                @pre gql must be in the range NO_TRACKING..NUM_GAZE_QUALITY_LEVELS-1

              */
            static const std::string& gazeQualityLevelName(GazeQualityLevel gql);
    
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
            void copyFrom(const GazeOutputData& rhs);
            //! Prints out Vergence Point, Vergence Distance and Vergence Angle
            void writeVergenceFields(std::ostream& s) const;
    
            std::vector<uint8> _gaze_quality_level;
            std::vector<fStdVector3> _eyeball_centre;
            std::vector<fStdVector2> _gaze_rotation;
            int8 _gaze_calibrated;
            int8 _saccade;
        };
        typedef boost::shared_ptr<GazeOutputData> GazeOutputDataPtr;
        typedef boost::shared_ptr<const GazeOutputData> ConstGazeOutputDataPtr;
    }
}

#endif

