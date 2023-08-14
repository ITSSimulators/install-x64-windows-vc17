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
#ifndef SM_COREDATA_EOD_FACEOUTPUTDATAV2_H
#define SM_COREDATA_EOD_FACEOUTPUTDATAV2_H

//! @file
#include "eod/engineoutputbase.h"
#include "eod/flmtypes.h"
#include "eod/facetextureoutputdata.h"
#include "eod/faceoutputdata.h"

namespace sm
{
    namespace eod
    {
        enum WearingGlassesType
        {
            WEARING_GLASSES_NO = 0, /*!< The subject is not wearing glasses */
            WEARING_GLASSES_YES,    /*!< The subject is wearing glasses */
            WEARING_GLASSES_UNKNOWN /*!< Do not know if the subject is wearing glasses */
        };

        //! FaceOutputDataV2 is a container for a set of facial landmark locations and an optional face-texture.
        /*! Facial landmarks are referenced by an integer value. They are defined
            in 3D coordinates (meters) with respect to the head-reference frame,
            and 2D normalised coordinates with respect to the face texture.
    
            The head-reference frame is right-handed, has the origin at
            the midpoint between the eyeball centres, Z axis pointing into the head
            opposite the direction of the nose, Y axis pointing up through top of
            the head, and X axis pointing towards the right eye.
    
            @see Facial Landmark Standard (FLM Standard) for a mapping of landmark
            index to facial location. 
    
            @note Do not inherit this class.

        */
        class SM_COREDATA_API FaceOutputDataV2 : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(FaceOutputDataV2)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(93);
    
            /*!
            */
            FaceOutputDataV2();
            FaceOutputDataV2(const FaceOutputDataV2& rhs);

            //! Construct from old version
            FaceOutputDataV2(const FaceOutputData& rhs);
            
            FaceOutputDataV2& operator=(const FaceOutputDataV2& rhs);
            //! Assign from old version
            FaceOutputDataV2& operator=(const FaceOutputData& rhs);
    
            /*! @return a deep copy of this object, allocated on the heap. */
            FaceOutputDataV2* clone() const;
            /*! @return THIS_OBJECT_ID */
            virtual ObjectID objectID() const;
   
            //! @return enumeration indicating the wearing glasses state of the face
            /*!
            */
            WearingGlassesType wearingGlasses() const;

            //! Sets the wearing glasses state of the face
            /*!
            */
            void setWearingGlasses(WearingGlassesType wearing_glasses);

            /*!
                @return Unique number identifying a found face

             */
            uint32 faceCount() const;

            //! Sets the unique number identifying a found face
            /*!
             */
            void setFaceCount(uint32 face_count);

            /*!
                @return the face texture, or 0 if not attached.

             */
            ConstFaceTextureOutputDataPtr faceTexture() const;
            FaceTextureOutputDataPtr faceTexture();
    
            //! Adds face texture. If 0, clears the texture.
            /*!
             */
            void addFaceTexture(const FaceTextureOutputDataPtr& face_texture);
    
            //! @return The mapping between landmark-ids and landmarks. Use this for enumerating all the face-coordinates.
            /*!

             */
            const FaceLandmarkMap& faceLandmarks() const;
    
            //! Adds a landmark to the FaceOutputDataV2
            /*!
                @pre landmark.id in not the range 800..899 

              */
            void addLandmark(const sm::eod::FaceLandmark& landmark);

            //! Sets the coordinate of a landmark in 3D coordinates in head space
            /*!
                If the landmark doesn't currently exist it is added with FaceTextureCoordinates default constructed.
                @pre landmark.id in not the range 800..899 

            */
            void setFaceCoordinate(FaceLandmarkId id, const FaceCoordinate& fc);
    
            //! Gets the face coordinate associated with @a landmark_id.
            /*!
                @param landmark_id integer value representing a specific location on the face. Refer to the FLM Standard for details.
                @param coord Current position of the facial landmark in 3D coordinates with respect to the head-reference frame (meters).
                @return true if the landmark exists. If false, the value of @a coord is unchanged. 

             */
            bool faceCoordinate(sm::eod::FaceLandmarkId landmark_id, sm::eod::FaceCoordinate& coord) const;

            //! Gets the face texture coordinate associated with @a landmark_id.
            /*!
                @param landmark_id integer value representing a specific location on the face. Refer to the FLM Standard for details.
                @param coord Current position of the facial landmark in face-texture coordinates (2D normalized). Refer to the FTC Standard for details.
                @return true if the landmark exists. If false, the value of @a coord is unchanged. 

             */
            bool faceTextureCoordinate(sm::eod::FaceLandmarkId landmark_id, sm::eod::FaceTextureCoordinate& coord) const;
    
            //! Sets the landmark coordinates for a landmark id to all 0.
            /*!
             */
            void zeroLandmark(sm::eod::FaceLandmarkId landmark_id);

            //! @return true if @a landmark_id has been added
            bool hasLandmark(FaceLandmarkId landmark_id) const;

            //! @return true if all landmarks in @a landmark_ids are present
            bool hasAllLandmarks(const FaceLandmarkIdVec& landmark_ids) const;

            //! Clears a landmark.
            /*!
             */
            void clearLandmark(sm::eod::FaceLandmarkId landmark_id);

            //! Removes all landmarks
            void clearLandmarks();
        protected:
            void appendEngineSpecificData(std::vector<uint8>& buffer) const;
            void readEngineSpecificData(const std::vector<uint8>& buffer,int& read_pos);
            uint32 numEngineSpecificDataBytes() const;
            void printOwnData(std::ostream& s) const;
            void printOwnHeader(std::ostream& s) const;
    
        private:
            void copyFrom(const FaceOutputDataV2& rhs);
    
        private:
            FaceLandmarkMap _landmarks;
            uint32 _face_count;
            uint8 _wearing_glasses;
        };
        typedef boost::shared_ptr<FaceOutputDataV2> FaceOutputDataV2Ptr;
        typedef boost::shared_ptr<const FaceOutputDataV2> ConstFaceOutputDataV2Ptr;
    }
}
#endif

