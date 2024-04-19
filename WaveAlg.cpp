#include <cmath>
#include <iostream>
#include <stdio.h>
#include "WaveAlg.hpp"
using namespace std;

Labyrinth::Labyrinth()
{
	this->inputFile = "";
	this->exit = 0;
	this->hero = 0;
	this->cols = 0;
	this->rows = 0;
}

Labyrinth::Labyrinth(const char* _inputFile)
{
	this->inputFile = _inputFile;
	this->exit = 0;
	this->hero = 0;
	this->cols = 0;
	this->rows = 0;
}

Labyrinth::~Labyrinth()
{

}

void Labyrinth::CalcWave()
{
	this->cells[this->hero].first = 0;
	this->waveCells.push(this->hero);
	while (this->waveCells.size() != 0)
	{
		this->CalcCell();
	}
}

void Labyrinth::CalcCell()
{
	unsigned int cell = this->waveCells.front();
	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			unsigned int nextCell = (cell + y * (this->cols) ) + x;
			if ((this->cells[nextCell].first == -1) && (this->cells[nextCell].second != '1') && (!((y==0)&&(x==0))))
			{
				this->cells[nextCell].first = this->cells[cell].first + 1;
				this->waveCells.push(nextCell);
				if (this->cells[nextCell].second == '3')
				{
					while (this->waveCells.size() != 0)
					{
						this->waveCells.pop();
					}
				}
			}
		}
	}
	if (this->waveCells.size() != 0) this->waveCells.pop();
}

void Labyrinth::DrawRoute()
{
	int i[8] = { -1, 0, 0, 1, -1, -1, 1, 1 };
	int j[8] = { 0, -1, 1, 0, -1, 1, -1, 1 };
	unsigned int cell = this->exit;
	int level = this->cells[cell].first;
	while(level>0)
	{
		char iter = 0;
		unsigned int nextCell = 0;
		for (iter = 0; level == this->cells[cell].first; iter++)
		{
			nextCell = ((cell + j[iter] * (this->cols)) + i[iter]);
			if (this->cells[nextCell].first == (level - 1))
			{
				level--;
				if (this->cells[cell].second == '0') this->cells[cell].second = '*';
			}
		}
		cell = nextCell;
	}
}

void Labyrinth::PrintCells()
{
	unsigned int size = this->cols * this->rows;
	std::map<unsigned int, std::pair<int, char>>::iterator iter = this->cells.begin();
	for (iter; iter != this->cells.end(); iter++)
	{
		printf("%c", iter->second.second);
		if ((iter->first + 1) % this->cols == 0)
		{
			if ((iter->first + 1) != size)
			{
				printf("\n");
			}
		}
		else
		{
			printf(" ");
		}
	}
	printf("\n");
}

void Labyrinth::PrintCellsLevel()
{
	unsigned int size = this->cols * this->rows;
	std::map<unsigned int, std::pair<int, char>>::iterator iter = this->cells.begin();
	for (iter; iter != this->cells.end(); iter++)
	{
		printf("%d", iter->second.first);
		if ((iter->first + 1) % this->cols == 0)
		{
			if ((iter->first + 1) != size)
			{
				printf("\n");
			}
		}
		else
		{
			printf(" ");
		}
	}
	printf("\n");
}

