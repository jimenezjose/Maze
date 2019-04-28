/****************************************************************************
                                                Jose Jorge Jimenez-Olivas
                                                April 17, 2019
File Name:       Maze.cpp
Description:     Graph data structure for a 2D Maze.
Sources of Help: TODO
****************************************************************************/
#include <vector>
#include <utility>
#include "Maze.h"

using namespace std;

/*****************************************************************************
% Constructor: Maze
% File:        Maze.h
% Parameters:  width  - width of rectangular maze.
%              height - height of rectangular maze.
% Description: Creates a two dimensional maze data structure.
*****************************************************************************/
Maze::Maze( int width, int height ) : width( width ), height( height ) {
  maze = vector<vector<MazeNode>>( height, vector<MazeNode>() );
  /* creating maze nodes */
  for( int row = 0; row < height; row++ ) {
    for( int column = 0; column < width; column++ ) {
      maze[ row ].push_back( MazeNode(row, column) );
    }
  }
}

/*****************************************************************************
% Routine Name: addEdge
% File:         Maze.h
% Parameters:   node_A - a cell in this maze.
%               node_B - a cell in this maze.
% Description:  Creates an undirected egde between the given nodes.
% Return:       Nothing. 
*****************************************************************************/
void Maze::addEdge( MazeNode & node_A, MazeNode & node_B ) {

}

/*****************************************************************************
% Routine Name: removeEdge
% File:         Maze.h
% Parameters:   node_A - a cell in this maze.
%               node_B - a cell in this maze.
% Description:  Removes an undirected egde that is between the given nodes.
% Return:       Nothing.
*****************************************************************************/
void Maze::removeEdge( MazeNode & node_A, MazeNode & node_B ) {

}

/*****************************************************************************
% Routine Name: clearWalls
% File:         Maze.h
% Parameters:   None. 
% Description:  Clears the maze such that no walls will exist - this will 
%               create a fully connected maze (definition of wall).
% Return:       Nothing. 
*****************************************************************************/
void Maze::clearWalls() {

}

/*****************************************************************************
% Routine Name: addWall
% File:         Maze.h
% Parameters:   node_A - a cell in this maze.
%               node_B - a cell in this maze.
% Description:  Creates a wall between two neighbor nodes in maze.
% Return:       Nothing. 
*****************************************************************************/
void Maze::addWall( MazeNode & node_A, MazeNode & node_B ) {

}

/*****************************************************************************
% Routine Name: removeWall 
% File:         Maze.h
% Parameters:   node_A - a cell in this maze.
%               node_B - a cell in this maze.
% Description:  Removes the wall betweeb two neighbor nodes in maze. 
% Return:       Nothing. 
*****************************************************************************/
void Maze::removeWall( MazeNode & node_A, MazeNode & node_B ) {

}

/*****************************************************************************
% Routine Name: optimize
% File:         Maze.h
% Parameters:   path - linked list path of maze nodes to be optimized.
% Description:  Path optimization with regards to the micromouse's ability to 
%               move in diagonal directions.
% Return:       Nothing. 
*****************************************************************************/
vector<MazeNode> Maze::optimize( vector<MazeNode> path ) {
  return vector<MazeNode>();
}

/*****************************************************************************
% Routine Name: clear
% File:         Maze.h
% Parameters:   None.
% Description:  Clears all internal data of node relationships in maze.
% Return:       Nothing. 
*****************************************************************************/
void Maze::clear() {

}

/*****************************************************************************
% Routine Name: at
% File:         Maze.h
% Parameters:   row    - row of node in maze
%               column - column of node in maze
% Description:  Accessor method for maze internal nodal data structures.
% Return:       MazeNode object at (x, y) position in two-dimensional maze. 
*****************************************************************************/
MazeNode & Maze::at( int row, int column ) {
  return maze[ row ][ column ];
}

/*****************************************************************************
% Routine Name: outOfBounds
% File:         Maze.h
% Parameters:   row    - vertical deviated position of interest.
%               column - horizontal deviated position of interest.
% Description:  Checks if the (row, column) coordinate is not in the maze. 
% Return:       True if and only if (row,column) does not exist in maze. 
*****************************************************************************/
bool Maze::outOfBounds( int row, int column) {
  return false;
}

/*****************************************************************************
% Routine Name: getAdjacentCellsList
% File:         Maze.h
% Parameters:   node - the node of interest in the maze.
% Description:  Gets all global adjacent neighbors of node in maze.
% Return:       A list of all existing adjacent neighbors of node in maze.
*****************************************************************************/
vector<MazeNode> Maze::getAdjacentCellsList( MazeNode & node ) {
  return vector<MazeNode>();
}

/*****************************************************************************
% Routine Name: getWidth
% File:         Maze.h
% Parameters:   None.
% Description:  Getter method for the width, in unit cells, of the maze.
% Return:       The width of the maze in unit of cells.
*****************************************************************************/
int Maze::getWidth() {
  return width;
}

/*****************************************************************************
% Routine Name: getHeight
% File:         Maze.h
% Parameters:   None.
% Description:  Getter method for the height, in unit cells, of the maze.
% Return:       The height of the maze in units of cells.
*****************************************************************************/
int Maze::getHeight() {
  return height;
}


/************************* Maze Iterator Definitions ************************/


/*****************************************************************************
% Routine Name: Maze::Iterator::operator * 
% File:         Maze.h
% Parameters:   None.
% Description:  Overloads the * operator to direference the maze node pointer.
% Return:       The maze node that curr points to. 
*****************************************************************************/
MazeNode Maze::Iterator::operator*() const {
  return *curr;
}

/*****************************************************************************
% Routine Name: Maze::Iterator::operator ++ 
% File:         Maze.h
% Parameters:   None.
% Description:  Overloads the prefix operator++ and moves curr to the 
%               successor node of the maze container.
% Return:       The calling maze iteartor.
*****************************************************************************/
Maze::Iterator Maze::Iterator::operator++() {
  MazeNode * end = &maze.at( maze.getHeight() - 1, maze.getWidth() - 1 );

  if( curr == end ) {
    /* terminating case */
    curr = nullptr;
    return *this;
  }

  if( curr->column + 1 == maze.getWidth() ) {
    /* wrapping around 2d array */
    curr = &maze.at( curr->row + 1, 0 );
  }
  else {
    /* typical 1d array iteration */
    curr = &maze.at( curr->row, curr->column + 1);
  }
  return *this;
}

/*****************************************************************************
% Routine Name: Maze::Iterator::operator ++ 
% File:         Maze.h
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
% File:         Maze.h
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
% File:         Maze.h
% Parameters:   other - an iterator to compare with.
% Description:  Overloads the != opearator to evaluate when two maze iterators
%               are not equivalent based on curr pointer comparison. 
% Return:       True if the other iterator's curr is not same as this objects
%               curr, false otherwise. 
*****************************************************************************/
bool Maze::Iterator::operator!=( Maze::Iterator const & other ) const {
  return curr != other.curr;
}
