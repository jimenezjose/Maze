/*******************************************************************************
                                                    Jose Jorge Jimenez-Olivas
                                                    Brandon Cramer
                                                    Chris Robles
                                                    Srinivas Venkatraman

                 University of California, San Diego
                      IEEE Micromouse Team 2019

File Name:       Maze.h
Description:     Two dimensional maze data structure for a Micromouse. 
*******************************************************************************/
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

  /* Creates an undirected egde between the given nodes. */
  void addEdge( MazeNode node_A, MazeNode node_B );

  /* Removes an undirected egde that is between the given nodes. */
  void removeEdge( MazeNode node_A, MazeNode node_B );

  /* Clears the maze such that no walls will exist between two nodes */
  void clearWalls();

public:  
  /* Creates a two dimensional maze data structure. */
  Maze( int width, int height );

  /* Creates a wall between two neighbor nodes in maze. */
  void addWall( MazeNode node_A, MazeNode node_B );

  /* Removes the wall betweeb two neighbor nodes in maze. */
  void removeWall( MazeNode node_A, MazeNode node_B );

  /* Converts the 90 degree turns in the path to 45 degree steps. */
  vector<MazeNode> optimize( vector<MazeNode> path );

  /* Clears all internal data of node relationships in maze. */
  void clear();

  /* Accessor method for maze internal nodal data structures. */
  MazeNode at( Point alpha );
  MazeNode at( int row, int column );

  /* Checks if there exists a wall between the given points or nodes. */
  bool wallBetween( Point alpha, Point beta );
  bool wallBetween( MazeNode node_A, MazeNode node_B );

  /* Checks if the (row, column) coordinate is not in the maze. */
  bool outOfBounds( int row, int column);

  /* Gets all global adjacent neighbors of node in maze. */
  vector<MazeNode> getAdjacentCellsList( MazeNode node );

  /* Getter method for the width/height, in unit cells, of the maze. */
  int getWidth();
  int getHeight();

};

#endif
