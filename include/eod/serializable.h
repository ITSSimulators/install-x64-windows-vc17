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
#ifndef SM_COREDATA_EOD_SERIALIZABLE_H
#define SM_COREDATA_EOD_SERIALIZABLE_H

//! \file
#include "eod/serializableerror.h"

namespace sm
{
    namespace eod
    {

            /*! \brief The status of the deserialization of an object.

                Deserialization can be partial due to unknown codecs or
                unknown object ids. If the root codec or object id then
                a status of DESERIALIZATION_NONE is used.
            */
            enum DeserializationStatus
            {
                /*! \brief All subobjects were deserialized successfully. */
                DESERIALIZATION_COMPLETE = 0x00,
                /*! \brief Bit flag indicating some deserialized subobjects were unknown.

                    The deserialized object contains missing data.
                */
                DESERIALIZATION_UNKNOWN_OBJECT_ID = 0x01,
                /*! \brief Bit flag indicating some deserialized subobjects were compressed using an unknown codec.

                    The deserialized object contains missing data.
                */
                DESERIALIZATION_UNKNOWN_CODEC_ID = 0x02,
                /*! \brief Bit flag indicating that there was insufficient data to deserialize the object

                    If deserializing from a file then the file has an incomplete object
                    otherwise read more data and try again.
                */
                DESERIALIZATION_INSUFFICIENT_DATA = 0x04,
                /*! \brief Bit flag indicating that the data was invalid.

                    This would most likely be due to a header indicating the incorrect size.
                */
                DESERIALIZATION_INVALID_DATA =  0x08,
                /*! \brief Bit flag indicating some deserialized subobjects are missing (most likely because of data loss).

                    The deserialized object contains missing data.
                */
                DESERIALIZATION_MISSING_OBJECTS = 0x10,
                /*! \brief Bit flag indicating some deserialized subobjects were corrupted and thus discarded.

                    The deserialized object contains missing data.
                */
                DESERIALIZATION_CORRUPT_OBJECTS = 0x20,
                /*! \brief Bit flag mask for partial deserialization flags. */
                DESERIALIZATION_PARTIAL_MASK = DESERIALIZATION_UNKNOWN_OBJECT_ID | DESERIALIZATION_UNKNOWN_CODEC_ID | DESERIALIZATION_MISSING_OBJECTS | DESERIALIZATION_CORRUPT_OBJECTS,
                /*! \brief Bit flag mask for deserialization error flags. */
                DESERIALIZATION_ERROR_MASK = DESERIALIZATION_INSUFFICIENT_DATA | DESERIALIZATION_INVALID_DATA,
            };
            typedef uint32 DeserializationStatusFlags;

        /*! \brief Abstract interface class for all objects that can read and write themselves from/to a buffer.
        
            For a complete UML diagram of the Serializable/EngineOutputData hierachy, see
            <A HREF="serializablecomposite.htm">
            serializablecomposite.htm</A> in the doc/html directory

            \if SM_COREDATA_LANGUAGE_PYTHON
            class Serializable:
                """Abstract interface class for all objects that can read and write themselves from/to a buffer.
                """
            \endif
        */
        class SM_COREDATA_API Serializable
        {
            COREDATA_MEMORY_ALLOCATORS(Serializable)

        public:

            //! Type used to hold an value identifying a type of serializeable object.
            typedef int8 ObjectID;
            //! A vector of ObjectIDs
            typedef std::vector<ObjectID> ObjectIDVec;
    
            /*!
                \name Unique ids for objects that inherit this class.

                Do not change these values.
                \note These values were used by the previous Serializable framework (before Factories were
                introduced) and are provided for backwards compatibility only. New Serializable derived 
                classes should declare their IDs as a class constant 

                @{
            */
    
                //! The thing you don't want to receive
                COREDATA_DECLARE_NAMED_OBJECT_ID(ERROR_ID, 0);
                //! World model objects
                COREDATA_DECLARE_NAMED_OBJECT_ID(WSPHERE_ID, 2);
                COREDATA_DECLARE_NAMED_OBJECT_ID(WPLANE_ID, 3);
                
