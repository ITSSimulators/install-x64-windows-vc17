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
#ifndef SM_COREDATA_EOD_ZLIBCODEC_H
#define SM_COREDATA_EOD_ZLIBCODEC_H

//! \file
#include "eod/io/serializablecompressorcodec.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            template<typename Codec>
            struct ZLibCodec : public Codec
            {
                BOOST_STATIC_CONSTANT(CodecID, CODEC_ID = CodecIDRegistry::ZLIB);
                CodecID codecID() const { return CODEC_ID; }
            };
        }
    }
}

#endif //SM_COREDATA_EOD_ZLIBCODEC_H

