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
#ifndef SM_COREDATA_EOD_SERIALIZABLECOMPRESSORCODEC_H
#define SM_COREDATA_EOD_SERIALIZABLECOMPRESSORCODEC_H

//! \file
#include "eod/platform_types.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            /*! \brief Type identifying a encoder/decoder ID data type */
            typedef uint32 CodecID;

            /*! \brief Type identifying a presentation timestamp data type */
            typedef uint32 PTS;

            /*! \brief List of build-in codec id's and codec id ranges.
                       LSB of the codec id is reserved for codec version.
                       MSB is reserved for future use (e.g. category).*/
            struct CodecIDRegistry
            {
                BOOST_STATIC_CONSTANT(CodecID, COREDATA_RANGE_BEGIN = 0x00000000);
                BOOST_STATIC_CONSTANT(CodecID, COREDATA_RANGE_END   = 0x00FFFFFF);

                BOOST_STATIC_CONSTANT(CodecID, IMAGE_COLLECTION = COREDATA_RANGE_BEGIN + 0x2000);
                BOOST_STATIC_CONSTANT(CodecID, ZLIB = COREDATA_RANGE_BEGIN + 0x4000);
                BOOST_STATIC_CONSTANT(CodecID, VP8  = COREDATA_RANGE_BEGIN + 0x8000);

                BOOST_STATIC_CONSTANT(CodecID, USER_RANGE_BEGIN = 0x80000000);
                BOOST_STATIC_CONSTANT(CodecID, USER_RANGE_END   = 0xEFFFFFFF);
            };
        }
    }
}

#endif //SM_COREDATA_EOD_SERIALIZABLECOMPRESSORCODEC_H

