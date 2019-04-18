#ifndef MAZE_H
#define MAZE_H

//#include <Arduino.h>
#include <iostream>
#include <vector>
#include <utility>

#include "MazeNode.hpp"

using namespace std;

class Maze {
private:
  static const int EVEN = 2;
  const int width, height;
  vector<vector<MazeNode>> maze;


public:  
  Maze( int width, int height ) : width( width ), height( height ) {
    maze = vector<vector<MazeNode>>( height, vector<MazeNode>() );
    /* creating maze nodes */
    for( int row = 0; row < height; row++ ) {
      for( int column = 0; column < width; column++ ) {
        maze[ row ].push_back( MazeNode(row, column) );
      }
    }
  }



};

#endif