void Labyrinth::WriteFile()
{
	FILE* outputFile = NULL;
	fopen_s(&outputFile, "output.txt", "w");
	if (outputFile != NULL)
	{
		unsigned int size = this->cols * this->rows;
		std::map<unsigned int, std::pair<int, char>>::iterator iter = this->cells.begin();
		for (iter; iter != this->cells.end(); iter++)
		{
			fwrite(&(iter->second.second), sizeof(char), 1, outputFile);
			if ((iter->first + 1) % this->cols == 0)
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
	if (outputFile!=NULL)fclose(outputFile);
}

void Labyrinth::ReadFile()
{
	FILE* inputFile = NULL;
	fopen_s(&inputFile, this->inputFile, "r");
	if (inputFile != NULL)
	{
		char type = ' ';
		unsigned int i = 0;
		unsigned int j = 0;
		char flag = 0;
		int phase = 1;
		while (phase == 1) /*считывание ширины по верхней границе*/
		{
			fread(&type, sizeof(char), 1, inputFile);
			if (feof(inputFile))
			{
				phase = 0;
				break;
			}
			if (type == '\n')
			{
				this->cols = i;
				this->rows = 1;
				i = 0;
				phase = 2;
				if (feof(inputFile))
				{
					phase = 0;
					break;
				}
			}
			else
			{
				if (flag == 0)
				{
					if ((type != '1')&&(type != '3'))
					{
						phase = 0;
						break;
					}
					else
					{
						unsigned int pos = CalcPos(i, 0);
						this->cells.insert({ pos, {-1, type} });
						if (type == '3') this->exit = pos;
					}
					flag = 1;
					i++;
				}
				else
				{
					if (type != ' ')
					{
						phase = 0;
						break;
					}
					flag = 0;
				}
			}
		}
		//printf("SizeCells %d SizePoints %d SizeEdges %d\n", SizeCells(map), SizePoints(map), SizeEdges(map));
		while (phase == 2) /*считывание высоты по правой границе*/
		{
			fread(&type, sizeof(char), 1, inputFile);
			if (feof(inputFile))
			{
				phase = 0;
				break;
			}
			else
			{
				fseek(inputFile, -1, SEEK_CUR);
			}
			for (unsigned int j = 0; j < (2 * (this->cols) - 1); j++)
			{
				if (j == (2 * (this->cols) - 2))
				{
					unsigned int pos = CalcPos((this->cols - 1), this->rows);
					
					fread(&type, sizeof(char), 1, inputFile);
					if (type == '3')
					{
						this->cells.insert({ pos, {-1,'3'}});
						this->exit = pos;
					}
					if (type == '1')
					{
						this->cells.insert({ pos, {-1,'1'} });
					}
					fseek(inputFile, -1, SEEK_CUR);
				}
				fseek(inputFile, 1, SEEK_CUR);
				if (feof(inputFile))
				{
					phase = 0;
					break;
				}
			}
			fread(&type, sizeof(char), 1, inputFile);
			if (type == '\n')
			{
				this->rows = this->rows + 1;
			}
			else
			{
				this->rows = this->rows + 1;
				phase = 3;
				fseek(inputFile, 0, SEEK_SET);
				break;
			}
		}
		while (phase == 3) /*проверка левой границы*/
		{
			fread(&type, sizeof(char), 1, inputFile);
			if (i == this->rows)
			{
				phase = 4;
				flag = 0;
				i = 0;
				//printf("SizeCells %d SizePoints %d SizeEdges %d\n", SizeCells(map), SizePoints(map), SizeEdges(map));
				fseek(inputFile, -((int)(2 * (this->cols) - 1)), SEEK_END);
				break;
			}
			else
			{
				if ((type == '1')||(type == '3'))
				{
					unsigned int pos = CalcPos(0, i);
					this->cells.insert({ pos, {-1, type} });
					if (type == '3') this->exit = pos;
					i++;
				}
				else
				{
					phase = 0;
					break;
				}
				fseek(inputFile, (2 * (this->cols)), SEEK_CUR);
			}
		}
		while (phase == 4) /*проверка нижней границы*/
		{
			fread(&type, sizeof(char), 1, inputFile);
			if (feof(inputFile))
			{
				phase = 5;
				j = 1;
				i = 1;
				flag = 1;
				fseek(inputFile, (2 * (this->cols) + 2), SEEK_SET);
				break;
			}
			else
			{
				if (flag == 0)
				{
					if ((type != '1')&&(type != '3'))
					{
						phase = 0;
						break;
					}
					else
					{
						unsigned int pos = CalcPos(i, this->rows - 1);
						this->cells.insert({ pos, {-1, type} });
						if (type == '3') this->exit = pos;
					}
					flag = 1;
					i++;
				}
				else
				{
					if (type != ' ')
					{
						phase = 0;
						break;
					}
					flag = 0;
				}
			}
		}

		while (phase == 5) /*считывание и проверка карты*/
		{
			fread(&type, sizeof(char), 1, inputFile);
			if ((j == this->rows - 2) && (i == this->cols - 1))
			{
				phase = -1;
				break;
			}
			else
			{
				if (i == this->cols)
				{
					i = 1;
					j++;
					fseek(inputFile, 1, SEEK_CUR);
					flag = 1;
				}
				else
				{
					if (flag == 0)
					{
						unsigned int pos = CalcPos(i, j);
						switch (type)
						{
						case '3':
						{
							this->cells.insert({ pos, {-1, '3'} });
							break;
						}
						case '2':
						{
							this->cells.insert({ pos, {-1, '2'} });
							if (type == '2') this->hero = pos;
							break;
						}
						case '1':
						{
							this->cells.insert({ pos, {-1, '1'} });
							break;
						}
						case '0':
						{
							this->cells.insert({ pos, {-1, '0'} });
							break;
						}
						default:
						{
							phase = 0;
							break;
						}
						}
						flag = 1;
						i++;
					}
					else
					{
						if (type != ' ')
						{
							phase = 0;
							break;
						}
						flag = 0;
					}
				}
			}
		}
		if (
			(phase != 0)
			&&
			(
				(this->cols < 3)
				||
				(this->rows < 3)
				)
			)
		{
			this->cells.clear();
		}
		fclose(inputFile);
	}
}

void Labyrinth::PrintMapType()
{
	for (unsigned int y = 0; y < (this->cells.size()/this->cols); y++)
	{
		for (unsigned int x = 0; x < this->cols; x++)
		{
			cout << this->cells[y * this->cols + x].second << ' ';
		}
		cout << endl;
	}
}

void Labyrinth::PrintMapLevel()
{
	for (unsigned int y = 0; y < (this->cells.size() / this->cols); y++)
	{
		for (unsigned int x = 0; x < this->cols; x++)
		{
			cout << this->cells[y * this->cols + x].first << ' ';
		}
		cout << endl;
	}
}

int Labyrinth::CalcPos(unsigned int x, unsigned int y)
{
	return y * this->cols + x;
}