                //! Object sent to FamousFaces plugin
                COREDATA_DECLARE_NAMED_OBJECT_ID(FAMOUS_PLUGIN_ID, 5);
                //! The face-state version objects
                COREDATA_DECLARE_NAMED_OBJECT_ID(FACE_STATE_ID_V1_0, 1);
                COREDATA_DECLARE_NAMED_OBJECT_ID(FACE_STATE_ID_V2_0, 6);
                COREDATA_DECLARE_NAMED_OBJECT_ID(FACE_STATE_ID_V3_0, 7);
                COREDATA_DECLARE_NAMED_OBJECT_ID(FACE_STATE_ID_V3_0_SERIAL, 8);
                COREDATA_DECLARE_NAMED_OBJECT_ID(TEST_ID, 127);   //!< For testing purposes
                //! Maximum of 255 object types (range is -128 -> 127)
            /*! @} - end name */
    
            //! Virtual destructor to allow deletion via base-class pointer
            virtual ~Serializable();
    
            //! Each child class must return a unique value.
            /*! 
                These are defined as the constants above
                \if SM_COREDATA_LANGUAGE_PYTHON
                def objectID(self):
                    """Identifier for type of object
                    """
                \endif
            */
            virtual ObjectID objectID() const COREDATA_PURE_METHOD;
    
            //! Returns the number of header bytes that are written to the buffer by the serialize function before the actual data is appended.
            /*!
                \if SM_COREDATA_LANGUAGE_PYTHON
                def numHeaderBytes(data_size):
                    """Returns the number of header bytes that are written to the buffer by the serialize function before the actual data is appended.
                    """
                \endif
            */
            static uint16 numHeaderBytes(uint32 data_size);
            
            //! Returns true if an extended header is required for data_size.
            /*!
                \if SM_COREDATA_LANGUAGE_PYTHON
                def extendedHeaderSize(data_size):
                    """Returns true if an extended header is required for data_size.
                    """
                \endif
            */
            static bool extendedHeaderSize(uint32 data_size);

            //! Minimum number of bytes to read to determine the kind of header for a packet.
            /*!
                Returns the minimum number of header bytes that need to be read
                to be able to determine if the header is an extended header or not.
                This is the number of bytes for the object_id and 16 bit data size.
                An extended header the data size field equal to the value returned
                from extendedHeaderSizeMagicCookie().

                \if SM_COREDATA_LANGUAGE_PYTHON
                def minHeaderBytes():
                    """Returns the minimum number of header bytes that need to be read
                    to be able to determine if the header is an extended header or not.
                    This is the number of bytes for the object_id and 16 bit data size.
                    An extended header the data size field equal to the value returned
                    from extendedHeaderSizeMagicCookie().
                    """
                \endif
            */
            static uint16 minHeaderBytes();
    
            //! Number of bytes of data required to serialize class.
            /*!
                Each child class must define its size.
                This doesn't include the header (network-id) byte.
                NOTE: Do NOT use sizeof(<classname>)

                \if SM_COREDATA_LANGUAGE_PYTHON
                def numDataBytes(self):
                    """Returns the number of bytes of data required to serialize class."""
                \endif
            */
            virtual uint32 numDataBytes() const COREDATA_PURE_METHOD;
    
            //! Returns the number of bytes in one packet, including the header and the data bytes
            /*!
                \if SM_COREDATA_LANGUAGE_PYTHON
                def numTotalBytes(self):
                    """Returns the total number of bytes required tp serialize the object,
                    This includes the header and the data bytes.
                    """
                \endif
            */
            uint32 numTotalBytes() const;
    
            //! Appends to the buffer the object's data
            /*!
                The first byte written is the object's unique ID

                \if SM_COREDATA_LANGUAGE_PYTHON
                def serialize(self, buffer):
                    """Appends to the buffer the object's data.
                    """
                \endif
            */
            void serialize(std::vector<uint8>& buffer) const;
    
