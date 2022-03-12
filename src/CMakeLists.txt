#v1.1 copyright Comine.com 20211228T1508
#
#
#   
#       $ mkdir build
#       $ cd build
#       $ cmake <directory>  -DCMAKE_INSTALL_PREFIX=<targetdir>
#       $ cmake --build . --config Release --target install
#

cmake_minimum_required(VERSION 3.21)
SET(CMAKE_TOOLCHAIN_FILE "c:/vcpkg/scripts/buildsystems/vcpkg.cmake")

########################################################
project(Main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_EXAMPLE ON)
option(BUILD_SHARED_LIBS "Build shared library" OFF) 
set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules")

if(MSVC)
	set (TRIPLET "x64-windows-static")
	set (VCPKG_ROOT  "c:/vcpkg" )
	set(ZLIB_INCLUDE_DIR "${VCPKG_ROOT}/installed/${TRIPLET}/include" )
	set(ZLIB_LIBRARY "${VCPKG_ROOT}/installed/${TRIPLET}/lib/zlib.lib" )
endif()

find_package(ZLIB REQUIRED) 

file(GLOB msource "*.h" "*.cpp")

add_executable(Main ${msource} )

target_link_libraries(Main PRIVATE ZLIB::ZLIB)

install(TARGETS Main DESTINATION bin)


