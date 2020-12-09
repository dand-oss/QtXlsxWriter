cmake_minimum_required(VERSION 3.0)
project(xlsx CXX)

###############
# ASI default settings
list(APPEND CMAKE_MODULE_PATH "$ENV{ASV_CMAKE}")
include(asv_cmake_defaults)
asv_cmake_defaults( )
###############

set(libname xlsx)

message(STATUS ${CMAKE_CURRENT_LIST_FILE})

list(APPEND CMAKE_PREFIX_PATH ${AQTDIR})
set(QT_LIBINFIX "ASV")
find_package(Qt5 CONFIG REQUIRED COMPONENTS Gui)

# get header files that are not *_p.h
file(GLOB tmp_hdr ${CMAKE_CURRENT_SOURCE_DIR}/src/xlsx/*.h)
foreach(hdr_file ${tmp_hdr})
    string(REGEX MATCH ".*_p.h" hdr_match ${hdr_file})
    if ("${hdr_match}" STREQUAL "")
        list(APPEND hdrs ${hdr_file})
    endif()
endforeach()

add_library(${libname} SHARED)
target_link_libraries(${libname} Qt5::GuiPrivate)
set_target_properties(${libname} PROPERTIES AUTOMOC ON)
set_target_properties(${libname} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
if (UNIX)
    # force linker to resolve all deps
    set_target_properties(${libname} PROPERTIES LINK_FLAGS "-Wl,--no-undefined")
endif (UNIX)

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

    ${hdrs}
    )

# libraries
install(
    TARGETS ${libname}
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
)

install(
    FILES ${hdrs}
    DESTINATION include/${libname}
    )
