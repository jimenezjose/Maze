/*******************************************************************************
                                                    Jose Jorge Jimenez-Olivas
                                                    Brandon Cramer

                 University of California, San Diego
                           IEEE Micromouse

File Name:       Maze.cpp
Description:     2D matrix data structure with an internal graph abstraction. 
*******************************************************************************/
#include "Maze.h"

/* Helper Functions */
namespace MazeHelper {
  std::stack<std::string> verticallyStackedRange( int min, int max );
}

/*******************************************************************************
% Constructor: Maze
% File:        Maze.cpp
% Parameters:  width  - width of rectangular maze.
%              height - height of rectangular maze.
% Description: Creates a two dimensional maze data structure.
*******************************************************************************/
Maze::Maze( int width, int height ) : width( width ), height( height ) {
  if( width < 0 || height < 0 ) {
    #if defined( ARDUINO )
      width = height = 0;
    #else
      throw std::length_error("Maze");
    #endif
  }
  maze = std::vector<std::vector<MazeCell>>( height, std::vector<MazeCell>() );
  /* creating maze cells */
  for( int row = 0; row < height; row++ ) {
    for( int column = 0; column < width; column++ ) {
      maze[ row ].push_back( MazeCell(row, column) );
    }
  }
}

/*******************************************************************************
% Constructor: Maze
% File:        Maze.cpp
% Parameters:  filename - File location of a stored maze.
% Description: Loads stored maze from disk to memory.
*******************************************************************************/
Maze::Maze( const char * filename ) : 
  Maze( deserializeWidth(filename), deserializeHeight(filename) ) {
    
  load( filename );
}

/*******************************************************************************
% Destructor: ~Maze 
% File:        Maze.cpp
% Parameters:  None.
% Description: Deletes all heap allocated memory associated with the maze.
*******************************************************************************/
Maze::~Maze() {}

/*******************************************************************************
% Routine Name: addEdge
% File:         Maze.cpp
% Parameters:   cell_A - a cell in this maze.
%               cell_B - a cell in this maze.
% Description:  Creates an undirected egde between the given cells.
% Return:       Nothing. 
*******************************************************************************/
void Maze::addEdge( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return;
  /* undirected edge added */
  cell_A->addNeighbor( cell_B );
  cell_B->addNeighbor( cell_A );
}


/*******************************************************************************
% Routine Name: removeEdge
% File:         Maze.cpp
% Parameters:   cell_A - a cell in this maze.
%               cell_B - a cell in this maze.
% Description:  Removes an undirected egde that is between the given cells.
% Return:       Nothing.
*******************************************************************************/
void Maze::removeEdge( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return;
  /* removing undirected edge */
  cell_A->removeNeighbor( cell_B );
  cell_B->removeNeighbor( cell_A );
}

/*******************************************************************************
% Routine Name: clearWalls
% File:         Maze.cpp
% Parameters:   None. 
% Description:  Clears the maze such that no walls will exist - this will 
%               create a fully connected maze (definition of wall).
% Return:       Nothing. 
*******************************************************************************/
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

/*******************************************************************************
% Routine Name: addWall
% File:         Maze.cpp
% Parameters:   cell_A - a cell in this maze.
%               cell_B - a cell in this maze.
% Description:  Creates a wall between two neighbor cells in maze.
% Return:       Nothing. 
*******************************************************************************/
void Maze::addWall( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return;
  removeEdge( cell_A, cell_B );
}

/*******************************************************************************
% Routine Name: removeWall 
% File:         Maze.cpp
% Parameters:   cell_A - a cell in this maze.
%               cell_B - a cell in this maze.
% Description:  Removes the wall between two neighbor cells in maze. 
% Return:       Nothing. 
*******************************************************************************/
void Maze::removeWall( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return;
  addEdge( cell_A, cell_B );
}

