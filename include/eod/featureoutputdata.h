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
#ifndef SM_COREDATA_EOD_FEATUREOUTPUTDATA_H
#define SM_COREDATA_EOD_FEATUREOUTPUTDATA_H

//! @file
#include "eod/serializable.h"

namespace sm
{
    namespace eod
    {
        //! Abstract base class for output data that is related to Features within an image
        /*!
         */
        class SM_COREDATA_API FeatureOutputData : public Serializable
        {
            COREDATA_MEMORY_ALLOCATORS(FeatureOutputData)

        public:
    
            /*! @see Serializable::objectID */
            virtual ObjectID objectID() const;
    
            //! Set the name that will be prepended to the text headers for this object
            /*!
             */
            void setName(const std::string& name);
    
            //! The name of this object
            /*! 
                When printHeader() is called, this string is prepended to the names
                of the data members. For example, if the prefix was set to "LPUPIL_CAMA_",
                then the header for the data members might be logged as LPUPIL_CAMA_X,
                LPUPIL_CAMA_Y etc.

             */
            const std::string name() const;
    
            //! @return the invalid feature value
            /*!
             */
            static float invalidValue();

        protected:
            /*! @param object_id the Serializable Object ID of this object */
            FeatureOutputData(ObjectID object_id);

            FeatureOutputData(const FeatureOutputData& rhs);
    
            FeatureOutputData& operator=(const FeatureOutputData& rhs);
    
        private:
    
            //! Store the objectID of this object
            const ObjectID _object_id;
    
            //! The string that is prepended to the header for data members
            std::string _name;
        };
        typedef boost::shared_ptr<FeatureOutputData> FeatureOutputDataPtr;
        typedef boost::shared_ptr<const FeatureOutputData> ConstFeatureOutputDataPtr;
    }
}

#endif

