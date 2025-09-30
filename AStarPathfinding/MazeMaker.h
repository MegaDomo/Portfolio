#pragma once
#include "Grid.h"

class MazeMaker {
public:
	// Constructor
	MazeMaker();

	// Fucntions
	void MakeMaze(Grid& grid);
	void GetRandomCoords(Grid& grid, int& outX, int& outY);
};
