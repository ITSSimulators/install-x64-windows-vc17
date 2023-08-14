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
#ifndef SM_COREDATA_EOD_SDK_H
#define SM_COREDATA_EOD_SDK_H

//! @file

// CORE DATA MAIN INCLUDE FILE
// ----------------------------------
// Include this file into your project to use the CoreData API
// All objects and methods are inside the namespace "sm::eod"
// Add the "using namespace sm::eod;" using-directive to the top of your .cpp / .c++ source files.

#include "eod/basics.h"

#include "eod/headintersectionoutputdatav1.h"
#include "eod/compressedserializable.h"
#include "eod/compressedserializabletoken.h"
#include "eod/customeventoutputdata.h"
#include "eod/engineoutputbase.h"
#include "eod/engineoutputdata.h"
#include "eod/enginestateoutputdata.h"
#include "eod/eyeclosureoutputdata.h"
#include "eod/eyeoutputdata.h"
#include "eod/faceoutputdata.h"
#include "eod/faceoutputdatav2.h"
#include "eod/facesetoutputdata.h"
#include "eod/facetextureoutputdata.h"
#include "eod/featurecircle.h"
#include "eod/featureline.h"
#include "eod/featureoutputdata.h"
#include "eod/featurepoint.h"
#include "eod/featurerect.h"
#include "eod/featureset.h"
#include "eod/featuresetsbycamera.h"
#include "eod/flmids.h"
#include "eod/flmtypes.h"
#include "eod/gazeintersectionoutputdatabase.h"
#include "eod/gazeintersectionoutputdatav1.h"
#include "eod/gazeintersectionoutputdatav2.h"
#include "eod/gazeintersectionoutputdatav3.h"
#include "eod/gazeintersectionoutputdatav4.h"
#include "eod/gazeoutputdata.h"
#include "eod/gpsoutputdata.h"
#include "eod/gpsoutputdatav2.h"
#include "eod/headoutputdata.h"
#include "eod/headoutputdatav2.h"
#include "eod/headintersectionoutputdatav2.h"
#include "eod/headtrackerstateoutputdata.h"
#include "eod/imagecollectionoutputdata.h"
#include "eod/imageoutputdata.h"
#include "eod/inertiaoutputdata.h"
#include "eod/intersectionoutputbase.h"
#include "eod/intersectionoutputbasev2.h"
#include "eod/irpodstateoutputdata.h"
#include "eod/pupiloutputdata.h"
#include "eod/serializable.h"
#include "eod/serializablecomposite.h"
#include "eod/serializablefactory.h"
#include "eod/timingoutputdata.h"
#include "eod/worldoutputdata.h"
#include "eod/worldoutputdatav2.h"
#include "eod/eodupgrade.h"
#include "eod/eodconversion.h"

// utils
#include "eod/utils/geomutils.h"
#include "eod/utils/outputdatautils.h"


// io
#include "eod/io/datagramsocket.h"
#include "eod/io/devicesettings.h"
#include "eod/io/engineoutputdatafilereader.h"
#include "eod/io/engineoutputdatafilewriter.h"
#include "eod/io/engineoutputdatatcpclient.h"
#include "eod/io/inetaddress.h"
#include "eod/io/outputdataprinter.h"
#include "eod/io/portnumbervalidatorconsts.h"
#include "eod/io/serialport.h"
#include "eod/io/serialporterror.h"
#include "eod/io/socketerror.h"
#include "eod/io/tcpclient.h"
#include "eod/io/tcpendpoint.h"
#include "eod/io/tcpsocket.h"
#include "eod/io/stringfuns.h"
#include "eod/io/filereader.h"
#include "eod/io/filewriter.h"
#include "eod/io/decompressingfilereader.h"
#include "eod/io/compressingfilewriter.h"
#include "eod/io/serializablecompressor.h"
#include "eod/io/serializabledecompressor.h"


#endif