            //! Attempts to build the object from the buffer.
            /*!
                \pre read_pos_inout >= 0
                \return false - insufficient data om the the buffer, read_pos_inout is left unmodified.
                    true - object was successfully deserialized, read_pos_inout has been updated
                        to the next read position.
                    
                \throw SerializableError when
                    objectid in buffer does not match this object,
                    data_size in header didn't match amount of data read,
                    duplicate sub-object ids were found.
                    The object may have been partially updated. read_pos_inout is left unmodified.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def unSerialize(self, buffer, read_pos_inout):
                    """Attempts to build the object from the buffer.

                    The arguments are:
                        - buffer    The buffer of data to use to reconstruct the object
                                    with.
                        - read_pos_inout  The offset into the buffer to start reading data from.
                                    This value must be >= 0.

                    Returns a tuple consisting of:

                        - boolean success indicator.  The success indicator can be false
                          if the buffer contained insufficent data in which case the object will be left unmodified.
                          Otherwise, it returns true when the object was successfully deserialized.

                        - next read position, only valid if the success indicator is True.
                        
                    This method may raise the following exceptions:

                        SerializableError   The objectid in buffer does not match this object, or
                                            the data_size in header didn't match amount of data read, or
                                            duplicate sub-object ids were found.
                                            The object may have been partially updated.
                    """
                \endif
            */
            bool unSerialize(const std::vector<uint8>& buffer, int& read_pos_inout);
            void unSerializeWithStatus(const std::vector<uint8>& buffer, int& read_pos_inout, DeserializationStatusFlags& status_inout);
    
            /*! 
                \return whether this object (and its descendents) are to be serialized.
                A SerializableComposite will not serialize a sub-object that is not 
                serializeEnabled(). By default, this function returns true, but this can 
                be overridden if the extra functionality is required

                \if SM_COREDATA_LANGUAGE_PYTHON
                def serializeEnabled(self):
                    """Returns whether this object, and its descendents, are to be serialized.
                    """
                \endif
            */
            virtual bool serializeEnabled() const;
    
            //! Virtual copy contructor.
            /*!
                Allocate a copy of this object on the heap, and return a pointer to it 
                \if SM_COREDATA_LANGUAGE_PYTHON
                def clone(self):
                    """Returns a new copy of the object"""
                \endif
            */
            virtual Serializable* clone() const COREDATA_PURE_METHOD;
    
            //! Writes the serialized representation of this object to a binary output stream
            /*!
                \param output_stream The output stream to write to. In the case of a file stream,
                this should be opened in binary mode
                \pre output_stream open and valid.
            */
            void writeToBinaryStream(std::ostream& output_stream) const;
    
            //! Print this object as text to the stream s. This method is called by the stream operator <<
            /*!
                \if SM_COREDATA_LANGUAGE_PYTHON
                def lineText(self):
                    """Returns a string containing the data of the object in a fixed width format.
                    """
                \endif
            */
            virtual void printLine(std::ostream& s) const COREDATA_PURE_METHOD;
    
            //! Prints a one line text header for this object's fields.
            /*!
                Must not append a newline character

                \if SM_COREDATA_LANGUAGE_PYTHON
                def headerText(self):
                    """Returns a string containing the column headings for lineText() of the object in a fixed width format.
                    """
                \endif
            */
            virtual void printHeader(std::ostream& s) const COREDATA_PURE_METHOD;
   
            /*! \brief Returns true if siblings with the same objectID() are forbidden

                A parent objects have the capability to have multiple subobjects with
                the same objectID(). For some output data objects this is not OK as there 
                is no valid meaning to having duplicates.
                As an example there is no valid meaning to having multiple TimingOutputData 
                objects while multiple GazeIntersectionOutputDataV4 are fine as the
                GazeIntersectionOutputDataV4::eyeId() function specifies which eye the data
                relates to.

                By default this function returns true which forbids multiple subobjects being
                attached to a SerializableComposite. Overriding this function and return
                false if the output data object should allow siblings.
            */
            virtual bool forbidDuplicateSiblings() const;

            //! Magic size value to indicate that the objects size is held in a uint32.
            /*!
                The old header consisted of a <uint8 - objectid> <uint16 - object size>.
                When the size matched the magic cookie the header will be:
                    <uint8 - objectid> <uint16 - magic cookie> <uint32 - object size>.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def extendedHeaderSizeMagicCookie():
                    """Returns the 'magic' size value used to indicate that the object's size is held in a uint32.

                    The old header consisted of:

                        objectid    - uint8
                        object size - uint16

                    When the object's size matches the return value from this method then
                    the header consists of:

                        objectid     - uint8
                        magic cookie - uint16
                        object size  - uint32
                    """
                \endif
            */
            static uint16 extendedHeaderSizeMagicCookie();

