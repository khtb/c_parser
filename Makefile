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


# Compiler and linker
CC := gcc
CXX := g++
AR := ar


#define librarires
LIBS := spdlog
LIB1_CXX_FLG :=-O2 -g -std=c++11 -DSPDLOG_COMPILED_LIB
LIB1_DIR:= libs/spdlog/src
LIB1_SRC:= $(wildcard $(LIB1_DIR)/*.cpp)
LIB1_INC:= libs/spdlog/include
LIB1_OBJ := $(patsubst $(LIB1_DIR)/%.cpp, $(OBJ_DIR)/$(LIB1_DIR)/%.o, $(LIB1_SRC))

LIBS_OBJS = $(LIB1_OBJ)

# Project source files
CPP_FILES := $(wildcard $(SRC_DIR)/**/*.cpp)

DEPS := $(CPP_FILES:.cpp=.d) 

# Generate a list of header files
H_FILES := $(wildcard $(SRC_DIR)/**/*.h)

# Generate include directories from header file paths
INCLUDE_DIRS := $(dir $(H_FILES))

# Convert include directories into -I flags
INCLUDES := $(addprefix -I ,$(INCLUDE_DIRS))  $(addprefix -I ,$(LIB1_INC))


# Derive the corresponding object file paths inside the obj/ directory
CPP_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_FILES))

# Define two different sets of and CPPFLAGS
CPPFLAGS := -O2 -g -std=c++11 -MMD 

# Output binary names
CPP_BIN := program_cpp


# Targets for compiling C files with different CFLAGS
$(C_BIN): $(C_OBJS)
	$(CC) $(CFLAGS) -o $(C_BIN) $(C_OBJS)


# Targets for compiling C++ files with different CPPFLAGS
$(CPP_BIN): $(CPP_OBJS) $(LIBS_OBJS)
	@echo *** Linking ***
	$(CXX) $(CPPFLAGS) -o $(CPP_BIN) $(CPP_OBJS) $(LIBS_OBJS)


# Pattern rule for compiling library object files
$(OBJ_DIR)/$(LIB1_DIR)/%.o: $(LIB1_DIR)/%.cpp $(LIB1_INC)
	@echo Compiling: $<
	@mkdir -p $(dir $@)
	$(CXX) $(LIB1_CXX_FLG) $(INCLUDES) -c $< -o $@

-include $(DEPS)

# Rule for building C++ object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Compiling: $<
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(INCLUDES) -c $< -o $@


# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(C_BIN) $(CPP_BIN)

all: $(CPP_BIN)
