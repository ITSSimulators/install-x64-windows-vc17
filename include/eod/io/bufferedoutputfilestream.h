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
#ifndef SM_COREDATA_EOD_BUFFEREDOUTPUTFILESTREAM_H
#define SM_COREDATA_EOD_BUFFEREDOUTPUTFILESTREAM_H

//! @file
#include "eod/basics.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            class SM_COREDATA_API BufferedOutputFileStream: public std::ofstream
            {
            public:
                BufferedOutputFileStream(const std::string& file_name, ios_base::openmode mode, std::streamsize buffer_size = 8192);
                BufferedOutputFileStream(const std::wstring& file_name, ios_base::openmode mode, std::streamsize buffer_size = 8192);
                ~BufferedOutputFileStream();

                void setBufferSize(std::streamsize buffer_size);
                std::streamsize bufferSize();

            private:
                char_type* _buffer;
                std::streamsize _buffer_size;
            };
        }
    }
}

#endif

