# Define the compiler and flags
CC = g++
CFLAGS_DEBUG = -g -Wall -std=c++11
CFLAGS_OPT = -O3 -Wall -std=c++11
LDFLAGS = -shared

# Define source files and object files
SRC_FILES = $(wildcard ./*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Output DLL and executable names
DLL_NAME = libwifi4_sim.dll
EXE_NAME_DEBUG = run_debug
EXE_NAME_OPT = run_opt

# Define the build rules
all: $(DLL_NAME) $(EXE_NAME_DEBUG) $(EXE_NAME_OPT)

# Rule to create the DLL
$(DLL_NAME): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

# Rule to create the debug executable
$(EXE_NAME_DEBUG): $(OBJ_FILES)
	$(CC) $(CFLAGS_DEBUG) -o $@ $^

# Rule to create the optimized executable
$(EXE_NAME_OPT): $(OBJ_FILES)
	$(CC) $(CFLAGS_OPT) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@  # Default to debug for compilation

# Clean up the build files
clean:
	rm -f *.o $(DLL_NAME) $(EXE_NAME_DEBUG) $(EXE_NAME_OPT)

.PHONY: all clean
