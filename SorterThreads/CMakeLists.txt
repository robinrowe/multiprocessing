# SorterThreads/CMakeLists.txt
# Created by Robin Rowe 2019-01-22
# License MIT open source

cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Project SorterThreads)
project(SorterThreads)
enable_testing()
file(STRINGS sources.cmake SOURCES)
add_library(SorterThreads_lib ${SOURCES})
link_libraries(SorterThreads_lib)
if(NOT WIN32 AND NOT APPLE)
	link_libraries(rt pthread)
endif(NOT WIN32 AND NOT APPLE)

add_executable(ProducerConsumer ProducerConsumer.cpp)
add_executable(generate generate.cpp)

add_executable(test_Producer test/test_Producer.cpp)
add_test(test_Producer test_Producer)
add_executable(test_Consumer test/test_Consumer.cpp)
add_test(test_Consumer test_Consumer)
add_executable(test_Sorter test/test_Sorter.cpp)
add_test(test_Sorter test_Sorter)
add_executable(test_ThreadPool test/test_ThreadPool.cpp)
add_test(test_ThreadPool test_ThreadPool)
add_executable(test_Task test/test_Task.cpp)
add_test(test_Task test_Task)
add_executable(test_SortItem test/test_SortItem.cpp)
add_test(test_SortItem test_SortItem)
