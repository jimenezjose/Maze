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
| `Maze::addWall()`    |    | 
| `Maze::removeWall()` |  |
| `Maze::clear()` |  |
| `Maze::clearWalls()` |  |
| `Maze::at()` |  |
| `Maze::wallBetween( MazeCell * cell_A, MazeCell * cell_B )` |  |
| `Maze::outOfBounds( int row, int column )` |  |
| `Maze::getAdjacentCellList( MazeCell * cell )` |  |
| `Maze::getWidth()` |  |
| `Maze::getHeight()` |  |

## Maze Visualization:
![Alt Text](https://github.com/jimenezjose/Maze/blob/master/.images/Maze-Graph.png)
