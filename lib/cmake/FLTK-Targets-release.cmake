#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "fltk_z" for configuration "Release"
set_property(TARGET fltk_z APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_z PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk_z.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_z )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_z "${_IMPORT_PREFIX}/lib/fltk_z.lib" )

# Import target "fltk_z_SHARED" for configuration "Release"
set_property(TARGET fltk_z_SHARED APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_z_SHARED PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/fltk_z_SHARED.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libfltk_z_SHARED.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_z_SHARED )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_z_SHARED "${_IMPORT_PREFIX}/lib/fltk_z_SHARED.lib" "${_IMPORT_PREFIX}/bin/libfltk_z_SHARED.dll" )

# Import target "fltk_png" for configuration "Release"
set_property(TARGET fltk_png APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_png PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "fltk_z"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk_png.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_png )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_png "${_IMPORT_PREFIX}/lib/fltk_png.lib" )

# Import target "fltk_png_SHARED" for configuration "Release"
set_property(TARGET fltk_png_SHARED APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_png_SHARED PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/fltk_png_SHARED.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "fltk_z"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libfltk_png_SHARED.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_png_SHARED )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_png_SHARED "${_IMPORT_PREFIX}/lib/fltk_png_SHARED.lib" "${_IMPORT_PREFIX}/bin/libfltk_png_SHARED.dll" )

# Import target "fluid" for configuration "Release"
set_property(TARGET fluid APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fluid PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/fluid.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS fluid )
list(APPEND _IMPORT_CHECK_FILES_FOR_fluid "${_IMPORT_PREFIX}/bin/fluid.exe" )

# Import target "fltk" for configuration "Release"
set_property(TARGET fltk APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "comctl32"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk "${_IMPORT_PREFIX}/lib/fltk.lib" )

# Import target "fltk_forms" for configuration "Release"
set_property(TARGET fltk_forms APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_forms PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "fltk"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk_forms.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_forms )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_forms "${_IMPORT_PREFIX}/lib/fltk_forms.lib" )

# Import target "fltk_images" for configuration "Release"
set_property(TARGET fltk_images APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_images PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "fltk;jpeg.lib;fltk_z;fltk_png"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk_images.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_images )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_images "${_IMPORT_PREFIX}/lib/fltk_images.lib" )

# Import target "fltk_gl" for configuration "Release"
set_property(TARGET fltk_gl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_gl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "fltk;opengl32;glu32"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/fltk_gl.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_gl )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_gl "${_IMPORT_PREFIX}/lib/fltk_gl.lib" )

# Import target "fltk_SHARED" for configuration "Release"
set_property(TARGET fltk_SHARED APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_SHARED PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/fltk_SHARED.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "comctl32"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libfltk_SHARED.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_SHARED )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_SHARED "${_IMPORT_PREFIX}/lib/fltk_SHARED.lib" "${_IMPORT_PREFIX}/bin/libfltk_SHARED.dll" )

# Import target "fltk_forms_SHARED" for configuration "Release"
set_property(TARGET fltk_forms_SHARED APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_forms_SHARED PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/fltk_forms_SHARED.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "fltk"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libfltk_forms_SHARED.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_forms_SHARED )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_forms_SHARED "${_IMPORT_PREFIX}/lib/fltk_forms_SHARED.lib" "${_IMPORT_PREFIX}/bin/libfltk_forms_SHARED.dll" )

# Import target "fltk_images_SHARED" for configuration "Release"
set_property(TARGET fltk_images_SHARED APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_images_SHARED PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/fltk_images_SHARED.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "fltk;jpeg.lib;fltk_png;fltk_z"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libfltk_images_SHARED.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_images_SHARED )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_images_SHARED "${_IMPORT_PREFIX}/lib/fltk_images_SHARED.lib" "${_IMPORT_PREFIX}/bin/libfltk_images_SHARED.dll" )

# Import target "fltk_gl_SHARED" for configuration "Release"
set_property(TARGET fltk_gl_SHARED APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(fltk_gl_SHARED PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/fltk_gl_SHARED.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "fltk;opengl32;glu32"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libfltk_gl_SHARED.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS fltk_gl_SHARED )
list(APPEND _IMPORT_CHECK_FILES_FOR_fltk_gl_SHARED "${_IMPORT_PREFIX}/lib/fltk_gl_SHARED.lib" "${_IMPORT_PREFIX}/bin/libfltk_gl_SHARED.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
