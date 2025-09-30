#pragma once
#include "Utility.h"
#include <random>

int Utility::RandRange(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}