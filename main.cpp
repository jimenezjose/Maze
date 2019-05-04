#include "Maze.h"
#include <iostream>
#include <vector>

using namespace std;

void printVector( vector<MazeNode *> list ) {
  cerr << "[ ";
  for( MazeNode * node : list  ) {
    cerr << *node << " ";
  }
  cerr << "]" << endl;
}

int main() {
  Maze maze(3, 3);
  cerr << "size of MazeNode: " << sizeof(MazeNode) << endl;

  MazeNode * curr = maze.at(0, 0);

  maze.clearWalls();
  printVector( curr->getNeighborList() );

  maze.clear();
  printVector( curr->getNeighborList() );

  printVector( maze.getAdjacentCellList(curr) );

  return 0;
}


