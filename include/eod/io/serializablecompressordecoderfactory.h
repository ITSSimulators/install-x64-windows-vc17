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
#ifndef SM_COREDATA_EOD_SERIALIZABLECOMPRESSORDECODERFACTORY_H
#define SM_COREDATA_EOD_SERIALIZABLECOMPRESSORDECODERFACTORY_H

//! \file
#include "serializablecompressordecoder.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            /*! \brief Factory for creating decoders.
          
                Each CompressedSerializable contains streams encoded with a codec.
                This factory is used to instantiate a decoder for handling the data
                within a stream.

            */
            class SM_COREDATA_API SerializableCompressorDecoderFactory
            {
            public:
                SerializableCompressorDecoderFactory();

                ~SerializableCompressorDecoderFactory();

                /*! \brief Registers a decoder via its type.
                    The default constructor is used to initialize the codec.
                    If the codec id was previously registered it is overwritten.

                    \param id The codec id.
                */
                template<class Decoder>
                void registerDecoder(CodecID id)
                {
                    const DecoderCreatorPtr decoder_creator(new NewCreator<Decoder>());
                    registerDecoderImpl(id, decoder_creator);
                }

                /*! \brief Registers a decoder with a creation functor.

                    If the codec id was previously registered it is overwritten.

                    \param id The codec id.
                    \param creator The functor(SerializableCompressorDecoder*(void)) for creating the decoder.
                    \pre creator is not NULL.
                */
                template<class CreatorImpl>
                void registerDecoder(CodecID id, CreatorImpl creator)
                {
                    //COREDATA_PRECONDITION(creator, "creator cannot be NULL");
                    const DecoderCreatorPtr decoder_creator(new CreatorWrapper<CreatorImpl>(creator));
                    registerDecoderImpl(id, decoder_creator);
                }

                /*! \brief Creates a decoder for the codec id.

                    \return A decoder or NULL if \a id is unknown. Ownership
                        of the decoder is transferred to the caller.
                */
                SerializableCompressorDecoder* newDecoder(CodecID id) const;

                /*! \brief Checks if a codec has been registered

                    \param id A codec id to lookup
                    \return true if the codec was registered with registerDecoder
                */
                bool haveDecoder(CodecID id) const;

            private:

                struct SM_COREDATA_API Creator
                {
                    virtual SerializableCompressorDecoder* create() COREDATA_PURE_METHOD;
                    virtual ~Creator();
                };
                typedef boost::shared_ptr<Creator> DecoderCreatorPtr;

                void registerDecoderImpl(CodecID id, const DecoderCreatorPtr& creator);

                template<class Decoder>
                struct NewCreator : Creator
                {
                    Decoder* create() 
                    {                 
                        return new Decoder(); 
                    }
                };

                template<class CreatorImpl>
                struct CreatorWrapper : Creator
                {
                    CreatorWrapper(CreatorImpl impl) : _impl(impl) {}
                    SerializableCompressorDecoder* create()
                    {
                        return _impl();
                    }
                    CreatorImpl _impl;
                };

                typedef std::map<CodecID, DecoderCreatorPtr> CreatorStore;
                CreatorStore _creators;
            };
        }
    }
}

#endif //SM_COREDATA_EOD_SERIALIZABLECOMPRESSORDECODERFACTORY_H

