cmake_minimum_required(VERSION 3.16)
project(voiXXX-plugin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(OBS REQUIRED)

include_directories(${OBS_INCLUDE_DIRS})
link_directories(${OBS_LIBRARY_DIRS})

add_library(voiXXX-plugin MODULE src/voiXXX-plugin.cpp src/voiXXX-plugin.h)
target_link_libraries(voiXXX-plugin Qt5::Core Qt5::Widgets ${OBS_LIBRARIES})

# Configuración para Windows
if(WIN32)
    set_target_properties(voiXXX-plugin PROPERTIES SUFFIX ".dll")
endif()