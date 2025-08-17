cmake_minimum_required(VERSION 3.30)
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

find_package(Qt5 CONFIG REQUIRED
    PATHS ${ASV_PLAT_PORTS}/qt5 NO_DEFAULT_PATH
    COMPONENTS
      Gui
)
asv_print_package_properties(
    Qt5::Gui
)

add_subdirectory(src/xlsx)
