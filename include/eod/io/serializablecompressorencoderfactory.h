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
#ifndef SM_COREDATA_EOD_SERIALIZABLECOMPRESSORENCODERFACTORY_H
#define SM_COREDATA_EOD_SERIALIZABLECOMPRESSORENCODERFACTORY_H

//! \file
#include "eod/serializable.h"
#include "eod/io/serializablecompressorencoder.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            struct SM_COREDATA_API EncoderCreator
            {
                virtual SerializableCompressorEncoder* create() COREDATA_PURE_METHOD;
                virtual ~EncoderCreator();
            };
            typedef boost::shared_ptr<EncoderCreator> EncoderCreatorPtr;

            /*! \brief Interface for an encoder factory

                Creates encoders for nodes within a tree.
            */
            class SM_COREDATA_API SerializableCompressorEncoderFactory
            {
            public:
                typedef std::pair<Serializable::ObjectID, int> StreamKeyElement;
                typedef std::vector<StreamKeyElement> StreamKey;

            public:
                BOOST_STATIC_CONSTANT(int, LINGER_FORVER = -1);
                BOOST_STATIC_CONSTANT(int, DO_NOT_LINGER =  0);

            public:
                virtual ~SerializableCompressorEncoderFactory();

                /*! \brief Returns a new encoder for \a key 

                    \param key The node within tree that needs to be encoded
                    \return An encoder instance or NULL if the key cannot be handled.
                        Ownership of the instance is transferred to the caller.
                */
                virtual SerializableCompressorEncoder* newEncoder(const StreamKey& key) const COREDATA_PURE_METHOD;

                /*! \brief Returns the number of frames the stream is kept alive waiting for data */
                virtual int encoderLingerInterval(const StreamKey& key) const COREDATA_PURE_METHOD;

                /*! \brief Returns true if there is an encoder available for \a key */
                virtual bool haveEncoder(const StreamKey& key) const COREDATA_PURE_METHOD;

            protected:
                SerializableCompressorEncoderFactory()
                {
                }

            private:
                // Ban copy construction
                SerializableCompressorEncoderFactory(const SerializableCompressorEncoderFactory&);
                // Ban assignment
                SerializableCompressorEncoderFactory& operator=(const SerializableCompressorEncoderFactory&);
            };
        }
    }
}

#endif //SM_COREDATA_EOD_SERIALIZABLECOMPRESSORENCODERFACTORY_H