/*******************************************************************************
% Routine Name: clear
% File:         Maze.cpp
% Parameters:   None.
% Description:  Clears all internal data of cell relationships in maze.
% Return:       Nothing. 
*******************************************************************************/
void Maze::clear() {
  for( MazeCell * cell : *this ) {
    /* clear data for all cells in maze */
    cell->clearData();
  }
}

/*******************************************************************************
% Routine Name: at
% File:         Maze.cpp
% Parameters:   coordinate - std::pair of integers (row, col). 
% Description:  Accessor method for maze internal nodal data structures.
% Return:       MazeCell pointer at (row, col) position in 2-dimensional maze.
*******************************************************************************/
MazeCell * Maze::at( std::pair<int, int> & coordinate ) {
  return at( coordinate.first, coordinate.second );
}

/*******************************************************************************
% Routine Name: at
% File:         Maze.cpp
% Parameters:   row    - row of cell in maze
%               column - column of cell in maze
% Description:  Accessor method for maze internal nodal data structures.
% Return:       MazeCell pointer at (row, col) position in 2-dimensional maze. 
*******************************************************************************/
MazeCell * Maze::at( int row, int column ) {
  if( outOfBounds(row, column) ) {
    return nullptr;
  }
  return &maze[ row ][ column ];
}

/*******************************************************************************
% Routine Name: wallBetween
% File:         Maze.cpp
% Parameters:   cell_A - cell from maze of interest.
%               cell_B - cell from maze of interest.
% Description:  Evaluates if a wall exists between two nodes in the maze.
% Return:       true if there exists a wall between the cell-std::pair.
*******************************************************************************/
bool Maze::wallBetween( MazeCell * cell_A, MazeCell * cell_B ) {
  if( cell_A == nullptr || cell_B == nullptr ) return false;

  std::vector<MazeCell *> neighbors_of_A = cell_A->getNeighborList();

  for( MazeCell * neighbor : neighbors_of_A ) {
    if( neighbor == cell_B ) {
      /* There is a path directly connect A and B, therefore no wall */
      return false;
    }
  }
  return true;
}

/*******************************************************************************
% Routine Name: outOfBounds
% File:         Maze.cpp
% Parameters:   row    - vertical deviated position of interest.
%               column - horizontal deviated position of interest.
% Description:  Checks if the (row, column) coordinate is not in the maze. 
% Return:       True if and only if (row,column) does not exist in maze. 
*******************************************************************************/
bool Maze::outOfBounds( int row, int column) {
  bool row_out_of_bounds = row < 0 || row >= getHeight();
  bool column_out_of_bounds = column < 0 || column >= getWidth();
  return row_out_of_bounds || column_out_of_bounds;
}

