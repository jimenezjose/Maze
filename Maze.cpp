/*******************************************************************************
                                                    Jose Jorge Jimenez-Olivas
                                                    Brandon Cramer
                                                    Chris Robles
                                                    Srinivas Venkatraman

                 University of California, San Diego
                      IEEE Micromouse Team 2019

File Name:       Maze.cpp
Description:     2D matrix data structure with an internal graph abstraction. 
*******************************************************************************/
#include "Maze.h"

using namespace std;

/* helper methods - function prototypes */
stack<string> verticallyStackedRange( int min, int max );

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
      width = height = 0;
    #else
      throw std::length_error("Maze");
    #endif
  }
  maze = vector<vector<MazeCell>>( height, vector<MazeCell>() );
  /* creating maze cells */
  for( int row = 0; row < height; row++ ) {
    for( int column = 0; column < width; column++ ) {
      maze[ row ].push_back( MazeCell(row, column) );
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
% Parameters:   cell_A - a cell in this maze.
%               cell_B - a cell in this maze.
% Description:  Creates an undirected egde between the given cells.
% Return:       Nothing. 
*****************************************************************************/
void Maze::addEdge( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return;
  /* undirected edge added */
  cell_A->addNeighbor( cell_B );
  cell_B->addNeighbor( cell_A );
}


/*****************************************************************************
% Routine Name: removeEdge
% File:         Maze.cpp
% Parameters:   cell_A - a cell in this maze.
%               cell_B - a cell in this maze.
% Description:  Removes an undirected egde that is between the given cells.
% Return:       Nothing.
*****************************************************************************/
void Maze::removeEdge( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return;
  /* removing undirected edge */
  cell_A->removeNeighbor( cell_B );
  cell_B->removeNeighbor( cell_A );
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
      MazeCell * currentCell = at(row, column);

      if( !outOfBounds(row + 1, column) ) {
	/* vertical deviation downwards */
	removeWall( currentCell, at(row + 1, column) );
      }
      if( !outOfBounds(row, column + 1) ) {
	/* horizontal deviation to the right */
	removeWall( currentCell, at(row, column + 1) );
      }
    }
  }
}

/*****************************************************************************
% Routine Name: addWall
% File:         Maze.cpp
% Parameters:   cell_A - a cell in this maze.
%               cell_B - a cell in this maze.
% Description:  Creates a wall between two neighbor cells in maze.
% Return:       Nothing. 
*****************************************************************************/
void Maze::addWall( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return;
  removeEdge( cell_A, cell_B );
}

/*****************************************************************************
% Routine Name: removeWall 
% File:         Maze.cpp
% Parameters:   cell_A - a cell in this maze.
%               cell_B - a cell in this maze.
% Description:  Removes the wall betweeb two neighbor cells in maze. 
% Return:       Nothing. 
*****************************************************************************/
void Maze::removeWall( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return;
  addEdge( cell_A, cell_B );
}

/*****************************************************************************
% Routine Name: clear
% File:         Maze.cpp
% Parameters:   None.
% Description:  Clears all internal data of cell relationships in maze.
% Return:       Nothing. 
*****************************************************************************/
void Maze::clear() {
  for( MazeCell * cell : *this ) {
    /* clear data for all cells in maze */
    cell->clearData();
  }
}

/*****************************************************************************
% Routine Name: at
% File:         Maze.cpp
% Parameters:   coordinate - pair of integers (row, col). 
% Description:  Accessor method for maze internal nodal data structures.
% Return:       MazeCell pointer at (row, col) position in 2-dimensional maze.
*****************************************************************************/
MazeCell * Maze::at( pair<int, int> & coordinate ) {
  return at( coordinate.first, coordinate.second );
}

/*****************************************************************************
% Routine Name: at
% File:         Maze.cpp
% Parameters:   row    - row of cell in maze
%               column - column of cell in maze
% Description:  Accessor method for maze internal nodal data structures.
% Return:       MazeCell pointer at (row, col) position in 2-dimensional maze. 
*****************************************************************************/
MazeCell * Maze::at( int row, int column ) {
  if( outOfBounds(row, column) ) {
    return nullptr;
  }
  return &maze[ row ][ column ];
}

