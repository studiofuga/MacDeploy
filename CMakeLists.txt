PROJECT(MacDeploy)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)


find_package(Boost 1.64 REQUIRED COMPONENTS log program_options filesystem)

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

include_directories(${Boost_INCLUDE_DIR})

add_executable(MacDeploy main.cpp Target.cpp Target.h Dependency.cpp Dependency.h ComponentInfo.cpp ComponentInfo.h)

target_link_libraries(MacDeploy Boost::filesystem Boost::system Boost::log Boost::thread Boost::program_options)

