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
#ifndef SM_COREDATA_EOD_COMPRESSEDSERIALIZABLETOKEN_H
#define SM_COREDATA_EOD_COMPRESSEDSERIALIZABLETOKEN_H

//! \file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        /*! \brief A token indicating that a node has been moved into a compressed stream.
                   This is an internal object. Please do not use it.
         */
        class SM_COREDATA_API CompressedSerializableToken : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(CompressedSerializableToken)

        public:
            typedef int32 StreamID;

            BOOST_STATIC_CONSTANT(StreamID, INVALID_STREAM_ID = -1);
            COREDATA_DECLARE_THIS_OBJECT_ID(96);

            /*! \brief Constructs the token with an invalid stream ID */
            CompressedSerializableToken();
            virtual ~CompressedSerializableToken();

            virtual ObjectID objectID() const;
            virtual CompressedSerializableToken* clone() const;

            /*! \brief Sets the stream ID that the object has been compressed into.

                \param stream_id The ID of the stream that contains the object.
            */
            void setStreamID(StreamID stream_id);

            /*! \return The ID of the stream that contains the object. */
            StreamID streamID() const;

        protected:
            virtual void printOwnHeader(std::ostream&) const ;
            virtual void printOwnData(std::ostream&) const ;
            virtual void appendEngineSpecificData(std::vector<uint8>& buffer) const;
            virtual void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_pos);
            virtual uint32 numEngineSpecificDataBytes() const;

            virtual bool forbidDuplicateSiblings() const;

        private:
            StreamID _streamID;
        };
        typedef boost::shared_ptr<CompressedSerializableToken> CompressedSerializableTokenPtr;
    }
}

#endif //SM_COREDATA_EOD_COMPRESSEDSERIALIZABLETOKEN_H

