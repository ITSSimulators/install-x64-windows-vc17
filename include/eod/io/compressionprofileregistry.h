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
#ifndef SM_COREDATA_EOD_COMPRESSIONPROFILEREGISTRY_H
#define SM_COREDATA_EOD_COMPRESSIONPROFILEREGISTRY_H

//! \file
#include "eod/serializable.h"
#include "eod/io/filewriter.h"
#include "eod/io/genericserializablecompressorencoderfactory.h"
#include "eod/io/serializablecompressordecoderfactory.h"
#include <set>

namespace sm
{
    namespace eod
    {
        namespace io
        {

            /*! \brief Combination of compression type and compression time.
            */
            enum CompressionProfile
            {
                // compression type
                COMPRESSION_PROFILE_UNCOMPRESSED = 0x00,
                COMPRESSION_PROFILE_LOSSY        = 0x40,
                COMPRESSION_PROFILE_LOSSLESS     = 0x80,
                COMPRESSION_PROFILE_TYPE_MASK    = COMPRESSION_PROFILE_LOSSY | COMPRESSION_PROFILE_LOSSLESS,
                

                // compression time
                COMPRESSION_PROFILE_REALTIME     = 0x8,
                COMPRESSION_PROFILE_GOOD_QUALITY = 0x10,
                COMPRESSION_PROFILE_BEST_QUALITY = 0x18,
                COMPRESSION_PROFILE_TIME_MASK    = COMPRESSION_PROFILE_REALTIME | COMPRESSION_PROFILE_GOOD_QUALITY | COMPRESSION_PROFILE_BEST_QUALITY,

                COMPRESSION_PROFILE_LOSSLESS_REALTIME = COMPRESSION_PROFILE_LOSSLESS | COMPRESSION_PROFILE_REALTIME,
                COMPRESSION_PROFILE_LOSSY_REALTIME    = COMPRESSION_PROFILE_LOSSY | COMPRESSION_PROFILE_REALTIME,

            };

            typedef uint32 CompressionProfileValue;

            struct SM_COREDATA_API EncoderCreationInfo
            {
                //! Object to create the encoder.
                sm::eod::io::EncoderCreatorPtr creator;

                //! Stream key if matchType() == MATCH_PATH
                SerializableCompressorEncoderFactory::StreamKey key;

                //! Object ID to match or 0 for root encoder.
                Serializable::ObjectID object_id;

                //! Linger parameter for encoder.
                size_t linger;

                /*! \brief Constructor for root encoder

                    \param creator Encoder creator factory.
                */
                EncoderCreationInfo(const sm::eod::io::EncoderCreatorPtr& creator);

                /*! \brief Constructor for encoder for a specific object id.

                    \param creator Encoder creator factory.
                    \param object_id The object_id the creator encodes.
                    \param linger The linger parameter.

                    \todo Add reference to linger info.
                */
                EncoderCreationInfo(const sm::eod::io::EncoderCreatorPtr& creator,
                    Serializable::ObjectID object_id,
                    size_t linger);

                //! The kind of matching this object requires.
                enum MatchType
                {
                    MATCH_ALL,
                    MATCH_OBJECT_ID,
                    MATCH_PATH
                };

                /*! \brief Returns the type of match this instance performs.

                    An EncoderCreationInfo can match all object ids for a
                    root encoder, a specific object_id or a particular object
                    path.
                */
                MatchType matchType() const;

                /*! \brief Key Comparison class

                    Orders by MATCH_ALL, MATCH_OBJECT_ID, MATCH_PATH
                */
                bool operator<(const EncoderCreationInfo& rhs) const;
                bool operator==(const EncoderCreationInfo& rhs) const;

            };

            /*! \brief Default profile registry

                Contains mapping from compression profiles to the encoders used to
                compress the Serializable sub-objects.
            */
            class SM_COREDATA_API CompressionProfileRegistry
            {
            public:
                CompressionProfileRegistry();


                //! Set of encoding patterns
                typedef std::set<EncoderCreationInfo/*, KeyComp*/> EncodingProfile;
                
                /*! \brief Returns a reference to the encoders for a compression profile 
                
                    \param compression_profile The compression profile.
                    \see CompressionProfile
                */
                const EncodingProfile& encoders(CompressionProfileValue compression_profile) const;
                EncodingProfile& encoders(CompressionProfileValue compression_profile);

                /*! \brief Sets the encoders to use for a compression profile.

                    \param compression_profile The compression profile.
                    \param profile The encoders to use.
                    \see CompressionProfile
                */
                void setEncoders(CompressionProfileValue compression_profile, const EncodingProfile& profile);

                /*! \brief Removes all encoders for a compression profile.

                    This will result in no compression being used.

                    \param compression_profile The compression profile.
                    \see CompressionProfile
                */
                void clearEncoders(CompressionProfileValue compression_profile);

            private:

                typedef std::map<CompressionProfileValue, EncodingProfile> Profiles;

                // mutable to allow encoders(int compression_profile) const to return
                // a reference to an empty EncodingProfile if one is not defined.
                mutable Profiles _profiles;
            };


            /*! \brief The default compression profile registry.

                This is the registry used by default for the CompressingFileWriter unless
                overriden by a constructor taking a CompressionProfileRegistry or the 
                CompressingFileWriter::setProfileRegistry() function.
            */
            SM_COREDATA_API CompressionProfileRegistry& defaultCompressionProfileRegistry();

            /*! \brief The default decoder factory

                This is the factory used by default for the DecompressingFileReader unless
                overriden by a constructor taking a SerializableCompressorDecoderFactory or the 
                DecompressingFileReader::setDecoderFactory() function.
            */
            SM_COREDATA_API SerializableCompressorDecoderFactory& defaultDecoderFactory();

        }
    }
}

#endif




