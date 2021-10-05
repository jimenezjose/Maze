#include <Maze.h>

Maze maze( 16, 16 );

void setup() {
  Serial.begin(9600);
  
  int row = 15;
  int column = 15;
  
  if( maze.outOfBounds(row, column) ) {
    Serial.println("out of bounds"); 
    row = column = 0;
  }
  
  MazeCell * cell = maze.at(row, column);
  for( MazeCell * openNeighbor : cell->getNeighborList() ) {
    /* visit cell neighbors and change their distance */
    if( openNeighbor->visited ) continue;
    openNeighbor->setVisited( true );
    openNeighbor->distance = cell->distance + 1;
  }

}

void loop() {
  // for more inspiration take a look at https://github.com/jimenezjose/Micromouse_Firmware_2019/
}
