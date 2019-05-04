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

#if defined( ARDUINO_NUCLEO_F446RE )
#include <Arduino.h>
#define ARDUINO 
#endif

#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include "MazeNode.hpp"

using namespace std;

class Maze {
private:
  const int width, height;
  vector<vector<MazeNode>> maze;

  /* Creates an undirected egde between the given nodes. */
  void addEdge( MazeNode * node_A, MazeNode * node_B );
  /* Removes an undirected egde that is between the given nodes. */
  void removeEdge( MazeNode * node_A, MazeNode * node_B );
public:  
  /* Creates a two dimensional maze data structure. */
  Maze( int width, int height );
  /* Destructs the maze data structure */
  ~Maze();
  /* Creates a wall between two neighbor nodes in maze. */
  void addWall( MazeNode * node_A, MazeNode * node_B );
  /* Removes the wall betweeb two neighbor nodes in maze. */
  void removeWall( MazeNode * node_A, MazeNode * node_B );
  /* Clears all internal data of node relationships in maze. */
  void clear();
  /* Clears the maze such that no walls will exist between two nodes */
  void clearWalls();
  /* Accessor method for maze internal nodal data structures. */
  MazeNode * at( int row, int column );
  /* Checks if there exists a wall between the given points or nodes. */
  bool wallBetween( MazeNode * node_A, MazeNode * node_B );
  /* Checks if the (row, column) coordinate is not in the maze. */
  bool outOfBounds( int row, int column );
  /* Gets all global adjacent neighbors of node in maze. */
  vector<MazeNode *> getAdjacentCellList( MazeNode * node );
  /* Getter method for the width, in unit cells, of the maze. */
  int getWidth();
  /* Getter method for the height, in unit cells, of the maze. */
  int getHeight();

  /* Iterator class for the maze container - allowing ranging for loops */
  class Iterator : public iterator<input_iterator_tag, MazeNode> {
  private:
    Maze & maze;
    MazeNode * curr;
  public:
    Iterator( Maze & maze, MazeNode * curr ) : maze(maze), curr(curr) {}
    MazeNode * operator*() const;
    Iterator operator++();
    Iterator operator++(int);
    bool operator==( Iterator const & other ) const;
    bool operator!=( Iterator const & other ) const;
  };

  Maze::Iterator begin() { return Maze::Iterator( *this, at(0, 0) ); }
  Maze::Iterator end() { return Maze::Iterator( *this, nullptr ); }

};
#endif
