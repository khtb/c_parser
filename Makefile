##############################################################
#	| | _| |__ | |_| |__  
#	| |/ / '_ \| __| '_ \ 
#	|   <| | | | |_| |_) |
#	|_|\_\_| |_|\__|_.__/ 
#	                     
##############################################################
# Makefile
# Author: Khattab	
# Date: 16/09/2024
# license: MIT
##############################################################


# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -g -std=c++17
LINK_FLAGS =
SRC_DIR := src
OBJS_DIR := obj

# Target executable
TARGET = $(OBJS_DIR)/my_program

# Source files
CPP_FILES:=$(wildcard **/*.cpp)
C_FILES := $(wildcard *.cpp)

# Object files
CPP_OBJS := $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(CPP_FILES))

info:
	@echo "SRCS: $(CPP_FILES)"
	@echo "OBJS: $(CPP_OBJS)"
	@echo $(C_FILES)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(CPP_OBJS)
	$(CC) $(LINK_FLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean