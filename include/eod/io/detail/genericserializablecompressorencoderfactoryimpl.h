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
#error must be included from within "genericserializablecompressorencoderfactory.h"
#endif

#include "eod/io/serializablecompressorencoderfactory.h"

namespace sm
{
    namespace eod
    {
        namespace io
        {
            template<class Key, class Base> class GSCFBlock;
            

            namespace detail
            {
                class SM_COREDATA_API GSCFBase : public SerializableCompressorEncoderFactory
                {
                protected:
                    typedef EncoderCreator Creator;

                    template<class Encoder>
                    struct NewCreator : Creator
                    {
                        Encoder* create() 
                        {                 
                            return new Encoder(); 
                        }
                    };

                    template<class CreatorImpl>
                    struct CreatorWrapper : Creator
                    {
                        CreatorWrapper(CreatorImpl impl) : _impl(impl) {}
                        SerializableCompressorEncoder* create()
                        {
                            return _impl();
                        }
                        CreatorImpl _impl;
                    };

                    typedef std::pair<EncoderCreatorPtr, int> EncoderInfo;

                    const EncoderInfo* getEncoderInfo(const StreamKey&) const { return 0L; }
                    void clear() {}
                };

                template<class Key, class T>
                struct BaseType {};

                template<class Key1, class Key2, class Base>
                struct BaseType<Key1, GSCFBlock<Key2, Base> >
                {
                    typedef typename BaseType<Key1, Base>::type type;
                };

                template<class Key, class Base>
                struct BaseType<Key, GSCFBlock<Key, Base> >
                {
                    typedef GSCFBlock<Key, Base> type;
                };
            }

            template<class Key>
            struct GSCFKeyConverter
            {
                static Key convert(const SerializableCompressorEncoderFactory::StreamKey& key) { return Key(key); }
            };

            template<class Key, class Base = detail::GSCFBase>
            class GSCFBlock : public Base
            {
            public:
                template<class Encoder>
                void registerEncoder(const Key& key, int linger)
                {
                    registerEncoderImpl(key, EncoderCreatorPtr(new detail::GSCFBase::NewCreator<Encoder>()), linger);
                }

                template<class CreatorImpl>
                void registerEncoder(const Key& key, CreatorImpl creator, int linger)
                {
                    registerEncoderImpl(key, EncoderCreatorPtr(new detail::GSCFBase::CreatorWrapper<CreatorImpl>(creator)), linger);
                }

                void registerEncoder(const Key& key, const EncoderCreatorPtr& creator, int linger)
                {
                    registerEncoderImpl(key, creator, linger);
                }

            protected:

                const detail::GSCFBase::EncoderInfo* getEncoderInfo(const SerializableCompressorEncoderFactory::StreamKey& key) const
                {
                    Key myKey(GSCFKeyConverter<Key>::convert(key));
                    typename EncoderInfoStore::const_iterator pos = _encoderInfo.find(myKey);

                    if (pos == _encoderInfo.end())
                        return Base::getEncoderInfo(key);

                    return &pos->second;
                }

                void clear()
                {
                    _encoderInfo.clear();
                    Base::clear();
                }

            private:
                void registerEncoderImpl(const Key& key, const EncoderCreatorPtr& creator, int linger)
                {
                    _encoderInfo[key] = std::make_pair(creator, linger);
                }


            private:
                typedef std::map<Key, detail::GSCFBase::EncoderInfo> EncoderInfoStore;
                EncoderInfoStore _encoderInfo;
            };
        }
    }
}

