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
#ifndef SM_COREDATA_EOD_FEATURESETSBYCAMERA_H
#define SM_COREDATA_EOD_FEATURESETSBYCAMERA_H

//! @file
#include "eod/engineoutputbase.h"
#include "eod/featureset.h"

namespace sm
{
    namespace eod
    {
        //! A group of FeatureSet objects, grouped by camera
        /*!
         */
        class SM_COREDATA_API FeatureSetsByCamera : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(FeatureSetsByCamera)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(20);
            COREDATA_DECLARE_NAMED_OBJECT_ID(FEATURE_SETS_BY_CAMERA_ID, 20);
    
            /*!
            */
            FeatureSetsByCamera();
    
            FeatureSetsByCamera(const FeatureSetsByCamera& rhs);
    
            FeatureSetsByCamera& operator=(const FeatureSetsByCamera& rhs);
    
            /*! @see Serializable::objectID */
            virtual ObjectID objectID() const;
    
            /*! @see Serializable::clone */
            virtual FeatureSetsByCamera* clone() const;
    
            //! @return the feature set for a specific camera ID
            /*!
                @param cam_id The camera ID is 0 for CamA, 1 for CamB
                @pre cam_id must be either 0 or 1 

             */
            FeatureSetPtr featureSetForCamera(int cam_id);
    
            //! Convenience method that returns the set of features in Camera A
            /*!
             */
            ConstFeatureSetPtr featureSetCamA() const;
            FeatureSetPtr featureSetCamA();
    
            //! Convenience method that returns the set of features in Camera B
            /*!
             */
            ConstFeatureSetPtr featureSetCamB() const;
            FeatureSetPtr featureSetCamB();
    
        protected:
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
        };
        typedef boost::shared_ptr<FeatureSetsByCamera> FeatureSetsByCameraPtr;
        typedef boost::shared_ptr<const FeatureSetsByCamera> ConstFeatureSetsByCameraPtr;
    }
}

#endif

