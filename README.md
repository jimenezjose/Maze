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
| `Maze::removeWall()` | Removes the wall betweeb two neighboring cells in the maze. |
| `Maze::clear()` | Clears all internal data of node relationships in maze. |
| `Maze::clearWalls()` | Clears the maze such that no walls will exist between two nodes |
| `Maze::at()` | Accessor method for maze internal nodal data structures. |
| `Maze:: wallBetween( MazeNode * node_A, MazeNode * node_B );` | Checks if there exists a wall between the given points or nodes. |

## Maze Visualization:
![Alt Text](https://github.com/jimenezjose/Maze/blob/master/.images/Maze-Graph.png)
