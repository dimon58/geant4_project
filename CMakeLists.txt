#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(geant4_project)

set(CMAKE_MODULE_PATH
        ${Geant4_DIR}/Modules/
        ${CMAKE_MODULE_PATH})

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if (WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else ()
    find_package(Geant4 REQUIRED)
endif ()

#include (FindROOT.cmake)
find_package(ROOT REQUIRED)
#find_package(abc) -> Findabc.cmake
# -> abc_LIBRARIES
# -> abc_INCLUDE_DIR ...

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
#include(FindROOT.cmake) 
set(INCLUDE_DIRECTORIES ${ROOT_INCLUDE_DIRS})

include_directories(${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(geant4_project main.cpp ${sources} ${headers})
target_link_libraries(geant4_project ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(GEANT4_PROJECT_SCRIPTS
        macros/init.mac
        macros/init_vis.mac
        macros/vis.mac
        macros/run.mac
        )

foreach (_script ${GEANT4_PROJECT_SCRIPTS})
    configure_file(
            ${PROJECT_SOURCE_DIR}/${_script}
            ${PROJECT_BINARY_DIR}/${_script}
            COPYONLY
    )
endforeach ()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(Geant4Project DEPENDS geant4_project)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS geant4_project DESTINATION .)


