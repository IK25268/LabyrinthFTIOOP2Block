#pragma once
#ifndef __WaveAlg_hpp
#define __WaveAlg_hpp
#include <string>
#include <map>
#include <queue>
#include <array>
#include "Labyrinth.hpp"

class WaveAlg {

private:
	Labyrinth& labyrinth;
	std::queue<unsigned int> waveCells;
	std::array<int, 8> i = { -1, 0, 0, 1, -1, -1, 1, 1 };
	std::array<int, 8> j = { 0, -1, 1, 0, -1, 1, -1, 1 };
public:
	WaveAlg(Labyrinth& _labyrinth);
	~WaveAlg();
	void CalcLabyrinth();
	void CalcWave();
	void CalcCell();
	void DrawRoute();
	int CalcPos(unsigned int x, unsigned int y);
};

#endif