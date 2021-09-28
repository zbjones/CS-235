//
// Created by zacha on 3/7/2020.
//

#ifndef INC_3D_MAZE_MAZE_H
#define INC_3D_MAZE_MAZE_H

#include "MazeInterface.h"
#include <string>
#include <sstream>


//define directions for readability later.
#define UP row - 1, column, layer
#define DOWN row + 1, column, layer
#define RIGHT row, column + 1, layer
#define LEFT row, column - 1, layer
#define OUT row, column, layer - 1
#define IN row, column, layer + 1

//enums to help with readability
enum CellValue { OPEN, PATH, EXIT, TEMPORARY, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, MOVE_OUT, MOVE_IN };

class Maze : MazeInterface {

private:
int mazeHeight;
int mazeWidth;
int mazeLayers;
int*** myMaze;

public:
    Maze(int height, int width, int layers);

    //destructor, delete array that [i][j] points to, then the array pointed to by I, then, the final array.
    ~Maze() {
        for(int i = 0; i < mazeHeight; ++i) {
            for (int j = 0; j < mazeWidth; j++) {
                delete [] myMaze[i][j];
            }
            delete [] myMaze[i];
        }
            delete [] myMaze;
    };

    //helper function to mark values at specified points of 3d array
    void setValue(int height, int width, int layer, int value) {
        myMaze[height][width][layer] = value;
    };

    std::string toString() const;

    //wrapper function with no parameters
    bool find_maze_path() {
        return find_maze_path(0, 0, 0); //starting point is always 0, 0, 0
    }

    //recursive find path function with parameters
    bool find_maze_path(int row, int column, int layer);

    //helper function to not inadvertently replace the layer numbers in the string
    bool checkLayerLine(std::string strToReturn, int index) const {
        if (strToReturn.at(index - 2) == 'r' || isdigit(strToReturn.at(index - 1))) {
            return false;
        }
        return true;
    }
};


#endif //INC_3D_MAZE_MAZE_H
