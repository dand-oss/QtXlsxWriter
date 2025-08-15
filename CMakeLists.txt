cmake_minimum_required(VERSION 3.31)
project(xlsx
    LANGUAGES CXX
    VERSION 1.1.0
    DESCRIPTION "Read/Write xlsx"
    )

###############
# ASI default settings
list(APPEND CMAKE_MODULE_PATH "$ENV{ASV_CMAKE}")
include(asv_cmake_defaults)
asv_cmake_defaults( )
###############

set(libname xlsx)

find_package(Qt5 CONFIG REQUIRED
    PATHS ${ASV_PLAT_PORTS}/qt5 NO_DEFAULT_PATH
    COMPONENTS
        Gui
)
asv_print_package_properties(
    Qt5::Gui
)

# -----------------------
# Public header list
# -----------------------
set(public_headers
    src/xlsx/xlsxabstractooxmlfile.h
    src/xlsx/xlsxabstractsheet.h
    src/xlsx/xlsxanchor.h
    src/xlsx/xlsxcell.h
    src/xlsx/xlsxcellformula.h
    src/xlsx/xlsxcellrange.h
    src/xlsx/xlsxcellreference.h
    src/xlsx/xlsxchart.h
    src/xlsx/xlsxchartsheet.h
    src/xlsx/xlsxconditionalformatting.h
    src/xlsx/xlsxdatavalidation.h
    src/xlsx/xlsxdocument.h
    src/xlsx/xlsxdrawinganchor.h
    src/xlsx/xlsxformat.h
    src/xlsx/xlsxglobal.h
    src/xlsx/xlsxoleobject.h
    src/xlsx/xlsxrichstring.h
    src/xlsx/xlsxworkbook.h
    src/xlsx/xlsxworksheet.h
)

add_library(${libname} SHARED)
asv_optimize_target(${libname})
target_link_libraries(${libname} Qt5::GuiPrivate)
set_target_properties(${libname} PROPERTIES
    AUTOMOC ON
    OUTPUT_NAME "Qt5Xlsx")

if (UNIX)
    # force linker to resolve all deps
    set_target_properties(${libname} PROPERTIES LINK_FLAGS "-Wl,--no-undefined")
endif (UNIX)

# Use file sets for public headers
target_sources(${libname} PUBLIC
    FILE_SET HEADERS
    BASE_DIRS src
    FILES ${public_headers}
)

target_sources(${libname} PRIVATE
    src/xlsx/xlsxabstractooxmlfile.cpp
    src/xlsx/xlsxabstractsheet.cpp
    src/xlsx/xlsxanchor.cpp
    src/xlsx/xlsxcell.cpp
    src/xlsx/xlsxcellformula.cpp
    src/xlsx/xlsxcellrange.cpp
    src/xlsx/xlsxcellreference.cpp
    src/xlsx/xlsxchart.cpp
    src/xlsx/xlsxchartsheet.cpp
    src/xlsx/xlsxcolor.cpp
    src/xlsx/xlsxconditionalformatting.cpp
    src/xlsx/xlsxcontenttypes.cpp
    src/xlsx/xlsxdatavalidation.cpp
    src/xlsx/xlsxdocpropsapp.cpp
    src/xlsx/xlsxdocpropscore.cpp
    src/xlsx/xlsxdocument.cpp
    src/xlsx/xlsxdrawing.cpp
    src/xlsx/xlsxdrawinganchor.cpp
    src/xlsx/xlsxformat.cpp
    src/xlsx/xlsxmediafile.cpp
    src/xlsx/xlsxnumformatparser.cpp
    src/xlsx/xlsxoleobject.cpp
    src/xlsx/xlsxrelationships.cpp
    src/xlsx/xlsxrichstring.cpp
    src/xlsx/xlsxsharedstrings.cpp
    src/xlsx/xlsxsimpleooxmlfile.cpp
    src/xlsx/xlsxstyles.cpp
    src/xlsx/xlsxtheme.cpp
    src/xlsx/xlsxutility.cpp
    src/xlsx/xlsxworkbook.cpp
    src/xlsx/xlsxworksheet.cpp
    src/xlsx/xlsxzipreader.cpp
    src/xlsx/xlsxzipwriter.cpp
    )

# libraries
install(
    TARGETS ${libname}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    FILE_SET HEADERS DESTINATION include
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

# -----------------------
# Config and version files
# -----------------------
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION       ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

# Use configure_package_config_file to properly expand @PACKAGE_INIT@
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION lib/cmake/${PROJECT_NAME}
)

# -----------------------
# CPack configuration
# -----------------------
set(CPACK_PACKAGE_NAME        "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION     "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION "Read and write xlsx with QT")
set(CPACK_PACKAGE_VENDOR      "xAI")
set(CPACK_GENERATOR           "ZIP;TGZ")
include(CPack)
