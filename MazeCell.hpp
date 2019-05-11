/*******************************************************************************
                                                    Jose Jorge Jimenez-Olivas
						    Brandon Cramer
						    Chris Robles
						    Srinivas Venkatraman

                 University of California, San Diego
                      IEEE Micromouse Team 2019

File Name:       MazeCell.hpp
Description:     Cell data structure of the maze and internal vertex for the 
                 graph abstraction of the maze.
*******************************************************************************/
#ifndef MAZECELL_HPP
#define MAZECELL_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MazeCell {
public:
  friend class Maze;
  /* cell location in Maze */
  const int row;
  const int column;
  /* children */
  MazeCell * up    = nullptr;
  MazeCell * down  = nullptr;
  MazeCell * left  = nullptr;
  MazeCell * right = nullptr;
  /* path optimization attributes for diagonal directions */
  const double diagonal_row;
  const double diagonal_column;
  /* graph traversal/search data */
  MazeCell * prev = nullptr;
  int distance = 0;
  bool visited = false;

  /*****************************************************************************
  % Constructor:  MazeCell 
  % File:         MazeCell.hpp
  % Parameters:   row    - row that the cell belongs to in maze.
  %               column - column that the cell belongs to in maze. 
  % Description:  Creates a cell object for an associated cell in a 2D maze. 
  ******************************************************************************/
  MazeCell( double row, double column ) : row( (int)row ), column( (int)column ),
    diagonal_row( row ), diagonal_column( column ) {}

  /*****************************************************************************
  % Constructor:  MazeCell 
  % File:         MazeCell.hpp
  % Parameters:   row    - row that the cell belongs to in maze.
  %               column - column that the cell belongs to in maze. 
  % Description:  Creates a cell object for an associated cell in a 2D maze. 
  ******************************************************************************/
  MazeCell( const MazeCell & cell ) : row( cell.row ), column( cell.column ), 
    diagonal_row( cell.diagonal_row ), diagonal_column( cell.diagonal_column ) {}

  /*****************************************************************************
  % Routine Name:  clearData
  % File:          MazeCell.hpp
  % Parameters:    None. 
  % Description:   Clear MazeCell graph data.
  % Return:        Nothing.
  *****************************************************************************/
  void clearData() {
    up = down = left = right = nullptr;
    prev = nullptr;
    visited = false;
    distance = 0;
  }

  /*****************************************************************************
  % Routine Name:  setVisited
  % File:          MazeCell.hpp
  % Parameters:    visited - this cell has been flagged as visited.
  % Description:   Setter method for visited attribute.
  % Return:        Nothing.
  *****************************************************************************/
  void setVisited( bool visited ) {
    this->visited = visited;
  }

  /*****************************************************************************
  % Routine Name:  setPrev
  % File:          MazeCell.hpp
  % Parameters:    prev - link a cell to this cell.
  % Description:   Setter method for the prev attribute.
  % Return:        Nothing.
  *****************************************************************************/
  void setPrev( MazeCell * prev ) {
    this->prev = prev;
  }

  /*****************************************************************************
  % Routine Name:  setDistance
  % File:          MazeCell.hpp
  % Parameters:    distance - mark this cell the given distance attribute.
  % Description:   Setter method for the distance attribute.
  % Return:        Nothing.
  *****************************************************************************/
  void setDistance( int distance ) {
    this->distance = distance;
  }

  /*****************************************************************************
  % Routine Name:  getVisited
  % File:          MazeCell.hpp
  % Parameters:    None.
  % Description:   Getter method for the visited attribute.
  % Return:        The visited attribute value.
  *****************************************************************************/
  bool getVisited() {
    return visited;
  }

  /*****************************************************************************
  % Routine Name:  getPrev
  % File:          MazeCell.hpp
  % Parameters:    None.
  % Description:   Getter method for the prev attribute.
  % Return:        The prev attribute.
  *****************************************************************************/
  MazeCell * getPrev() {
    return prev;
  }

  /*****************************************************************************
  % Routine Name:  getDistance
  % File :         MazeCell.hpp
  % Parameters:    None.
  % Description:   Getter method for the distance attribute.
  % Return:        The distance attribute value.
  *****************************************************************************/
  int getDistance() {
    return distance;
  }

  /*****************************************************************************
  % Routine Name: getNeighborList
  % File:         MazeCell.hpp
  % Parameters:   None.
  % Description:  Gets a list of the neighboring cells of the calling cell.
  % Return:       An iterable list of neighbors.
  *****************************************************************************/
  vector<MazeCell *> getNeighborList() {
    vector<MazeCell *> neighbor_list = vector<MazeCell *>();

    if( up != nullptr ) neighbor_list.push_back( up );
    if( right != nullptr ) neighbor_list.push_back( right );
    if( down != nullptr ) neighbor_list.push_back( down );
    if( left != nullptr ) neighbor_list.push_back( left );

    return neighbor_list;
  }

  /*****************************************************************************
  % Routine Name: operator ==
  % File:         MazeCell.hpp
  % Parameters:   cell - cell that will be compared with the calling cell.
  % Description:  Evaluates of two cells are internally equivalent.
  % Return:       True if and only if cell is equivaluent to the calling cell.
  *****************************************************************************/
  bool operator==( const MazeCell & cell ) {
    return ( row == cell.row && column == cell.column );
  }

  /*****************************************************************************
  % Routine Name: operator =
  % File:         MazeCell.hpp
  % Parameters:   cell - cell that will be copied. 
  % Description:  calls the copy constructor on the cell passed. 
  % Return:       A new copied MazeCell from the cell passed. 
  *****************************************************************************/
  MazeCell operator=( const MazeCell & cell ) {
    return MazeCell( cell );
  }


  /*****************************************************************************
  % Routine Name: operator (const char *)
  % File:         MazeCell.hpp
  % Parameters:   None. 
  % Description:  Overloads the type cast (const char *) to emulate implicit 
  %               string conversion of calling MazeCell. 
  % Return:       STring representation of calling cell. 
  *****************************************************************************/
  operator const char *() {
    string cell_info = "(" + to_string(row) + ", " + to_string(column) + ")";
    return cell_info.c_str();
  }

  /*****************************************************************************
  % Routine Name:  operator <<
  % File:          MazeCell.cpp
  % Parameters:    os   - output stream .
  %                cell - cell of interest.  
  % Description:   Allows for implicit string conversion of cell when printing. 
  % Return:        The passed output stram object.
  *****************************************************************************/
  friend ostream & operator<<( ostream & os, MazeCell & cell ) {
    os << "(" << cell.row << ", " << cell.column << ")";
    return os;
  }

