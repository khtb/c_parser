##############################################################
#		 _    _     _   _     
#		| | _| |__ | |_| |__  
#		| |/ / '_ \| __| '_ \ 
#		|   <| | | | |_| |_) |
#		|_|\_\_| |_|\__|_.__/ 
#	 	                    
##############################################################
# Makefile
# Author: Khattab	
# Date: 16/09/2024
# license: MIT
##############################################################


# Variables for listing C and C++ source files
SRC_DIR := src
OBJ_DIR := obj

C_FILES := $(wildcard $(SRC_DIR)/**/*.c)
CPP_FILES := $(wildcard $(SRC_DIR)/**/*.cpp)

# Generate a list of header files
H_FILES := $(wildcard $(SRC_DIR)/**/*.h)

# Generate include directories from header file paths
INCLUDE_DIRS := $(sort $(dir $(H_FILES)))

# Convert include directories into -I flags
INCLUDES := $(addprefix -I ,$(INCLUDE_DIRS))


# Derive the corresponding object file paths inside the obj/ directory
C_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_FILES))
CPP_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_FILES))

# Define two different sets of CFLAGS and CPPFLAGS
CFLAGS := -O2 -Wall

CPPFLAGS := -O2 -g -std=c++11

# Compiler and linker
CC := gcc
CXX := g++

# Output binary names
C_BIN := program_c
CPP_BIN := program_cpp

# Targets for compiling C files with different CFLAGS
$(C_BIN): $(C_OBJS)
	$(CC) $(CFLAGS) -o $(C_BIN) $(C_OBJS)


# Targets for compiling C++ files with different CPPFLAGS
$(CPP_BIN): $(CPP_OBJS)
	$(CXX) $(CPPFLAGS) -o $(CPP_BIN) $(CPP_OBJS)


# Rule for building C object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule for building C++ object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

# Target for listing the C and C++ files
list:
	@echo "C source files: $(C_FILES)"
	@echo "C++ source files: $(CPP_FILES)"
	@echo "C++ obj files: $(CPP_OBJS)"
	@echo "C++ h files: $(INCLUDES)"
	@echo "C++ h files: $(H_FILES)"

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(C_BIN) $(CPP_BIN)

all: $(CPP_BIN)
