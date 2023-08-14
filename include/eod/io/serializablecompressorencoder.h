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
#ifndef SM_COREDATA_EOD_SERIALIZABLECOMPRESSORENCODER_H
#define SM_COREDATA_EOD_SERIALIZABLECOMPRESSORENCODER_H

//! \file
#include "serializablecompressorcodec.h"
#include "eod/serializable.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            /*! \brief Interface for an encoder.

                An encoder encodes a serializable object and a presentation time stamp into a
                buffer.
            */
            class SM_COREDATA_API SerializableCompressorEncoder
            {
            public:
                typedef std::vector<uint8> Buffer;

                virtual ~SerializableCompressorEncoder();

                /*! An identifier which indicates the binary format handled by the encoder */
                virtual CodecID codecID() const COREDATA_NO_THROW COREDATA_PURE_METHOD;

                /*! \brief Encodes a serializable object into a buffer.

                    \param serializable The object to serialize.
                    \param pts A timestamp indicating what time in the stream the data appears.
                    \param buffer The buffer to write the encoded data into.
                */
                virtual void encode(const Serializable& serializable, PTS pts, Buffer& buffer) COREDATA_NO_THROW COREDATA_PURE_METHOD;

                /*! \brief Flushes any outstanding data from memory to the buffer

                    
                    \param buffer The buffer to append data to.
                */
                virtual void flush(Buffer& buffer) COREDATA_NO_THROW COREDATA_PURE_METHOD;
            protected:
                SerializableCompressorEncoder()
                {
                }
            private:
                // Ban copy construction
                SerializableCompressorEncoder(const SerializableCompressorEncoder&);
                // Ban assignment
                SerializableCompressorEncoder& operator=(const SerializableCompressorEncoder&);
            };

            typedef boost::shared_ptr<SerializableCompressorEncoder> SerializableCompressorEncoderPtr;
        }
    }
}

#endif //SM_COREDATA_EOD_SERIALIZABLECOMPRESSORENCODER_H

