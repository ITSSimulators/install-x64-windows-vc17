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
#ifndef SM_COREDATA_EOD_ENGINEOUTPUTDATA_H
#define SM_COREDATA_EOD_ENGINEOUTPUTDATA_H

//! \file
#include "eod/engineoutputbase.h"
#include "eod/gpsoutputdata.h"
#include "eod/gpsoutputdatav2.h"
#include "eod/eodupgrade.h"

namespace sm
{
    namespace eod
    {
    
        //! Data class that represents Tracking Engine data that is publicly output
        /*! 
            Read \ref coreapi_coredata_class_design before making any changes to this class.

\verbatim
    A typical object graph looks like:
    EngineOutputData
      - TimingOutputDataLatest
      - CustomEventOutputData
      - WorldOutputDataLatest
        - HeadIntersectionOutputData
        - GazeIntersectionOutputDataLatest **DUPLICATES ALLOWED
      - InertiaOutputDataLatest
      - GPSOutputData
      - EngineStateOutputDataLatest
        - HeadTrackerStateOutputData
        - IRPodStateOutputData 
      - FeatureSetsByCameraLatest
        - FeatureSet(CAM_A)
          - FeatureRect(FACE_RECT_ID)
          - FeatureRect(LEFT_EYE_RECT_ID)
          - FeatureRect(RIGHT_EYE_RECT_ID)
          - FeatureRect(MOUTH_RECT_ID)
          - FeaturePoint(RIGHT_PUPIL_ID)
          - FeaturePoint(LEFT_PUPIL_ID)
        - FeatureSet(CAM_B)
      - ImageCollectionOutputDataLatest
      - FaceSetOutputDataLatest **DUPLICATES ALLOWED
        - HeadOutputDataLatest
        - EyeOutputDataLatest
          - GazeOutputData
          - PupilOutputData
          - EyeClosureOutputData
        - FaceOutputDataLatest
\endverbatim

            \see eodupgrade.h

            \if SM_COREDATA_LANGUAGE_PYTHON
            class EngineOutputData(EngineOutputBase):
                """Data class that represents Tracking Engine data that is publicly output

                A typical object graph looks like:
                EngineOutputData
                  - TimingOutputDataLatest
                  - CustomEventOutputData
                  - WorldOutputDataLatest
                    - HeadIntersectionOutputData
                    - GazeIntersectionOutputDataLatest **DUPLICATES ALLOWED
                  - InertiaOutputDataLatest
                  - GPSOutputData
                  - EngineStateOutputDataLatest
                    - HeadTrackerStateOutputData
                    - IRPodStateOutputData 
                  - FeatureSetsByCameraLatest
                    - FeatureSet(CAM_A)
                      - FeatureRect(FACE_RECT_ID)
                      - FeatureRect(LEFT_EYE_RECT_ID)
                      - FeatureRect(RIGHT_EYE_RECT_ID)
                      - FeatureRect(MOUTH_RECT_ID)
                      - FeaturePoint(RIGHT_PUPIL_ID)
                      - FeaturePoint(LEFT_PUPIL_ID)
                    - FeatureSet(CAM_B)
                  - ImageCollectionOutputDataLatest
                  - FaceSetOutputDataLatest **DUPLICATES ALLOWED
                    - HeadOutputDataLatest
                    - EyeOutputDataLatest
                      - GazeOutputData
                      - PupilOutputData
                      - EyeClosureOutputData
                    - FaceOutputDataLatest
                """
            \endif
        */
        class SM_COREDATA_API EngineOutputData : public EngineOutputBase
        {
            COREDATA_MEMORY_ALLOCATORS(EngineOutputData)

        public:
    
            //! File extension for logfiles (*.fll)
            /*!
                \see narrow to convert to std::string

                \if SM_COREDATA_LANGUAGE_PYTHON
                def LOGFILE_EXTENSION(self):
                    """File extension for logfiles (*.fll).
                    """
                \endif
             */
            static const std::wstring LOGFILE_EXTENSION();
            //! File extension for logfile indexes (*.flli)
            /*!
                \see narrow to convert to std::string

                \if SM_COREDATA_LANGUAGE_PYTHON
                def LOGFILE_INDEX_EXTENSION(self):
                    """File extension for logfile indexes (*.flli)
                    """
                \endif
             */
            static const std::wstring LOGFILE_INDEX_EXTENSION();
    
            /*
                \if SM_COREDATA_LANGUAGE_PYTHON
                THIS_OBJECT_ID = 9
                \endif
            */
            COREDATA_DECLARE_THIS_OBJECT_ID(9);
            COREDATA_DECLARE_NAMED_OBJECT_ID(ENGINE_OUTPUT_DATA_ID, 9);
    
