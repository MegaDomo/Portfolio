#pragma once
#include "MazeMaker.h"
#include "Grid.h"
#include "Cell.h"
#include "Utility.h"
#include <iostream>

MazeMaker::MazeMaker() {}

void MazeMaker::MakeMaze(Grid& grid) {

	// Obstacle Placement
	for (int x = 0; x < grid.GetWidth(); x++)
		for (int y = 0; y < grid.GetHeight(); y++) {
			if (Utility::RandRange(0, 9) < 3)
				grid.SetCellWeight(x, y, -1);
		}
}

void MazeMaker::GetRandomCoords(Grid& grid, int& outX, int& outY) {
	outX = Utility::RandRange(0, grid.GetWidth() - 1);
	outY = Utility::RandRange(0, grid.GetHeight() - 1);
}