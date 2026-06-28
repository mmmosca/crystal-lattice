#[[
Copyright (C) 2026 Marco M. Mosca

This file is part of periodic-point-cloud.

periodic-point-cloud is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

periodic-point-cloud is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with periodic-point-cloud. If not, see <https://www.gnu.org/licenses/>.
*]]
cmake_minimum_required (VERSION 3.16)

project (
    crystal_lattice
    VERSION 0.1.0
    DESCRIPTION  "Crystal Lattice manager"
    LANGUAGES CXX
)

include(FetchContent)

if(DEFINED BUILD_TESTING)
    set(_BUILD_TESTING_SAVE "${BUILD_TESTING}")
    set(_BUILD_TESTING_WAS_DEFINED TRUE)
endif()

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    Eigen3
    URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
)
FetchContent_MakeAvailable(Eigen3)
FetchContent_Declare(
    periodic_point_cloud
    URL https://github.com/mmmosca/periodic-point-cloud/archive/refs/tags/0.1.0.tar.gz
)
FetchContent_MakeAvailable(periodic_point_cloud)

if(_BUILD_TESTING_WAS_DEFINED)
    set(BUILD_TESTING "${_BUILD_TESTING_SAVE}" CACHE BOOL "" FORCE)
else()
    unset(BUILD_TESTING CACHE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(crystal_lattice
    src/geom.cpp
    src/crystalattice.cpp
    src/unitcellreduction.cpp
    src/logging.cpp
)

target_include_directories(crystal_lattice
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(crystal_lattice
    PRIVATE
        Eigen3::Eigen
        periodic_point_cloud
)

if (BUILD_TESTING)
    enable_testing()
    include(GoogleTest)
    add_subdirectory ("tests")
endif()

install(
    TARGETS crystal_lattice
    EXPORT crystal_latticeTargets
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    EXPORT crystal_latticeTargets
    FILE crystal_latticeTargets.cmake
    NAMESPACE crystal_lattice::
    DESTINATION lib/cmake/crystal_lattice
)
