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
#include <zlib.h>

namespace sm
{
    namespace eod
    {
        namespace io
        {
            namespace detail
            {
                class RawBuffer
                {
                public:
                    RawBuffer(std::size_t size);
                    ~RawBuffer();

                    uint8* data() const;
                    std::size_t size() const;

                    void resize(std::size_t size);

                private:
                    uint8* _data;
                    uint8* _end;
                };

                class ZLibCodecImpl
                {
                public:
                    ZLibCodecImpl();

                    bool haveData();
                    void getData(uint8 const*& data, std::size_t& size);

                    static uint32 checksum(uint8 const* data, std::size_t size);

                protected:
                    int writeData(int (*processs)(z_streamp, int), int flush);
                    void syncBuffer();

                protected:
                    z_stream _stream;

                private:
                    RawBuffer _buffer;
                };

                class ZLibEncoderImpl : public ZLibCodecImpl
                {
                public:
                    ZLibEncoderImpl(int level);
                    ~ZLibEncoderImpl();

                    int encode(Bytef* data, std::size_t size);
                    int flush(int flush);
                    int reset();
                };

                class ZLibDecoderImpl : public ZLibCodecImpl
                {
                public:
                    ZLibDecoderImpl();
                    ~ZLibDecoderImpl();

                    int decode(Bytef* data, std::size_t size);
                    int reset();
                };
            }
        }
    }
}

