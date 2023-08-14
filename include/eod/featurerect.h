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
#ifndef SM_COREDATA_EOD_FEATURERECT_H
#define SM_COREDATA_EOD_FEATURERECT_H

//! @file
// From OutputDataPack
#include "eod/featureoutputdata.h"

namespace sm
{
    namespace eod
    {
        //! A feature within an image that is represented by a rectangle.
        /*!
            The geometry of the rectangle is output in normalised image coordinates. This means that
            (0,0) corresponds to the top-left corner of the image, and (1,1) corresponds to the 
            bottom-right. Note that the top-left corner of the rectangle may lie outside the image boundary,
            so the normalised values for the rectangles position may be outside the range [0..1]. If this
            rectangle is invalid (i.e. the region it represents does not exist in the image), then both
            width() and height() will return -1.

         */
        class SM_COREDATA_API FeatureRect : public FeatureOutputData
        {
            COREDATA_MEMORY_ALLOCATORS(FeatureRect)

        public:
            /*
            */
            //! The ID that identifies the FeatureRect representing the face
            COREDATA_DECLARE_NAMED_OBJECT_ID(FACE_RECT_ID, 25);
            //! The ID that identifies the FeaturePoint representing the right eye
            COREDATA_DECLARE_NAMED_OBJECT_ID(RIGHT_EYE_RECT_ID, 26);
            //! The ID that identifies the FeaturePoint representing the left eye
            COREDATA_DECLARE_NAMED_OBJECT_ID(LEFT_EYE_RECT_ID, 27);
            //! The ID that identifies the FeaturePoint representing the mouth
            COREDATA_DECLARE_NAMED_OBJECT_ID(MOUTH_RECT_ID, 28);
    
            //! @param object_id The Serializable ID of this object
            /*! 
                Sets the name of this object to be that returned by IDToHeaderPrefix for
                the supplied object_id

            */
            explicit FeatureRect(ObjectID object_id);
    
            FeatureRect(const FeatureRect& rhs);
    
            FeatureRect& operator=(const FeatureRect& rhs);
    
            //! Set the bounds of the rectangle.
            /*!
                @param x X-coordinate of the top-left hand corner in normalised image coordinates
                @param y Y-coordinate of the top-left hand corner in normalised image coordinates
                @param width The width of the rectangle in normalised image coordinates
                @param height The height of the rectangle in normalised image coordinates

            */
            void setRect(float x, float y, float width, float height);
    
            /*!
                @return x-coordinate of the top-left hand corner of the feature rectangle.
                This is a normalised value and is in image coordinates. 

            */
            float x() const;
    
            /*!
                @return y-coordinate of the top-left hand corner of the feature rectangle.
                This is a normalised value and is in image coordinates. 

            */
            float y() const;
    
            /*!
                @return width of the feature rectangle.
                This is a normalised value and is in image coordinates.
                Set to -1 if the rectangle is invalid 

            */
            float width() const;
    
            /*!
                @return height of the feature rectangle.
                This is a normalised value and is in image coordinates.
                Set to -1 if the rectangle is invalid 

            */
            float height() const;
    
            /*! @see Serializable::clone */
            FeatureRect* clone() const;
    
            /*! @see Serializable::printLine */
            void printLine(std::ostream& s) const;
    
            /*! @see Serializable::printHeader */
            void printHeader(std::ostream& s) const;
        protected:
            /*! @see Serializable::appendBuffer */
            virtual void appendBuffer(std::vector<uint8>& buffer) const;
    
            /*! @see Serializable::readBuffer */
            virtual void readFromBuffer(const std::vector<uint8>& buffer, int& read_pos_inout);
    
            /*! @see Serializable::numDataBytes */
            virtual uint32 numDataBytes() const;
    
    
            /*! @return an object name prefix, based on _object_id
                For example, returns "LEYERECT" if object_id is LEFT_EYE_RECT_ID */
            static std::string IDToName(ObjectID object_id);
    
        private:
            float _x;
            float _y;
            float _width;
            float _height;
        };

        typedef boost::shared_ptr<FeatureRect> FeatureRectPtr;
        typedef boost::shared_ptr<const FeatureRect> ConstFeatureRectPtr;
    }
}

#endif

