cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(blowfish)


IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release
RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)


# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

# Include directories needed for this compile
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories("${PROJECT_SOURCE_DIR}/../LightOutput-1.2/include")
include_directories("${PROJECT_SOURCE_DIR}/../G4Lucid-1.1/include")

# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
#file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


# get the extra libraries needed
find_library(G4Lucid_lib G4Lucid ${PROJECT_SOURCE_DIR}/../G4Lucid-1.1 )
find_library(Lucid_lib lucid /home/lucid/lib )
find_library(LightOutput_lib LightOutput ${PROJECT_SOURCE_DIR}/../LightOutput-1.2 )

# Add the executable, and link it to the Geant4 libraries
add_executable(blowfish blowfish.cc ${sources}) 
target_link_libraries(blowfish ${Geant4_LIBRARIES} ${G4Lucid_lib} ${Lucid_lib}
${LightOutput_lib})
 
set(TOCOPY
  vis.mac
  gui.mac
  )

foreach(_script ${TOCOPY})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

