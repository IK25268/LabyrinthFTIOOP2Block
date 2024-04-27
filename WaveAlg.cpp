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
	labyrinth.cells[labyrinth.hero].first = 0;
	waveCells.push(labyrinth.hero);
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
			unsigned int nextCell = (cell + y * (labyrinth.cols)) + x;
			if ((labyrinth.cells[nextCell].first == -1) && (labyrinth.cells[nextCell].second != '1') && (!((y == 0) && (x == 0))))
			{
				labyrinth.cells[nextCell].first = labyrinth.cells[cell].first + 1;
				waveCells.push(nextCell);
				if (labyrinth.cells[nextCell].second == '3')
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
	unsigned int cell = labyrinth.exit;
	int level = labyrinth.cells[cell].first;
	while (level > 0)
	{
		char iter = 0;
		unsigned int nextCell = 0;
		for (iter = 0; level == labyrinth.cells[cell].first; iter++)
		{
			nextCell = ((cell + j[iter] * (labyrinth.cols)) + i[iter]);
			if (labyrinth.cells[nextCell].first == (level - 1))
			{
				level--;
				if (labyrinth.cells[cell].second == '0') labyrinth.cells[cell].second = '*';
			}
		}
		cell = nextCell;
	}
}

int WaveAlg::CalcPos(unsigned int x, unsigned int y)
{
	return y * labyrinth.cols + x;
}