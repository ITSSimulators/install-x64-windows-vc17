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
#ifndef SM_COREDATA_EOD_FACETEXTUREOUTPUTDATA_H
#define SM_COREDATA_EOD_FACETEXTUREOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"
#include "eod/flmtypes.h"
#include "eod/imageoutputdata.h"

namespace sm
{
    namespace eod
    {
        //! FaceTextureOutputData contains an image and a transform between a FaceTextureCoordinate and a pixel.
        /*! FaceTextureOutputData is usually provided as an optional sub-object of FaceOutputData.
            @note Do not inherit.

         */
        class SM_COREDATA_API FaceTextureOutputData: public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(FaceTextureOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(92);


            /*
            */
            enum FaceTextureType
            {
                ORTHOGRAPHIC_PROJECTION = 0,
                UNKNOWN = -1,
            };

            /*!
            */
            FaceTextureOutputData();

            FaceTextureOutputData(const FaceTextureOutputData& rhs);

            FaceTextureOutputData& operator=(const FaceTextureOutputData& rhs);

            /*! @return a deep copy of this object, allocated on the heap. */
            FaceTextureOutputData* clone() const;

            /*! @return THIS_OBJECT_ID */
            virtual ObjectID objectID() const;

            //! Adds face texture. If @a type == UNKNOWN, clears the texture.
            /*!
               @pre (type==UNKNOWN && !face_texture) || (type!=UNKNOWN && face_texture)

             */
            void addFaceTexture(sm::eod::FaceTextureOutputData::FaceTextureType type, const ImageOutputDataPtr& face_texture);

            //! Return the type of the face texture, or UNKNOWN if not attached
            /*!

             */
            FaceTextureOutputData::FaceTextureType faceTextureType() const;

            //! @return the face texture, or 0 if not attached.
            /*!
             */
            ConstImageOutputDataPtr faceTexture() const;
            ImageOutputDataPtr faceTexture();

            //! @return The mapping between mask landmark-ids and landmark data. Use this for enumerating all the face-coordinates.
            /*!

             */
            const FaceLandmarkMap& faceMaskLandmarks() const;

            //! Adds a mask landmark to the FaceOutputData
            /*!
                @pre landmark.id is in range 800..899

              */
            void addMaskLandmark(const sm::eod::FaceLandmark& landmark);

            //! Gets the face coordinate associated with @a landmark_id, where landmark_id is a Mask Id.
            /*!
                @param landmark_id integer value representing a specific location on the face. Refer to the FLM Standard for details.
                @param coord Current position of the facial landmark in 3D coordinates with respect to the head-reference frame (meters).
                @return true if the landmark exists. If false, the value of @a coord is unchanged. 

             */
            bool faceMaskCoordinate(sm::eod::FaceLandmarkId landmark_id, sm::eod::FaceCoordinate& coord) const;

            //! Gets the face texture coordinate associated with @a landmark_id, where landmark_id is a Mask Id.
            /*!
                @param landmark_id integer value representing a specific location on the face. Refer to the FLM Standard for details.
                @param coord Current position of the facial landmark in face-texture coordinates. Refer to the FTC Standard for details.
                @return true if the landmark exists. If false, the value of @a coord is unchanged. 

             */
            bool faceMaskTextureCoordinate(sm::eod::FaceLandmarkId landmark_id, sm::eod::FaceTextureCoordinate& coord) const;

            //! Set the transform variables for converting from a face-texture coordinate to a pixel.
            /*!
             */
            void setPixelTransform(float origin_pixel_x, float origin_pixel_y, float scale_x, float scale_y);

            //! Get the transform variables for converting from a face-texture coordinate to a pixel.
            /*!
             */
            void getPixelTransform(float& origin_pixel_x_out, float& origin_pixel_y_out, float& scale_x_out, float& scale_y_out) const;

            //! Convert a face-texture coordinate to a pixel.
            /*!
                @param coord A 2D texture coordinate obtained from the FaceOutputData, representing a location on the face texture.
                @param x_out Pixel value x coordinate (column) in the face-texture image. May be out of bounds. Value is a float for sub-pixel accuracy.
                @param y_out Pixel value y coordinate (row) in the face-texture image. May be out of bounds. Value is a float for sub-pixel accuracy.
                A FaceTextureCoordinate is a 2D normalized coordinate obtained from FaceOutputData. 

             */
            void faceTCToPixel(const sm::eod::FaceTextureCoordinate& coord, float& x_out, float& y_out) const;

        protected:
            void appendEngineSpecificData(std::vector<uint8>& buffer) const;
            void readEngineSpecificData(const std::vector<uint8>& buffer,int& read_pos);
            uint32 numEngineSpecificDataBytes() const;
            void printOwnData(std::ostream& s) const;
            void printOwnHeader(std::ostream& s) const;
            /*! 
                Verifies that the subobject is ImageOutputData.

                @throw SerializableError if the object id already exists or the
                    object id is not valid for this object or sub_object is not derived 
                    from EngineOutputBase or FeatureOutputData.
            */
            virtual void doAddSubObject(const SerializablePtr& sub_object);


        private:
            void copyFrom(const FaceTextureOutputData& rhs);

        private:
            int32 _type;
            float _origin_x;
            float _origin_y;
            float _scale_x;
            float _scale_y;
            FaceLandmarkMap _landmarks;
        };
        typedef boost::shared_ptr<FaceTextureOutputData> FaceTextureOutputDataPtr;
        typedef boost::shared_ptr<const FaceTextureOutputData> ConstFaceTextureOutputDataPtr;
    }
}

#endif

