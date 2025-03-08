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
message(STATUS "Project sources: ${PROJECT_SOURCES}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0") # Enable GDB debugging

# # Recursively find all directories containing header files in 'include' directory
file(GLOB_RECURSE HEADER_FILES "${SOURCE_DIR}/*.h")
message(STATUS "Project header files: ${HEADER_FILES}")
foreach(header_file ${HEADER_FILES})
    get_filename_component(header_dir ${header_file} DIRECTORY)
    list(APPEND HEADER_DIRS ${header_dir})
endforeach()
# # Add these directories as include directories
include_directories(${header_dir})
message(STATUS "Project header files: ${HEADER_DIRS}")



# Add the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${HEADER_FILES})
set(CMAKE_PREFIX_PATH "/home/khtb/workset/c_parser/libs/spdlog/build" ${CMAKE_PREFIX_PATH})
set (spdlog_Dir="/home/khtb/workset/c_parser/libs/spdlog/build")
find_package(spdlog REQUIRED)

# Set global include directories (if any shared headers are in include/)
include_directories(
    ${HEADER_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    )
    include_directories(${PROJECT_SOURCE_DIR}/libs/spdlog/include)
    
    
    # Add TinyXML2
    include_directories(${CMAKE_SOURCE_DIR}/src/tinyxml2)
    add_library(TinyXML2 STATIC ${CMAKE_SOURCE_DIR}/src/tinyxml2/tinyxml2.cpp)
    
    
    
# If libclang headers are not found automatically, specify the include directory
# For example, if installed in /usr/local/include/clang
target_include_directories(
    ${PROJECT_NAME} PRIVATE /usr/lib/llvm-14/include/ 
    ${PROJECT_SOURCE_DIR}/libs/spdlog/include
    )




# Link libclang to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE clang)
target_link_libraries(${PROJECT_NAME} PRIVATE /usr/lib/llvm-14/lib/libclang.so )
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE readline)

