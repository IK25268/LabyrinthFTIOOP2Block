#include <cmath>
#include <iostream>
#include <fstream>
#include "WaveAlg.hpp"

WaveAlg::WaveAlg(Labyrinth& _labyrinth):labyrinth(_labyrinth){}

WaveAlg::~WaveAlg(){}

void WaveAlg::CalcLabyrinth()
{
	CalcWave();
	DrawRoute();
}

void WaveAlg::CalcWave()
{
	labyrinth.GetCells()[labyrinth.GetHero()].first = 0;
	waveCells.push(labyrinth.GetHero());
	while (waveCells.size() != 0)
	{
		CalcCell();
	}
}

void WaveAlg::CalcCell()
{
	unsigned int cell = waveCells.front();
	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			unsigned int nextCell = (cell + y * (labyrinth.GetCols())) + x;
			if ((labyrinth.GetCells()[nextCell].first == -1) && (labyrinth.GetCells()[nextCell].second != '1') && (!((y == 0) && (x == 0))))
			{
				labyrinth.GetCells()[nextCell].first = labyrinth.GetCells()[cell].first + 1;
				waveCells.push(nextCell);
				if (labyrinth.GetCells()[nextCell].second == '3')
				{
					while (waveCells.size() != 0)
					{
						waveCells.pop();
					}
				}
			}
		}
	}
	if (waveCells.size() != 0) waveCells.pop();
}

void WaveAlg::DrawRoute()
{
	unsigned int cell = labyrinth.GetExit();
	int level = labyrinth.GetCells()[cell].first;
	while (level > 0)
	{
		char iter = 0;
		unsigned int nextCell = 0;
		for (iter = 0; level == labyrinth.GetCells()[cell].first; iter++)
		{
			nextCell = ((cell + j[iter] * (labyrinth.GetCols())) + i[iter]);
			if (labyrinth.GetCells()[nextCell].first == (level - 1))
			{
				level--;
				if (labyrinth.GetCells()[cell].second == '0') labyrinth.GetCells()[cell].second = '*';
			}
		}
		cell = nextCell;
	}
}

int WaveAlg::CalcPos(unsigned int x, unsigned int y)
{
	return y * labyrinth.GetCols() + x;
}