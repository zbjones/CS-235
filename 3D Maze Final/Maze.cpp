//
// Created by zacha on 3/7/2020.
//

#include "Maze.h"
//recursive call for function to find the path.  Has 3 base cases,
bool Maze::find_maze_path(int row, int column, int layer) {
    //out of bounds first case
    if (row < 0 || column < 0 || layer < 0 || row >= mazeHeight || column >= mazeWidth || layer >= mazeLayers) {
        return false;
    }
        //base case when the next value is not open to go through
    else if (myMaze[row][column][layer] != OPEN) {
        return false;
    }
        //base case when the value IS the exit.
    else if (row == mazeHeight - 1 && column == mazeWidth - 1 && layer == mazeLayers - 1) {
        myMaze[row][column][layer] = EXIT;
        return true;
    }
    //Case when it the value is open and it may be the path, check all directions in specified order.
    myMaze[row][column][layer] = PATH;
    if (find_maze_path(LEFT)) {
        setValue(row, column, layer, MOVE_LEFT);
        return true;
    }
    if (find_maze_path(RIGHT)) {
        setValue(row, column, layer, MOVE_RIGHT);
        return true;
    }
    if (find_maze_path(UP)) {
        setValue(row, column, layer, MOVE_UP);
        return true;
    }
    if (find_maze_path(DOWN)) {
        setValue(row, column, layer, MOVE_DOWN);
        return true;
    }
    if (find_maze_path(OUT)) {
        setValue(row, column, layer, MOVE_OUT);
        return true;
    }
    if (find_maze_path(IN)) {
        setValue(row, column, layer, MOVE_IN);
        return true;
    }
    myMaze[row][column][layer] = TEMPORARY; //This line prevents infinite recursive loops
    return false;
}
//toString function, also handles int to char conversions for bonus part
std::string Maze::toString() const {
    std::string strToReturn = "";
    for (int i = 0; i < mazeLayers; i++) {
        strToReturn = strToReturn + "\n" + "Layer " + std::to_string(i + 1);
        for (int j = 0; j < mazeHeight; j++) {
            strToReturn = strToReturn + "\n";
            for (int k = 0; k < mazeWidth; k++) {
                strToReturn = strToReturn + std::to_string(myMaze[j][k][i]) + " ";
            }
        }
    }
    //handle int to char conversions
    for (unsigned int i = 0; i < strToReturn.size(); i++) {
        if (strToReturn.at(i) == '0' || strToReturn.at(i) == '3') {
            if (checkLayerLine(strToReturn, i)) {
                strToReturn.at(i) = '_';
            }
        }
        if (strToReturn.at(i) == '1') {
            if (checkLayerLine(strToReturn, i)) {
                strToReturn.at(i) = 'X';
            }
        }
        if (strToReturn.at(i) == '2') {
            if (checkLayerLine(strToReturn, i)) {
                strToReturn.at(i) = 'E';
            }
        }
        if (strToReturn.at(i) == '4') {
            if (checkLayerLine(strToReturn, i)) {
                strToReturn.at(i) = 'L';
            }
        }
        if (strToReturn.at(i) == '5') {
            if (checkLayerLine(strToReturn, i)) {
                strToReturn.at(i) = 'R';
            }
        }
        if (strToReturn.at(i) == '6') {
            if (checkLayerLine(strToReturn, i)) {
                strToReturn.at(i) = 'U';
            }
        }
        if (strToReturn.at(i) == '7') {
            if (checkLayerLine(strToReturn, i)) {
                strToReturn.at(i) = 'D';
            }
        }
        if (strToReturn.at(i) == '8') {
            if (checkLayerLine(strToReturn, i)) {
                strToReturn.at(i) = 'O';
            }
        }
        if (strToReturn.at(i) == '9') {
            if (checkLayerLine(strToReturn, i)) {
                strToReturn.at(i) = 'I';
            }
        }
    }
    return strToReturn;
}

//Constructor for the maze
Maze::Maze(int height, int width, int layers) {
    mazeHeight = height;
    mazeWidth = width;
    mazeLayers = layers;
    myMaze = new int** [mazeHeight];
    for (int i = 0; i < height; ++i) {
        myMaze[i] = new int* [mazeWidth];
        for (int j = 0; j < width; j++) {
            myMaze[i][j] = new int [mazeLayers];
        }
    }
}
