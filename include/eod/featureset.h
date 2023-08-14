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
#ifndef SM_COREDATA_EOD_FEATURESET_H
#define SM_COREDATA_EOD_FEATURESET_H

//! @file
// From OutputDataPack
#include "eod/engineoutputbase.h"
#include "eod/featurerect.h"
#include "eod/featurepoint.h"

namespace sm
{
    namespace eod
    {
    
        //! A set of FeatureOutputData derived objects, for representing a group of related features 
        /*!
         */
        class SM_COREDATA_API FeatureSet : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(FeatureSet)

        public:
            /*
            */
            //! The ID that identifies the Set of features in Camera A
            COREDATA_DECLARE_NAMED_OBJECT_ID(FEATURE_SET_CAM_A_ID, 21);
            //! The ID that identifies the Set of features in Camera B
            COREDATA_DECLARE_NAMED_OBJECT_ID(FEATURE_SET_CAM_B_ID, 22);
    
            //! @param object_id The Serializable ID of this object
            /*!
            */
            explicit FeatureSet(ObjectID object_id);
    
            FeatureSet(const FeatureSet& rhs);
    
            /*! @pre self assignment not allowed
                @pre object ids must match
             */
            FeatureSet& operator=(const FeatureSet& rhs);
    
            /*! @see Serializable::objectID */
            virtual ObjectID objectID() const;
    
            /*! @see Serializable::clone */
            virtual FeatureSet* clone() const;
    
   
            //! Convenience method that returns the rectangle bounding the face
            /*!
            */
            ConstFeatureRectPtr faceRect() const;
            FeatureRectPtr faceRect();

            //! Convenience method that returns the rectangle bounding the left eye
            /*!
            */
            ConstFeatureRectPtr leftEyeRect() const;
            FeatureRectPtr leftEyeRect();

            //! Convenience method that returns the rectangle bounding the right eye
            /*!
            */
            ConstFeatureRectPtr rightEyeRect() const;
            FeatureRectPtr rightEyeRect();

            //! Convenience method that returns the rectangle bounding the mouth
            /*!
            */
            ConstFeatureRectPtr mouthRect() const;
            FeatureRectPtr mouthRect();
            
            //! @return the pupil pos for the specified eye. @see EngineOutputBase::EyeId
            /*!
                @param eye_id either RIGHT_EYE or LEFT_EYE.
                @pre eye_id is either RIGHT_EYE or LEFT_EYE.

            */
            ConstFeaturePointPtr pupilPosForEye(int eye_id) const;
            FeaturePointPtr pupilPosForEye(int eye_id);

            //! Convenience method that returns the position of the right pupil
            /*!
            */
            ConstFeaturePointPtr rightPupilPos() const;
            FeaturePointPtr rightPupilPos();

            //! Convenience method that returns the position of the left pupil
            /*!
            */
            ConstFeaturePointPtr leftPupilPos() const;
            FeaturePointPtr leftPupilPos();
    
        protected:
            /*! @see Serializable
                This method is overriden here so that the correct colum header names can be assigned to
                sub-objects after they have been unserialized */
            virtual void readFromBuffer(const std::vector<uint8>& , int& );
    
            /*! @see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8>& ) const;
    
            /*! @see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8>& , int& );
    
            /*! @see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;
    
            /*! @see SerializableComposite */
            virtual void printOwnData(std::ostream& ) const;
    
            /*! @see SerializableComposite */
            virtual void printOwnHeader(std::ostream& ) const;
            /*! 
                If sub_object is derived from FeatureOutputData then the name of the
                sub_object is updated with the name of this object.

                @throw SerializableError if the object id already exists or the
                    object id is not valid for this object or sub_object is not derived 
                    from EngineOutputBase or FeatureOutputData.
            */
            virtual void doAddSubObject(const SerializablePtr& sub_object);
 
            /*! @return a string representing a text header prefix, based on _object_id
                For example, returns "CA" if object_id is FEATURE_SET_CAM_A_ID */
            static std::string IDToName(ObjectID object_id);
    
        private:
            //! ID of this object
            const ObjectID _object_id;
    
            // The name of this object, used to create header field names
            std::string _name;
        };
        typedef boost::shared_ptr<FeatureSet> FeatureSetPtr;
        typedef boost::shared_ptr<const FeatureSet> ConstFeatureSetPtr;
    }
}

#endif

