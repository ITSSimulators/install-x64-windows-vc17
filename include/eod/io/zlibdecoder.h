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
#ifndef SM_COREDATA_EOD_ZLIBDECODER_H
#define SM_COREDATA_EOD_ZLIBDECODER_H

//! \file
#include "eod/io/zlibcodec.h"
#include "eod/io/serializablecompressordecoder.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            class SM_COREDATA_API ZLibDecoder : public ZLibCodec<SerializableCompressorDecoder>
            {
            public:
                ZLibDecoder();
                ~ZLibDecoder();

                void decode(const uint8* data, std::size_t size);
                DecoderData getNextWithStatus(DeserializationStatusFlags& status);

            private:
                class PImpl;
                boost::scoped_ptr<PImpl> _pImpl;
            };
        }
    }
}

#endif //SM_COREDATA_EOD_ZLIBDECODER_H