            //! Appends a header to the buffer.
            /*!
                \if SM_COREDATA_LANGUAGE_PYTHON
                def writeHeader(buffer, object_id, data_size):
                    """Writes a header to the buffer.

                    The arguments are:
                        - buffer    The buffer of data to append the header to.
                        - object_id The ID of the object that understands the data.
                        - data_size The size of the data associated with the header.
                    """
                \endif
            */
            static void writeHeader(std::vector<uint8>& buffer, ObjectID object_id, uint32 data_size);
            
            //! Reads the size if the data from the header.
            /*!
                \param buffer The buffer to read from.
                \param read_pos_inout The position in the buffer to read from.
                \param data_size_out Destination of the size read from the header or NULL.
                \return True if read successfull, false otherwise.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def readDataSizeHeader(buffer, read_pos_inout):
                    """Reads the size of the object header from the buffer.

                    The arguments are:
                        - buffer    The buffer of data.
                        - read_pos_inout  The position within the buffer to read from.

                    This method returns a tuple consisting of a boolean success indicator and the
                    size of the header. The success indicator can be false if there is 
                    insufficient data in the buffer.
                    """
                \endif
            */
            static bool readDataSizeHeader(const std::vector<uint8>& buffer, int& read_pos_inout, uint32* data_size_out);
        protected:
            //! Appends the object's state information to the buffer.
            /*!
                MUST BE IMPLEMENTED BY CHILD CLASSES
                This must includes any necessary information in base classes.
                No need to write the network id, only the class data
                Use the serializable appendBuffer functions from below to
                append different types to the buffer, in a specified order.
                This order must be copied in the readFromBuffer function
            */
            virtual void appendBuffer(std::vector<uint8>& buffer) const COREDATA_PURE_METHOD;
    
            //! Reads the class data from the network buffer and increments
            /*!
                MUST BE IMPLEMENTED BY CHILD CLASSES
                Must perform the opposite of appendBuffer.
                \param buffer the buffer containing data to read
                \param read_pos_inout position to start reading data from, updated by the number of bytes read.
                \throw SerializableError if the buffer is too small. \a read_pos_inout will be left
                    in an invalid state.
            */
            virtual void readFromBuffer(const std::vector<uint8>& buffer, int& read_pos_inout) COREDATA_PURE_METHOD;
            virtual void readFromBufferWithStatus(const std::vector<uint8>& buffer, int& read_pos_inout, DeserializationStatusFlags& status_inout);
    
    
            // Utility routines for child classes to read and write different data types in
            // network byte order.
    
            //! Appends a block of raw bytes to the buffer.
            /*!
                Use appendBuffer to send data in network order.
            */
            static void appendRawBytes(std::vector<uint8>& dest, const char*src_bytes, unsigned int size)
            {
                dest.insert(dest.end(), src_bytes, src_bytes + size);
            }
    
            // Note that the ordering of these functions in the header file is important!
            static void appendBuffer(std::vector<uint8>& buffer, const std::string& value);
            
            template <typename ValueType>
            static void appendBuffer(std::vector<uint8>& buffer, ValueType value)
            {
                COREDATA_STATIC_ASSERT(sizeof(value) == 1 || sizeof(value) == 2
                    || sizeof(value) == 4 || sizeof(value) == 8);
                appendNBytes(buffer, reinterpret_cast<char *>(&value), sizeof(value));
            }
            
            static void appendBuffer(std::vector<uint8>& buffer, bool value);
    
            //! Append an array to the buffer. Convenience function
            template <typename ArrayType>
            static void appendBuffer(std::vector<uint8>& buffer, const ArrayType *array, int num_elements)
            {
                for (int i=0; i < num_elements; i++)
                {
                    appendBuffer(buffer, array[i]);
                }
            }
    
            template <typename ValueType>
            static void readBuffer(const std::vector<uint8>& buffer, int& read_pos_inout, ValueType& value)
            {
                COREDATA_STATIC_ASSERT(sizeof(value) == 1 || sizeof(value) == 2
                    || sizeof(value) == 4 || sizeof(value) == 8);
                readNBytes(buffer, read_pos_inout, reinterpret_cast<char *>(&value), sizeof(value));
            }
            static void readBuffer(const std::vector<uint8>& buffer, int& read_pos_inout, bool& value);
            static void readBuffer(const std::vector<uint8>& buffer, int& read_pos_inout, std::string& value);
    