            /*!
                \if SM_COREDATA_LANGUAGE_PYTHON
                def __init__(self):
                    """All members zeroed."""
                    pass
                \endif
            */
            EngineOutputData();
    
            //! Copies _frame_num and calls base class copy constructor
            EngineOutputData(const EngineOutputData& rhs);
    
            //! Copies _frame_num and calls base class assignent operator
            /*!
                \param rhs The EngineOutputData instance to copy.
                \return This EngineOutputData instance.
             */
            EngineOutputData& operator=(const EngineOutputData& rhs);
    
            /*!
                \see SerializableComposite */
            virtual ObjectID objectID() const;

            //! \brief Unsigned type that can hold a number to uniquely identify a video frame.
            typedef uint32 FrameNumber;

            //! Unique video frame number.
            /*!
                Reset to 0 whenever the engine is restarted. 
                \if SM_COREDATA_LANGUAGE_PYTHON
                def frameNum(self):
                    """Returns the video frame number.

                    This number is reset to 0 whenever the tracking engine is restarted.
                    """
                \endif
             */
            FrameNumber frameNum() const;
    
            /*!
                Set the frame number of this data object 

                \if SM_COREDATA_LANGUAGE_PYTHON
                def setFrameNum(self, frame_num):
                    """Set the frame number of this data object 

                    The arguments are:
                        - frame_num    The frame number in the range 0..
                    """
                \endif
             */
            void setFrameNum(FrameNumber frame_num);
    
            // Convenience methods for accessing specific sub-object types.

            /*!
                \return the TimingOutputData attached to this object, or NULL if no Timing data is attached
                \throw SerializableError if an object with the ID of a TimingOutputData was found, but
                could not be cast to a TimingOutputData object 

                \if SM_COREDATA_LANGUAGE_PYTHON
                def timingOutputData(self):
                    """Returns the attached TimingOutputData or None.
                    """
                \endif
             */
            TimingOutputDataLatestPtr timingOutputData();
            /*!
                \overload
                \note Casts away const-ness
                \deprecated Use non-const version.
            */
            COREDATA_DEPRECATED("Use non-const version") TimingOutputDataLatestPtr timingOutputData() const;
    
            /*! \brief Returns the attached engine state output data upgraded to the latest version.

                \return The object if attached, otherwise NULL.
                \throw SerializableError If an object with the ID of a EngineStateOutputData was found, but 
                    could not be cast to a EngineStateOutputData object 

                \see sm::eod::engineStateOutputData(EngineOutputData&)

                \if SM_COREDATA_LANGUAGE_PYTHON
                def engineStateOutputData(self):
                    """Returns the attached engine state output data upgraded to the latest version or None.
                    """
                \endif
             */
            EngineStateOutputDataLatestPtr engineStateOutputData();

            /*!
                \overload
                \note Casts away const-ness
                \deprecated Use non-const version.
            */
            COREDATA_DEPRECATED("Use non-const version") EngineStateOutputDataLatestPtr engineStateOutputData() const;
   
            /*! \brief Returns the number of FaceSetOutputData objects attached.

                If the object has head, face or eye output data as immediate subobjects
                then a FaceSetOutputData object will be created and added as a subobject. 
                The head, face and eye output data objects will be upgraded to the latest 
                versions and moved under the FaceSetOutputData.

                \throw SerializableError There already exists a FaceSetOutputData object. The
                    head, face and eye output data will upgraded and moved if there doesn't
                    already exists a FaceSetOutputData object.
                \see sm::eod::numFaceSetOutputDataObjects

                \if SM_COREDATA_LANGUAGE_PYTHON
                def numFaces(self):
                    """Returns the number of FaceSetOutputData objects attached.

                       If the object has head, face or eye output data as immediate subobjects
                       then a FaceSetOutputData object will be created and added as a subobject. 
                       The head, face and eye output data objects will be upgraded to the latest 
                       versions and moved under the FaceSetOutputData.

                       This method may raise the following exceptions:

                           - SerializableError     Failed to migrate or upgrade objects.
                    """
                \endif
            */
            uint8 numFaces();

