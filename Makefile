# A useful Makefile

# SRC is set to all the .cpp files in the current directory

SRC = $(wildcard *.cpp)

# The OBJ macro is built from the SRC macro

OBJ = $(SRC:.cpp=.o)

# Macros for the compiler, linker, and compiler options

GCC = g++
LINK = g++

CFLAGS = -Wall -std=c++11
CXXFLAGS = $(CFLAGS)

# A macro to describe the main target

TARGET = phrase_finder_GA

all: $(TARGET)
 
# The 'main' target depends on the files in the OBJ macro
# $^ is a make macro that contains the target dependencies
# $@ is a make macro that contains the target

$(TARGET): $(OBJ)
	$(LINK) -o $@ $^

# Add a clean target to allow rebuilds

clean:
	rm -rf $(TARGET) *.o *.d

# This uses the compiler to create include file dependencies

-include $(SRC:.cpp=.d)

%.d: %.cpp
	@set -e; rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@