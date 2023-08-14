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
#ifndef SM_COREDATA_EOD_PUPILOUTPUTDATA_H
#define SM_COREDATA_EOD_PUPILOUTPUTDATA_H

//! @file
#include "eod/engineoutputbase.h"

namespace sm
{
    namespace eod
    {
        //! Data class that represents pupil related data output by the Tracking Engine
        /*!
         */
        class SM_COREDATA_API PupilOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(PupilOutputData)

        public:
            /*
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(14);
            COREDATA_DECLARE_NAMED_OBJECT_ID(PUPIL_OUTPUT_DATA_ID, 14);
    
            /*!
            */
             PupilOutputData();
    
            PupilOutputData(const PupilOutputData& rhs);
    
            PupilOutputData& operator=(const PupilOutputData& rhs);
    
            /*! @return a copy of this object, allocated on the heap */
            virtual PupilOutputData* clone() const;
    
            /*! @see EngineOutputBase */
            virtual ObjectID objectID() const;
    
            //! Positions of the centre of the pupils in world coordinates
            /*!
                The positions of the centre of the pupils in world coordinates
                is derived directly from the images by localising the iris in
                both images and triangulation. It is independent from eye ball
                calibration.
                This parameter was added for people who need to know the position
                of the pupils in space, i.e. for 3D displays. 
                The values are unfiltered image processing results.
                @param eye_id The eye to retrieve the pupil position for (either
                sm::eod::RIGHT_EYE or sm::eod::LEFT_EYE)
                @pre eye_id is either sm::eod::LEFT_EYE or sm::eod::RIGHT_EYE

            */
            const fStdVector3& pupilPosition(int eye_id) const;
    
            //! The diameter of the pupil (in metres)
            /*!
                This value is only available if the corresponding Gaze Quality Level for this frame is 3.
                @param eye_id he eye to retrieve the pupil diameter for (either
                sm::eod::RIGHT_EYE or sm::eod::LEFT_EYE)
                @pre eye_id is either sm::eod::LEFT_EYE or sm::eod::RIGHT_EYE

              */
            float pupilDiameter(int eye_id) const;
    
            //! Set the pupil diameter for an eye
            /*! @param eye_id The Eye to set the pupil diameter for
                @param pupil_diameter pupil diameter (in metres) 
                @pre eye_id is either sm::eod::LEFT_EYE or sm::eod::RIGHT_EYE
                @pre pupil_diameter is greater than or equal to zero

              */
            void setPupilDiameter(int eye_id, float pupil_diameter);
    
            //! Set the 3D pupil position for an eye
            /*! @param eye_id The Eye to set the pupil position for
                @param pupil_position vector of length 3 representing pupil position (in world coordinates) 
                @pre eye_id is either sm::eod::LEFT_EYE or sm::eod::RIGHT_EYE
                @pre pupil_position is a 3D point

              */
            void setPupilPosition(int eye_id, const fStdVector3& pupil_position);
    
        protected:
            /*! @see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8>& buffer) const;
    
            /*! @see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_pos);
    
            /*! @see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;
    
            /*! @see SerializableComposite */
            virtual void printOwnData(std::ostream& s) const;
    
            /*! @see SerializableComposite */
            virtual void printOwnHeader(std::ostream& s) const;
    
        private:
            //! Copy the data from rhs into this object
            void copyFrom(const PupilOutputData& rhs);
    
            std::vector<fStdVector3> _pupil_position;
            std::vector<float> _pupil_diameter;
        };
        typedef boost::shared_ptr<PupilOutputData> PupilOutputDataPtr;
        typedef boost::shared_ptr<const PupilOutputData> ConstPupilOutputDataPtr;
    }
}

#endif

