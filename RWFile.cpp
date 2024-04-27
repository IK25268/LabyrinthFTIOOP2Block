#include <cmath>
#include <iostream>
#include <fstream>
#include "RWFile.hpp"

RWFile::RWFile(){}

RWFile::~RWFile(){}

void RWFile::WriteFile(Labyrinth labyrinth, const char* outputName)
{
	std::ofstream out;         
	out.open(outputName);      
	if (out.is_open())
	{
		char digit = 0;
		for (size_t j = 0; j < labyrinth.GetRows(); j++)
		{
			for (size_t i = 0; i < labyrinth.GetCols(); i++)
			{
				out << labyrinth.GetCells()[j* labyrinth.GetCols()+i].second;
				if (i < (labyrinth.GetCols()-1)) out << ' ';
			}
			if (j < (labyrinth.GetRows() - 1)) out << std::endl;
		}
	}
	out.close();
}

Labyrinth RWFile::ReadFile(const char* inputName)
{
	Labyrinth labyrinth;
	std::string line;
	std::ifstream in(inputName); 
	if (in.is_open())
	{
		unsigned int pos = 0;
		std::getline(in, line);
		labyrinth.GetCols() = (line.size() + 1) / 2;
		for (int i = 0; i < labyrinth.GetCols(); i++)
		{
			labyrinth.GetCells().insert({ pos, {0, (char)line[2 * i]} });
			pos++;
		}
		labyrinth.GetRows()++;
		while (std::getline(in, line))
		{
			for (int i = 0; i < labyrinth.GetCols(); i++)
			{
				if ((char)line[2 * i] == '2') labyrinth.GetHero() = pos;
				if ((char)line[2 * i] == '3') labyrinth.GetExit() = pos;
				labyrinth.GetCells().insert({ pos, {-1, (char)line[2 * i]} });
				pos++;
			}
			labyrinth.GetRows()++;
		}
	}
	in.close();
	return labyrinth;
}