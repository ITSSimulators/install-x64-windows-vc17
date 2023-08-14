#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "osgAudio" for configuration "Release"
set_property(TARGET osgAudio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(osgAudio PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/osgAudio.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "E:/sim/Packages/install-2-x64-win64-vc14/lib/alut.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/OpenAL32.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/ogg.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/vorbis.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/vorbisfile.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osg.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgDB.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgUtil.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgGA.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgText.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgViewer.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/OpenThreads.lib;openalpp"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/osgAudio.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS osgAudio )
list(APPEND _IMPORT_CHECK_FILES_FOR_osgAudio "${_IMPORT_PREFIX}/lib/osgAudio.lib" "${_IMPORT_PREFIX}/bin/osgAudio.dll" )

# Import target "osgdb_osgAudio" for configuration "Release"
set_property(TARGET osgdb_osgAudio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(osgdb_osgAudio PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/osgdb_osgAudio.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS osgdb_osgAudio )
list(APPEND _IMPORT_CHECK_FILES_FOR_osgdb_osgAudio "${_IMPORT_PREFIX}/bin/osgdb_osgAudio.dll" )

# Import target "openalpp" for configuration "Release"
set_property(TARGET openalpp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(openalpp PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/openalpp.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "E:/sim/Packages/install-2-x64-win64-vc14/lib/alut.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/OpenAL32.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/ogg.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/vorbis.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/vorbisfile.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osg.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgDB.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgUtil.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgGA.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgText.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/osgViewer.lib;E:/sim/Packages/install-2-x64-win64-vc14/lib/OpenThreads.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/openalpp.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS openalpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_openalpp "${_IMPORT_PREFIX}/lib/openalpp.lib" "${_IMPORT_PREFIX}/bin/openalpp.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
