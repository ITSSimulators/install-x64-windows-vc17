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
#ifndef SM_COREDATA_EOD_SERIALIZABLECOMPOSITE_H
#define SM_COREDATA_EOD_SERIALIZABLECOMPOSITE_H

//! @file
#include "eod/serializable.h"
#include "eod/serializablefactory.h"

namespace sm
{
    namespace eod
    {

        //! Index into a sequence of Serializable objects.
        typedef uint8 ObjectIndex;
    
        //! Serializable object that is composed of many other Serializable sub-objects. 
        /*!
            When this class is Serialized/Unserialized, it applies the same 
            operation to it's sub-objects.
            For a complete UML diagram of the Serializable/EngineOutputData hierachy, see
            <A HREF="serializablecomposite.htm">
            serializablecomposite.htm</A> in the doc/html directory

        */
        class SM_COREDATA_API SerializableComposite : public Serializable
        {
            COREDATA_MEMORY_ALLOCATORS(SerializableComposite)
    
        public:
    
            //! Deletes all sub-objects
            virtual ~SerializableComposite();
    
            //! Number of bytes of data required to serialize class.
            /*!
                Returns total size of all child classes (including their header bytes, but not
                the header bytes of the composite class). This value will change every time a 
                sub-object is added to the composite 
            */
            virtual uint32 numDataBytes() const;
    
            /*! @return a pointer to a serializable sub-object, or NULL if no
                object with the given ID exists
                @param object_id ID of the sub_object to return

            */
            ConstSerializablePtr subObject(ObjectID object_id) const;
            SerializablePtr subObject(ObjectID object_id);

            /*! @return a pointer to a serializable sub-object, or NULL if no
                object with the given ID exists
                @param object_id ID of the sub_object to return
                @param index The zero-based index specifying which subobject to return.

            */
            ConstSerializablePtr subObjectAtIndex(ObjectID object_id, ObjectIndex index) const;
            SerializablePtr subObjectAtIndex(ObjectID object_id, ObjectIndex index);

            //! @return true if an object of @a object_id exists.
            /*!
            */
            bool hasSubObjectID(ObjectID object_id) const;
    
            /*! @return a pointer to a sub-object of a specific child type, or NULL if no such sub-object exists. */
            template <class SubObjectType>
            boost::shared_ptr<const SubObjectType> subObjectAtIndex(ObjectID object_id, ObjectIndex index) const
            {
                ConstSerializablePtr child(subObjectAtIndex(object_id, index));
                if (child)
                {
                    boost::shared_ptr<const SubObjectType> sub_object_ptr(boost::dynamic_pointer_cast<const SubObjectType>(child));
                    if (!sub_object_ptr)
                    {
                        throw SerializableError("SerializableComposite::subObject() - programming error. ID does not match object type");
                    }
                    return sub_object_ptr;
                }
                return boost::shared_ptr<const SubObjectType>();
            }

            template <class SubObjectType>
            boost::shared_ptr<SubObjectType> subObjectAtIndex(ObjectID object_id, ObjectIndex index)
            {
                SerializablePtr child(subObjectAtIndex(object_id, index));
                if (child)
                {
                    boost::shared_ptr<SubObjectType> sub_object_ptr(boost::dynamic_pointer_cast<SubObjectType>(child));
                    if (!sub_object_ptr)
                    {
                        throw SerializableError("SerializableComposite::subObject() - programming error. ID does not match object type");
                    }
                    return sub_object_ptr;
                }
                return boost::shared_ptr<SubObjectType>();
            }

            /*! @return a pointer to a sub-object of a specific child type, or NULL if no such sub-object exists. */
            template <class SubObjectType>
            boost::shared_ptr<const SubObjectType> subObject(ObjectID object_id) const
            {
                return this->subObjectAtIndex<SubObjectType>(object_id, 0);
            }

            template <class SubObjectType>
            boost::shared_ptr<SubObjectType> subObject(ObjectID object_id)
            {
                return this->subObjectAtIndex<SubObjectType>(object_id, 0);
            }

            template <class SubObjectType>
            boost::shared_ptr<const SubObjectType> subObjectAtIndex(ObjectIndex index) const
            {
                return subObjectAtIndex<SubObjectType>(SubObjectType::THIS_OBJECT_ID, index);
            }

            template <class SubObjectType>
            boost::shared_ptr<SubObjectType> subObjectAtIndex(ObjectIndex index)
            {
                return subObjectAtIndex<SubObjectType>(SubObjectType::THIS_OBJECT_ID, index);
            }

            template <class SubObjectType>
            boost::shared_ptr<const SubObjectType> subObject() const
            {
                return subObjectAtIndex<SubObjectType>(SubObjectType::THIS_OBJECT_ID, 0);
            }

            template <class SubObjectType>
            boost::shared_ptr<SubObjectType> subObject()
            {
                return subObjectAtIndex<SubObjectType>(SubObjectType::THIS_OBJECT_ID, 0);
            }


