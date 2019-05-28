/*******************************************************************************
                                                    Jose Jorge Jimenez-Olivas
                                                    Brandon Cramer
                                                    Chris Robles
                                                    Srinivas Venkatraman

                 University of California, San Diego
                      IEEE Micromouse Team 2019

File Name:       Maze.h
Description:     2D matrix data structure with an internal graph abstraction. 
*******************************************************************************/
#ifndef MAZE_H
#define MAZE_H

#if defined( ARDUINO_ARCH_STM32 )
  #include <Arduino.h>
#endif

/* stm32 architecture or non arduino */
#if defined( ARDUINO_ARCH_STM32 ) || !defined( ARDUINO )
  #include <iostream>
  #include <sstream>
  #include <string>
  #include <stack>
  #include <vector>
  #include <utility>
  #include <iterator>
  #include <cmath>
  #include "MazeCell.hpp"
#else
  #error "board not supported." 
#endif

namespace std {

class Maze {
private:
  vector<vector<MazeCell>> maze;
  string maze_str;
  /* Creates an undirected egde between the given cells. */
  void addEdge( MazeCell * cell_A, MazeCell * cell_B );
  /* Removes an undirected egde that is between the given cells. */
  void removeEdge( MazeCell * cell_A, MazeCell * cell_B );
public:  
  const int width, height;
  /* Creates a two dimensional maze data structure. */
  Maze( int width, int height );
  /* Destructs the maze data structure */
  ~Maze();
  /* Creates a wall between two neighbor cells in maze. */
  void addWall( MazeCell * cell_A, MazeCell * cell_B );
  /* Removes the wall betweeb two neighbor cells in maze. */
  void removeWall( MazeCell * cell_A, MazeCell * cell_B );
  /* Clears all internal data of cell relationships in maze. */
  void clear();
  /* Clears the maze such that no walls will exist between two cells */
  void clearWalls();
  /* draws the current state of the maze */
  void draw();
  /* overloaded - delgates to at(row, column) */
  MazeCell * at( pair<int, int> & coordinate );
  /* Accessor method for maze internal nodal data structures. */
  MazeCell * at( int row, int column );
  /* Checks if there exists a wall between the given points or cells. */
  bool wallBetween( MazeCell * cell_A, MazeCell * cell_B );
  /* Checks if the (row, column) coordinate is not in the maze. */
  bool outOfBounds( int row, int column );
  /* Gets all global adjacent neighbors of cell in maze. */
  vector<MazeCell *> getAdjacentCellList( MazeCell * cell );
  /* Getter method for the width, in unit cells, of the maze. */
  int getWidth();
  /* Getter method for the height, in unit cells, of the maze. */
  int getHeight();
  /* c string representation of the maze */
  operator const char *();
  /* implicit call to output the string representation of the maze */
  friend ostream & operator<<( ostream & os, Maze & maze );
  /* Iterator class for the maze container - allowing ranging for loops */
  class Iterator : public iterator<input_iterator_tag, MazeCell> {
  private:
    Maze & maze;
    MazeCell * curr;
  public:
    Iterator( Maze & maze, MazeCell * curr ) : maze(maze), curr(curr) {}
    MazeCell * operator*() const;
    Iterator operator++();
    Iterator operator++(int);
    bool operator==( Iterator const & other ) const;
    bool operator!=( Iterator const & other ) const;
  };

  Maze::Iterator begin() { return Maze::Iterator( *this, at(0, 0) ); }
  Maze::Iterator end() { return Maze::Iterator( *this, nullptr ); }
};

} /* namespace std */

#ifndef ARDUINO
  #include "Maze.cpp"
#endif
#endif /* MAZE_H */
