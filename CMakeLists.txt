cmake_minimum_required(VERSION 3.5)
project(TopEval3)
set(ProjDir ${CMAKE_CURRENT_LIST_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIE")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

set(CMAKE_CXX_STANDARD 11)

#set(SOURCE_FILES tinyxml.cpp tinystr.cpp tinyxmlerror.cpp tinyxmlparser.cpp )
set(CMAKE_PREFIX_PATH $ENV{TPV_SERVER_ROOT_DIR})
set(CMAKE_INSTALL_PREFIX $ENV{TPV_SERVER_ROOT_DIR})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(OpenCV)

file(GLOB_RECURSE PROJ_CPP_SOURCES
        export/*.h sources/*.h export/*.cpp sources/*.cpp )

link_directories(/home/kuangrx/tinyxml/)
#add_library(TopTrace SHARED ${PROJ_CPP_SOURCES})
#target_include_directories(TopTrace PUBLIC export PRIVATE sources)
#target_link_libraries(TopTrace TpInference TpRender TpVideoStream TpGPUCore TpCPUCore ${OpenCV_LIBS} boost_system boost_chrono boost_thread glog pthread)

add_executable(TopEval3 main.cpp tinyxml.cpp tinystr.cpp tinyxmlerror.cpp tinyxmlparser.cpp tinystr.h tinyxml.h )
target_link_libraries(TopEval3 TpInference ${OpenCV_LIBS} glog gflags boost_filesystem boost_thread)





