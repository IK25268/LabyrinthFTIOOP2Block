#include "pch.h"
#include "../LabyrinthFTIOOP2Block/Labyrinth.hpp"
#include "../LabyrinthFTIOOP2Block/Labyrinth.cpp"
#include "../LabyrinthFTIOOP2Block/RWFile.hpp"
#include "../LabyrinthFTIOOP2Block/RWFile.cpp"
#include "../LabyrinthFTIOOP2Block/WaveAlg.hpp"
#include "../LabyrinthFTIOOP2Block/WaveAlg.cpp"

TEST(Labyrinth, TestRead) {
	std::array<char, 70> mapRead = 
	{
		'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
		'1', '2', '0', '1', '0', '0', '0', '0', '0', '1',
		'1', '0', '0', '1', '0', '0' ,'1' ,'0' ,'0' ,'1',
		'1' ,'0' ,'0', '1', '0', '0' ,'1' ,'0' ,'0' ,'3',
		'1', '0', '0' ,'0' ,'0' ,'0' ,'1', '0', '0', '1',
		'1', '0', '0' ,'0' ,'0', '0' ,'0' ,'0', '0' ,'1',
		'1' ,'1' ,'1', '1' ,'1' ,'1' ,'1' ,'1' ,'1' ,'1'
	};
	Labyrinth labyrinth(RWFile::ReadFile("input.txt"));
	ASSERT_EQ(10, labyrinth.GetCols());
	ASSERT_EQ(7, labyrinth.GetRows());
	ASSERT_EQ(11, labyrinth.GetHero());
	ASSERT_EQ(39, labyrinth.GetExit());
	for (int iter = 0; iter < labyrinth.GetCells().size(); iter++)
	{
		ASSERT_EQ((int)mapRead[iter], (int)(labyrinth.GetCells()[iter].second));
	}
}

TEST(Labyrinth, TestDraw) {
	std::array<const char, 70> mapCalc =
	{
		'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
		'1', '2', '0', '1', '0', '0', '*', '0', '0', '1',
		'1', '0', '*', '1', '0', '*' ,'1' ,'*' ,'0' ,'1',
		'1' ,'0' ,'*', '1', '*', '0' ,'1' ,'0' ,'*' ,'3',
		'1', '0', '0' ,'*' ,'0' ,'0' ,'1', '0', '0', '1',
		'1', '0', '0' ,'0' ,'0', '0' ,'0' ,'0', '0' ,'1',
		'1' ,'1' ,'1', '1' ,'1' ,'1' ,'1' ,'1' ,'1' ,'1'
	};
	Labyrinth labyrinth(RWFile::ReadFile("input.txt"));
	WaveAlg waveAlg;
	waveAlg.CalcLabyrinth(labyrinth);
	for (int iter = 0; iter < labyrinth.GetCells().size(); iter++)
	{
		ASSERT_EQ((int)mapCalc[iter], (int)(labyrinth.GetCells()[iter].second));
	}
}