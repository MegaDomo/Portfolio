#pragma once
#include "Cell.h"
#include <vector>

class Grid {
public: 
	// Constructor
	Grid(int width, int height);

	// Functions
	bool InBounds(int x, int y) const;

	// Getters
	Cell& GetCell(int x, int y);
	const Cell& GetCell(int x, int y) const;
	const Cell* TryGetCell(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;

	// Setters
	void SetCellWeight(int x, int y, int weight);
	
	

private:
	// Fields
	int width;
	int height;
	std::vector<Cell> cells;

	inline size_t index(int x, int y) const;

	
};
