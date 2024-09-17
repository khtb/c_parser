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


# Project source files
CPP_FILES := $(wildcard $(SRC_DIR)/**/*.cpp)

# Generate a list of header files
H_FILES := $(wildcard $(SRC_DIR)/**/*.h)

# Generate include directories from header file paths
INCLUDE_DIRS := $(sort $(dir $(H_FILES)))

# Convert include directories into -I flags
INCLUDES := $(addprefix -I ,$(INCLUDE_DIRS)) -I $(LIB1_INC)


# Derive the corresponding object file paths inside the obj/ directory
CPP_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_FILES))

# Define two different sets of CFLAGS and CPPFLAGS
CPPFLAGS := -O2 -g -std=c++11

# Output binary names
CPP_BIN := program_cpp

STATIC_LIB1 := $(OBJ_DIR)/lib1.a

# Compile and archive libraries
$(STATIC_LIB1): $(LIB1_OBJ)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $(LIB1_OBJ)

# Targets for compiling C files with different CFLAGS
$(C_BIN): $(C_OBJS)
	$(CC) $(CFLAGS) -o $(C_BIN) $(C_OBJS)


# Targets for compiling C++ files with different CPPFLAGS
$(CPP_BIN): $(CPP_OBJS) $(STATIC_LIB1)
	@echo *** Linking ***
	$(CXX) $(CPPFLAGS) -o $(CPP_BIN) $(CPP_OBJS)


# Pattern rule for compiling library object files
$(OBJ_DIR)/$(LIB1_DIR)/%.o: $(LIB1_DIR)/%.cpp $(LIB1_INC)
	@echo Compiling: $<
	@mkdir -p $(dir $@)
	$(CXX) $(LIB1_CXX_FLG) $(addprefix -I,$(LIB1_INC)) -c $< -o $@


# Rule for building C++ object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Compiling: $<
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

# Target for listing the C and C++ files
list:
	@echo "C source files: $(C_FILES)"
	@echo "C++ source files: $(CPP_FILES)"
	@echo "C++ obj files: $(CPP_OBJS)"
	@echo "C++ h include folders: $(INCLUDES)"
	@echo "C++ h files: $(H_FILES)"
	@echo "lib1 src : $(LIB1_SRC)"
	@echo "lib1 objs : $(LIB1_OBJ)"

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(C_BIN) $(CPP_BIN)

all: $(CPP_BIN)
