/*******************************************************************************
                                                    Jose Jorge Jimenez-Olivas
						    Brandon Cramer
						    Chris Robles
						    Srinivas Venkatraman

                 University of California, San Diego
                      IEEE Micromouse Team 2019

File Name:       MazeNode.hpp
Description:     Cell data structure of the maze.
*******************************************************************************/
#ifndef MAZENODE_HPP
#define MAZENODE_HPP

#include <iostream>
#include <vector>

using namespace std;

/****************************************************************************
% MazeNode contains information about its location in Maze, and its 
% reachabble neighbors.
****************************************************************************/
class MazeNode {
public:
  const int MAX_CHILDREN = 4;
  /* cell location in Maze */
  const int row, y;
  const int column, x;
  /* path optimization attributes for diagonal directions */
  const double diagonal_x;
  const double diagonal_y;
  /* children */
  MazeNode * up    = nullptr;
  MazeNode * down  = nullptr;
  MazeNode * left  = nullptr;
  MazeNode * right = nullptr;
  /* graph traversal/search data */
  bool visited = false;
  MazeNode * prev = nullptr;
  int distance = 0;

  /**************************************************************************
  % Constructor:  MazeNode 
  % File:         MazeNode.hpp
  % Parameters:   row    - row that the node belongs to in maze.
  %               column - column that the node belongs to in maze. 
  % Description:  Creates a node object for an associated cell in a 2D maze. 
  **************************************************************************/
  MazeNode( double row, double column ) : row( (int)row ), column( (int)column ), 
    diagonal_x( column ), diagonal_y( row ), y( (int)row ), x( (int)column ) {}

  /*****************************************************************************
  % Routine Name: addNeighbor
  % File:         MazeNode.hpp
  % Parameters:   node - an adjacent cell in the maze from the calling node.
  % Description:  Attaches node as neighbobr of the calling node.
  % Return:       Nothing.
  *****************************************************************************/
  void addNeighbor( MazeNode * node ) {
    if( node == nullptr ) return;
    if( x == node->x ) {
      /* computer y-axis is inverted */
      if( y + 1 == node->y ) down = node;
      else if( y - 1 == node->y ) up = node;
    }
    else if( y == node->y ) {
      /* normal x-axis convention */
      if( x + 1 == node->x ) right = node;
      else if( x - 1 == node->x ) left = node;
    }
    else {
      /* node is not adjacent */
      cerr << ADD_EDGE_ERROR << *this << " <-> " << *node;
    }
  }

  /*****************************************************************************
  % Routine Name: removeNode
  % File:         MazeNode.hpp
  % Parameters:   node - an adjacent cell in the maze from the calling node. 
  % Description:  Removes node from the calling cells neighbor list. 
  % Return:       Nothing.
  *****************************************************************************/
  void removeNeighbor( MazeNode * node ) {
    if( node == nullptr ) return;
    if( x == node->x ) {
      /* vertical neighbor */
      if( y + 1 == node->y ) down = nullptr;
      else if( y - 1 == node->y ) up = nullptr;
    }
    else if( y == node->y ) {
      /* horizontal neighbor */
      if( x + 1 == node->x ) right = nullptr;
      else if( x - 1 == node->x ) left = nullptr;
    }
    else {
      /* node is not adjacent */
      cerr << REMOVE_EDGE_ERROR << *this << " <-> " << *node;
    }
  }

  /*****************************************************************************
  % Routine Name:  setVisited
  % File:          MazeNode.hpp
  % Parameters:    visited - this node has been flagged as visited.
  % Description:   Setter method for visited attribute.
  % Return:        Nothing.
  *****************************************************************************/
  void setVisited( bool visited ) {
    this->visited = visited;
  }

  /*****************************************************************************
  % Routine Name:  setPrev
  % File:          MazeNode.hpp
  % Parameters:    prev - link a node to this node.
  % Description:   Setter method for the prev attribute.
  % Return:        Nothing.
  *****************************************************************************/
  void setPrev( MazeNode * prev ) {
    this->prev = prev;
  }

  /*****************************************************************************
  % Routine Name:  setDistance
  % File:          MazeNode.hpp
  % Parameters:    distance - mark this node the given distance attribute.
  % Description:   Setter method for the distance attribute.
  % Return:        Nothing.
  *****************************************************************************/
  void setDistance( int distance ) {
    this->distance = distance;
  }

  /*****************************************************************************
  % Routine Name:  getVisited
  % File:          MazeNode.hpp
  % Parameters:    None.
  % Description:   Getter method for the visited attribute.
  % Return:        The visited attribute value.
  *****************************************************************************/
  bool getVisited() {
    return visited;
  }

  /*****************************************************************************
  % Routine Name:  getPrev
  % File:          MazeNode.hpp
  % Parameters:    None.
  % Description:   Getter method for the prev attribute.
  % Return:        The prev attribute.
  *****************************************************************************/
  MazeNode * getPrev() {
    return prev;
  }

  /*****************************************************************************
  % Routine Name:  getDistance
  % File :         MazeNode.hpp
  % Parameters:    None.
  % Description:   Getter method for the distance attribute.
  % Return:        The distance attribute value.
  *****************************************************************************/
  int getDistance() {
    return distance;
  }

  /*****************************************************************************
  % Routine Name: getNeighborList
  % File:         MazeNode.hpp
  % Parameters:   None.
  % Description:  Gets a list of the neighboring cells of the calling node.
  % Return:       An iterable list of neighbors.
  *****************************************************************************/
  vector<MazeNode *> getNeighborList() {
    vector<MazeNode *> neighbor_list = vector<MazeNode *>();

    if( up != nullptr ) neighbor_list.push_back( up );
    if( down != nullptr ) neighbor_list.push_back( down );
    if( left != nullptr ) neighbor_list.push_back( left );
    if( right != nullptr ) neighbor_list.push_back( right );

    return neighbor_list;
  }

  /*****************************************************************************
  % Routine Name: getDiagonalX
  % File:         MazeNode.hpp
  % Parameters:   None.
  % Description:  Getter for attribute diagonal_x. diagonal_x is used for path 
  %               optimization and it allows "half-steps" in the x-axis.
  % Return:       Double value of the attribute diagonal_x. 
  *****************************************************************************/
  double getDiagonalX() {
    return diagonal_x;
  }

  /*****************************************************************************
  % Routine Name: getDiagonalY
  % File:         MazeNode.hpp
  % Parameters:   None.
  % Description:  Getter for attribute diagona_y, which is used for diagonal 
  %               directions while traversing the  maze.
  % Return:       A floating point y-coordinate.
  *****************************************************************************/
  double getDiagonalY() {
    return diagonal_y;
  }

  /*****************************************************************************
  % Routine Name:  operator<<
  % File:          MazeNode.cpp
  % Parameters:    os   - output stream .
  %                node - node of interest.  
  % Description:   Allows for implicit string conversion of node when printing. 
  % Return:        The passed output stram object.
  *****************************************************************************/
  friend ostream & operator<<( ostream & os, MazeNode & node ) {
    os << "(" << node.row << ", " << node.column << ")";
    return os;
  }

  /*****************************************************************************
  % Routine Name: operator==
  % File:         MazeNode.hpp
  % Parameters:   node - node that will be compared with the calling node.
  % Description:  Evaluates of two nodes are internally equivalent.
  % Return:       True if and only if node is equivaluent to the calling node.
  *****************************************************************************/
  bool operator==( const MazeNode & node ) {
    return ( x == node.x && y == node.y );
  }

};

#endif