private:
  /*****************************************************************************
  % Routine Name: addNeighbor
  % File:         MazeCell.hpp
  % Parameters:   cell - an adjacent cell in the maze from the calling cell.
  % Description:  Attaches cell as neighbobr of the calling cell.
  % Return:       Nothing.
  *****************************************************************************/
  void addNeighbor( MazeCell * cell ) {
    if( cell == nullptr ) return;
    if( column == cell->column ) {
      /* vertical devaited neighbor */
      if( row + 1 == cell->row ) down = cell;
      else if( row - 1 == cell->row ) up = cell;
    }
    else if( row == cell->row ) {
      /* normal x-axis convention */
      if( column + 1 == cell->column ) right = cell;
      else if( column - 1 == cell->column ) left = cell;
    }
    else {
      /* cell is not adjacent */
      #if defined( ARDUINO )
        if( Serial ) {
	  Serial.print( ADD_EDGE_ERROR );
	  Serial.print( *this );
	  Serial.print( " <-> " );
	  Serial.print( *cell );
	}
      #else
        cerr << ADD_EDGE_ERROR << *this << " <-> " << *cell;
      #endif
    }
  }

  /*****************************************************************************
  % Routine Name: removeNeighbor
  % File:         MazeCell.hpp
  % Parameters:   cell - an adjacent cell in the maze from the calling cell. 
  % Description:  Removes cell from the calling cells neighbor list. 
  % Return:       Nothing.
  *****************************************************************************/
  void removeNeighbor( MazeCell * cell ) {
    if( cell == nullptr ) return;
    if( column == cell->column ) {
      /* vertical neighbor */
      if( row + 1 == cell->row ) down = nullptr;
      else if( row - 1 == cell->row ) up = nullptr;
    }
    else if( row == cell->row ) {
      /* horizontal neighbor */
      if( column + 1 == cell->column ) right = nullptr;
      else if( column - 1 == cell->column ) left = nullptr;
    }
    else {
      /* cell is not adjacent */
      #if defined( ARDUINO )
        if( Serial ) {
	  Serial.print( REMOVE_EDGE_ERROR );
	  Serial.print( *this );
	  Serial.print( " <-> " );
	  Serial.print( *cell );
	}
      #else
        cerr << REMOVE_EDGE_ERROR << *this << " <-> " << *cell;
      #endif
    }
  }

protected: 
  static constexpr const char * ADD_EDGE_ERROR = 
    "Error: attempt to add edge to a pair on non-adjacent cells. ";
  static constexpr const char * REMOVE_EDGE_ERROR = 
    "Error: attempt to remove edge to a non-adjacent cell. ";
};

#endif
