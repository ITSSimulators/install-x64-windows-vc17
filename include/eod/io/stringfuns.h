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
#ifndef SM_COREDATA_EOD_STRINGFUNS_H
#define SM_COREDATA_EOD_STRINGFUNS_H

//! @file
#include <locale>
#include <sstream>

namespace sm
{
    namespace eod
    {
        namespace io
        {
            /*!
                @name String Utility Functions
            */
            //@{

            /*! Any characters outside the 'narrow' range will be converted to '?'.
                If UNICODE is not enabled, this function will just copy dst to src. */
            inline void narrow(const std::wstring& src, std::string& dst)
            {
                std::locale loc1;
                dst.resize(src.length());
                std::use_facet<std::ctype<wchar_t> > ( loc1 ).narrow(&src[0], &src[0] + src.length(), '?', &dst[0]);
            }
            /*! Any characters outside the 'narrow' range will be converted to '?'.
                If UNICODE is not enabled, this function will just copy dst to src. */
            inline void narrow(const std::string& src, std::string& dst)
            {
                dst = src;
            }
        
            //! Convenience function that is less efficient than the above function
            inline std::string narrow(const std::wstring& src)
            {
                std::string ret_val;
                narrow(src, ret_val);
                return ret_val;
            }
            //! Convenience function that is less efficient than the above function
            inline std::string narrow(const std::string& src)
            {
                return src;
            }
        
            //! Convert narrow string to wide string. 
            inline void widen(const std::wstring& src, std::wstring& dst)
            {
                dst = src;
            }

            //! Convert narrow string to wide string. 
            inline void widen(const std::string& src, std::wstring& dst)
            {
                std::locale loc1;
                dst.resize(src.length());
                std::use_facet<std::ctype<wchar_t> > ( loc1 ).widen(&src[0], &src[0] + src.length(), &dst[0]);
            }
        
            //! Convenience function that is less efficient than the above function
            inline std::wstring widen(const std::string& src)
            {
                std::wstring ret_val;
                widen(src, ret_val);
                return ret_val;
            }
        
            //! Ensures the string is terminated by a single carriage-return.
            template <class T>
            std::basic_string<T> singleCR(const std::basic_string<T>& str)
            {
                const T CR('\n');
                std::basic_string<T> res(str);
        
                // remove any CR at end of string (may be multiple) 
                while (!res.empty() && *res.rbegin() == CR)
                {
                    res.erase(res.size()-1);
                }
        
                // append single CR
                res.append(1,CR);
        
                return res;
            }
        
            //! Converts a string to lowercase
            template <class T>
            inline T& tolower(T& str) 
            {
                std::transform(str.begin(),str.end(),str.begin(),::tolower); 
                return str; 
            }
        
            //! Returns lowercase version of @a str
            template <class T>
            inline T lower(const T& str) 
            {
                std::string l(str);
                std::transform(l.begin(),l.end(),l.begin(),::tolower); 
                return l; 
            }
        
            //! Converts a std::string to uppercase
            template <class T>
            inline T& toupper(T& str) 
            { 
                std::transform(str.begin(),str.end(),str.begin(),::toupper); 
                return str; 
            }
        
            //! Returns uppercase version of @a str
            template <class T>
            inline T upper(const T& str) 
            {
                std::string l(str);
                std::transform(l.begin(),l.end(),l.begin(),::toupper); 
                return l; 
            }
        
            //! Works with anything defining a toupper and comparison operator.
            template <class T>
            inline bool noCaseCompare(const T& s1, const T& s2) 
            {
                return upper(s1) == upper(s2);
            }
        
            //! Convert primitive type to string representation.
            /*  @param val value to convert
                @param precision number of decimals for floating point number.
                       Default value for string stream is used if this is not specified.
                      (unless \a flags is general, in which case it is the number of digits)
                @param flags standard c++ format flags passed to a stringstream.
                @deprecated use toString(...)
            */
            template<class T> 
            inline std::string 
            num2str(T val, int precision = -1, std::ios_base::fmtflags flags = std::ios_base::fixed)
            {
                std::stringstream s;
                s.setf(flags);
                s.precision(precision);
                s << val;
                return s.str(); 
            }
        
            /*! Replaces each occurance of a character that is in @a chars_to_replace
                that is found in the string @a src, with the string @a replace_with_string.
                @param chars_to_replace Set of characters that are to be replaced if found in @a src
                @param replace_with_string Replaces each occurance
                @param src The string to scan. */
            template<class CharType> 
            inline std::basic_string<CharType>
            replaceChars(const std::basic_string<CharType>& chars_to_replace, 
                         const std::basic_string<CharType>& replace_with_string, 
                         const std::basic_string<CharType>& src)
            {
                std::basic_string<CharType> result;
                typename std::basic_string<CharType>::const_iterator it;
                for (it=src.begin(); it!=src.end(); ++it)
                {
                    if (chars_to_replace.find(*it)!=std::basic_string<CharType>::npos)
                        result.append(replace_with_string);
                    else
                        result.push_back(*it);
                }
                return result;
            }
            //@}
        }
    }
}
#endif

