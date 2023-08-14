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
#ifndef SM_COREDATA_EOD_EODCONVERSION_H
#define SM_COREDATA_EOD_EODCONVERSION_H

//! \file
#include "eod/gazeintersectionoutputdatav1.h"
#include "eod/gazeintersectionoutputdatav2.h"
#include "eod/gazeintersectionoutputdatav3.h"
#include "eod/gazeintersectionoutputdatav4.h"
#include "eod/faceoutputdata.h"
#include "eod/faceoutputdatav2.h"
#include "eod/headoutputdata.h"
#include "eod/headoutputdatav2.h"
#include "eod/gpsoutputdata.h"
#include "eod/gpsoutputdatav2.h"
#include "eod/worldoutputdata.h"
#include "eod/worldoutputdatav2.h"

namespace sm
{
    namespace eod
    {
        /*!
            \name EOD Conversions

            The following types and functions convert between versions of EOD objects.
            Some of the old EOD objects allow construction and assignment between versions
            but with the number of versions of some objects increasing this is becoming to
            hard to maintain. The functions in this file allow conversion from a particular
            version to the next and previous versions. Though this may not be as efficient as
            allowing conversion to skip versions for an EOD with 4 versions we reduce the number
            of conversion functions from 12 to 6.

            All conversion functions clone the sub-objects of the object being converted from.

            @{
        */

        /*! \brief Converts from GazeIntersectionOutputDataV1 to GazeIntersectionOutputDataV2.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GazeIntersectionOutputDataV1& old_object, GazeIntersectionOutputDataV2& new_object);

        /*! \brief Converts from GazeIntersectionOutputDataV2 to GazeIntersectionOutputDataV3.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GazeIntersectionOutputDataV2& old_object, GazeIntersectionOutputDataV3& new_object);

        /*! \brief Converts from GazeIntersectionOutputDataV3 to GazeIntersectionOutputDataV4.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GazeIntersectionOutputDataV3& old_object, GazeIntersectionOutputDataV4& new_object);

        /*! \brief Converts from GazeIntersectionOutputDataV2 to GazeIntersectionOutputDataV1.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GazeIntersectionOutputDataV2& old_object, GazeIntersectionOutputDataV1& new_object);

        /*! \brief Converts from GazeIntersectionOutputDataV3 to GazeIntersectionOutputDataV2.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GazeIntersectionOutputDataV3& old_object, GazeIntersectionOutputDataV2& new_object);

        /*! \brief Converts from GazeIntersectionOutputDataV4 to GazeIntersectionOutputDataV3.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GazeIntersectionOutputDataV4& old_object, GazeIntersectionOutputDataV3& new_object);

        /*! \brief Converts from FaceOutputData to FaceOutputDataV2.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const FaceOutputData& old_object, FaceOutputDataV2& new_object);

        /*! \brief Converts from FaceOutputDataV2 to FaceOutputData.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const FaceOutputDataV2& old_object, FaceOutputData& new_object);

        /*! \brief Converts from GPSOutputData to GPSOutputDataV2.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GPSOutputData& old_object, GPSOutputDataV2& new_object);

        /*! \brief Converts from GPSOutputDataV2 to GPSOutputData.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GPSOutputDataV2& old_object, GPSOutputData& new_object);

        /*! \brief Converts from HeadOutputData to HeadOutputDataV2.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const HeadOutputData& old_object, HeadOutputDataV2& new_object);

        /*! \brief Converts from HeadOutputDataV2 to HeadOutputData.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const HeadOutputDataV2& old_object, HeadOutputData& new_object);

        /*! \brief Converts from WorldOutputData to WorldOutputDataV2.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const WorldOutputData& old_object, WorldOutputDataV2& new_object);

        /*! \brief Converts from WorldOutputDataV2 to WorldOutputData.

            All child objects of \a old_object are cloned.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const WorldOutputDataV2& old_object, WorldOutputData& new_object);

        /*! \brief Converts from GPSCoordinateV1 to GPSCoordinateV2.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GPSCoordinateV1& old_object, GPSCoordinateV2& new_object);

        /*! \brief Converts from GPSCoordinateV2 to GPSCoordinateV1.

            \param [in] old_object The object to convert from.
            \param [out] new_object The object to initialized.
        */
        SM_COREDATA_API void convert(const GPSCoordinateV2& old_object, GPSCoordinateV1& new_object);

        //! @} -end name EOD Conversions


    }
}
#endif




