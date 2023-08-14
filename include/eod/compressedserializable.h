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
#ifndef SM_COREDATA_EOD_COMPRESSEDSERIALIZABLE_H
#define SM_COREDATA_EOD_COMPRESSEDSERIALIZABLE_H

//! \file
#include "eod/serializable.h"

namespace sm
{
    namespace eod
    {

        /*! \brief A blob of compressed data.

            CompressedSerializable objects are created by \ref sm::eod::io::CompressingFileWriter "CompressingFileWriter" and
            sm::eod::io::SerializableCompressor "SerializableCompressor" objects. They contain a blob
            of compressed data which can be decompressed using the 
            \ref sm::eod::io::DecompressingFileReader "DecompressingFileReader " or 
            \ref sm::eod::io::SerializableDecompressor "SerializableDecompressor".

            \see \ref coreapi_coredata_binarystandard_compression "Compressed Data Binary Format"

            
        */
        class SM_COREDATA_API CompressedSerializable : public Serializable
        {
            COREDATA_MEMORY_ALLOCATORS(CompressedSerializable)

        public:
            COREDATA_DECLARE_THIS_OBJECT_ID(95);
            
            /*! \brief Constructs an empty compressed data blob */
            CompressedSerializable();
            virtual ~CompressedSerializable();

            typedef std::vector<uint8> DataStore;
            typedef DataStore::const_iterator DataIterator;


            /*! \brief Append a block of data to the compressed data blob

                \param begin Iterator to the start of the range.
                \param end Iterator to the end of the range.
            */
            template<typename Iterator>
            void appendData(Iterator begin, Iterator end) 
            { 
                _data.insert(_data.end(), begin, end); 
            }

            //! \return An iterator to the beginning of the blob of data
            DataIterator begin() const;
            //! \return An iterator to the end of the blob of data
            DataIterator end() const;

            //! \see Serializable::objectID
            virtual ObjectID objectID(void) const;
            //! \see Serializable::clone
            virtual CompressedSerializable* clone() const;
            //! \see Serializable::printLine
            virtual void printLine(std::ostream& s) const;
            //! \see Serializable::printHeader
            virtual void printHeader(std::ostream& s) const;
            //! \see Serializable::numDataBytes
            virtual uint32 numDataBytes() const;

        protected:
            virtual void appendBuffer(std::vector<uint8>& buffer) const;
            virtual void readFromBuffer(const std::vector<uint8>& buffer, int& read_pos_inout);

        private:
            DataStore _data;
        };
        typedef boost::shared_ptr<CompressedSerializable> CompressedSerializablePtr;
    }
}

#endif //SM_COREDATA_EOD_COMPRESSEDSERIALIZABLE_H

