# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Source files
SRC = main.cpp AccessPoint.cpp FrequencyChannel.cpp Packet.cpp User.cpp WifiProtocols.cpp
OBJ = $(SRC:.cpp=.o)

# Executable
EXEC = wifi_simulator

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile individual source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(EXEC)

# Phony target
.PHONY: all clean
