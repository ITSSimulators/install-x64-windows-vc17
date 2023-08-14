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
#ifndef SM_COREDATA_EOD_SERIALIZABLECOMPRESSOR_H
#define SM_COREDATA_EOD_SERIALIZABLECOMPRESSOR_H

//! \file
#include "eod/engineoutputdata.h"
#include "eod/compressedserializable.h"
#include "eod/io/serializablecompressorcodec.h"
#include "eod/io/serializableidextractor.h"
#include "eod/io/serializablecompressorencoder.h"
#include "eod/io/serializablecompressorencoderfactory.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            /*! \brief A compressor for Serializable objects.

                Usage:
                \code
                TestEncoder defaultEncoder(33);

                SerializableCompressor::IdExtractorStore idExtractors;
                TestEncoderFactory encoderFactory;
                SerializableCompressor compressor(defaultEncoder, encoderFactory, idExtractors);
                compressor.compress(input, 25);
                CompressedSerializablePtr ceod = compressor.getNext();
                \endcode
            */
            class SM_COREDATA_API SerializableCompressor
            {
            public:
                typedef std::map<Serializable::ObjectID, SerializableIdExtractorPtr> IdExtractorStore;

                SerializableCompressor(SerializableCompressorEncoder& defaultEncoder,
                                       const SerializableCompressorEncoderFactory& encoderFactory, 
                                       const IdExtractorStore& idExtractors);
                ~SerializableCompressor();


                /*! \brief Queues another object to be compressed

                    \param obj The uncompressed object.
                    \param pts Unknown??
                */
                void compress(SerializablePtr obj, PTS pts);

                /*! \brief Returns the next compressed data object

                    \return A compressed object or NULL if insufficient uncompressed data has
                            been supplied to compress().
                */
                CompressedSerializablePtr getNext();

                /*! \brief Forces the end of compression
                    
                    Any data left to compress is compressed and a CompressedSerializablePtr added
                    to the compressed data fifo.
                */
                void flush();

                /*! \brief Resets the compressor without disrupting coherency of the stream
                           Also performs a flush and terminates all running codecs
                  
                */
                void reset(SerializableCompressorEncoder& defaultEncoder,
                           const SerializableCompressorEncoderFactory& encoderFactory, 
                           const IdExtractorStore& idExtractors);

            private:
                // Ban copy construction
                SerializableCompressor(const SerializableCompressor&);
                // Ban assignment
                SerializableCompressor& operator=(const SerializableCompressor&);

                class PImpl;
                boost::scoped_ptr<PImpl> _pImpl;
            };
        }
    }
}

#endif //SM_COREDATA_EOD_SERIALIZABLECOMPRESSOR_H