            /*! Adds a child object to this object.
                @param sub_object shared pointer to a Serializable derived object. If
                    the pointer is NULL then the function call does nothing.
                @throw SerializableError if the object id already exists or the
                    object id is not valid for this object.

            */
            void addSubObject(const SerializablePtr& sub_object);

            //! Create and adds a new object of type SubObjectType.
            /*!
                @return The new or existing sub-object. 
                @throw SerializableError if an error occured when unserializing from the buffer
                @throw SerializableError if the object id already exists or the
                    object id is not valid for this object, or the SerializableFactory
                    produced an object using @a object_id that is not castable to
                    SubObjectType.
                @see addSubObject(const SerializablePtr&)
            */
            template <class SubObjectType>
            boost::shared_ptr<SubObjectType> addSubObject(ObjectID object_id)
            {
                boost::shared_ptr<SubObjectType> sub_object(SerializableFactory::newObject<SubObjectType>(object_id));
                if (!sub_object)
                {
                    throw SerializableError("SerializableComposite::addSubObject - unable to create object or object not castable to type");
                }
                addSubObject(sub_object);
                return sub_object;
            }

            //! Create and adds a new object of type SubObjectType.
            /*!
                SubObjectType must have the constant THIS_OBJECT_ID defined.
                @return The new sub-object. 
                @throw SerializableError if the object id already exists or the
                    object id is not valid for this object, or the SerializableFactory
                    produced an object using @a object_id that is not castable to
                    SubObjectType.
             */
            template <class SubObjectType>
            boost::shared_ptr<SubObjectType> addSubObject()
            {
                return addSubObject<SubObjectType>(SubObjectType::THIS_OBJECT_ID);
            }

            //! Create and add a new object by object id if it does not already exist.
            /*!
                @return The new or existing sub-object. 
                @throw SerializableError if the object did not exist and the
                    object id is not valid for this object, or the SerializableFactory
                    produced an object using @a object_id that is not castable to
                    SubObjectType.
            */
            template <class SubObjectType>
            boost::shared_ptr<SubObjectType> addIfMissing(ObjectID object_id)
            {
                boost::shared_ptr<SubObjectType> sub_object(subObject<SubObjectType>(object_id));
                if (!sub_object)
                {
                    sub_object = addSubObject<SubObjectType>(object_id);
                }
                return sub_object;
            }

            //! Create and add a new object of type SubObjectType if does not already exist.
            /*!
                SubObjectType must have the constant THIS_OBJECT_ID defined.
                @return The new or existing sub-object. 
                @throw SerializableError if the object did not exist and the
                    object id is not valid for this object, or the SerializableFactory
                    produced an object using @a object_id that is not castable to
                    SubObjectType.
            */
            template <class SubObjectType>
            boost::shared_ptr<SubObjectType> addIfMissing()
            {
                return addIfMissing<SubObjectType>(SubObjectType::THIS_OBJECT_ID);
            }
 
            /*!
                @return the number of sub-objects that have been added to this SerializableComposite 

            */
            uint8 numSubObjects() const;
    
            /*!
                @return the number of sub-objects that have been added to this SerializableComposite 

            */
            uint8 numSubObjects(ObjectID object_id) const;
   
            template <class T>
            uint8 numSubObjects() const
            {
                return this->numSubObjects(T::THIS_OBJECT_ID);
            }

            /*! @see Serializable::printLine */
            virtual void printLine(std::ostream& s) const;
    
            //! @see Serializable::printHeader
            /*! Calls printOwnHeader(), then calls printHeader() on each of it's sub-objects */
            virtual void printHeader(std::ostream& s) const;
    
            /*!
                @return The number of sub-objects that are valid 

            */
            uint8 numValidSubObjects() const;
    
            typedef std::vector<SerializablePtr> SerializablePtrVec;
            typedef std::vector<ConstSerializablePtr> ConstSerializablePtrVec;

            /*!
                @return vector of shared pointers to child sub-objects 

            */
            ConstSerializablePtrVec subObjects() const;
            SerializablePtrVec subObjects();

            /*!
                @return vector of shared pointers to child sub-objects 
            */
            ConstSerializablePtrVec subObjects(ObjectID object_id) const;
            SerializablePtrVec subObjects(ObjectID object_id);
    
            /*! \brief Removes a sub-object from this composite object.

                \param sub_object The object to remove
                \return a pointer to the extracted sub-object
                \throw SerializableError if \a sub_object is not present.
            */
            void removeSubObject(const Serializable& sub_object);

            /*! 
                Removes a sub-object from this composite object.  
                @return a pointer to the extracted sub-object, or NULL if there is no
                sub-object corresponding to @a object_id

            */
            SerializablePtr removeSubObject(ObjectID object_id);

            /*! 
                Removes a sub-object from this composite object.  
                @return a pointer to the extracted sub-object, or NULL if there is no
                sub-object corresponding to object_id

            */
            SerializablePtr removeSubObjectAtIndex(ObjectID object_id, ObjectIndex index);
    
