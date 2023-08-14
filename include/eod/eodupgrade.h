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
#ifndef SM_COREDATA_EOD_EODUPGRADE_H
#define SM_COREDATA_EOD_EODUPGRADE_H

//! \file

#include "eod/headoutputdatav2.h"
#include "eod/worldoutputdatav2.h"
#include "eod/faceoutputdatav2.h"
#include "eod/facesetoutputdata.h"
#include "eod/timingoutputdata.h"
#include "eod/featuresetsbycamera.h"
#include "eod/imagecollectionoutputdata.h"
#include "eod/eyeoutputdata.h"
#include "eod/inertiaoutputdata.h"
#include "eod/enginestateoutputdata.h"
#include "eod/gazeintersectionoutputdatav4.h"

namespace sm
{
    namespace eod
    {
        class EngineOutputData;
        /*!
            \name EOD Version Upgrade

            The following types and functions upgrade old versions of EOD objects
            to the latest versions.
        */
        //\{

        typedef FaceSetOutputDataPtr FaceSetOutputDataLatestPtr;
        typedef ConstFaceSetOutputDataPtr ConstFaceSetOutputDataLatestPtr;
        typedef FaceSetOutputData FaceSetOutputDataLatest;

        /*! \brief Upgrades an old version of a FaceSetOutputData to the latest

            \param parent The object whose immediate subobjects will be upgraded.
            \note The subobjects are probed from the latest version to older versions.
            As soon as a version is found it is upgraded to the latest version and
            probing finishes. This means it is possible to add 2 versions of the same
            object and only the oldest version is upgraded.
        */
        SM_COREDATA_API void upgradeFaceSetOutputData(EngineOutputData& parent);
        SM_COREDATA_API void upgradeWorldOutputData(SerializableComposite& container);
        SM_COREDATA_API void upgradeHeadOutputData(SerializableComposite& parent);
        SM_COREDATA_API void upgradeFaceOutputData(SerializableComposite& container);
        SM_COREDATA_API void upgradeTimingOutputData(SerializableComposite& container);
        SM_COREDATA_API void upgradeEngineStateOutputData(SerializableComposite& container);
        SM_COREDATA_API void upgradeEyeOutputData(SerializableComposite& container);
        SM_COREDATA_API void upgradeFeatureSetsByCamera(SerializableComposite& container);
        SM_COREDATA_API void upgradeImageCollectionOutputData(SerializableComposite& container);
        SM_COREDATA_API void upgradeInertiaOutputData(SerializableComposite& container);
        SM_COREDATA_API void upgradeGazeIntersectionOutputData(SerializableComposite& container);


        //! Returns the attached faceset output data upgraded to the latest version.
        /*!
            \param container The object to extract the FaceSetOutputDataLatestPtr from
            \param index Which one to return.
            \return null pointer or a pointer to the latest faceset output data
                defined in coredata.

        */
        SM_COREDATA_API FaceSetOutputDataLatestPtr faceSetOutputData(EngineOutputData& container, 
                                                                     ObjectIndex index);

        /*! \brief Returns the number of faces.

            Migrates
        */
        SM_COREDATA_API uint8 numFaceSetOutputDataObjects(EngineOutputData& container);

        //! Adds the latest faceset output data if it doesn't already exist.
        /*!
            \return A pointer to the latest faceset output data
                defined in coredata.
        */
        SM_COREDATA_API FaceSetOutputDataLatestPtr addFaceSetOutputDataIfMissing(EngineOutputData&);


        typedef WorldOutputDataV2Ptr WorldOutputDataLatestPtr;
        typedef ConstWorldOutputDataV2Ptr ConstWorldOutputDataLatestPtr;
        typedef WorldOutputDataV2 WorldOutputDataLatest;

        //! Returns the attached world output data upgraded to the latest version.
        /*!
            \return null pointer or a pointer to the latest world output data
                defined in coredata.
        */
        SM_COREDATA_API WorldOutputDataLatestPtr worldOutputData(EngineOutputData&);

        //! Adds the latest world output data if it doesn't already exist.
        /*!
            \return A pointer to the latest world output data
                defined in coredata.
        */
        SM_COREDATA_API WorldOutputDataLatestPtr addWorldOutputDataIfMissing(EngineOutputData&);


