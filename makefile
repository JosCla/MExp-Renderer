CXX = g++
CFLAGS = -g -Wall
SRC = src/

# CPPFILES = src/main.cpp src/calc_file_lib/calcfile.cpp src/calc_file_lib/fileutils.cpp
CPPFILES = $(wildcard $(SRC)*.cpp) $(wildcard $(SRC)**/*.cpp)
OBJFILES = $(CPPFILES:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJFILES)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJFILES)
	$(RM) $(TARGET)
