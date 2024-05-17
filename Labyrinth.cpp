#include <cmath>
#include <iostream>
#include <fstream>
#include "Labyrinth.hpp"

std::map<unsigned int, std::pair<int, char>>& Labyrinth::GetCells()
{
	return cells;
}

unsigned int& Labyrinth::GetCols()
{
	return cols;
}

unsigned int& Labyrinth::GetRows()
{
	return rows;
}

unsigned int& Labyrinth::GetHero()
{
	return hero;
}

unsigned int& Labyrinth::GetExit()
{
	return exit;
}