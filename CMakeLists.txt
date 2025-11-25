cmake_minimum_required(VERSION 3.25)

project(mclutils LANGUAGES CXX)

add_executable(tests
    src/fs.hpp
    src/fs.cpp
    src/log.hpp
    src/log.cpp
    src/math.hpp
    src/math.cpp
    src/string.hpp
    src/string.cpp
    src/time.hpp
    src/time.cpp
    src/vector.hpp
    tests/all.cpp)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})
target_compile_features(tests PRIVATE cxx_std_20)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME catch2
    GITHUB_REPOSITORY catchorg/Catch2
    VERSION 3.11.0)

if(catch2_ADDED)	 
    target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
endif()