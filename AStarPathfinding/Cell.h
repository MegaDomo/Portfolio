#pragma once

// Functions as a Node
struct Cell {
	int x;
	int y;
	int value = 1;

	int g = 0; // "Cost So Far" - the Distance from this cell back to the start
	int h = 0; // "How Far To Go" - the Distance from this cell to the end
	int f = 0; // "Total Effective Cost" - g + h, a value to determinet he best choice.


	// Constructor
	Cell(int x, int y, int value);
	Cell();
};