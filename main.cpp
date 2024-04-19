#include <iostream>
#include "WaveAlg.hpp"
using namespace std;

int main()
{
	Labyrinth labyrinth("input.txt");
	labyrinth.ReadFile();
	labyrinth.CalcWave();
	labyrinth.DrawRoute();
	labyrinth.PrintCells();
	labyrinth.PrintCellsLevel();
	labyrinth.WriteFile();
	return 0;
}