        typedef HeadOutputDataV2Ptr HeadOutputDataLatestPtr;
        typedef ConstHeadOutputDataV2Ptr ConstHeadOutputDataLatestPtr;
        typedef HeadOutputDataV2 HeadOutputDataLatest;

        //! Returns the attached head output data upgraded to the latest version.
        /*!
            \return null pointer or a pointer to the latest head output data
                defined in coredata.
        */
        SM_COREDATA_API HeadOutputDataLatestPtr headOutputData(FaceSetOutputDataLatest&);

        //! Adds the latest world output data if it doesn't already exist.
        /*!
            \return A pointer to the latest head output data
                defined in coredata.
        */
        SM_COREDATA_API HeadOutputDataLatestPtr addHeadOutputDataIfMissing(FaceSetOutputDataLatest&);



        typedef TimingOutputDataPtr TimingOutputDataLatestPtr;
        typedef ConstTimingOutputDataPtr ConstTimingOutputDataLatestPtr;
        typedef TimingOutputData TimingOutputDataLatest;

        //! Returns the attached timing output data upgraded to the latest version.
        /*!
            \return null pointer or a pointer to the latest timing output data
                defined in coredata.
        */
        SM_COREDATA_API TimingOutputDataLatestPtr timingOutputData(EngineOutputData&);

        //! Adds the latest timing output data if it doesn't already exist.
        /*!
            \return A pointer to the latest timing output data
                defined in coredata.
        */
        SM_COREDATA_API TimingOutputDataLatestPtr addTimingOutputDataIfMissing(EngineOutputData&);

        typedef EngineStateOutputDataPtr EngineStateOutputDataLatestPtr;
        typedef ConstEngineStateOutputDataPtr ConstEngineStateOutputDataLatestPtr;
        typedef EngineStateOutputData EngineStateOutputDataLatest;

        //! Returns the attached enginestate output data upgraded to the latest version.
        /*!
            \return null pointer or a pointer to the latest enginestate output data
                defined in coredata.
        */
        SM_COREDATA_API EngineStateOutputDataLatestPtr engineStateOutputData(EngineOutputData&);

        //! Adds the latest enginestate output data if it doesn't already exist.
        /*!
            \return A pointer to the latest enginestate output data
                defined in coredata.
        */
        SM_COREDATA_API EngineStateOutputDataLatestPtr addEngineStateOutputDataIfMissing(EngineOutputData&);

        typedef EyeOutputDataPtr EyeOutputDataLatestPtr;
        typedef ConstEyeOutputDataPtr ConstEyeOutputDataLatestPtr;
        typedef EyeOutputData EyeOutputDataLatest;

        //! Returns the attached eye output data upgraded to the latest version.
        /*!
            \return null pointer or a pointer to the latest eye output data
                defined in coredata.
        */
        SM_COREDATA_API EyeOutputDataLatestPtr eyeOutputData(FaceSetOutputDataLatest&);

        //! Adds the latest eye output data if it doesn't already exist.
        /*!
            \return A pointer to the latest eye output data
                defined in coredata.
        */
        SM_COREDATA_API EyeOutputDataLatestPtr addEyeOutputDataIfMissing(FaceSetOutputDataLatest&);

        typedef FeatureSetsByCameraPtr FeatureSetsByCameraLatestPtr;
        typedef ConstFeatureSetsByCameraPtr ConstFeatureSetsByCameraLatestPtr;
        typedef FeatureSetsByCamera FeatureSetsByCameraLatest;

        //! Returns the attached featureSetsByCamera data upgraded to the latest version.
        /*!
            \return null pointer or a pointer to the latest featureSetsByCamera data
                defined in coredata.
        */
        SM_COREDATA_API FeatureSetsByCameraLatestPtr featureSetsByCamera(EngineOutputData&);

        //! Adds the latest featureSetsByCamera data if it doesn't already exist.
        /*!
            \return A pointer to the latest featureSetsByCamera data
                defined in coredata.
        */
        SM_COREDATA_API FeatureSetsByCameraLatestPtr addFeatureSetsByCameraIfMissing(EngineOutputData&);

        typedef ImageCollectionOutputDataPtr ImageCollectionOutputDataLatestPtr;
        typedef ConstImageCollectionOutputDataPtr ConstImageCollectionOutputDataLatestPtr;
        typedef ImageCollectionOutputData ImageCollectionOutputDataLatest;

