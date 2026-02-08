cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
project(ParseCFile)

set(CMAKE_CXX_STANDARD 17) # Updated to C++17 for better modern C++ support
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()

# Set the source directory
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# Find all .cpp files recursively
file(GLOB_RECURSE PROJECT_SOURCES "${SOURCE_DIR}/*.cpp")
message(STATUS "Project sources: ${PROJECT_SOURCES}")

# Find all header files recursively to include their directories
file(GLOB_RECURSE HEADER_FILES "${SOURCE_DIR}/*.h")
foreach(header_file ${HEADER_FILES})
    get_filename_component(header_dir ${header_file} DIRECTORY)
    list(APPEND HEADER_DIRS ${header_dir})
endforeach()
if(HEADER_DIRS)
    list(REMOVE_DUPLICATES HEADER_DIRS)
endif()

# Dependencies
# spdlog
set(SPDLOG_BUILD_DIR "${PROJECT_SOURCE_DIR}/libs/spdlog/build")
list(APPEND CMAKE_PREFIX_PATH "${SPDLOG_BUILD_DIR}")
find_package(spdlog REQUIRED)

# string_util
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/string_util)

# TinyXML2
set(TINYXML2_DIR "${PROJECT_SOURCE_DIR}/src/tinyxml2")
add_library(TinyXML2 STATIC ${TINYXML2_DIR}/tinyxml2.cpp)
target_include_directories(TinyXML2 PUBLIC ${TINYXML2_DIR})


# Add the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${HEADER_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/libs/spdlog/include
    # ${PROJECT_SOURCE_DIR}/src/tinyxml2 # Already handled by target_include_directories for TinyXML2
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    spdlog::spdlog
    string_util
    readline
    TinyXML2
)

# Optional: Libclang support (commented out as in original, but cleaner)
# find_package(Clang)
# if(Clang_FOUND)
#     target_include_directories(${PROJECT_NAME} PRIVATE ${CLANG_INCLUDE_DIRS})
#     target_link_libraries(${PROJECT_NAME} PRIVATE ${CLANG_LIBS})
# endif()

