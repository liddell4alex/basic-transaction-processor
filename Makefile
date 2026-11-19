CXX = g++
CXXFLAGS = -Wall -I./include -I/usr/include/mysql/
SOURCE = ./src/dbInteractions.c ./src/initConnection.c main.cpp
TARGET = ./build/ddbs
LDLIBS = -lmariadb

all:
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET) $(LDLIBS)

clean:
	rm -f $(TARGET)
