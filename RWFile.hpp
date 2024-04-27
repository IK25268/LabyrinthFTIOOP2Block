#pragma once
#ifndef __RWFile_hpp
#define __RWFile_hpp
#include <string>
#include <map>
#include <queue>
#include "Labyrinth.hpp"
class RWFile
{
public:
	RWFile();
	~RWFile();
	void WriteFile(Labyrinth labyrinth, const char* outputName);
	Labyrinth ReadFile(const char* inputName);
};

#endif
