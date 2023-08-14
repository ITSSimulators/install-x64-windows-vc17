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
#ifndef SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATAV4_H
#define SM_COREDATA_EOD_GAZEINTERSECTIONOUTPUTDATAV4_H

//! \file
#include "eod/intersectionoutputbasev2.h"

namespace sm
{
    namespace eod
    {
        /*! \brief Data representing intersections between a gaze vector and world model items

            This class can represent the intersection from the left eye, right eye or the unified
            gaze ray.

            \if SM_COREDATA_LANGUAGE_PYTHON
            class GazeIntersectionOutputDataV4(IntersectionOutputBaseV2):
                """A data class which contains intersections between the gaze vector and world model items.
                """
            \endif
         */
        class SM_COREDATA_API GazeIntersectionOutputDataV4 : public IntersectionOutputBaseV2
        {
            COREDATA_MEMORY_ALLOCATORS(GazeIntersectionOutputDataV4)

        public:

            /*
                \if SM_COREDATA_LANGUAGE_PYTHON
                THIS_OBJECT_ID = 39
                \endif
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(39);
    
            //! Constructor
            /*!

                \if SM_COREDATA_LANGUAGE_PYTHON
                def __init__(self):
                    """Initializes object
                    """
                \endif
             */
            GazeIntersectionOutputDataV4();

            GazeIntersectionOutputDataV4(const GazeIntersectionOutputDataV4& rhs);
            
            GazeIntersectionOutputDataV4& operator=(const GazeIntersectionOutputDataV4& rhs);
    
            /*! \return a copy of this object, allocated on the heap */
            virtual GazeIntersectionOutputDataV4* clone() const;
    
            /*! \see Serializable */
            virtual ObjectID objectID() const;

            /*! \brief Returns the intersection type.

                The intersections may be from the LEFT_EYE, RIGHT_EYE or
                from BOTH_EYES by unify the gaze from both left and right.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def eyeId(self):
                    """Returns the intersection type/

                    The intersections may be from the LEFT_EYE, RIGHT_EYE or
                    from BOTH_EYES by unify the gaze from both left and right.
                    """
                \endif
            */
            EyeId eyeId() const;

            /*! \brief Sets the intersection type

                \param eye_id Which eye (or both) the intersections are from.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def eyeId(self, eye_id):
                    """Sets the intersection type.

                    The arguments are:
                        - eye_id        One of the constants LEFT_EYE, RIGHT_EYE or
                                        BOTH_EYES.
                    """
                \endif
            */
            void setEyeId(EyeId eye_id);

            virtual bool forbidDuplicateSiblings() const;

        protected:
            /*! \see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8>& buffer) const;
            /*! \see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_pos);
            /*! \see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;
            /*! \see SerializableComposite */
            virtual void printOwnData(std::ostream& s) const;
            /*! \see SerializableComposite */
            virtual void printOwnHeader(std::ostream& s) const;
        private:
            uint8 _eye_id;
        };
        typedef boost::shared_ptr<GazeIntersectionOutputDataV4> GazeIntersectionOutputDataV4Ptr;
        typedef boost::shared_ptr<const GazeIntersectionOutputDataV4> ConstGazeIntersectionOutputDataV4Ptr;
    }
}

#endif