            /*! \brief Returns a FaceSetOutputData by index.

                If the object has head, face or eye output data as immediate subobjects
                then they are upgraded to the latest versions and moved to the first 
                FaceSetOutputData object under this object.
                If there is no FaceSetOutputData object it will be created.
                If there already exists a FaceSetOutputData object which already contains the upgraded
                object being moved that an exception will be thrown.

                \throw SerializableError There already exists a FaceSetOutputData object with the
                    data being moved.

                \see sm::eod::faceSetOutputData(EngineOutputData&,ObjectIndex)

                \if SM_COREDATA_LANGUAGE_PYTHON
                def numFaces(self):
                    """Returns a FaceSetOutputData by index or None.

                       If the object has head, face or eye output data as immediate subobjects
                       then a FaceSetOutputData object will be created and added as a subobject. 
                       The head, face and eye output data objects will be upgraded to the latest 
                       versions and moved under the FaceSetOutputData.

                       This method may raise the following exceptions:

                           - SerializableError     Failed to migrate or upgrade objects.
                    """
                \endif
            */
            FaceSetOutputDataLatestPtr face(ObjectIndex index);

            //! Returns a HeadOutputDataLatest object or a NULL shared pointer if none has been attached.
            /*! 
                If a HeadOutputDataV2 sub object exists it is returned. Otherwise if an older head
                output data exists then it is upgraded to a HeadOutputDataV2 object. The older version
                of the head output data object will be removed.
                
                \return the attached HeadOutputDataV2 object, or NULL if no Head data is attached
                \throw SerializableError if an object with the ID of a HeadOutputData was found, but
                    could not be cast to a HeadOutputData object 
                \see sm::eod::headOutputData(EngineOutputData&)

                \if SM_COREDATA_LANGUAGE_PYTHON
                def headOutputData(self):
                    """Returns a HeadOutputDataV2 object or a NULL shared pointer if none has been attached.

                       If a HeadOutputDataV2 sub object exists it is returned. Otherwise if an older head
                       output data exists then it is upgraded to a HeadOutputDataV2 object. The older version
                       of the head output data object will be removed.

                       This method may raise the following exceptions:

                           - SerializableError     A subobject with the head output id exists but it is not
                                                   a head output data instance.
                     """
                \endif
             */      
            HeadOutputDataLatestPtr headOutputData();

            /*!
                \overload
                \note Casts away const-ness
            */
            COREDATA_DEPRECATED("Use non-const version") HeadOutputDataLatestPtr headOutputData() const;
            
            /*!
                If the latest versioned FaceOutputData sub object exists it is 
                returned. Otherwise if an older face output data exists then it
                is upgraded to the latest version. The older version will be removed.

                \return the FaceOutputData attached to this object, or NULL if no Face data is attached
                \throw SerializableError if an object with the ID of a FaceOutputData was found, but
                could not be cast to a FaceOutputData object 

                \see sm::eod::faceOutputData(EngineOutputData&)

                \if SM_COREDATA_LANGUAGE_PYTHON
                def faceOutputData(self):
                    """Returns the attached FaceOutputData or None.
                    """
                \endif
             */
            FaceOutputDataLatestPtr faceOutputData();

            /*!
                \overload
                \note Casts away const-ness
                \deprecated Use non-const version.
            */
            COREDATA_DEPRECATED("Use non-const version") FaceOutputDataLatestPtr faceOutputData() const;
    
            /*! 
                \return the EyeOutputData attached to this object, or NULL if no Eye data is attached
                \throw SerializableError if an object with the ID of a EyeOutputData was found, but
                could not be cast to a EyeOutputData object 

                \see sm::eod::eyeOutputData(EngineOutputData&)
                \note Can mutate object!

                \if SM_COREDATA_LANGUAGE_PYTHON
                def eyeOutputData(self):
                    """Returns the attached EyeOutputData or None.
                    """
                \endif
             */
            EyeOutputDataLatestPtr eyeOutputData();

            /*!
                \overload
                \note Casts away const-ness
                \deprecated Use non-const version.
            */
            COREDATA_DEPRECATED("Use non-const version") EyeOutputDataLatestPtr eyeOutputData() const;
    
            //! Returns a WorldOutputDataV2 object or a NULL shared pointer if none has been attached.
            /*!
                If a WorldOutputDataV2 sub object exists it is returned. Otherwise if an older world
                output data exists then it is upgraded to a WorldOutputDataV2 object. The older version
                of the world output data object will be removed.

                \return the WorldOutputDataV2 attached to this object, or NULL if no World data is attached
                \throw SerializableError if an object with the ID of a WorldOutputData was found, but
                    could not be cast to a WorldOutputData object
                \see sm::eod::worldOutputData()

                \if SM_COREDATA_LANGUAGE_PYTHON
                def worldOutputData(self):
                    """Returns a WorldOutputDataV2 object or a NULL shared pointer if none has been attached.

                       If a WorldOutputDataV2 sub object exists it is returned. Otherwise if an older world
                       output data exists then it is upgraded to a WorldOutputDataV2 object. The older version
                       of the world output data object will be removed.

                       This method may raise the following exceptions:

                           - SerializableError     A subobject with the world output id exists but it is not
                                                   a world output data instance.
                    """
                \endif
             */
            WorldOutputDataLatestPtr worldOutputData();

