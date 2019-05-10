# Maze
Two-Dimensional Maze data structure.

## Arduino Installation:
To learn how to include the Maze library to your Arduino project click [here](https://www.arduino.cc/en/guide/libraries#toc4). 
```c++
#include <Maze.h>
```

## C++ Library Installation:
Download the repository to your project directory.
```c++
#include "Maze-master/Maze.h"
```

# Maze Member Functions:

| Functions | Description| 
| -------------------  |:-----------------------------------------------------------:| 
| `Maze::addWall()`    | Creates a wall between two neighboring cells in the maze.   | 
| a | 
```c++
int index = 0;
``` |
| `Maze::removeWall()` | Removes the wall betweeb two neighboring cells in the maze. |
| `Maze::clear()` | Clears all internal data of node relationships in maze. |
| `Maze::clearWalls()` | Clears the maze such that no walls will exist between two nodes |
| `Maze::at()` | Accessor method for maze internal nodal data structures. |
| `Maze::wallBetween( MazeNode * node_A, MazeNode * node_B )` | Checks if there exists a wall between the given nodes. |
| `Maze::outOfBounds( int row, int column )` | Checks if the (row, column) coordinate is not in the maze. |
| `Maze::getAdjacentCellList( MazeNode * node )` | Gets all global adjacent neighbors of node in maze. |
| `Maze::getWidth()` | Getter method for the width, in unit cells, of the maze. |
| `Maze::getHeight()` | Getter method for the height, in unit cells, of the maze. |

## Maze Visualization:
![Alt Text](https://github.com/jimenezjose/Maze/blob/master/.images/Maze-Graph.png)
