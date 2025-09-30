#include "Grid.h"
#include "MazeMaker.h"
#include "AStar.h"
#include <iostream>
#include <string>

void PrintMaze(Grid& grid, std::vector<const Cell*>& path, int& sx, int& sy, int& gx, int& gy);

int main()
{
    // Initialization
    Grid g(20, 20);
    MazeMaker mazer;
    AStar astar(g);

    // Creating Maze in Grid
    mazer.MakeMaze(g);
    int sx = 1;
    int sy = 1;
    int gx = 10;
    int gy = 10;
    mazer.GetRandomCoords(g, sx, sy);
    mazer.GetRandomCoords(g, gx, gy);
    g.SetCellWeight(sx, sy, 1);
    g.SetCellWeight(gx, gy, 1);

    // Pathfinding
    std::vector<const Cell*> path = astar.FindPath(sx, sy, gx, gy);

    
    PrintMaze(g, path, sx, sy, gx, gy);
}

// For the purposes of clean visuals this will change the values in the Maze
void PrintMaze(Grid& grid, std::vector<const Cell*>& path, int& sx, int& sy, int& gx, int& gy) {
    //std::cout << "Grid Stats\n";

    // No Path
    if (path.size() <= 0) std::cout << "=======XX=No Path=XX========\n";
    else std::cout << "========!!Path Found!!========\n";
    
    // Cells along path are changed to 0
    for (int i = 0; i < path.size(); i++) 
        grid.SetCellWeight(path[i]->x, path[i]->y, 0);

    // Set Start and Goal
    grid.SetCellWeight(sx, sy, -2);
    grid.SetCellWeight(gx, gy, -3);


    int w = grid.GetWidth();
    int h = grid.GetHeight();

    // Loop through and Print final configurations
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            std::string cellValue;

            if (grid.GetCell(x, y).value == 1)
                cellValue = ".";
            if (grid.GetCell(x, y).value == -1)
                cellValue = "X";
            if (grid.GetCell(x, y).value == 0)
                cellValue = "-";
            if (grid.GetCell(x, y).value == -2)
                cellValue = "S";
            if (grid.GetCell(x, y).value == -3)
                cellValue = "E";
                        
            std::cout << cellValue + " ";
        }
        std::cout << "\n";
    }
}


