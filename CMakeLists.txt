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

set( THIRD_PARTY_LIBS 
    ${OpenCV_LIBS}
  #  ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
)
############### source and test ######################
include_directories(${PROJECT_SOURCE_DIR}/include )
#添加含有CMakeLists文件的子文件夹
add_subdirectory( src )
