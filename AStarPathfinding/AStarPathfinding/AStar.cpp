#pragma once
#include "AStar.h"
#include <iostream>

AStar::AStar(Grid& maze) : maze(maze) {}


std::vector<const Cell*> AStar::FindPath(int sx, int sy, int gx, int gy) {
	// Set Start and goal
	const Cell* start = maze.TryGetCell(sx, sy);
	const Cell* goal = maze.TryGetCell(gx, gy);
	

	// Edge Cases
	if (!start || !goal) return {};                     // out of bounds
	if (start->value < 0 || goal->value < 0) return {}; // Blocked start/goal
	
	struct OpenNode {
		const Cell* cell;
		int f;
		int g;

		// Reverse comparator for std::priority_queue (min-heap behavior)
		bool operator<(const OpenNode& other) const {
			if (f != other.f) return f > other.f;
			return g > other.g;
		}
	};

	std::priority_queue<OpenNode> frontier;

	// Mpas keyed by cell pointer (safe because grid pointers are stable
	std::unordered_map<const Cell*, int> gScore; // Best known cost from start
	std::unordered_map<const Cell*, int> fScore; // g + h
	std::unordered_map<const Cell*, const Cell*> cameFrom; // Parent Link

	// Seed 
	cameFrom[start] = nullptr;
	
	// Lambda function for Manhattan 
	auto manhattan = [&](const Cell* a, const Cell* b) {
		return std::abs(a->x - b->x) + std::abs(a->y - b->y);
	};

	// Setting up for the Priority Queue loop
	gScore[start] = 0;
	fScore[start] = manhattan(start, goal);
	frontier.push({ start, fScore[start], gScore[start]});
	
	// Main Loop
	while (!frontier.empty()) {
		OpenNode current = frontier.top();
		frontier.pop();

		//Stale entry? (We pushed a better g later)
		auto itg = gScore.find(current.cell);
		if (itg == gScore.end() || current.g != itg->second) {
			continue;
		}
		
		// Found Goal
		if (current.cell == goal) {
			// Reconstruct Path
			return ReconstructPath(cameFrom, start, goal);
		}
		
		// No Early Finishes
		// Explore neighbors
		const Cell* nb[4];
		int ncount = GetNeighbors(current.cell->x, current.cell->y, nb);
		for (int i = 0; i < ncount; ++i) {
			const Cell* neighbor = nb[i];
			
			// Null Case
			if (!neighbor) continue;

			// Blocked/Obstacle
			if (neighbor->value < 0) continue;

			// cost to step into neighbor
			int step = neighbor->value; // Value is traversal cost
			int tentativeG = current.g + step;

			auto itN = gScore.find(neighbor);
			// Either we've never visited this cell before || This new path is cheaper than earlier recorded
			if (itN == gScore.end() || tentativeG < itN->second) {
				// Better Path Found
				cameFrom[neighbor] = current.cell;          // Record the Breadcrumb
				gScore[neighbor] = tentativeG;              // Updates g records
				int h = manhattan(neighbor, goal);          // Finds h
				int f = tentativeG + h;                     // Finds f
				fScore[neighbor] = f;                       // Updates f records
				frontier.push({ neighbor, f, tentativeG }); // Pushes this new options onto the Queue
			}
		}
	}

	// No Path
	return {};
}

// Fill a small buffer with up to 4 walkable neighbors. Returns count.
int AStar::GetNeighbors(int x, int y, const Cell* out[4]) const {
	int count = 0;
	static const int dx[4] = { -1, 1, 0, 0 };
	static const int dy[4] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; ++i) {
		const Cell* c = maze.TryGetCell(x + dx[i], y + dy[i]);
		if (c && c->value >= 0) { // value < 0 means blocked
			out[count++] = c;
		}
	}
	return count;
}

std::vector<const Cell*> AStar::ReconstructPath(
	const std::unordered_map<const Cell*, const Cell*>& cameFrom,
	const Cell* start,
	const Cell* goal)
{
	std::vector<const Cell*> path;
	const Cell* cur = goal;
	while (cur) {
		path.push_back(cur);

		// Finished Reconstruction
		if (cur == start) break;
		
		auto it = cameFrom.find(cur);
		if (it == cameFrom.end()) break; // safety
		
		cur = it->second;
	}
	std::reverse(path.begin(), path.end());
	return path;
}
