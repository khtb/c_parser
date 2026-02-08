

add_library(string_util STATIC
	string_util.cpp
	string_util.h
	)
target_include_directories(string_util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})