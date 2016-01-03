## Copyright (c) 2015-  Félix Piédallu <felix@piedallu.me>
##
## This file is part of FretStorm.
##
## FretStorm is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by the
## Free Software Foundation, either version 2 of the License, or
## (at your option) any later version.
##
## FretStorm is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
## See the GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "cmake")


####################################################################
#   Project configuration
####################################################################

project (FretStorm)
set     (FretStorm_VERSION_MAJOR 1)
set     (FretStorm_VERSION_MINOR 0)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/FretStormConfig.h.in"
    "${PROJECT_SOURCE_DIR}/src/FretStormConfig.h"
)

####################################################################
#   C++11 support
####################################################################
set     (CMAKE_CXX_STANDARD 11)


####################################################################
#   Libraries
####################################################################
find_package(Boost 1.40
    COMPONENTS program_options filesystem system
    REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(Sqlite3)
include_directories(${Sqlite3_INCLUDE_DIR})


####################################################################
#   Main executable
####################################################################

add_executable(FretStorm
    src/fretstorm.cpp
    src/midi/BinUtils.cpp
    src/midi/MidiEvent.cpp
    src/midi/MidiFile.cpp
    src/midi/MidiTrack.cpp
    src/midi/midi.cpp
    src/scanner/node.cpp
)
include_directories (
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/src/game"
    "${PROJECT_SOURCE_DIR}/src/midi"
    "${PROJECT_SOURCE_DIR}/src/scanner"
)

target_link_libraries(FretStorm
    ${Boost_LIBRARIES}
    ${Sqlite3_LIBRARY}
)


