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
#ifndef SM_COREDATA_EOD_HEADOUTPUTDATA_H
#define SM_COREDATA_EOD_HEADOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        class HeadOutputDataV2;
    
        //! Data class that represents public head-pose related engine data
        /*!
        */
        class SM_COREDATA_API HeadOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(HeadOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(11);
            COREDATA_DECLARE_NAMED_OBJECT_ID(HEAD_OUTPUT_DATA_ID, 11);
    
            /*!
                Represents the current state of the head tracker. 
                Is it currently tracking the head, or searching for it? 

            */
            enum 
            {
                SEARCHING = 0,
                TRACKING
            };
    
            HeadOutputData();
    
            //! Copies data members and calls base class copy constructor
            HeadOutputData(const HeadOutputData& rhs);
    
            //! Copy construct a HeadOutputData object from a HeadOutputDataV2 object
            HeadOutputData(const HeadOutputDataV2& rhs);
    
            //! Copies data members and calls base class assignent operator
            const HeadOutputData& operator=(const HeadOutputData& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            virtual HeadOutputData* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! Head position [x,y,z]
            /*!
                The head position vector in the world coordinate system in meters is 
                stored in these fields. The vector points from the origin of the world 
                coordinate system to the point in the middle between the centres of the
                eye balls. If the system is in search mode, the values are 0.

             */
            const fStdVector3& headPosition() const;
    
            //! Head rotation [x,y,z]
            /*!
                The Euler angles in radians which describe the rotation of the head
                coordinate system with respect to the world coordinate system are 
                stored in these fields. 
                If the system is in search mode, the values are 0.

             */
            const fStdVector3& headRotation() const;
    
            //! Head tracking state 
            /*!
                The state of the head tracker is encoded in this enum. 
                If the system is in tracking mode, ie. the head is tracked 
                successfully, the value is 1, and if the system is in 
                search mode the value is 0. 
                NOTE: In search mode, when this field is set to 0, most data
                fields that contain information on the tracking do not contain
                valid data and are set to 0.

            */
            int8 trackingState() const;
    
            //! Confidence of head measurement [0..1]
            /*!
                The confidence value produced by the Kalman filter used to calculate
                the head pose is stored in this field. A value of 1.0 denotes a high
                confidence, a value of 0.0 denotes that the system could not track 
                the location of the head at all. 
                If the system is in search mode, the value is 0.

             */
            float headPositionConfidence() const;
    
            //! Model Quality Level
            /*!
                This is the current value of the head-model quality. A higher model quality
                means that it will track more accurately 

             */
            int8 modelQualityLevel() const;
    
            //! Positions of the eye balls in world coordinates, calculated from the head-pose
            /*!
                The positions of the centre of the eye balls in world coordinates
                is derived from the calibrated, or if not available, from the
                uncalibrated eye ball positions relative to the head model features.
                The values are "filtered" in the same way the head pose is filtered,
                that is with the Kalman filter which determines the head pose.
                If the system is in search mode, the value is 0.
                @param eye_id Specifies which eyeball centre is returned (sm::eod::RIGHT_EYE 
                or sm::eod::LEFT_EYE)
                @pre eye_id must be either LEFT_EYE or RIGHT_EYE

             */
            const fStdVector3& headEyeBallPos(int eye_id) const;
    
            //! Set the 3D head position
            /*! 
                @param pos vector of length 3 containing the world co-ordinates of
                the head position [X, Y, Z] 
                @pre pos must be a 3D point

              */
            void setHeadPosition(const fStdVector3& pos);
    
            //! Set the filtered 3D head rotation
            /*! 
                @param rotation Euler angles in radians [X, Y, Z] 
                @pre rotation must be a 3D rotation

              */
            void setHeadRotation(const fStdVector3& rotation);
    
            //! Set the tracking flag
            /*! 
                @param tracking_state Whether or not the head is being tracked 

              */
            void setTrackingState(int8 tracking_state);
    
            //! Set the head position confidence
            /*!
                @param confidence The confidence value associated with the head position 
                @pre confidence must be in the range 0..1

              */
            void setHeadPositionConfidence(float confidence);
    
            //! Set the eyeball centre position, based on head-pose
            /*! @param eye_id ID of the eye that we are setting position for
                @param eyeball_pos vector of length 3 containing the 3D position [X, Y, Z]
                in world coordinates of the eyeball centre 
                @pre eye_id is either LEFT_EYE or RIGHT_EYE
                @pre eyeball_pos is a 3D point

              */
            void setHeadEyeballPos(int eye_id, const fStdVector3& eyeball_pos);
    
            //! Set the model quality level
            /*!
                @param model_quality The integer level of Model Quality 

             */
            void setModelQualityLevel(int8 model_quality);
    
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
            void copyFrom(const HeadOutputData& rhs);
    
            int8 _tracking_state;
            fStdVector3 _head_position;
            fStdVector3 _head_rotation;
            float _head_confidence;
            int8 _model_quality;
            std::vector< fStdVector3 > _head_eyeball_pos;
        };
        typedef boost::shared_ptr<HeadOutputData> HeadOutputDataPtr;
        typedef boost::shared_ptr<const HeadOutputData> ConstHeadOutputDataPtr;
    }
}

#endif

