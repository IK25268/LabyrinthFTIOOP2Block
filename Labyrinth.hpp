#pragma once
#ifndef __Labyrinth_hpp
#define __Labyrinth_hpp
#include <string>
#include <map>
#include <queue>

class Labyrinth final {
private:
	std::map<unsigned int, std::pair<int, char>> cells;
	unsigned int cols;
	unsigned int rows;
	unsigned int hero;
	unsigned int exit;
public:
	std::map<unsigned int, std::pair<int, char>>& GetCells();
	unsigned int& GetCols();
	unsigned int& GetRows();
	unsigned int& GetHero();
	unsigned int& GetExit();
	Labyrinth();
	Labyrinth(std::map<unsigned int, std::pair<int, char>> cells);
	~Labyrinth();
	void PrintMapType();
	void PrintMapLevel();
	void PrintCells();
	void PrintCellsLevel();
};

#endif