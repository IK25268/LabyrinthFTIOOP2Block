#ifndef __WaveAlg_hpp
#define __WaveAlg_hpp
#include <string>
#include <map>
#include <queue>

class Labyrinth {

private:
	const char* inputFile;
	std::map<unsigned int, std::pair<int, char>> cells;
	std::queue<unsigned int> waveCells;
	unsigned int cols;
	unsigned int rows;
	unsigned int hero;
	unsigned int exit;
	void PrintMapType();
	void PrintMapLevel();
public:
	Labyrinth();
	Labyrinth(const char* _inputFile);
	~Labyrinth();
	void CalcWave();
	void CalcCell();
	void DrawRoute();
	void PrintCells();
	void PrintCellsLevel();
	void WriteFile();
	void ReadFile();
	int CalcPos(unsigned int x, unsigned int y);
};

#endif