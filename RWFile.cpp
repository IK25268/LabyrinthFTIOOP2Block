#include <cmath>
#include <iostream>
#include <fstream>
#include "RWFile.hpp"

RWFile::RWFile(){}

RWFile::~RWFile(){}

void RWFile::WriteFile(Labyrinth labyrinth, const char* outputName)
{
	FILE* outputFile = NULL;
	fopen_s(&outputFile, "output.txt", "w");
	if (outputFile != NULL)
	{
		unsigned int size = labyrinth.cols * labyrinth.rows;
		std::map<unsigned int, std::pair<int, char>>::iterator iter = labyrinth.cells.begin();
		for (iter; iter != labyrinth.cells.end(); iter++)
		{
			fwrite(&(iter->second.second), sizeof(char), 1, outputFile);
			if ((iter->first + 1) % labyrinth.cols == 0)
			{
				if ((iter->first + 1) != size)
				{
					fputc('\n', outputFile);
				}
			}
			else
			{
				fputc(' ', outputFile);
			}
		}
	}
	if (outputFile != NULL)fclose(outputFile);
}

Labyrinth RWFile::ReadFile(const char* inputName)
{
	Labyrinth labyrinth;
	std::string line;
	std::ifstream in(inputName); // окрываем файл для чтения
	if (in.is_open())
	{
		unsigned int pos = 0;
		std::getline(in, line);
		labyrinth.cols = (line.size() + 1) / 2;
		for (int i = 0; i < labyrinth.cols; i++)
		{
			labyrinth.cells.insert({ pos, {0, (char)line[2 * i]} });
			pos++;
		}
		labyrinth.rows++;
		while (std::getline(in, line))
		{
			for (int i = 0; i < labyrinth.cols; i++)
			{
				if ((char)line[2 * i] == '2') labyrinth.hero = pos;
				if ((char)line[2 * i] == '3') labyrinth.exit = pos;
				labyrinth.cells.insert({ pos, {-1, (char)line[2 * i]} });
				pos++;
			}
			labyrinth.rows++;
		}
	}
	in.close();
	return labyrinth;
}