/*****************************************************************************
% Routine Name: wallBetween
% File:         Maze.cpp
% Parameters:   cell_A - cell from maze of interest.
%               cell_B - cell from maze of interest.
% Description:  Evaluates if a wall exists between two nodes in the maze.
% Return:       true if there exisits a wall between the cell-pair.
*****************************************************************************/
bool Maze::wallBetween( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return false;

  vector<MazeCell *> neighbors_of_A = cell_A->getNeighborList();

  for( MazeCell * neighbor : neighbors_of_A ) {
    if( neighbor == cell_B ) {
      /* There is a path directly connect A and B, therefore no wall */
      return false;
    }
  }
  return true;
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
% Parameters:   cell - the cell of interest in the maze.
% Description:  Gets all global adjacent neighbors of cell in maze.
% Return:       A list of all existing adjacent neighbors of cell in maze.
*****************************************************************************/
vector<MazeCell *> Maze::getAdjacentCellList( MazeCell * cell ) {
  if( cell == nullptr ) return vector<MazeCell *>();
  const int MAX_CELLS = 4;
  const int EVEN = 2;
  vector<MazeCell *> list;

  for( int index = 0; index < MAX_CELLS; index++ ) {
    /* append all adjacent neighbors to list */
    int deviation = ( index < EVEN ) ? -1 : +1;
    int dr = ( index % EVEN == 0 ) ? deviation : 0;
    int dc = ( index % EVEN == 1 ) ? -deviation : 0;
    if( !outOfBounds(cell->row + dr, cell->column + dc) ) { 
      list.push_back( at(cell->row + dr, cell->column + dc) );
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
% Routine Name: operator (const char *) 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Casts the maze to a c string representation. 
% Return:       A c string representation of the state of the maze.
*****************************************************************************/
Maze::operator const char *() {
  ostringstream ss;

  /* draw column indices - vertically */
  stack<string> indices_stack = verticallyStackedRange( 0, getWidth() );
  while( !indices_stack.empty() ) {
    ss << " \t " << indices_stack.top() << endl;
    indices_stack.pop();
  }

  /* draw top-most walls of maze */
  ss << " \t ";
  for( int column = 0; column < getWidth(); column++ ) {
    ss << "_ ";
  }
  ss << endl;

  /* draw right and bottom walls in maze */
  for( int row = 0; row < getHeight(); row++ ) {
    ss << row << "\t|";
    for( int column = 0; column < getWidth(); column++ ) {
      MazeCell * currentCell = at( row, column );
      MazeCell * rightCell   = at( row, column + 1 );
      MazeCell * downCell    = at( row + 1, column );
      bool bottom_wall_exists = wallBetween(currentCell, downCell);
      bool right_wall_exists  = wallBetween(currentCell, rightCell);

      if( row < getHeight() - 1 && bottom_wall_exists  ) {
        /* bottom-wall character */
        ss << "_";
      }
      else if( row < getHeight() - 1 ) {
        /* bottom-wall is absent */
        ss << " ";
      }

      if( row == getHeight() - 1 ) {
        /* botton of maze */
        ss << "_";
      }

      if( column < getWidth() - 1 && right_wall_exists ) {
        /* right-wall character */
        ss << "|";
      }
      else if( column < getWidth() - 1 ) {
        /* right-wall is absent */
        ss << " ";
      }

      if( column == getWidth() - 1  ) {
        /* right-end of maze */
        ss << "|";
      }
    }
    ss << endl;
  }

  maze_str = ss.str();
  return maze_str.c_str(); 
}

/*****************************************************************************
% Routine Name: verticallyStackedRange 
% File:         Maze.cpp
% Parameters:   min - smallest integer in the range. 
%               max - largest integer in the range.
% Description:  Given the range [min, max] this function will return stack of
%               strings that represent columns of the vertically stacked 
%               integers.
% Example:      min = 0, max = 15:
%                                   1 1 1 1 1 1
%               0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
% Return:       A stack of strings for every row of the vertically aligned 
%               integers.
*****************************************************************************/
stack<string> verticallyStackedRange( int min, int max ) {
  if( min > max ) return stack<string>();

  stack<string> stak;
  bool column_print_done = false;
  int base = 10;
  int exponent = 1;
  ostringstream ss;

  while( !column_print_done ) {
    int prev_base = pow( base, exponent - 1 );
    int curr_base = pow( base, exponent );
    column_print_done = true;

    for( int column = min; column < max; column++ ) {
      int remainder = column % curr_base;

      if( column == 0 ) {
        /* special case for all evenly divisible 0 */
	if( prev_base == 1 ) ss << "0 ";
	else ss << "  ";
	continue;
      }
      
      if( column / prev_base == 0 && column % curr_base != 0  ) {
        /* skip - for no leading zeros */
        ss <<  " ";
      }
      else {
        /* append single digit remainer */
        ss << remainder / prev_base;
        column_print_done = false;
      }
      ss << " ";
    }
    stak.push( ss.str() );
    ss.str("");
    exponent++;
  }

  return stak;
}


/*****************************************************************************
% Routine Name: operator<< 
% File:         Maze.cpp
% Parameters:   os   - output stream reference.
%               maze - reference to maze of interest.
% Description:  Overloads the << operator to draw the given state of the maze. 
% Return:       A reference to the passed output stream.
*****************************************************************************/
ostream & operator<<( ostream & os, Maze & maze ) {
  os << (const char *) maze;
  return os;
}

/*****************************************************************************
% Routine Name: Maze::Iterator::operator * 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Overloads the * operator to return the curr maze cell pointer.
% Return:       The maze cell that curr points to. 
*****************************************************************************/
MazeCell * Maze::Iterator::operator*() const {
  return curr;
}

/*****************************************************************************
% Routine Name: Maze::Iterator::operator ++ 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Overloads the prefix operator++ and moves curr to the 
%               successor cell of the maze container.
% Return:       The calling maze iteartor.
*****************************************************************************/
Maze::Iterator Maze::Iterator::operator++() {
  MazeCell * end = maze.at( maze.getHeight() - 1, maze.getWidth() - 1 );

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