            /*! 
                Method that returns the size (in bytes) of the data that is owned
                by this object (as opposed to sub-objects). You need to overload this method if you want to add
                any extra data to a derived class

            */
            virtual uint32 numOwnDataBytes() const;
    
            //! Method to print a header for data belonging to this object
            /*! You need to overload this method if you are adding any extra data to a derived class */
            virtual void printOwnHeader(std::ostream& s) const COREDATA_PURE_METHOD;

            //! Clear and destroy the contents of _sub_objects;
            void clearSubObjects();
    
        protected:
            SerializableComposite();

            //! Makes a deep copy of all sub-objects.
            SerializableComposite(const SerializableComposite& rhs);
    
            //! Makes a deep copy of all sub-objects.
            SerializableComposite& operator=(const SerializableComposite& rhs);
    
    
            //! Append each sub-object's serialized state to the buffer
            virtual void appendBuffer(std::vector<uint8>& buffer) const;
    
            /*! Reads each sub-object's class data from the buffer and
                increments \a read_pos_inout by the number of bytes read.
                @throw SerializableError if the buffer is too small, data size in header
                    was less than amount of data required for object, duplicate sub-object
                    ids were found.
            */
            virtual void readFromBuffer(const std::vector<uint8>& buffer, int& read_pos_inout);
            virtual void readFromBufferWithStatus(const std::vector<uint8>& buffer, int& read_pos_inout, DeserializationStatusFlags& status_inout);
    
            /*! Method that appends any data that is owned by this object (as opposed to a
                sub-object) to the buffer. You need to overload this method if you want to add
                any extra data to a derived class */
            virtual void appendOwnData(std::vector<uint8>& buffer) const;
    
            /*! Method that reads any data that is owned by this object (as opposed to a
                sub-object) from the buffer. You need to overload this method if you want to add
                any extra data to a derived class */
            virtual void readOwnData(const std::vector<uint8>& buffer, int& read_pos);
    
            /*! Map between Serializable object ids and the objects they represent.
                An STL map is used to ensure a consistent ordering of bytes when serialized 
            */
            typedef std::multimap<ObjectID, SerializablePtr> SerializableMap;
    
            /*! 
                @return map containing all sub-objects, ordered by ID 

                Function is non-const as the objects in the map are non-const.
                Enforces logical const-ness.
            */
            const SerializableMap& subObjectMap();
    
            //! Print this objects own data to the output data stream s as text
            virtual void printOwnData(std::ostream& s) const COREDATA_PURE_METHOD;

            /*! Add Serializable sub-object to the composite object
                @param sub_object A non-null shared pointer to a Serializable derived object. 
                @throw SerializableError if the object id already exists or the
                    object id is not valid for this object.
                @note Derived classes can restrict which types of sub-objects can be
                    by overriding this function. If the object is not to be added then
                    don't call this function and throw a SerializableError instead.
            */
            virtual void doAddSubObject(const SerializablePtr& sub_object);
   
            //! Indicates whether multiple sub-objects with the same objectID() can exist.
            /*!
                Unless overridden this returns @b false.
                \deprecated All objects now support duplicates.
            */
            virtual COREDATA_DEPRECATED("All objects support duplicates") bool allowDuplicateSubObjects() const;

            //! Throws a duplicate sub object exception
            /*!
                @throw SerializableError with a message indicating a subobject with
                    the same ObjectID already exists.
            */
            void throwDuplicateSubObject();
        private:
            //! Copy the data from rhs into this object
            void copyFrom(const SerializableComposite& rhs);
            //! Performs validity checks and then inserts a subobject
            /*!
                if @a sub_object is NULL then nothing is done, otherwise,
                checks are done and the object is then inserted at the end
                of the range of sub-objects matching sub_object->objectID().

                @throw SerializableError Attempt to add an object to itself,
                    there exists 255 sub objects, forbidDuplicateSiblings() 
                    returned true and the object already exists.
            */
            void insertSubObject(const SerializablePtr& sub_object);
            
            /*! \brief Throws duplicate object exception if there is another object of the same id

                \param insert The insertion position. Must be upper_bound.
                \param object_id The Object ID to check for.
                \throw SerializableError The object previous to \a insert has objectID() == \a object_id.
            */
            void throwIfDuplicate(SerializableMap::iterator insert, ObjectID object_id);

    
            typedef std::pair<SerializableMap::iterator, SerializableMap::iterator> IteratorRange;
            typedef std::pair<SerializableMap::const_iterator, SerializableMap::const_iterator> ConstIteratorRange;

            //! The sub-objects, ordered by object ID.
            SerializableMap _sub_objects;
        };
        typedef boost::shared_ptr<const SerializableComposite> ConstSerializableCompositePtr;
        typedef boost::shared_ptr<SerializableComposite> SerializableCompositePtr;
    }
}
#endif


