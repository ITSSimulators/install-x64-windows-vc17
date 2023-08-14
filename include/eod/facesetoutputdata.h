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
#ifndef SM_COREDATA_EOD_FACESETOUTPUTDATA_H
#define SM_COREDATA_EOD_FACESETOUTPUTDATA_H

//! @file
// From OutputDataPack
#include "eod/engineoutputbase.h"
#include "eod/serializablefactory.h"
#include "eod/eyeclosureoutputdata.h"
#include "eod/pupiloutputdata.h"
#include "eod/gazeoutputdata.h"

namespace sm
{
    namespace eod
    {
        //! A container of information for a single face 
        /*!
            Used as a parent to hold sub objects for head, eye and face output data.

         */
        class SM_COREDATA_API FaceSetOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(FaceSetOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(94);
    
            /*!
            */
            FaceSetOutputData();
    
            FaceSetOutputData(const FaceSetOutputData& rhs);
      
            FaceSetOutputData& operator=(const FaceSetOutputData& rhs);
      
            /*! @return a copy of this object, allocated on the heap */
            virtual FaceSetOutputData* clone() const;
    
            /*! @see SerializableComposite */
            virtual ObjectID objectID() const;
            virtual bool forbidDuplicateSiblings() const;
    
        protected:
            /*! @see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8> &) const;
    
            /*! @see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8> &, int &);
    
            /*! @see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;
    
            /*! @see SerializableComposite */
            virtual void printOwnData(std::ostream &) const;
    
            /*! @see SerializableComposite */
            virtual void printOwnHeader(std::ostream &) const;
        };
        typedef boost::shared_ptr<FaceSetOutputData> FaceSetOutputDataPtr;
        typedef boost::shared_ptr<const FaceSetOutputData> ConstFaceSetOutputDataPtr;
    }
}

#endif



