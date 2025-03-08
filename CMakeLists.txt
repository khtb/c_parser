cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
project(ParseCFile)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find libclang
find_package(Clang REQUIRED)

set(CMAKE_BUILD_TYPE Debug)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()

# Set the source directory where all .cpp files are located
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# Find all .cpp files in the source directory and subdirectories
file(GLOB_RECURSE PROJECT_SOURCES "${SOURCE_DIR}/*.cpp")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0") # Enable GDB debugging

# # Recursively find all directories containing header files in 'include' directory
file(GLOB_RECURSE HEADER_DIRECTORIES ""${SOURCE_DIR}/*.h"")

# # Add these directories as include directories
include_directories(${HEADER_DIRECTORIES})

# add_subdirectory(${PROJECT_SOURCE_DIR}/src/main)
# add_subdirectory(${PROJECT_SOURCE_DIR}/src/mod1)
# add_subdirectory(${PROJECT_SOURCE_DIR}/src/mod2)
# add_subdirectory(${PROJECT_SOURCE_DIR}/src/file)
# add_subdirectory(${PROJECT_SOURCE_DIR}/libs/spdlog)


# Add the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
set(CMAKE_PREFIX_PATH "/home/khtb/workset/c_parser/libs/spdlog/build" ${CMAKE_PREFIX_PATH})
set (spdlog_Dir="/home/khtb/workset/c_parser/libs/spdlog/build")
find_package(spdlog REQUIRED)

# Set global include directories (if any shared headers are in include/)
include_directories(${PROJECT_SOURCE_DIR}/include)
# spdlog
include_directories(${PROJECT_SOURCE_DIR}/libs/spdlog/include)


# Add TinyXML2
include_directories(${CMAKE_SOURCE_DIR}/src/tinyxml2)
add_library(TinyXML2 STATIC ${CMAKE_SOURCE_DIR}/src/tinyxml2/tinyxml2.cpp)


include_directories(${CMAKE_SOURCE_DIR}/src/svd_parser)
add_library(svdParser STATIC ${CMAKE_SOURCE_DIR}/src/svd_parser/svdParser.cpp)




# Find TinyXML2
# set(CMAKE_PREFIX_PATH ".lib/tinyxml/cmake/" ${CMAKE_PREFIX_PATH})
# set (TinyXML2_DIR ${PROJECT_SOURCE_DIR}/libs/tinyxml2/cmake)

# find_package(TinyXML2 REQUIRED)

# If libclang headers are not found automatically, specify the include directory
# For example, if installed in /usr/local/include/clang
target_include_directories(${PROJECT_NAME} PRIVATE /usr/lib/llvm-14/include/ ${PROJECT_SOURCE_DIR}/libs/spdlog/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/main)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/mod1)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/mod2)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/file)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/tinyxml2)
# target_include_directories(${PROJECT_NAME} PRIVATE )
target_link_libraries(${PROJECT_NAME} PRIVATE /usr/lib/llvm-14/lib/libclang.so )
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE readline)

# Link TinyXML2 to the executable
# target_link_libraries(${PROJECT_NAME} PRIVATE TinyXML2::TinyXML2)


# Link libclang to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE clang)
