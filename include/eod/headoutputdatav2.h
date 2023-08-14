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
#ifndef SM_COREDATA_EOD_HEADOUTPUTDATAV2_H
#define SM_COREDATA_EOD_HEADOUTPUTDATAV2_H

//! @file
#include "eod/headoutputdata.h"

namespace sm
{
    namespace eod
    {
    
        //! Data class that represents public head-pose related engine data
        /*!
        */
         class SM_COREDATA_API HeadOutputDataV2 : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(HeadOutputDataV2)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(16);
            COREDATA_DECLARE_NAMED_OBJECT_ID(HEAD_OUTPUT_DATA_V2_ID, 16);
    
            /*!
            */
             HeadOutputDataV2();
    
            HeadOutputDataV2(const HeadOutputDataV2& rhs);
    
            //! Conversion constructor from older version
            explicit HeadOutputDataV2(const HeadOutputData& rhs);

            HeadOutputDataV2& operator=(const HeadOutputDataV2& rhs);
    
            //! Converts from older version
            const HeadOutputDataV2& operator=(const HeadOutputData& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            virtual HeadOutputDataV2* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! Head position [x,y,z]
            /*!
                The head position vector in the world coordinate system in meters is
                stored in these fields. The vector points from the origin of the world
                coordinate system to the point in the middle between the centres of the
                eye balls. If the system is in search mode, the values are 0.

             */
            const dStdVector3& headPosition() const;
    
            //! Get the head rotation value measured as Euler Angles [x,y,z]
            /*!
                The Euler angles in radians which describe the rotation of the head
                coordinate system with respect to the world coordinate system are
                stored in these fields.
                The head rotation value is stored internally using a Quaternion. It
                is converted to Euler angles by this method before being returned.
                If the system is in search mode, the values are 0.
                For information on converting Quaternions to Euler angles refer to
                http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

            */
            const dStdVector3& headRotation() const;
    
            //! Get the head rotation value measured as a Quaternion [q0, q1, q2, q3].
            /*!
                The Unit Quaternion which describes the rotation of the head
                coordinate system with respect to the world coordinate system are
                stored in these fields.
                The head rotation value is stored internally as a Quaternion. Its
                value is simply returned by this method.
                If the system is in search mode, the values are [1, 0, 0, 0].
            */
            const dStdVector4& headRotationQuaternion() const;
    
            //! Head tracking state
            /*!
                If the system is tracking the head this returns true. For
                more detailed engine state information refer to EngineStateOutputData.
                NOTE: If not tracking, most data fields do not contain
                valid data and are set to 0.

             */
            bool isTracking() const;
    
            //! Confidence of head measurement [0..1]
            /*!
                The confidence value used to calculate
                the head pose is stored in this field. A value of 1.0 denotes a high
                confidence, a value of 0.0 denotes that the system could not track
                the location of the head at all.
                If the system is in search mode, the value is 0.

            */
            double headPositionConfidence() const;
    
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
                @pre eye_id must be is either LEFT_EYE or RIGHT_EYE

             */
            const dStdVector3 headEyeBallPos(sm::eod::EyeId eye_id) const;
    
            //! Set the 3D head position
            /*! @param pos vector of length 3 containing the world co-ordinates of
                the head position [X, Y, Z] 
                @pre pos must be a 3D point
 
             */
            void setHeadPosition(const dStdVector3& pos);
    
            //! Set the filtered 3D head rotation using Euler Angles [x, y, z]
            /*! @param rotation Euler angles in radians [X, Y, Z] 
                @pre rotation is a 3D vector
 
             */
            void setHeadRotation(const dStdVector3& rotation);
    
            //! Set the filtered 3D head rotation value with a quaternion [q0, q1, q2, q3]
            /*! @param rotation unit quaternion [q0, q1, q2, q3] 
                @pre rotation is a 4D vector

              */
            void setHeadRotationQuaternion(const dStdVector4& rotation);
    
            //! Set the tracking state
            /*!
                @param tracking_state Whether or not the head is being tracked 

             */
            void setTrackingState(bool tracking_state);
    
            //! Set the head position confidence
            /*! @param head_confidence The confidence value associated with the head position 
                @pre head_confidence is in the range 0..1

              */
            void setHeadPositionConfidence(double head_confidence);
    
            //! Set the eyeball centre position, based on head-pose
            /*! @param eye_id ID of the eye that we are setting position for
                @param eyeball_pos vector of length 3 containing the 3D position [X, Y, Z]
                in world coordinates of the eyeball centre 
                @pre eye_id is either LEFT_EYE or RIGHT_EYE
                @pre eyeball_pos is a 3D point

              */
            void setHeadEyeballPos(sm::eod::EyeId eye_id,
                                   const dStdVector3& eyeball_pos);
    
            //! Set the model quality level
            /*!
                @param model_quality The integer level of Model Quality 

             */
            void setModelQualityLevel(int8 model_quality);
    
        protected:
            /*! @see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8>& buffer) const;
    
            /*! @see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8>& buffer,
                                                int& read_pos);
    
            /*! @see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;
    
            /*! @see SerializableComposite */
            virtual void printOwnData(std::ostream& s) const;
    
            /*! @see SerializableComposite */
            virtual void printOwnHeader(std::ostream& s) const;
    
        private:
            //! Copy the data from rhs into this object
            void copyFrom(const HeadOutputDataV2& rhs);
    
            int8 _tracking_state;
            dStdVector3 _head_position;
            dStdVector4 _head_rotation_quaternion;
            dStdVector3 _head_rotation_euler;
            double _head_confidence;
            int8 _model_quality;
            std::vector<dStdVector3> _head_eyeball_pos;
        };
        typedef boost::shared_ptr<HeadOutputDataV2> HeadOutputDataV2Ptr;
        typedef boost::shared_ptr<const HeadOutputDataV2> ConstHeadOutputDataV2Ptr;
    }
}
#endif

