cmake_minimum_required(VERSION 3.30)

set(libname xlsx)

message(STATUS ${CMAKE_CURRENT_LIST_FILE})

# -----------------------
# Public header list
# -----------------------
set(public_headers
    xlsxabstractooxmlfile.h
    xlsxabstractsheet.h
    xlsxanchor.h
    xlsxcell.h
    xlsxcellformula.h
    xlsxcellrange.h
    xlsxcellreference.h
    xlsxchart.h
    xlsxchartsheet.h
    xlsxconditionalformatting.h
    xlsxdatavalidation.h
    xlsxdocument.h
    xlsxdrawinganchor.h
    xlsxformat.h
    xlsxglobal.h
    xlsxoleobject.h
    xlsxrichstring.h
    xlsxworkbook.h
    xlsxworksheet.h
)

# -----------------------
# Library target
# -----------------------
add_library(${libname} SHARED)

# Bundle all headers
set(public_header_sources)
foreach(h IN LISTS public_headers)
  list(APPEND public_header_sources
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${h}>
    $<INSTALL_INTERFACE:include/xlsx/${h}>
  )
endforeach()

target_sources(${libname}
  PUBLIC  ${public_header_sources}
  PRIVATE 
    xlsxabstractooxmlfile.cpp
    xlsxabstractsheet.cpp
    xlsxanchor.cpp
    xlsxcell.cpp
    xlsxcellformula.cpp
    xlsxcellrange.cpp
    xlsxcellreference.cpp
    xlsxchart.cpp
    xlsxchartsheet.cpp
    xlsxcolor.cpp
    xlsxconditionalformatting.cpp
    xlsxcontenttypes.cpp
    xlsxdatavalidation.cpp
    xlsxdocpropsapp.cpp
    xlsxdocpropscore.cpp
    xlsxdocument.cpp
    xlsxdrawing.cpp
    xlsxdrawinganchor.cpp
    xlsxformat.cpp
    xlsxmediafile.cpp
    xlsxnumformatparser.cpp
    xlsxoleobject.cpp
    xlsxrelationships.cpp
    xlsxrichstring.cpp
    xlsxsharedstrings.cpp
    xlsxsimpleooxmlfile.cpp
    xlsxstyles.cpp
    xlsxtheme.cpp
    xlsxutility.cpp
    xlsxworkbook.cpp
    xlsxworksheet.cpp
    xlsxzipreader.cpp
    xlsxzipwriter.cpp

    # Private headers
    xlsxabstractooxmlfile_p.h
    xlsxabstractsheet_p.h
    xlsxcell_p.h
    xlsxcellformula_p.h
    xlsxchart_p.h
    xlsxchartsheet_p.h
    xlsxcolor_p.h
    xlsxconditionalformatting_p.h
    xlsxcontenttypes_p.h
    xlsxdatavalidation_p.h
    xlsxdocpropsapp_p.h
    xlsxdocpropscore_p.h
    xlsxdocument_p.h
    xlsxdrawing_p.h
    xlsxformat_p.h
    xlsxmediafile_p.h
    xlsxnumformatparser_p.h
    xlsxrelationships_p.h
    xlsxrichstring_p.h
    xlsxsharedstrings_p.h
    xlsxsimpleooxmlfile_p.h
    xlsxstyles_p.h
    xlsxtheme_p.h
    xlsxutility_p.h
    xlsxworkbook_p.h
    xlsxworksheet_p.h
    xlsxzipreader_p.h
    xlsxzipwriter_p.h
)

target_include_directories(${libname}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(${libname} PROPERTIES
  PUBLIC_HEADER  "${public_headers}"
  AUTOMOC        ON
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

if(UNIX)
  set_target_properties(${libname} PROPERTIES LINK_FLAGS "-Wl,--no-undefined")
endif()

target_link_libraries(${libname}
  PUBLIC Qt::GuiPrivate
)

# -----------------------
# Install library and headers
# -----------------------
install(TARGETS ${libname}
  EXPORT        ${PROJECT_NAME}Targets
  LIBRARY       DESTINATION lib
  RUNTIME       DESTINATION bin
  ARCHIVE       DESTINATION lib
  PUBLIC_HEADER DESTINATION include/xlsx
)

install(EXPORT ${PROJECT_NAME}Targets
  FILE      ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME}
)
