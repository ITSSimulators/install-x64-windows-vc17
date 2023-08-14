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
#ifndef SM_COREDATA_EOD_VP8VIDEOCODEC_H
#define SM_COREDATA_EOD_VP8VIDEOCODEC_H

//! \file
#include "eod/io/serializablecompressorcodec.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            template<typename Codec>
            struct VP8VideoCodec : public Codec
            {
                BOOST_STATIC_CONSTANT(CodecID, CODEC_ID = CodecIDRegistry::VP8);
                CodecID codecID() const { return CODEC_ID; }
            };

            namespace VP8VideoCodecConfig
            {
                typedef void(*RGBToYCbCr420Func)(const uint8* src, int srcStep, uint8* const dst[3], int const dstStep[3], int w, int h);
                typedef void(*YCbCr420ToRGBFunc)(const uint8* const src[3], int const srcStep[3], uint8* dst, int dstStep, int w, int h);
                SM_COREDATA_API RGBToYCbCr420Func setRGBToYCbCr420Func(RGBToYCbCr420Func func);
                SM_COREDATA_API YCbCr420ToRGBFunc setYCbCr420ToRGBFunc(YCbCr420ToRGBFunc func); 
            }
        }
    }
}

#endif //SM_COREDATA_EOD_VP8VIDEOCODEC_H

