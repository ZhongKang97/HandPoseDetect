cmake_minimum_required( VERSION 2.8 )
project ( HandPoseDetect )

set( CMAKE_BUILD_TYPE "Release" )
#set( CMAKE_BUILD_TYPE "Debug" )
set( CMAKE_CXX_FLAGS "-std=c++11" )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )

############### dependencies ######################
#Boost
set(BOOST_LIBRARYDIR /usr/lib/x86_64-linux-gnu/)
find_package(Boost REQUIRED COMPONENTS  system thread)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    MESSAGE( STATUS "Boost_INCLUDE_DIRS =  ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION =  ${Boost_LIB_VERSION}.")
endif()
# OpenCV
find_package( OpenCV REQUIRED )
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
include_directories( ${OpenCV_INCLUDE_DIRS} )
#Threads
#find_package(Threads)

#python2.7
set(Python2_Version 2.7)
set(Python2_INCLUDE_DIRS "/usr/include/python2.7/")
set(Python2_LIBS "/usr/lib/python2.7/config-arm-linux-gnueabihf/libpython2.7.so")
message(STATUS "Python2 library status:")
message(STATUS "    version: ${Python2_Version}")
message(STATUS "    libraries: ${Python2_LIBS}")
message(STATUS "    include path: ${Python2_INCLUDE_DIRS}")
include_directories(${Python2_INCLUDE_DIRS})

set( THIRD_PARTY_LIBS 
    ${OpenCV_LIBS}
  #  ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    ${Python2_LIBS}
)
############### source and test ######################
include_directories(${PROJECT_SOURCE_DIR}/include )
#添加含有CMakeLists文件的子文件夹
add_subdirectory( src )
