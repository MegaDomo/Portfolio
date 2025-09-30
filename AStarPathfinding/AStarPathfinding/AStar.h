#pragma once
#include <vector>
#include <array>
#include <queue>
#include <unordered_map>
#include <limits>
#include <optional>
#include <cmath>
#include "Grid.h"
#include "Path.h"

class AStar {
public:
	// Constructor
	AStar(Grid& maze);

	// Methods
	std::vector<const Cell*> FindPath(int sx, int sy, int gx, int gy);
	int GetNeighbors(int x, int y, const Cell* out[4]) const;

private:
	// Fields
	const Grid& maze;

	// Private Methods
	std::vector<const Cell*> ReconstructPath(
		const std::unordered_map<const Cell*, const Cell*>& cameFrom,
		const Cell* start,
		const Cell* goal);
};

