/*******************************************************************************
                                                    Jose Jorge Jimenez-Olivas
                                                    Brandon Cramer
                                                    Chris Robles
                                                    Srinivas Venkatraman

                 University of California, San Diego
                      IEEE Micromouse Team 2019

File Name:       Maze.cpp
Description:     Graph data structure for a 2D Maze.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <utility>
#include "Maze.h"

using namespace std;

/*****************************************************************************
% Constructor: Maze
% File:        Maze.cpp
% Parameters:  width  - width of rectangular maze.
%              height - height of rectangular maze.
% Description: Creates a two dimensional maze data structure.
*****************************************************************************/
Maze::Maze( int width, int height ) : width( width ), height( height ) {
  if( width < 0 || height < 0 ) {
    #if defined( ARDUINO )
      width = height = 1;
    #else
      throw std::length_error("Maze");
    #endif
  }
  maze = vector<vector<MazeNode>>( height, vector<MazeNode>() );
  /* creating maze nodes */
  for( int row = 0; row < height; row++ ) {
    for( int column = 0; column < width; column++ ) {
      maze[ row ].push_back( MazeNode(row, column) );
    }
  }
}

/*****************************************************************************
% Destructor: ~Maze 
% File:        Maze.cpp
% Parameters:  None.
% Description: Deletes all heap allocated memory associated with the maze.
*****************************************************************************/
Maze::~Maze() {}

/*****************************************************************************
% Routine Name: addEdge
% File:         Maze.cpp
% Parameters:   node_A - a cell in this maze.
%               node_B - a cell in this maze.
% Description:  Creates an undirected egde between the given nodes.
% Return:       Nothing. 
*****************************************************************************/
void Maze::addEdge( MazeNode * node_A, MazeNode * node_B ) {
  if( node_A == nullptr || node_B == nullptr ) return;
  /* undirected edge added */
  node_A->addNeighbor( node_B );
  node_B->addNeighbor( node_A );
}


/*****************************************************************************
% Routine Name: removeEdge
% File:         Maze.cpp
% Parameters:   node_A - a cell in this maze.
%               node_B - a cell in this maze.
% Description:  Removes an undirected egde that is between the given nodes.
% Return:       Nothing.
*****************************************************************************/
void Maze::removeEdge( MazeNode * node_A, MazeNode * node_B ) {
  if( node_A == nullptr || node_B == nullptr ) return;
  /* removing undirected edge */
  node_A->removeNeighbor( node_B );
  node_B->removeNeighbor( node_A );
}

/*****************************************************************************
% Routine Name: clearWalls
% File:         Maze.cpp
% Parameters:   None. 
% Description:  Clears the maze such that no walls will exist - this will 
%               create a fully connected maze (definition of wall).
% Return:       Nothing. 
*****************************************************************************/
void Maze::clearWalls() {
  for( int row = 0; row < getHeight(); row++ ) {
    for( int column = 0; column < getWidth(); column++ ) {
      MazeNode * currentNode = at(row, column);

      if( !outOfBounds(row + 1, column) ) {
	/* vertical deviation downwards */
	removeWall( currentNode, at(row + 1, column) );
      }
      if( !outOfBounds(row, column + 1) ) {
	/* horizontal deviation to the right */
	removeWall( currentNode, at(row, column + 1) );
      }
    }
  }
}

/*****************************************************************************
% Routine Name: addWall
% File:         Maze.cpp
% Parameters:   node_A - a cell in this maze.
%               node_B - a cell in this maze.
% Description:  Creates a wall between two neighbor nodes in maze.
% Return:       Nothing. 
*****************************************************************************/
void Maze::addWall( MazeNode * node_A, MazeNode * node_B ) {
  if( node_A == nullptr || node_B == nullptr ) return;
  removeEdge( node_A, node_B );
}

/*****************************************************************************
% Routine Name: removeWall 
% File:         Maze.cpp
% Parameters:   node_A - a cell in this maze.
%               node_B - a cell in this maze.
% Description:  Removes the wall betweeb two neighbor nodes in maze. 
% Return:       Nothing. 
*****************************************************************************/
void Maze::removeWall( MazeNode * node_A, MazeNode * node_B ) {
  if( node_A == nullptr || node_B == nullptr ) return;
  addEdge( node_A, node_B );
}

/*****************************************************************************
% Routine Name: clear
% File:         Maze.cpp
% Parameters:   None.
% Description:  Clears all internal data of node relationships in maze.
% Return:       Nothing. 
*****************************************************************************/
void Maze::clear() {
  for( MazeNode * node : *this ) {
    /* clear data for all nodes in maze */
    node->clearData();
  }
}

/*****************************************************************************
% Routine Name: at
% File:         Maze.cpp
% Parameters:   row    - row of node in maze
%               column - column of node in maze
% Description:  Accessor method for maze internal nodal data structures.
% Return:       MazeNode pointer at (x, y) position in two-dimensional maze. 
*****************************************************************************/
MazeNode * Maze::at( int row, int column ) {
  if( outOfBounds(row, column) ) {
    #if defined( ARDUINO )
      if( Serial ) {
        Serial.println( "Maze::at() out of range. Defaulting to (0, 0)");
      }
      row = column = 0;
    #else
      throw std::out_of_range("Maze");
    #endif
  }
  return &maze[ row ][ column ];
}

