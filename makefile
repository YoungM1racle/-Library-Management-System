CXX = g++
CXXFLAGS = -Wall -g
OBJ = main.o Book.o User.o BookList.o Library.o
TARGET = library

# Detect the operating system
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    OS = mac
else ifeq ($(UNAME_S),Linux)  
    OS = linux
else
    OS = windows  
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
ifeq ($(OS),mac)
	rm -f $(OBJ) $(TARGET)
else ifeq ($(OS),linux)
	rm -f $(OBJ) $(TARGET)
else
	del $(TARGET).exe
	del $(OBJ)
endif