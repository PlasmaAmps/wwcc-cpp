# Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Target executable
TARGET = makefile_demo

# Default target
all: $(TARGET)

$(TARGET): makefile_demo.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) makefile_demo.cpp

# Clean target to remove the compiled binary
clean:
	rm -f $(TARGET)
