#include <iostream>
#include "WaveAlg.hpp"
#include "Labyrinth.hpp"
#include "RWFile.hpp"

int main()
{
	RWFile rwFile;
	Labyrinth labyrinth(rwFile.ReadFile("input.txt"));
	WaveAlg waveAlg(labyrinth);
	waveAlg.CalcLabyrinth();
	labyrinth.PrintCells();
	rwFile.WriteFile(labyrinth, "output.txt");
	return 0;
}