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
#ifndef SM_COREDATA_EOD_ENGINEOUTPUTBASE_H
#define SM_COREDATA_EOD_ENGINEOUTPUTBASE_H

//! @file
#include "eod/serializablecomposite.h"

namespace sm
{
    namespace eod
    {
        //! Indexes for data values that are logged individually for each eye
        /*!
        */
        enum EyeId 
        { 
            RIGHT_EYE=0,            //!< Index of the right eye (of the person)
            LEFT_EYE,               //!< Index of the left eye (of the person)
            BOTH_EYES               //!< Internal index used to tag data common to both eyes
        };
    
        //! Base class for data objects output by the tracking engine
        /*!
        */
        class SM_COREDATA_API EngineOutputBase : public SerializableComposite
        {
            COREDATA_MEMORY_ALLOCATORS(EngineOutputBase)

        public:
    
            /*
            */
            enum 
            {
                ARRAY_SIZE_2D_DATA = 2,   //!< 2D data points need arrays this big
                ARRAY_SIZE_3D_DATA = 3,   //!< 3D data points need arrays this big
                ARRAY_SIZE_4D_DATA = 4,   //!< 4D data points need arrays this big
                ARRAY_SIZE_PAIR_DATA = 2  //!< data pairs need arrays this big
            };
    
            //! EngineOutputData objects are *invalid* by default
            EngineOutputBase();

            //! @return whether this object will be serialized or not.
            /*! This is true by default */
            virtual bool serializeEnabled() const;
    
            //! Set whether or not the object will be serialized.
            /*!

            */
            void setSerializeEnabled(bool enabled);
    
            //! Set sub-object serialization enabled by object-id. 
            /*!
                By default, sub-objects are serializeEnabled() and will be serialized.\n
                Any attached sub-object with an id not in this vector will be 
                setSerializeEnabled(false) preventing it from being serialized.
                @param valid_object_ids List of object-ids to enable serialization for.
                @param recursive whether to recurse into sub-object tree. 
                    Note that only valid objects are recursed into. If recursive is true
                    then the only sub objects that will be serialized will be the objects
                    that can be traversed with all object ids in valid_object_ids.

@verbatim
    1
   / \
  2   3
 /   / \
4   5   6
If this method is called on object marked as 1 and the vector of
objects ids is [3, 4]. Then objects 2 will be set false, object 4 will
be untouched, object 3 will be set true and obects 5 and 6 will be set false.
The only sub object serialized would be object 3.
@endverbatim

            */
            void setSerialableSubObjectsEnabled(const ObjectIDVec& valid_object_ids, bool recursive = false);
    
    
            //! Returns the size of the _valid flag, plus the size returned by numEngineSpecificDataBytes
            virtual uint32 numOwnDataBytes() const;
    
            /*! @param eye_id Eye
                @return Textual representation of the particular eye(s).
                @pre eye_id is either LEFT_EYE, RIGHT_EYE or BOTH_EYES.
                @pre dynamic initialization has occured for this library. This function
                    returns a reference to objects which require dynamic initialization.

             */
            static const std::string& eyeIdName(EyeId eye_id);
    
        protected:
            EngineOutputBase(const EngineOutputBase& rhs);
    
            //! Copies _valid and calls base class assignent operator
            /*! @param rhs An instance of EngineOutputBase subtype to copy.
                @return This EngineOutputBase instance.
             */
            EngineOutputBase& operator=(const EngineOutputBase& rhs);
    
            //! Appends the _valid flag, then calls appendEngineSpecificData
            virtual void appendOwnData(std::vector<uint8>& buffer) const;
    
            //! Reads the _valid flag, then calls readEngineSpecificData
            virtual void readOwnData(const std::vector<uint8>& buffer, int& read_pos);
    
            //! Append any further object-specific data members in a derived class
            virtual void appendEngineSpecificData(std::vector<uint8>& buffer) const COREDATA_PURE_METHOD;
    
            //! Read any further object-specific data members in a derived class
            virtual void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_pos) COREDATA_PURE_METHOD;
    
            /*! @return the number of object-specific data members in a derived class */
            virtual uint32 numEngineSpecificDataBytes() const COREDATA_PURE_METHOD;
    
            //! Overide to verify @a sub_object is an EngineOutputBase derived object.
            /*!
                @throw SerializableError if the object id already exists or the
                    object id is not valid for this object or sub_object is not derived 
                    from EngineOutputBase.
            */
            virtual void doAddSubObject(const boost::shared_ptr<Serializable>& sub_object);
        private:
            //! Valid flag
            int8 _valid;
        };
        typedef boost::shared_ptr<EngineOutputBase> EngineOutputBasePtr;
        typedef boost::shared_ptr<const EngineOutputBase> ConstEngineOutputBasePtr;
    }
}
#endif

