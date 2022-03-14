#v1.0 copyright Comine.com 20220314M0950
#
#
#   
#       $ mkdir build
#       $ cd build
#       $ cmake <directory>  -DCMAKE_INSTALL_PREFIX=<targetdir>
#       $ cmake --build . --config Release --target install
#

cmake_minimum_required(VERSION 3.12)

########################################################
project(Main)
file(GLOB msource "*.h" "*.cpp")
add_executable(Main ${msource} )
install(TARGETS Main DESTINATION bin)


