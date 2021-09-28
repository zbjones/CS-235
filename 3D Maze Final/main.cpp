#include <fstream>
#include <ostream>
#include "Maze.h"

using namespace std;

int main(int argc, const char * argv[]) {
    //Open File Stream
    ifstream in(argv[1]);
    ofstream out;
    out.open(argv[2]);

    int mazeHeight = 0;
    int mazeWidth = 0;
    int mazeLayers = 0;
    in >> mazeHeight >> mazeWidth >> mazeLayers;
    Maze userMaze = Maze(mazeHeight, mazeWidth, mazeLayers);

    for (int i = 0; i < mazeLayers; i++ ) {
        for (int j = 0; j < mazeHeight; j++) {
            for (int k = 0; k < mazeWidth; k++) {
                int tempValue;
                in >> tempValue;
                userMaze.setValue(j, k, i, tempValue);
            }
        }
    }
    out << "Solve Maze: " << userMaze.toString() << endl;
    if (userMaze.find_maze_path()) {
        out << endl << "Solution:";
        out << userMaze.toString();
    }
    else {
        out << endl << "No Solution Exists!";
    }

    in.close();
    out.close();
    return 0;
}
