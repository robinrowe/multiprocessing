# SorterThreads/CMakeLists.txt
# Created by Robin Rowe 2019-01-22
# License MIT open source

cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Project SorterThreads)
project(${Project})
enable_testing()
file(STRINGS sources.cmake SOURCES)

add_executable(producer_consumer ${SOURCES} producer_consumer.cpp)
if(NOT WIN32 AND NOT APPLE)
  target_link_libraries(producer_consumer rt pthread)
endif(NOT WIN32 AND NOT APPLE)

add_executable(test_Producer ${SOURCES} test/test_Producer.cpp)
add_test(test_Producer test_Producer)
add_executable(test_Consumer ${SOURCES} test/test_Consumer.cpp)
add_test(test_Consumer test_Consumer)
add_executable(test_Sorter ${SOURCES} test/test_Sorter.cpp)
add_test(test_Sorter test_Sorter)
