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

  /*****************************************************************************
  % Routine Name: addEdge
  % File:         Maze.h
  % Parameters:   node_A - a cell in this maze.
  %               node_B - a cell in this maze.
  % Description:  Creates an undirected egde between the given nodes.
  % Return:       Nothing. 
  *****************************************************************************/
  void addEdge( MazeNode node_A, MazeNode node_B );

  /*****************************************************************************
  % Routine Name: removeEdge
  % File:         Maze.h
  % Parameters:   node_A - a cell in this maze.
  %               node_B - a cell in this maze.
  % Description:  Removes an undirected egde that is between the given nodes.
  % Return:       Nothing. 
  *****************************************************************************/
  void removeEdge( MazeNode node_A, MazeNode node_B );

  /*****************************************************************************
  % Routine Name: clearWalls
  % File:         Maze.h
  % Parameters:   None. 
  % Description:  Clears the maze such that no walls will exist - this will 
  %               create a fully connected maze (definition of wall).
  % Return:       Nothing. 
  *****************************************************************************/
  void clearWalls();

public:  
  /*****************************************************************************
  % Constructor: Maze
  % File:        Maze.h
  % Parameters:  width  - width of rectangular maze.
  %              height - height of rectangular maze.
  % Description: Creates a two dimensional maze data structure.
  *****************************************************************************/
  Maze( int width, int height );

  /*****************************************************************************
  % Routine Name: addWall
  % File:         Maze.h
  % Parameters:   node_A - a cell in this maze.
  %               node_B - a cell in this maze.
  % Description:  Creates a wall between two neighbor nodes in maze.
  % Return:       Nothing. 
  *****************************************************************************/
  void addWall( MazeNode node_A, MazeNode node_B );

  /*****************************************************************************
  % Routine Name: removeWall 
  % File:         Maze.h
  % Parameters:   node_A - a cell in this maze.
  %               node_B - a cell in this maze.
  % Description:  Removes the wall betweeb two neighbor nodes in maze. 
  % Return:       Nothing. 
  *****************************************************************************/
  void removeWall( MazeNode node_A, MazeNode node_B );

  /*****************************************************************************
  % Routine Name: optimize
  % File:         Maze.h
  % Parameters:   path - linked list path of maze nodes to be optimized.
  % Description:  Path optimization with regards to the micromouse's aility to 
  %               move in diagonal directions.
  % Return:       Nothing. 
  *****************************************************************************/
  vector<MazeNode> optimize( vector<MazeNode> path );

  /*****************************************************************************
  % Routine Name: clear
  % File:         Maze.h
  % Parameters:   None.
  % Description:  Clears all internal data of node relationships in maze.
  % Return:       Nothing. 
  *****************************************************************************/
  void clear();

  /*****************************************************************************
  % Routine Name: at
  % File:         Maze.h
  % Parameters:   alpha - point with (x, y) coordinates of node of interest.
  % Description:  Accessor method for maze internal nodal data structures.
  % Return:       MazeNode object at (x, y) position in two-dimensional maze. 
  *****************************************************************************/
  MazeNode at( Point alpha );

  /*****************************************************************************
  % Routine Name: at
  % File:         Maze.h
  % Parameters:   row    - row of node in maze
  %               column - column of node in maze
  % Description:  Accessor method for maze internal nodal data structures.
  % Return:       MazeNode object at (x, y) position in two-dimensional maze. 
  *****************************************************************************/
  MazeNode at( int row, int column );

  /*****************************************************************************
  % Routine Name: wallBetween
  % File:         Maze.h
  % Parameters:   alpha - point with (x, y) coordinates of node of interest.
  %               beta - point with (x, y) coordinates of node of interest.
  % Description:  Checks if there exists a wall between the given points.
  % Return:       true if a wall existed between the points, false otherwise. 
  *****************************************************************************/
  bool wallBetween( Point alpha, Point beta );

  /*****************************************************************************
  % Routine Name: wallBetween
  % File:         Maze.h
  % Parameters:   node_A - a cell in this maze.
  %               node_B - a cell in this maze.
  % Description:  Checks if there exists a wall between the given nodes.
  % Return:       true if a wall existed between the nodes, false otherwise.
  *****************************************************************************/
  bool wallBetween( MazeNode node_A, MazeNode node_B );

  /*****************************************************************************
  % Routine Name: outOfBounds
  % File:         
  % Parameters:    
  % Description:   
  % Return:        
  *****************************************************************************/
  bool outOfBounds( int row, int column) {

  /*****************************************************************************
  % Routine Name: 
  % File:         
  % Parameters:    
  % Description:   
  % Return:        
  *****************************************************************************/
  vector<MazeNode> getAdjacentCellsList( MazeNode node );

  /*****************************************************************************
  % Routine Name: 
  % File:         
  % Parameters:    
  % Description:   
  % Return:        
  *****************************************************************************/
  int getWidth();

  /*****************************************************************************
  % Routine Name: 
  % File:         
  % Parameters:    
  % Description:   
  % Return:        
  *****************************************************************************/
  int getHeight();

};

#endif
