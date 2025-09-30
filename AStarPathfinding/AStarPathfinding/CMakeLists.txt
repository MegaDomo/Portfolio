cmake_minimum_required(VERSION 3.16)
project(AStarPathfinding LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Files (list explicitly; safer than GLOB for portfolios)
add_executable(AStarPathfinding
	main.cpp
	AStar.cpp     
	AStar.h
	Grid.cpp      
	Grid.h
	Cell.cpp      
	Cell.h
 	MazeMaker.cpp 
	MazeMaker.h
	Utility.cpp   
	Utility.h
)
