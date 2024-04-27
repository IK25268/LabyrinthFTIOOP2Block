#include <cmath>
#include <iostream>
#include <fstream>
#include "Labyrinth.hpp"

Labyrinth::Labyrinth()
{
	exit = 0;
	hero = 0;
	cols = 0;
	rows = 0;
}

Labyrinth::Labyrinth(std::map<unsigned int, std::pair<int, char>> cells)
{
	cells = cells;
	exit = 0;
	hero = 0;
	cols = 0;
	rows = 0;
}

Labyrinth::~Labyrinth(){}

void Labyrinth::PrintMapType()
{
	for (unsigned int y = 0; y < (cells.size() / cols); y++)
	{
		for (unsigned int x = 0; x < cols; x++)
		{
			std::cout << cells[y * cols + x].second << ' ';
		}
		std::cout << std::endl;
	}
}

void Labyrinth::PrintMapLevel()
{
	for (unsigned int y = 0; y < (cells.size() / cols); y++)
	{
		for (unsigned int x = 0; x < cols; x++)
		{
			std::cout << cells[y * cols + x].first << ' ';
		}
		std::cout << std::endl;
	}
}

void Labyrinth::PrintCells()
{
	unsigned int size = cols * rows;
	std::map<unsigned int, std::pair<int, char>>::iterator iter = cells.begin();
	for (iter; iter != cells.end(); iter++)
	{
		std::cout << iter->second.second;
		if ((iter->first + 1) % cols == 0)
		{
			if ((iter->first + 1) != size)
			{
				std::cout << std::endl;
			}
		}
		else
		{
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}

void Labyrinth::PrintCellsLevel()
{
	unsigned int size = cols * rows;
	std::map<unsigned int, std::pair<int, char>>::iterator iter = cells.begin();
	for (iter; iter != cells.end(); iter++)
	{
		std::cout << iter->second.first;
		if ((iter->first + 1) % cols == 0)
		{
			if ((iter->first + 1) != size)
			{
				std::cout << std::endl;
			}
		}
		else
		{
			std::cout << " ";
		}
	}
	std::cout<<std::endl;
}