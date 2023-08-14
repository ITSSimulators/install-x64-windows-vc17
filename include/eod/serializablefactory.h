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
#ifndef SM_COREDATA_EOD_SERIALIZABLEFACTORY_H
#define SM_COREDATA_EOD_SERIALIZABLEFACTORY_H

//! @file
#include "eod/serializable.h"

namespace sm
{
    namespace eod
    {      
         
        //! Factory for creating new Serializable objects
        /*! Factory class for Serializable objects. You can request a new object from the factory by passing in an ID.
            The factory returns a base-class pointer (allocated on the heap) that points to a new object of the type
            specified by the ID

         */
        class SM_COREDATA_API SerializableFactory
        {
        public:
            /*! \brief Creates a new, default initialized Serializable Object with the specified ID

                @param object_id ID of the object to create
                @return Pointer to the new Serializable object, or NULL if the serializable id was not recognised 
                @throw SerializableError if the ID of the new object does not match object_id
             */
            static SerializablePtr newObject(Serializable::ObjectID object_id);

            /*! \brief Creates and a new, default initialized Serializable Object with the specified ID
                \param object_id ID of the object to create.
                \param status_inout DeserializationStatusFlags to possibly update. If the \a object_id
                        is unknown then the DESERIALIZATION_UNKNOWN_OBJECT_ID bit flag is set.
                \return Pointer to the new Serializable object, or NULL if the serializable id was not recognised 
                \throw SerializableError if the ID of the new object does not match object_id
             */
            static SerializablePtr newObjectWithStatus(Serializable::ObjectID object_id, DeserializationStatusFlags& status_inout);

            //! Create and return a new, default initialized Object with the specified ID
            /*! @param object_id ID of the object to create
                @return Pointer to the new object, or NULL if the serializable id was not recognised
                        or the object is not dynamically castable to type T.
                @throw SerializableError if the ID of the new object does not match object_id
             */
            template <class T>
            static boost::shared_ptr<T> newObject(Serializable::ObjectID object_id)
            {
                return boost::shared_ptr<T>(boost::dynamic_pointer_cast<T>(newObject(object_id)));
            }

            //! Create and return a new, default initialized Object of the specified type
            /*!
                The object must define the object id as a static constant named THIS_OBJECT_ID.

                @return Pointer to the new object, or NULL if the serializable id was not recognised
                        or the object is not dynamically castable to type T.
                @throw SerializableError if the ID of the new object does not match object_id
             */
            template <class T>
            static boost::shared_ptr<T> newObject()
            {
                return newObject<T>(T::THIS_OBJECT_ID);
            }
 
            //! Returns true of there is enough data to deserialize the object at read_pos.
            /*!
                First checks if there is enough data for an object header and if so, then
                determines the data size from the header and checks that there is enough data
                in the buffer.
            */
            static bool canDeserialize(const std::vector<uint8>& buffer, int read_pos = 0);

            //! Create a new Serializable object from the contents of a buffer
            /*!
                @param buffer Buffer of bytes to initialise the object from
                @param read_pos_inout The index into \a buffer to start reading from. Updated
                    by this function to point to the position following the object unless an exception is thrown. 
                    Left unmodified if the object id is unknown or an exception is thrown.
                @return Pointer to the new Serializable object, or NULL if the object is unrecognised.
                    read_pos will point to where the next object will start.
                @throw SerializableError when:
                    insufficient data in buffer,
                    if an error occured when unserializing from the buffer.
                    Caused by malformed data within a packet. read_pos is left unmodified.

             */
            static SerializablePtr newObject(const std::vector<uint8>& buffer, int& read_pos_inout);

            /*! \brief Create a new Serializable object from the contents of a buffer.

                \param buffer Buffer of bytes to initialise the object from.
                \param read_pos_inout The index into \a buffer to start reading from. Updated
                    by this function to point to the position following the object unless there was
                    insufficient or invalid data to deserialize the object. 
                \param status_inout Status flags updated to reflect the deserialization status.
                \return Pointer to the new Serializable object, or NULL if the object is unrecognised or invalid.
                    read_pos will point to where the next object will start.
                \throw SerializableError if the factory for the object id creates an object with a different object id.
            */
            static SerializablePtr newObjectWithStatus(const std::vector<uint8>& buffer, int& read_pos_inout, DeserializationStatusFlags& status_inout);
    
            //! Create a new SerializableObject from an open input stream
            /*! @param s Input stream to read the serialized object data from. This function assumes the current
                read position is set to the start of a serialized object in the stream. This method reads one 
                Serializable object from the stream and returns it, updating the stream's read position accordingly.
                If the object's ID is unrecognised, that object will be skipped over, and a null pointer is returned
                @throw SerializableError if reading from the stream failed, or an error occured whilst 
                unserializing the buffer, or the stream is at the end of the file.
            */
            static SerializablePtr newObject(std::istream& s);

            /*! \brief Create a new SerializableObject from an open input stream.

                This function assumes the current read position is set to 
                the start of a serialized object in the stream. This method reads one 
                Serializable object from the stream and returns it, updating the 
                stream's read position accordingly. If the object's ID is 
                unrecognised, that object will be skipped over, and a null 
                pointer is returned.

                \param s            Input stream to read the serialized object data from. 
                \param status_inout Status flags updated to reflect the deserialization status.
                \return The deserialized object or NULL.
                \throw SerializableError if the factory for the object id creates an object with a different object id.
            */
            static SerializablePtr newObjectWithStatus(std::istream& s, DeserializationStatusFlags& status_inout);
            
      
            //! Typedef: pointer to function that creates a Serializable object
            typedef SerializablePtr (*CreateObjectFunPtr)();

            //! Register a Serializable object type.
            /*! @param object_id A unique object identifier
                @param creation_fn_ptr Pointer to a creation function which creates objects of the type associated with \a object_id
                @return any creation function pointer previously registered for the specified \a object_id (NULL if no creation function
                        has previously been registered).

                This function can be used to register a different creation function than any previously registered for the specified \a object_id,
                as long as the function returns an object of the same type as that previously registered, and whose \a objectID() function
                return value matches \a object_id.

                @throw SerializableError under the following invalid conditions:
                    - \a creation_fn_ptr is a NULL pointer
                    - \a creation_fn_ptr points to function which returns a NULL pointer
                    - \a creation_fn_ptr generates a object type different to an object already registered.
                    - \a creation_fn_ptr generates an object whose \a objectID() return value does not match the \a object_id argument. 
                
                @note:
                - This static function should not be called by static initialization code (i.e it shouldn't be called until main())
                - This function is NOT thread-safe (i.e do not register object while serializing/deserializing objects)
            */
            static CreateObjectFunPtr registerObjectType(Serializable::ObjectID object_id, CreateObjectFunPtr creation_fn_ptr);

            /*! \brief Unregisters an object id

                \param object_id The id that may have been previously registered with registerObjectType()
                \return The previous creation function or NULL if the \a object_id was not registered.
            */
            static CreateObjectFunPtr unregisterObjectType(Serializable::ObjectID object_id);

        private:
            //! Banned constructor
            SerializableFactory();
            //! Banned Copy Constructor
            SerializableFactory(const SerializableFactory& rhs);
            //! Banned Assignment Operator
            const SerializableFactory& operator=(const SerializableFactory& rhs);

         
            
        };
    }
}


#endif