/*****************************************************************************
% Routine Name: outOfBounds
% File:         Maze.cpp
% Parameters:   row    - vertical deviated position of interest.
%               column - horizontal deviated position of interest.
% Description:  Checks if the (row, column) coordinate is not in the maze. 
% Return:       True if and only if (row,column) does not exist in maze. 
*****************************************************************************/
bool Maze::outOfBounds( int row, int column) {
  bool row_out_of_bounds = row < 0 || row >= getHeight();
  bool column_out_of_bounds = column < 0 || column >= getWidth();
  return row_out_of_bounds || column_out_of_bounds;
}

/*****************************************************************************
% Routine Name: getAdjacentCellList
% File:         Maze.cpp
% Parameters:   node - the node of interest in the maze.
% Description:  Gets all global adjacent neighbors of node in maze.
% Return:       A list of all existing adjacent neighbors of node in maze.
*****************************************************************************/
vector<MazeNode *> Maze::getAdjacentCellList( MazeNode * node ) {
  if( node == nullptr ) return vector<MazeNode *>();
  const int MAX_CELLS = 4;
  const int EVEN = 2;
  vector<MazeNode *> list;

  for( int index = 0; index < MAX_CELLS; index++ ) {
    /* append all adjacent neighbors to list */
    int deviation = ( index < EVEN ) ? -1 : +1;
    int dr = ( index % EVEN == 0 ) ? deviation : 0;
    int dc = ( index % EVEN == 1 ) ? -deviation : 0;
    if( !outOfBounds(node->row + dr, node->column + dc) ) { 
      list.push_back( at(node->row + dr, node->column + dc) );
    }
  }
  return list;
}

/*****************************************************************************
% Routine Name: getWidth
% File:         Maze.cpp
% Parameters:   None.
% Description:  Getter method for the width, in unit cells, of the maze.
% Return:       The width of the maze in unit of cells.
*****************************************************************************/
int Maze::getWidth() {
  return width;
}

/*****************************************************************************
% Routine Name: getHeight
% File:         Maze.cpp
% Parameters:   None.
% Description:  Getter method for the height, in unit cells, of the maze.
% Return:       The height of the maze in units of cells.
*****************************************************************************/
int Maze::getHeight() {
  return height;
}

/*****************************************************************************
% Routine Name: Maze::Iterator::operator * 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Overloads the * operator to return the curr maze node pointer.
% Return:       The maze node that curr points to. 
*****************************************************************************/
MazeNode * Maze::Iterator::operator*() const {
  return curr;
}

/*****************************************************************************
% Routine Name: Maze::Iterator::operator ++ 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Overloads the prefix operator++ and moves curr to the 
%               successor node of the maze container.
% Return:       The calling maze iteartor.
*****************************************************************************/
Maze::Iterator Maze::Iterator::operator++() {
  MazeNode * end = maze.at( maze.getHeight() - 1, maze.getWidth() - 1 );

  if( curr == end ) {
    /* terminating case */
    curr = nullptr;
    return *this;
  }

  if( curr->column + 1 == maze.getWidth() ) {
    /* wrapping around 2d array */
    curr = maze.at( curr->row + 1, 0 );
  }
  else {
    /* typical 1d array iteration */
    curr = maze.at( curr->row, curr->column + 1);
  }
  return *this;
}

/*****************************************************************************
% Routine Name: Maze::Iterator::operator ++ 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Overloads the postfix operator++ and moves curr to the 
%               successor of the maze container.
% Return:       The calling maze iterator before moving curr to its sucessor. 
*****************************************************************************/
Maze::Iterator Maze::Iterator::operator++(int) {
  Maze::Iterator before( maze, curr );
  ++(*this);
  return before;
}

/*****************************************************************************
% Routine Name: Maze::Iterator::operator ==
% File:         Maze.cpp
% Parameters:   other - an iterator to compare with.
% Description:  Overloads the == operator to check equality of two maze 
%               iterators based on a shallow comparsion of curr pointers.
% Return:       True if both curr and the other iterators curr point to the 
%               same address in memory, false otherwise. 
*****************************************************************************/
bool Maze::Iterator::operator==( Maze::Iterator const & other ) const {
  return curr == other.curr;
}

/*****************************************************************************
% Routine Name: Maze::Iterator::operator !=
% File:         Maze.cpp
% Parameters:   other - an iterator to compare with.
% Description:  Overloads the != opearator to evaluate when two maze iterators
%               are not equivalent based on curr pointer comparison. 
% Return:       True if the other iterator's curr is not same as this objects
%               curr, false otherwise. 
*****************************************************************************/
bool Maze::Iterator::operator!=( Maze::Iterator const & other ) const {
  return curr != other.curr;
}