            //! Read an array from the buffer. Convenience function
            template <typename ArrayType>
            static void readBuffer(const std::vector<uint8>& buffer, int& read_pos_inout, ArrayType *array, int num_elements)
            {
                for (int i=0; i < num_elements; i++)
                {
                    readBuffer(buffer, read_pos_inout, array[i]);
                }
            }
    
            //! Reads a block of bytes.
            /*!
                Use readBuffer for types that require tranforming to and from network order.
                
                \param buffer Buffer of bytes.
                \param read_pos_inout reference to the current read cursor.
                \param array pointer to the non-null destination buffer.
                \param num_elements the number of elements to read.
    
                \pre read_pos_inout must not be negative.
                \pre read_pos_inout + num_elements must be <= buffer.end().
                \pre array cannot be NULL.
            */
            static void readRawBytes(const std::vector<uint8>& buffer, int& read_pos_inout, uint8* array, size_t num_elements);
    
        private:
            //! Writes the size of the data
            static void writeDataSizeHeader(std::vector<uint8>& buffer, uint32 data_size);
    
            // Functions to do reading and appending at byte level.
            // Assume that 1 char = 8 bits
    
            //! Append a specified number of bytes (usually with sizeof(someval)) into the buffer, in network byte order
            /*!
                \param buffer The buffer to append to
                \param b_ptr A pointer to memory that is initialised, must have at least
                             num_bytes consecutive chars allocated
                \param num_bytes The number of bytes to append (1, 2, 4 or 8)
            */
            static void appendNBytes(std::vector<uint8>& buffer, const char *b_ptr, int num_bytes);

            static void append1Byte(std::vector<uint8>& buffer, const char *b_ptr);
            static void append2Bytes(std::vector<uint8>& buffer, const char *b_ptr);
            static void append4Bytes(std::vector<uint8>& buffer, const char *b_ptr);
            static void append8Bytes(std::vector<uint8>& buffer, const char *b_ptr);
    
            //! Read a specified number of bytes (usually with sizeof(someval)) from the buffer, converting back from network byte order
            /*!
                \param buffer The buffer to read from
                \param read_pos_inout The position in the buffer to read from
                \param v_ptr A pointer to memory that is initialised, must have at least
                             num_bytes consecutive chars allocated
                \param num_bytes The number of bytes to read (1, 2, 4 or 8)
            */
            static void readNBytes(const std::vector<uint8>& buffer, int& read_pos_inout, char *v_ptr, int num_bytes);

            static void read1Byte(const std::vector<uint8>& buffer, int& read_pos_inout, char *v_ptr);
            static void read2Bytes(const std::vector<uint8>& buffer, int& read_pos_inout, char *v_ptr);
            static void read4Bytes(const std::vector<uint8>& buffer, int& read_pos_inout, char *v_ptr);
            static void read8Bytes(const std::vector<uint8>& buffer, int& read_pos_inout, char *v_ptr);
        };
        typedef boost::shared_ptr<Serializable> SerializablePtr;
        typedef boost::shared_ptr<const Serializable> ConstSerializablePtr;
    
        /*!
            \name Text Streaming

            @{
        */

        //! Constant defining the width of the text field
        enum
        {
            MAX_STRING_WIDTH = 15
        };
        
        //! Write a field to an output stream. Writes with 15 padding and one following space
        template <typename FieldType>
        void writeField(std::ostream& s, FieldType field)
        {
            s << std::setw(MAX_STRING_WIDTH) << field << " ";
        }
    
        //! Pad \a text with prepended spaces, to ensure the string's length is \a length.
        /*!
            If \a text is already longer than \a length, the string is
            not changed
            \return padded string
        */
        SM_COREDATA_API std::string padString(const std::string& text, int length);
    
        //! Remove any leading spaces from \a text
        /*!
            \return un-padded string
        */
        SM_COREDATA_API std::string unPadString(const std::string& text);
    
        //! Stream operator. Writes a Serializable object as text.
        /*! \param s The output stream to write to
            \param serializable Serializable object to be written to the stream
        */
        SM_COREDATA_API std::ostream& operator<<(std::ostream& s, const Serializable& serializable);

        //!@} - end name Text Streaming
    }
}
#endif

