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
#ifndef SM_COREDATA_EOD_IMAGECOLLECTIONOUTPUTDATA_H
#define SM_COREDATA_EOD_IMAGECOLLECTIONOUTPUTDATA_H

//! \file
#include "eod/engineoutputbase.h"
#include "eod/imageoutputdata.h"

namespace sm
{
    namespace eod
    {
        class ImageOutputData;
    
        /*! \brief Data class that represents a collection of images output by the Tracking Engine

            \if SM_COREDATA_LANGUAGE_PYTHON
            class ImageCollectionOutputData(EngineOutputBase):
                """A data class that represents a collection of images output by the Tracking Engine.
                """
            \endif
         */
        class SM_COREDATA_API ImageCollectionOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(ImageCollectionOutputData)

        public:
            /*
                \if SM_COREDATA_LANGUAGE_PYTHON
                THIS_OBJECT_ID = 30
                \endif
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(30);
            COREDATA_DECLARE_NAMED_OBJECT_ID(IMAGE_COLLECTION_OUTPUT_DATA_ID, 30);
    
            /*!
                \if SM_COREDATA_LANGUAGE_PYTHON
                def __init__(self):
                    """All members zeroed."""
                    pass
                \endif
            */
            ImageCollectionOutputData();
    
            ImageCollectionOutputData(const ImageCollectionOutputData& rhs);
    
            virtual ~ImageCollectionOutputData();
    
            ImageCollectionOutputData& operator=(const ImageCollectionOutputData& rhs);
    
            /*! \return a copy of this object, allocated on the heap */
            virtual ImageCollectionOutputData* clone() const;
    
            /*! \see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            /*! \brief Removes all images from the collection.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def clear(self):
                    """Removes all images from the collection.
                    """
                \endif
             */
            void clear();
    
            /*! \brief Returns the number of images.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def numImages(self):
                    """Returns the the number of images.
                    """
                \endif
             */
            uint16 numImages() const;
    
            /*! \brief Returns an image by index.

                \post returned image is not null
            */
            ConstImageOutputDataPtr image(unsigned int index) const;
    
            /*! \brief Returns an image by index.

                \post returned image is not null

                \if SM_COREDATA_LANGUAGE_PYTHON
                def image(self, index):
                    """Returns the ImageOutputData instance at index.

                    The arguments are:
                        - index     Zero based index as an int. Must be smaller than
                                    numImages().
                    """
                \endif
             */
            ImageOutputDataPtr image(unsigned int index);
    
            /*! \brief Adds an image to the collection.

                \param image The image to be added to the collection. 
                \return true if image added to collection.
                \pre image is not NULL.
                \pre image has not already been added.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def addImage(self, image):
                    """Adds an image to the collection.

                    The arguments are:
                        - image     The not None ImageOutputData instance to add
                                    to the collection. It must not already have
                                    been added to this collection.
                    """
                \endif
             */
            bool addImage(const ImageOutputDataPtr& image);
    
            /*! \brief Removes an image from the collection.

                \param image The image to be removed.
                \return true if the image was in the collection.
                \pre image is not NULL.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def removeImage(self, image):
                    """Removes an image from the collection.

                    The arguments are:
                        - image    The not None ImageOutputData, or image identifier to remove.

                    Returns True if the image was in the collection.
                    """
                \endif
             */
            bool removeImage(const ImageOutputDataPtr& image);

            /*! \brief Removes an image from the collection by identifier.

                \param image_identifier The image identifier to be removed.
                \return true if the image was in the collection.
            */
            bool removeImage(const std::string& image_identifier);
    
            /*! \brief Returns the index of the image with the identifier or -1 if not found.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def findImageIndex(self, image_identifier):
                    """Returns the index of the image with the identifier or -1 if not found.

                    The arguments are:
                        - image_identifier    The identifier for an image.
                    """
                \endif
             */
            int findImageIndex(const std::string& image_identifier) const;
    
        protected:
            /*! \see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8>& buffer) const;
    
            /*! \see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_pos);
    
            /*! \see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;
    
            /*! \see SerializableComposite */
            virtual void printOwnData(std::ostream& s) const;
    
            /*! \see SerializableComposite */
            virtual void printOwnHeader(std::ostream& s) const;
    
    
        private:
            //! Copy the data from rhs into this object
            void copyFrom(const ImageCollectionOutputData& rhs);
    
            typedef std::vector<ImageOutputDataPtr> Images;
            Images _images;
        };
        typedef boost::shared_ptr<ImageCollectionOutputData> ImageCollectionOutputDataPtr;
        typedef boost::shared_ptr<const ImageCollectionOutputData> ConstImageCollectionOutputDataPtr;
    }
}

#endif