            /*!
                \overload
                \note Casts away const-ness
                \deprecated Use non-const version.
            */
            COREDATA_DEPRECATED("Use non-const version") WorldOutputDataLatestPtr worldOutputData() const;
    
            /*!
                \return the FeatureSetsByCamera attached to this object, or NULL if no Image feature data is attached
                \throw SerializableError if an object with the ID of a FeatureSetsByCamera was found, but
                could not be cast to a FeatureSetsByCamera object 

                \if SM_COREDATA_LANGUAGE_PYTHON
                def featureSetsByCamera(self):
                    """Returns the attached FeatureSetsByCamera or None.
                    """
                \endif
             */
            FeatureSetsByCameraLatestPtr featureSetsByCamera();

            /*!
                \overload
                \note Casts away const-ness
                \deprecated Use non-const version.
            */
            COREDATA_DEPRECATED("Use non-const version") FeatureSetsByCameraLatestPtr featureSetsByCamera() const;

    
            /*!
                \return the images attached to this object, or NULL if no images data is attached
                \throw SerializableError if an object with the ID of a ImageCollectionOutputData was found, but
                could not be cast to a ImageCollectionOutputData object 

                \if SM_COREDATA_LANGUAGE_PYTHON
                def imagesOutputData(self):
                    """Returns the attached ImagesOutputData or None.
                    """
                \endif
             */
            ImageCollectionOutputDataLatestPtr imagesOutputData();

            /*!
                \overload
                \note Casts away const-ness
                \deprecated Use non-const version.
            */
            COREDATA_DEPRECATED("Use non-const version") ImageCollectionOutputDataLatestPtr imagesOutputData() const;
    
            /*!
                \return the InertiaOutputDataLatest attached to this object, or NULL if no object is attached.
                \throw SerializableError if an object with the ID of a InertiaOutputDataLatest was found, but
                could not be cast to a InertiaOutputDataLatest object 

                \if SM_COREDATA_LANGUAGE_PYTHON
                def inertiaOutputData(self):
                    """Returns the attached InertiaOutputDataLatest or None.
                    """
                \endif
             */
            InertiaOutputDataLatestPtr inertiaOutputData();

            /*!
                \overload
                \note Casts away const-ness
                \deprecated Use non-const version.
            */
            COREDATA_DEPRECATED("Use non-const version") InertiaOutputDataLatestPtr inertiaOutputData() const;
    
    
            /*!
                \return the GPSOutputDataV2 attached to this object, or NULL if no object is attached.
                \throw SerializableError if an object with the ID of a GPSOutputDataV2 was found, but
                could not be cast to a GPSOutputDataV2 object 

                \if SM_COREDATA_LANGUAGE_PYTHON
                def gpsOutputDataV2(self):
                    """Returns the attached GPSOutputDataV2 or None.
                    """
                \endif
             */
            ConstGPSOutputDataV2Ptr gpsOutputDataV2() const;
            GPSOutputDataV2Ptr gpsOutputDataV2();
    
            /*!
                \note GPSOutputData has been superceded by GPSOutputDataV2, however, there are some
                older logfiles that require the use of this object.

                \if SM_COREDATA_LANGUAGE_PYTHON
                def gpsOutputData(self):
                    """Returns the attached GPSOutputData or None.
                    """
                \endif
             */
            ConstGPSOutputDataPtr gpsOutputData() const;
            GPSOutputDataPtr gpsOutputData();
    
            /*!
                \return a copy of this object, allocated on the heap
            */
            virtual EngineOutputData* clone() const;
    
            /*!
                \see SerializableComposite
            */
            virtual void printOwnHeader(std::ostream& s) const;
    
        protected:
            /*! Clear all attached sub-objects and reset the frame number and valid state */
            void reset();
    
            /*!  \see EngineOutputBase */
            virtual void appendEngineSpecificData(std::vector<uint8>& buffer) const;
    
            /*!  \see EngineOutputBase */
            virtual void readEngineSpecificData(const std::vector<uint8>& buffer, int& read_pos);
    
            /*!  \see EngineOutputBase */
            virtual uint32 numEngineSpecificDataBytes() const;
    
            /*!  \see SerializableComposite */
            virtual void printOwnData(std::ostream& s) const;

            virtual bool forbidDuplicateSiblings() const;
    
        private:
            //! The frame number associated with this data object
            FrameNumber _frame_num;
        };

        typedef boost::shared_ptr<EngineOutputData> EngineOutputDataPtr;
        typedef boost::shared_ptr<const EngineOutputData> ConstEngineOutputDataPtr;
    }
}
#endif

