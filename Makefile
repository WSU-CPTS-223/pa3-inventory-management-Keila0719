# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Executable name
TARGET = game

# Source files
SRCS = main.cpp inventory.cpp test.cpp 

# Build rule
all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean
clean:
	rm -f $(TARGET)
