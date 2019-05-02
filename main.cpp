#include "Maze.h"
#include <iostream>

using namespace std;

int main() {
  Maze maze(3, 2);
  cerr << sizeof(MazeNode) << endl;
  cerr << sizeof(int) << endl;
  return 0;
}
