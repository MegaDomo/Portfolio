#pragma once
#include "Grid.h"
#include "Cell.h"
#include <vector>
Grid::Grid(int width, int height) : width(width), height(height), cells(static_cast<size_t>(width * height)){
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++) {
			Cell& c = cells[index(x, y)];
			c.x = x; c.y = y; c.value = 1;
		}
}

bool Grid::InBounds(int x, int y) const { return x >= 0 && x < width && y >= 0 && y < height; }
size_t Grid::index(int x, int y) const {
	return static_cast<size_t>(y) * static_cast<size_t>(width)
		+ static_cast<size_t>(x);
}

// Must Exist (reference)
Cell&       Grid::GetCell(int x, int y)	      { return cells[index(x, y)]; }
const Cell& Grid::GetCell(int x, int y) const { return cells[index(x, y)]; }

// Maybe Exist (pointer)
const Cell* Grid::TryGetCell(int x, int y) const { return InBounds(x, y) ? &cells[index(x, y)] : nullptr; }

// Other Getters
int Grid::GetWidth() const { return width; }
int Grid::GetHeight() const { return height; }

// Setters
void Grid::SetCellWeight(int x, int y, int weight) { if (InBounds(x, y)) cells[index(x, y)].value = weight; }