        //! Returns the attached image collection output data upgraded to the latest version.
        /*!
            \return null pointer or a pointer to the latest image collection output data
                defined in coredata.
        */
        SM_COREDATA_API ImageCollectionOutputDataLatestPtr imageCollectionOutputData(EngineOutputData&);

        //! Adds the latest image collection output data if it doesn't already exist.
        /*!
            \return A pointer to the latest image collection output data
                defined in coredata.
        */
        SM_COREDATA_API ImageCollectionOutputDataLatestPtr addImageCollectionOutputDataIfMissing(EngineOutputData&);

        typedef InertiaOutputDataPtr InertiaOutputDataLatestPtr;
        typedef ConstInertiaOutputDataPtr ConstInertiaOutputDataLatestPtr;
        typedef InertiaOutputData InertiaOutputDataLatest;

        //! Returns the attached inertia output data upgraded to the latest version.
        /*!
            \return null pointer or a pointer to the latest interia output data
                defined in coredata.
        */
        SM_COREDATA_API InertiaOutputDataLatestPtr inertiaOutputData(EngineOutputData&);

        //! Adds the latest inertia output data if it doesn't already exist.
        /*!
            \return A pointer to the latest inertia output data
                defined in coredata.
        */
        SM_COREDATA_API InertiaOutputDataLatestPtr addInertiaOutputDataIfMissing(EngineOutputData&);


        typedef FaceOutputDataV2Ptr FaceOutputDataLatestPtr;
        typedef ConstFaceOutputDataV2Ptr ConstFaceOutputDataLatestPtr;
        typedef FaceOutputDataV2 FaceOutputDataLatest;

        //! Returns the attached face output data upgraded to the latest version.
        /*!
            \return null pointer or a pointer to the latest face output data
                defined in coredata.
        */
        SM_COREDATA_API FaceOutputDataLatestPtr faceOutputData(FaceSetOutputDataLatest&);

        //! Adds the latest face output data if it doesn't already exist.
        /*!
            \return A pointer to the latest face output data
                defined in coredata.
        */
        SM_COREDATA_API FaceOutputDataLatestPtr addFaceOutputDataIfMissing(FaceSetOutputDataLatest&);

        typedef GazeIntersectionOutputDataV4Ptr GazeIntersectionOutputDataLatestPtr;
        typedef ConstGazeIntersectionOutputDataV4Ptr ConstGazeIntersectionOutputDataLatestPtr;
        typedef GazeIntersectionOutputDataV4 GazeIntersectionOutputDataLatest;

        /*! \brief Returns the merged gaze intersection output data object
        */
        SM_COREDATA_API GazeIntersectionOutputDataV4Ptr gazeIntersectionOutputDataLatest(WorldOutputDataLatest&);

        //\}


        /*!
            \name FaceSetOutputData Migration

            The following functions move any head, eye or face output data immediately 
            under the EngineOutputData to the first FaceSetOutputData creating one
            if necessary.
        */
        //\{

        /*! \brief Migrates EOD objects from the old single face structure to using FaceSetOutputDataLatest.

            Checks if we there exists head, eye or face data immediately under \a parent.
            If so, then upgrade to latest version and move under the first FaceSetOutputDataLatest
            creating one if necessary. 
            If there already exists objects with that id then throws.
        */
        SM_COREDATA_API void migrateFaceSetOutputData(EngineOutputData& parent);

        SM_COREDATA_API FaceOutputDataLatestPtr faceOutputData(EngineOutputData&);
        SM_COREDATA_API FaceOutputDataLatestPtr addFaceOutputDataIfMissing(EngineOutputData&);
        SM_COREDATA_API HeadOutputDataLatestPtr headOutputData(EngineOutputData&);
        SM_COREDATA_API HeadOutputDataLatestPtr addHeadOutputDataIfMissing(EngineOutputData&);
        SM_COREDATA_API EyeOutputDataLatestPtr eyeOutputData(EngineOutputData&);
        SM_COREDATA_API EyeOutputDataLatestPtr addEyeOutputDataIfMissing(EngineOutputData&);
        //\}


        
    }
}
#endif



