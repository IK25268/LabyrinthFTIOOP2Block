#pragma once
#ifndef __Labyrinth_hpp
#define __Labyrinth_hpp
#include <string>
#include <map>
#include <queue>

class Labyrinth {
public:
	std::map<unsigned int, std::pair<int, char>> cells;
	unsigned int cols;
	unsigned int rows;
	unsigned int hero;
	unsigned int exit;
	Labyrinth();
	Labyrinth(std::map<unsigned int, std::pair<int, char>> cells);
	~Labyrinth();
	void PrintMapType();
	void PrintMapLevel();
	void PrintCells();
	void PrintCellsLevel();
};

#endif