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

#include <boost/detail/endian.hpp>

#include <algorithm>

#if   defined(BOOST_LITTLE_ENDIAN)
#define XPLATCOPY std::copy
#elif defined(BOOST_BIG_ENDIAN)
#define XPLATCOPY std::reverse_copy
#else
#error unknown endianness
#endif

namespace sm
{
    namespace eod
    {
        namespace io
        {
            namespace detail
            {
                template<typename Iter, typename IterCat = typename std::iterator_traits<Iter>::iterator_category>
                struct iter_value_type
                {
                    typedef typename std::iterator_traits<Iter>::value_type type;
                };
                template<typename Iter>
                struct iter_value_type<Iter, std::output_iterator_tag>
                {
                    typedef typename Iter::container_type::value_type type;
                };

                template<typename T>
                struct remove_const
                {
                    typedef T type;
                };

                template<typename T>
                struct remove_const<const T>
                {
                    typedef typename remove_const<T>::type type;
                };
            }

            //NOTE: this function only handles endianness, choose platform independent types
            template<class InIter, class OutIter>
            inline OutIter xplatcopy(InIter first, InIter last, OutIter out)
            {
                return XPLATCOPY(first, last, out);
            }

            //NOTE: this function only handles basic types
            template<class T, class OutIter>
            inline OutIter xplatwrite(T& t, OutIter out)
            {
                typedef typename detail::iter_value_type<OutIter>::type* PType;
                return xplatcopy(reinterpret_cast<PType>(&t), reinterpret_cast<PType>(&t+1), out);
            }

            //NOTE: this function only handles basic types
            template<class T, class InIter>
            inline InIter xplatread(T& t, InIter data)
            {
                typedef typename detail::iter_value_type<InIter>::type VType;
                typedef typename detail::remove_const<VType>::type* PType;
                xplatcopy(data, data + sizeof(T), reinterpret_cast<PType>(&t));
                return data + sizeof(T);
            }

            template<class T>
            struct ImmediateValueWriter
            {
                ImmediateValueWriter(T& value, std::vector<uint8>& buffer)
                {
                    xplatwrite(value, std::back_inserter(buffer));
                }
            };

            template<class T>
            struct DelayedValueWriter
            {
                DelayedValueWriter(T& value, std::vector<uint8>& buffer) : _buffer(buffer), _value(value)
                {
                    _offset = _buffer.size();
                    _buffer.resize(_buffer.size() + sizeof(T));
                }

                ~DelayedValueWriter()
                {
                    xplatwrite(_value, &_buffer[_offset]);
                }

                T& _value;
                std::vector<uint8>& _buffer;
                std::size_t _offset;
            };
        }
    }
}

#undef XPLATCOPY

