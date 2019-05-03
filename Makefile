LIBRARY_FILES = Maze.cpp
DRIVER_FILE = main.cpp
CPP_FLAGS = -std=c++11

all:
	g++ $(CPP_FLAGS) $(LIBRARY_FILES) $(DRIVER_FILE)
	
