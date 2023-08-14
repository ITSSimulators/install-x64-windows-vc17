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
#ifndef SM_COREDATA_EOD_IMAGEOUTPUTDATA_H
#define SM_COREDATA_EOD_IMAGEOUTPUTDATA_H

//! @file
#include "eod/serializable.h"

namespace sm
{
    namespace eod
    {
        //! Data class that represents an image output by the Tracking Engine
        /*!
         */
        class SM_COREDATA_API ImageOutputData : public Serializable
        {
            COREDATA_MEMORY_ALLOCATORS(ImageOutputData)

        public:
            //! enumeration must fit into a int32
            /*!
            */
            enum ImageFormat
            {
                GRAY_8U = 0x30303859,
                RGB_24U = 21,
            };
    
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(31);
            COREDATA_DECLARE_NAMED_OBJECT_ID(IMAGE_OUTPUT_DATA_ID, 31);

            //! The byte boundary that rawData will be aligned to.
            BOOST_STATIC_CONSTANT(int, RAW_DATA_BYTE_ALIGNMENT = 32);
    
            //! Constructs andImageOutputDataTestCase empty object.
            /*!
                @post imageFormat() == 1
                @post width, height, rawData and bytesPerLine are all 0
                @post imageIdentifier is the empty string

            */
            ImageOutputData();
    
            ImageOutputData(const ImageOutputData& rhs);
    
            virtual ~ImageOutputData();
    
            ImageOutputData& operator=(const ImageOutputData& rhs);
    
            //! Returns the width of the image in pixels.
            /*!
             */
            uint32 width() const;
    
            //! Returns the height of the image in pixels.
            /*!
             */
            uint32 height() const;
    
            //! Returns the positive stride in bytes between two lines.
            /*!
             */
             uint32 bytesPerLine() const;
            
            //! Returns the format of the image.
            /*!
             */
             int32 imageFormat() const;
    
            //! Returns a string used to identify an image.
            /*!
                Images can be associated with an identifier. This can
                be used to identify images such as raw image or a data image.

             */
            std::string imageIdentifier() const;
    
            //! Sets a string used to identify an image.
            /*!
             */
            void setImageIdentifier(const std::string& image_identifier);
    
            //! Returns a pointer to the immutable raw image data or NULL.
            const uint8* rawData() const;
    
            //! Returns a pointer to the mutable raw image data or NULL.
            /*!
                @post result % RAW_DATA_BYTE_ALIGNMENT == 0

             */
            uint8* rawData();
    
            //! Allocates a new block of aligned memory copying the raw data.
            /*!
                Deallocates any previously allocated raw data.

                @param width The width of the image. Must be in 
                    the range (0, bytes_per_line].
                @param height The height of the image.
                @param bytes_per_line The number of bytes between 2 lines.
                @param raw_data Pointer to the raw data.
                @param image_format #ImageFormat describing the image format.
                @post rawData() != 0
                @post rawData() % RAW_DATA_BYTE_ALIGNMENT == 0

             */
            void setNewImage(uint32 width, uint32 height, uint32 bytes_per_line, 
                             const uint8* raw_data, int32 image_format);
            
            //! Uses an existing block of memory for image data
            /*!
                Deallocates any previously allocated raw data.
                The existing block of memory must outlive the lifetime of this
                object or until setNewImage() is called.

                @param width The width of the image. Must be in 
                    the range (0, bytes_per_line].
                @param height The height of the image.
                @param bytes_per_line The number of bytes between 2 lines.
                @param raw_data Pointer to the raw data which must be aligned on a
                        RAW_DATA_BYTE_ALIGNMENT byte boundary.
                @param image_format #ImageFormat describing the image format.
             */
            void shareNewImage(uint32 width, uint32 height, uint32 bytes_per_line, 
                             uint8* raw_data, int32 image_format);
    
            //! @return true if the rawData() is memory passed into the shareNewImage function.
            bool isSharingMemory() const;

            // Overriden Serializable methods
            /*! @see Serializable */
            virtual ObjectID objectID() const;

            /*! @see Serializable */
            virtual uint32 numDataBytes() const;

            //! Clones the object.
            /*! 
                The cloned object will allocated its own raw data image memory.

                @see Serializable
            */
            virtual ImageOutputData* clone() const;

            /*! @see Serializable */
            virtual void printLine(std::ostream& s) const;

            /*! @see Serializable */
            virtual void printHeader(std::ostream& s) const;
    
   
            // Allocates num_bytes of memory aligned to a RAW_DATA_BYTE_ALIGNMENT byte boundary
            static uint8* rawDataAlloc(int num_bytes);
            // Frees memory previously allocated with imageMemoryAlloc
            static void rawDataFree(uint8* aligned_memory);
        protected:
            // Overriden Serializable methods
            /*! @see Serializable */
            virtual void appendBuffer(std::vector<uint8>& buffer) const;
            /*! @see Serializable */
            virtual void readFromBuffer(const std::vector<uint8>& buffer, int& read_pos_inout);
    
        private:
            //! Copy the data from rhs into this object
            /*!
                @pre& rhs != this
            */
            void copyFrom(const ImageOutputData& rhs);
    
            //! Deallocates raw data memory.
            void freeRawData();
    
            //! Width of image in pixels.
            uint32 _width;
            //! Height of image in pixels.
            uint32 _height;
            //! Stride bewteen to lines in bytes.
            uint32 _bytes_per_line;
            //! Format fo image.
            int32 _image_format;
            //! Identifies an image or class of images.
            std::string _image_identifier;
            //! Raw image data.
            uint8* _raw_data;
            //! True if the memory in _raw_data was not allocated by us
            bool _sharing_memory;
        };

        typedef boost::shared_ptr<ImageOutputData> ImageOutputDataPtr;
        typedef boost::shared_ptr<const ImageOutputData> ConstImageOutputDataPtr;
    }
}
#endif

