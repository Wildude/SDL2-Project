# ================================
# General Purpose Makefile
# ================================

# Project directories
CORE_DIR    := core
SDL_DIR := $(CORE_DIR)/SDL
BAS_DIR := $(CORE_DIR)/BAS
# DLL directories
DLLS_DIR := DLLS
DLL_FILES := $(wildcard $(DLLS_DIR)/*.dll)

# Source codes directories
SDL_SRC    := $(SDL_DIR)/src
BAS_SRC    := $(BAS_DIR)/src

# Include directories
SDL_INC    := $(SDL_DIR)/include
BAS_INC    := $(BAS_DIR)/include
# Automate directory collection
INC_DIR := $(filter %_INC,$(.VARIABLES))
# Add "-I" into list of include directories
INC_FLAGS := $(foreach dir,$(INC_DIR),-I$($(dir)))

# Object directories
SDL_OBJ    := $(SDL_DIR)/obj
BAS_OBJ    := $(BAS_DIR)/obj
# Automate object directory collection
CORE_OBJ   := $(filter %_OBJ,$(.VARIABLES))
# Test directories
TEST_DIR    := tests
TEST_SRC    := $(TEST_DIR)/src
TEST_OBJ    := $(TEST_DIR)/obj

# Vender directories
VENDOR_DIR  := src
VENDOR_INC  := $(VENDOR_DIR)/include
VENDOR_LIB  := $(VENDOR_DIR)/lib

# Executable path
BIN_DIR     := bin

# Compiler settings
CXX         := g++
# no warnings (-Wall -Wextra)
CXXFLAGS    := -w -std=c++17 $(INC_FLAGS) -I$(VENDOR_INC)
CPPFLAGS    := -MMD -MP  # for dependency tracking

# Source codes
SDL_SRCS	:= $(wildcard $(SDL_SRC)/*.cpp)
BAS_SRCS	:= $(wildcard $(BAS_SRC)/*.cpp)

# Object files
SDL_OBJS   := $(patsubst $(SDL_SRC)/%.cpp,$(SDL_OBJ)/%.o,$(SDL_SRCS))
BAS_OBJS   := $(patsubst $(BAS_SRC)/%.cpp,$(BAS_OBJ)/%.o,$(BAS_SRCS))

# dependency files
SDL_DEPS   := $(SDL_OBJS:.o=.d)
BAS_DEPS   := $(BAS_OBJS:.o=.d)

# automatically collect all core dependency variables
CORE_DEPS := $(filter %_DEPS,$(.VARIABLES))

# Test files (each .cpp builds to a separate exe)
TEST_SRCS   := $(wildcard $(TEST_SRC)/*.cpp)
TEST_OBJS   := $(patsubst $(TEST_SRC)/%.cpp,$(TEST_OBJ)/%.o,$(TEST_SRCS))
TEST_DEPS   := $(TEST_OBJS:.o=.d)
TEST_BINS   := $(patsubst $(TEST_SRC)/%.cpp,$(BIN_DIR)/%,$(TEST_SRCS))

.SECONDARY: $(SDL_OBJS) $(BAS_OBJS) $(TEST_OBJS)
# Default target
.PHONY: all
all: $(BIN_DIR)/RadioButtonTest

# Default rule for building test binaries
$(BIN_DIR)/RadioButtonTest: $(TEST_OBJ)/RadioButtonTest.o $(SDL_OBJS) $(BAS_OBJS) | $(BIN_DIR)
	@echo "Linking $@"
	$(CXX) $^ -o $@ $(LDFLAGS)

#$(BIN_DIR)/%: $(TEST_OBJ)/%.o $(SDL_OBJS) $(BAS_OBJS) | $(BIN_DIR)
#	@echo "Linking $@"
#	$(CXX) $^ -o $@ $(LDFLAGS)

# Build rules
# Default rule for building test binaries
#bin/test2: $(TEST_OBJ)/test2.o $(DEPS_test2) | $(BIN_DIR)
#	@echo "Linking $@"
#	$(CXX) $^ -o $@ $(LDFLAGS_test2)

# Rule for test objects
$(TEST_OBJ)/%.o: $(TEST_SRC)/%.cpp | $(TEST_OBJ)
	@echo "Compiling test $<"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Rule for core objects
$(SDL_OBJ)/%.o: $(SDL_SRC)/%.cpp | $(SDL_OBJ)
	@echo "Compiling core/SDL $<"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

#Rule for core objects	
$(BAS_OBJ)/%.o: $(BAS_SRC)/%.cpp | $(BAS_OBJ)
	@echo "Compiling core/BAS $<"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@ 

LDFLAGS := -L$(VENDOR_LIB) \
-lSDL2_gfx -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_net -lSDL2_mixer \
-lavcodec -lavformat -lswresample -lswscale -lavutil\
-llua -lz 
LDFLAGS_test1 = -L$(VENDOR_LIB) -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf 
LDFLAGS_test2 = -L$(VENDOR_LIB) -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
LDFLAGS_test3 = -L$(VENDOR_LIB) -lz

# Ensure necessary directories exist
#$(SDL_OBJ):
#	@mkdir "$@" 2>nul || exit 0

#$(BAS_OBJ):
#	@mkdir "$@" 2>nul || exit 0

#$(TEST_OBJ):
#	@mkdir "$@" 2>nul || exit 0

#$(BIN_DIR):
#	@mkdir "$@" 2>nul || exit 0
#	@for %%f in ($(DLL_FILES)) do copy /Y "%%f" "$(DLLS_DIR)" >nul


# Cleaning
.PHONY: clean
clean:
	@for %%d in ($(TEST_OBJ) $(BIN_DIR) $(SDL_OBJ) $(BAS_OBJ)) do ( \
		if exist "%%d" rmdir /S /Q "%%d" \
	)
	

# Include dependency files
-include $(CORE_DEPS) $(TEST_DEPS)