/*******************************************************************************
% Routine Name: getAdjacentCellList
% File:         Maze.cpp
% Parameters:   cell - the cell of interest in the maze.
% Description:  Gets all global adjacent neighbors of cell in maze.
% Return:       A list of all existing adjacent neighbors of cell in maze.
*******************************************************************************/
std::vector<MazeCell *> Maze::getAdjacentCellList( MazeCell * cell ) {
  if( cell == nullptr ) return std::vector<MazeCell *>();
  const int MAX_CELLS = 4;
  const int EVEN = 2;
  std::vector<MazeCell *> list;

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

/*******************************************************************************
% Routine Name: getWidth
% File:         Maze.cpp
% Parameters:   None.
% Description:  Getter method for the width, in unit cells, of the maze.
% Return:       The width of the maze in unit of cells.
*******************************************************************************/
int Maze::getWidth() {
  return width;
}

/*******************************************************************************
% Routine Name: getHeight
% File:         Maze.cpp
% Parameters:   None.
% Description:  Getter method for the height, in unit cells, of the maze.
% Return:       The height of the maze in units of cells.
*******************************************************************************/
int Maze::getHeight() {
  return height;
}

/*******************************************************************************
% Routine Name: save
% File:         Maze.cpp
% Parameters:   filename - File to serialize maze data to. 
% Description:  Saves maze to the disk.
% Return:       Save status.
*******************************************************************************/
bool Maze::save( const char * filename ) {
  #ifndef ARDUINO
  std::ofstream outstream;
  outstream.open( filename, std::ios::out | std::ios::binary );
  std::cerr << "Saving Maze..." << std::endl;
  if( !outstream.is_open() ) {
    std::cerr << "Unable to open file: " << filename << std::endl;
    return false;
  }
  bool status = serialize( outstream );
  outstream.close();
  return status;
  #endif
}

/*******************************************************************************
% Routine Name: load
% File:         Maze.cpp
% Parameters:   filename - File to serialize maze data to. 
% Description:  Loads maze from the disk.
% Return:       Load status.
*******************************************************************************/
bool Maze::load( const char * filename ) {
  #ifndef ARDUINO
  std::ifstream instream;
  instream.open( filename, std::ios::in | std::ios::binary );
  std::cerr << "Loading Maze..." << std::endl;
  if( !instream.is_open() ) {
    std::cerr << "Unable to open file: " << filename << std::endl;
    return false;
  }
  bool status = deserialize( instream );
  instream.close();
  return status;
  #endif
}

/*******************************************************************************
% Routine Name: serialize
% File:         Maze.cpp
% Parameters:   outstream - Output stream pointing to an open file to write to.
% Description:  Encoding maze data to the disk.
% Return:       Nothing.
*******************************************************************************/
bool Maze::serialize( std::ofstream & outstream ) {
  #ifndef ARDUINO
  int data = 0;
  int bitcount = 0;
  /* write dimensions of maze out to stream - order: width height */
  int w = ntohl(width);
  int h = ntohl(width);
  outstream.write( (char *) &w, sizeof(width) );
  outstream.write( (char *) &h, sizeof(height) );

  /* write each cell info to data file */
  for( int row = 0; row < getHeight(); row++ ) {
    for( int column = 0; column < getWidth(); column++ ) {
      MazeCell * currentCell = at( row, column );
	    /* bitflag of open down neighbor */
	    data = data << 1;
	    if( currentCell->down != nullptr ) data |= 0x01;
	    bitcount++;
      /* bitflag of open right neighbor */
	    data = data << 1;
	    if( currentCell->right != nullptr ) data |= 0x01;
	    bitcount++;
	    /* time to write byte to stream */
	    if( bitcount == CHAR_BIT ) {
        outstream.write( (char *) &data, sizeof(char) );
	      data = bitcount = 0;
	    }
    }
  } 
  /* flush data to data file */
  if( bitcount != 0 ) {
    data = data << (CHAR_BIT - bitcount); /* trailing zeros only */
    outstream.write( (char *) &data, sizeof(char)); 
  }
  return true;
  #endif
}

/*******************************************************************************
% Routine Name: deserialize
% File:         Maze.cpp
% Parameters:   instream - Input stream pointing to a file to read from.
% Description:  Decoding maze from the disk.
% Return:       True for successful decode and maze build, false otherwise.
*******************************************************************************/
bool Maze::deserialize( std::ifstream & instream ) {
  #ifndef ARDUINO
  const int codeword_size = 2; /* bit size */
  const int codeword_bitmask = ( 0x3 << (CHAR_BIT - codeword_size) );

  /* read dimensions of maze from input stream - order: width height */
  char buffer[BUFSIZ] = { 0 };
  instream.read( buffer, 2 * sizeof(int) );
  if( !instream ) {
    /* corrupted datafile - missing bytes */
    std::cerr << "Currupted file detected: Incompatible file size: Aborting maze build" << std::endl; 
    return false;
  }
  /* strict order of: width, height */
  int read_width, read_height;
  std::memcpy( &read_width, buffer, sizeof(int) );
  std::memcpy( &read_height, buffer + sizeof(int), sizeof(int) );
  read_width = ntohl(read_width);
  read_height = ntohl(read_height);
  std::cerr << "Loading dimensions: (" << read_width << "," << read_height << ")" << std::endl;
  if( read_width != getWidth() || read_height != getHeight() ) {
    /* width or height is not the same dimension as this maze object */
    std::cerr << "Incompatible dimensions read from file: Aborting maze build" << std::endl;
    return false;
  }

  /* read and build maze graph cell by cell */
  int recieved = 0;
  int row = 0;
  int column = 0;
  clearWalls(); /* creating walls are easier than removing walls */
  instream.read(buffer, sizeof(char)); /* read byte */
  memcpy(&recieved, buffer, sizeof(char));
  while( instream ) {
    /* reading 2-bit codewords. (1 codeword = 1 encoded maze node) */
    for( int index = 0; index < CHAR_BIT / codeword_size; index++ ) {
      if( row == getHeight() ) {
        /* maze building is done - all cells visited */
        int bytes_read = instream.tellg();
        instream.seekg( 0, instream.end );
        int bytes_available = ((int)instream.tellg()) - bytes_read;
        if( bytes_available ) {
          std::cerr << "Curropted file detected: Incompatible file size: Aborting maze build" << std::endl;
          clear();
          return false; 
        }
        return true;
      }
      /* build walls of cell */
      MazeCell * currentCell = at( row, column );
      int codeword = ((recieved & codeword_bitmask) >> (CHAR_BIT - codeword_size)); 
      deserializeCell( currentCell, codeword );
      recieved = recieved << codeword_size;
      column++;
      if( column == getWidth() ) {
          column = 0;
	        row++;
	    }
    }
    instream.read(buffer, sizeof(char));
    memcpy(&recieved, buffer, sizeof(char));
  }

  return true;
  #endif
}

/*******************************************************************************
% Routine Name: deserializeCell 
% File:         Maze.cpp
% Parameters:   cell     - Cell to be deserialized.
%               codeword - Two-bit encoded cell. 
% Description:  Builds encoded maze node from a two bit codeword. 
% Return:       Nothing.
*******************************************************************************/
void Maze::deserializeCell( MazeCell * cell, int codeword ) {
  const int down_bitmask = 0x01 << 1; 
  const int right_bitmask = 0x01;
  
  if( (codeword & down_bitmask) == 0 && cell->row != getHeight() - 1 ) {
    /* add down wall */
    addWall( at(cell->row, cell->column), at(cell->row + 1, cell->column) );
  }
  if( (codeword & right_bitmask) == 0 && cell->column != getWidth() - 1 ) {
    /* add right wall */
    addWall( at(cell->row, cell->column), at(cell->row, cell->column + 1) );
  }
}

/*******************************************************************************
% Routine Name: deserializeWidth
% File:         Maze.cpp
% Parameters:   filename - file location maze is stored and encoded.
% Description:  Reads the width of the maze from the file.
% Return:       The width of the stored maze.
*******************************************************************************/
int Maze::deserializeWidth( const char * filename ) {
  #ifndef ARDUINO
  int read_width;
  std::ifstream instream;
  instream.open( filename, std::ios::in | std::ios::binary );
  if( !instream.is_open() ) {
    return 0;
  }
  /* encoded maze dimesion order: width, height */
  instream.seekg( 0, instream.end );
  int bytes_available = instream.tellg();
  if( bytes_available < sizeof(int) ) {
    /* corrupted datafile - missing bytes */
    return 0;
  }
  instream.seekg( 0, instream.beg );
  instream.read( (char *)&read_width, sizeof(int) );
  instream.close();
  return ntohl( read_width );
  #endif
}

/*******************************************************************************
% Routine Name: deserializeHeight
% File:         Maze.cpp
% Parameters:   filename - file location maze is stored and encoded.
% Description:  Reads the height of the maze from the file.
% Return:       The height of the stored maze.
*******************************************************************************/
int Maze::deserializeHeight( const char * filename ) {
  #ifndef ARDUINO
  int read_height;
  std::ifstream instream;
  instream.open( filename, std::ios::in | std::ios::binary );
  if( !instream.is_open() ) {
    return 0;
  }
  /* encoded maze dimesion order: width, height */
  instream.seekg( 0, instream.end );
  int bytes_available = instream.tellg();
  if( bytes_available < 2 * sizeof(int) ) {
    /* corrupted datafile - missing bytes */
    return 0;
  }
  instream.seekg( sizeof(int), instream.beg );
  instream.read( (char *)&read_height, sizeof(int) );
  instream.close();
  return ntohl( read_height );
  #endif
}

/*******************************************************************************
% Routine Name: operator (const char *) 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Casts the maze to a c string representation. 
% Return:       A c string representation of the state of the maze.
*******************************************************************************/
Maze::operator const char *() {
  std::stack<std::string> indices_stack;
  maze_str = "";

  /* draw column indices - vertically */
  indices_stack = MazeHelper::verticallyStackedRange( 0, getWidth() );
  
  while( !indices_stack.empty() ) {
    maze_str += " \t " + indices_stack.top() + "\n";
    indices_stack.pop();
  }

  /* draw top-most walls of maze */
  maze_str += " \t ";
  for( int column = 0; column < getWidth(); column++ ) {
    maze_str += "_ ";
  }
  maze_str += "\n";

  /* draw right and bottom walls in maze */
  for( int row = 0; row < getHeight(); row++ ) {
    maze_str += std::to_string(row) + "\t|";
    for( int column = 0; column < getWidth(); column++ ) {
      MazeCell * currentCell = at( row, column );
      MazeCell * rightCell   = at( row, column + 1 );
      MazeCell * downCell    = at( row + 1, column );
      bool bottom_wall_exists = wallBetween(currentCell, downCell);
      bool right_wall_exists  = wallBetween(currentCell, rightCell);

      if( row < getHeight() - 1 && bottom_wall_exists  ) {
        /* bottom-wall character */
        maze_str += "_";
      }
      else if( row < getHeight() - 1 ) {
        /* bottom-wall is absent */
        maze_str += " ";
      }

      if( row == getHeight() - 1 ) {
        /* botton of maze */
        maze_str += "_";
      }

      if( column < getWidth() - 1 && right_wall_exists ) {
        /* right-wall character */
        maze_str += "|";
      }
      else if( column < getWidth() - 1 ) {
        /* right-wall is absent */
        maze_str += " ";
      }

      if( column == getWidth() - 1  ) {
        /* right-end of maze */
        maze_str += "|";
      }
    }
    maze_str += "\n";
  }
  return maze_str.c_str(); 
}

/*******************************************************************************
% Routine Name: operator==
% File:         Maze.cpp
% Parameters:   other - Comparing maze.
% Description:  Maze graph equivalence.
% Return:       True if maze graphs are equivelent, false otherwise.
*******************************************************************************/
bool Maze::operator==( const Maze & other ) const {
  if( height != other.height ) return false;
  if( width != other.width ) return false;

  for( int row = 0; row < height; row++ ) {
    for( int column = 0; column < width; column++ ) {
      /* compare all cells for graph-node equivalence */
      const MazeCell * currentCell = &this->maze[ row ][ column ];
      const MazeCell * otherCell = &other.maze[ row ][ column ];
      if( !(currentCell->up) != !(otherCell->up) ) return false;
      if( !(currentCell->right) != !(otherCell->right) ) return false;
      if( !(currentCell->down) != !(otherCell->down) ) return false;
      if( !(currentCell->left) != !(otherCell->left) ) return false;
    }
  }
  return true;
}

/*******************************************************************************
% Routine Name: operator!=
% File:         Maze.cpp
% Parameters:   other - Comparing maze.
% Description:  Maze graph non-equivalence.
% Return:       True if maze graphs are non-equivelent, false otherwise.
*******************************************************************************/
bool Maze::operator!=( const Maze & other ) const {
  return !(*this==other);
}

/*******************************************************************************
% Routine Name: operator<< 
% File:         Maze.cpp
% Parameters:   os   - output stream reference.
%               maze - reference to maze of interest.
% Description:  Overloads the << operator to draw the given state of the maze. 
% Return:       A reference to the passed output stream.
*******************************************************************************/
std::ostream & operator<<( std::ostream & os, Maze & maze ) {
  os << (const char *) maze;
  return os;
}

/*******************************************************************************
% Routine Name: Maze::Iterator::operator * 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Overloads the * operator to return the curr maze cell pointer.
% Return:       The maze cell that curr points to. 
*******************************************************************************/
MazeCell * Maze::Iterator::operator*() const {
  return curr;
}

/*******************************************************************************
% Routine Name: Maze::Iterator::operator ++ 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Overloads the prefix operator++ and moves curr to the 
%               successor cell of the maze container.
% Return:       The calling maze iteartor.
*******************************************************************************/
Maze::Iterator & Maze::Iterator::operator++() {
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

/*******************************************************************************
% Routine Name: Maze::Iterator::operator ++ 
% File:         Maze.cpp
% Parameters:   None.
% Description:  Overloads the postfix operator++ and moves curr to the 
%               successor of the maze container.
% Return:       The calling maze iterator before moving curr to its sucessor. 
*******************************************************************************/
Maze::Iterator Maze::Iterator::operator++(int) {
  Maze::Iterator before( maze, curr );
  ++(*this);
  return before;
}

/*******************************************************************************
% Routine Name: Maze::Iterator::operator ==
% File:         Maze.cpp
% Parameters:   other - an iterator to compare with.
% Description:  Overloads the == operator to check equality of two maze 
%               iterators based on a shallow comparsion of curr pointers.
% Return:       True if both curr and the other iterators curr point to the 
%               same address in memory, false otherwise. 
*******************************************************************************/
bool Maze::Iterator::operator==( Maze::Iterator const & other ) const {
  return curr == other.curr;
}

/*******************************************************************************
% Routine Name: Maze::Iterator::operator !=
% File:         Maze.cpp
% Parameters:   other - an iterator to compare with.
% Description:  Overloads the != opearator to evaluate when two maze iterators
%               are not equivalent based on curr pointer comparison. 
% Return:       True if the other iterator's curr is not same as this objects
%               curr, false otherwise. 
*******************************************************************************/
bool Maze::Iterator::operator!=( Maze::Iterator const & other ) const {
  return curr != other.curr;
}

/*******************************************************************************
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
% Return:       A std::stack of strings for every row of the vertically aligned 
%               integers.
*******************************************************************************/
std::stack<std::string> MazeHelper::verticallyStackedRange( int min, int max ) {
  if( min > max ) return std::stack<std::string>();
  std::stack<std::string> stak;
  bool column_print_done = false;
  int base = 10;
  int exponent = 1;
  std::string str = "";

  while( !column_print_done ) {
    int prev_base = pow( base, exponent - 1 );
    int curr_base = pow( base, exponent );
    column_print_done = true;

    for( int column = min; column < max; column++ ) {
      int remainder = column % curr_base;

      if( column == 0 ) {
        /* special case for all evenly divisible 0 */
        if( prev_base == 1 ) str += "0 ";
        else str += "  ";
        continue;
      }
      
      if( column / prev_base == 0 && column % curr_base != 0  ) {
        /* skip - for no leading zeros */
        str +=  " ";
      }
      else {
        /* append single digit remainer */
        str += std::to_string( remainder / prev_base );
        column_print_done = false;
      }
      str += " ";
    }
    stak.push( str );
    str = ""; 
    exponent++;
  }

  return stak;
}  
