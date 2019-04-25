/****************************************************************************
                                                Jose Jorge Jimenez-Olivas
                                                April 17, 2019
File Name:       Maze.cpp
Description:     TODO
Sources of Help: 
****************************************************************************/
#include <vector>
#include <utility>
#include "Maze.h"
#include "MazeNode.hpp"

using namespace std;

Maze::Maze( int width, int height ) : width( width ), height( height ) {
  maze = vector<vector<MazeNode>>( height, vector<MazeNode>() );
  /* creating maze nodes */
  for( int row = 0; row < height; row++ ) {
    for( int column = 0; column < width; column++ ) {
      maze[ row ].push_back( MazeNode(row, column) );
    }
  }
}




