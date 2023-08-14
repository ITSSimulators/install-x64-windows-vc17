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
#ifndef SM_COREDATA_EOD_SERIALIZABLEDECOMPRESSOR_H
#define SM_COREDATA_EOD_SERIALIZABLEDECOMPRESSOR_H

//! \file
#include "eod/engineoutputdata.h"
#include "eod/compressedserializable.h"
#include "eod/io/serializablecompressordecoderfactory.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            class SM_COREDATA_API SerializableDecompressor
            {
            public:
                SerializableDecompressor(SerializableCompressorDecoderFactory& factory);
                ~SerializableDecompressor();

                void decompress(CompressedSerializablePtr ceod);
                std::pair<SerializablePtr, PTS> getNext();
                std::pair<SerializablePtr, PTS> getNextWithStatus(sm::eod::DeserializationStatusFlags& status_out);
            private:
                // Ban copy construction
                SerializableDecompressor(const SerializableDecompressor&);
                // Ban assignment
                SerializableDecompressor& operator=(const SerializableDecompressor&);

                class PImpl;
                boost::scoped_ptr<PImpl> _pImpl;
            };
        }
    }
}

#endif //SM_COREDATA_EOD_SERIALIZABLEDECOMPRESSOR_H

