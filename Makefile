# Define the compiler and flags
CC = g++
CFLAGS = -g -Wall -std=c++11
LDFLAGS = -shared

# Define source files and object files
SRC_FILES = $(wildcard ./*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Output DLL and executable names
DLL_NAME = libwifi4_sim.dll
EXE_NAME = run

# Define the build rules
all: $(DLL_NAME) $(EXE_NAME)

# Rule to create the DLL
$(DLL_NAME): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

# Rule to create the executable
$(EXE_NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f *.o $(DLL_NAME) $(EXE_NAME)

.PHONY: all clean
