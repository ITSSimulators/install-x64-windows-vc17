#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "osgwControls" for configuration "Release"
set_property(TARGET osgwControls APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(osgwControls PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/osgwControls.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "C:/sim/Packages/install-x64-windows-vc17/lib/osgGA.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgText.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgViewer.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgSim.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgDB.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgUtil.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osg.lib;C:/sim/Packages/install-x64-windows-vc17/lib/OpenThreads.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/osgwControls.dll"
  )

list(APPEND _cmake_import_check_targets osgwControls )
list(APPEND _cmake_import_check_files_for_osgwControls "${_IMPORT_PREFIX}/lib/osgwControls.lib" "${_IMPORT_PREFIX}/bin/osgwControls.dll" )

# Import target "osgwMx" for configuration "Release"
set_property(TARGET osgwMx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(osgwMx PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/osgwMx.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "C:/sim/Packages/install-x64-windows-vc17/lib/osgGA.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgText.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgViewer.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgSim.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgDB.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgUtil.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osg.lib;C:/sim/Packages/install-x64-windows-vc17/lib/OpenThreads.lib;opengl32;glu32;osgwTools"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/osgwMx.dll"
  )

list(APPEND _cmake_import_check_targets osgwMx )
list(APPEND _cmake_import_check_files_for_osgwMx "${_IMPORT_PREFIX}/lib/osgwMx.lib" "${_IMPORT_PREFIX}/bin/osgwMx.dll" )

# Import target "osgwQuery" for configuration "Release"
set_property(TARGET osgwQuery APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(osgwQuery PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/osgwQuery.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "C:/sim/Packages/install-x64-windows-vc17/lib/osgGA.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgText.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgViewer.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgSim.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgDB.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgUtil.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osg.lib;C:/sim/Packages/install-x64-windows-vc17/lib/OpenThreads.lib;opengl32;glu32;osgwTools"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/osgwQuery.dll"
  )

list(APPEND _cmake_import_check_targets osgwQuery )
list(APPEND _cmake_import_check_files_for_osgwQuery "${_IMPORT_PREFIX}/lib/osgwQuery.lib" "${_IMPORT_PREFIX}/bin/osgwQuery.dll" )

# Import target "osgwTools" for configuration "Release"
set_property(TARGET osgwTools APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(osgwTools PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/osgwTools.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "C:/sim/Packages/install-x64-windows-vc17/lib/osgGA.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgText.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgViewer.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgSim.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgDB.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osgUtil.lib;C:/sim/Packages/install-x64-windows-vc17/lib/osg.lib;C:/sim/Packages/install-x64-windows-vc17/lib/OpenThreads.lib;opengl32"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/osgwTools.dll"
  )

list(APPEND _cmake_import_check_targets osgwTools )
list(APPEND _cmake_import_check_files_for_osgwTools "${_IMPORT_PREFIX}/lib/osgwTools.lib" "${_IMPORT_PREFIX}/bin/osgwTools.dll" )

# Import target "osgdb_osgobjects" for configuration "Release"
set_property(TARGET osgdb_osgobjects APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(osgdb_osgobjects PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/osgdb_osgobjects.dll"
  )

list(APPEND _cmake_import_check_targets osgdb_osgobjects )
list(APPEND _cmake_import_check_files_for_osgdb_osgobjects "${_IMPORT_PREFIX}/bin/osgdb_osgobjects.dll" )

# Import target "osgdb_osgwTools" for configuration "Release"
set_property(TARGET osgdb_osgwTools APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(osgdb_osgwTools PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/osgdb_osgwTools.dll"
  )

list(APPEND _cmake_import_check_targets osgdb_osgwTools )
list(APPEND _cmake_import_check_files_for_osgdb_osgwTools "${_IMPORT_PREFIX}/bin/osgdb_osgwTools.dll" )

# Import target "osgdb_skeleton" for configuration "Release"
set_property(TARGET osgdb_skeleton APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(osgdb_skeleton PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/osgdb_skeleton.dll"
  )

list(APPEND _cmake_import_check_targets osgdb_skeleton )
list(APPEND _cmake_import_check_files_for_osgdb_skeleton "${_IMPORT_PREFIX}/bin/osgdb_skeleton.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
