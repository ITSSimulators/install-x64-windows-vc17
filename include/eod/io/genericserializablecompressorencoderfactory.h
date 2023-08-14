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
#ifndef SM_COREDATA_EOD_GENERICSERIALIZABLECOMPRESSORENCODERFACTORY_H
#define SM_COREDATA_EOD_GENERICSERIALIZABLECOMPRESSORENCODERFACTORY_H

//! \file
#include "eod/io/detail/genericserializablecompressorencoderfactoryimpl.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            template<>
            struct GSCFKeyConverter<Serializable::ObjectID>
            {
                static Serializable::ObjectID convert(const SerializableCompressorEncoderFactory::StreamKey& key) { return key.back().first; }
            };

            typedef GSCFBlock<SerializableCompressorEncoderFactory::StreamKey,
                GSCFBlock<Serializable::ObjectID> > GSCEFBase;

            /*! \brief Interface for an encoder factory

            Creates encoders for nodes within a tree.
            */
            class SM_COREDATA_API GenericSerializableCompressorEncoderFactory : public GSCEFBase
            {
            public:
                /*! \brief Returns a new encoder for \a key 

                \param key The node within tree that needs to be encoded
                \return An encoder instance or NULL if the key cannot be handled.
                Ownership of the instance is transferred to the caller.
                */
                SerializableCompressorEncoder* newEncoder(const StreamKey& key) const
                {
                    const EncoderInfo* info = getEncoderInfo(key);
                    if (info)
                        return info->first->create();

                    return 0L;
                }

                /*! \brief Returns the number of frames the stream is kept alive waiting for data */
                int encoderLingerInterval(const StreamKey& key) const
                {
                    const EncoderInfo* info = getEncoderInfo(key);
                    if (info)
                        return info->second;

                    return 0L;
                }

                /*! \brief Returns true if there is an encoder available for \a key */
                bool haveEncoder(const StreamKey& key) const
                {
                    return getEncoderInfo(key) != 0L;
                }

                /*! \brief Registers a decoder via its type.

                    The default constructor is used to initialize the encoder.
                    If the codec id was previously registered it is overwritten.

                    \todo Finish documenting this class.
                */
                template<class Encoder, class Key>
                void registerEncoder(const Key& key, int linger = DO_NOT_LINGER)
                {
                    typedef typename detail::BaseType<Key, GSCEFBase>::type BaseType;
                    static_cast<BaseType*>(this)->registerEncoder<Encoder>(key, linger);
                }

                /*! \brief Registers an encoder with a creation functor.

                    If the codec id was previously registered it is overwritten.

                    \param key The codec id.
                    \param creator The functor(SerializableCompressorEncoder*(void)) for creating the decoder.
                    \param linger To be documented.
                    \pre creator is not NULL.
                    \todo Finish documenting this class.
                */
                template<class Key, class CreatorImpl>
                void registerEncoder(const Key& key, CreatorImpl creator, int linger = DO_NOT_LINGER)
                {
                    typedef typename detail::BaseType<Key, GSCEFBase>::type BaseType;
                    static_cast<BaseType*>(this)->registerEncoder(key, creator, linger);
                }

                /*! \brief Removes all registred codecs
                */
                void clear();
            };
        }
    }
}

#endif //SM_COREDATA_EOD_GENERICSERIALIZABLECOMPRESSORENCODERFACTORY_H

