#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef enum states { Dead = 0, Alive = 1 };
typedef vector<int> Grid;

const int gridWidth  = 20;
const int gridHeight = 20;
const int waitTimeMS = 1250;
const int newlinesToClear = 50;

Grid grid (gridWidth * gridHeight);

#define USE_BUCKETS 1
#if USE_BUCKETS
#include "BucketRNG.h"
typedef BucketRNG* RNG;

float f(float x)
{
	return x; //this represents the function y = x
}

inline void InitRNG()
{
	//Create the buckets
}

int GetStartValue()
{
	return Alive;
}
#else
inline void InitRNG()
{
	srand(time(NULL));
}

inline int GetStartValue()
{
	return rand() % 2;
}
#endif

Grid InitGrid(int length, bool blank)
{
	if (blank)
	{
		Grid g(length, Dead);
		return g;
	}
	else
	{
		Grid g(length);
		//Init the values in the grid
		for (unsigned i = 0; i < grid.size(); i++)
		{
			g[i] = GetStartValue();
		}
		return g;
	}
}

void ClearPreviousBoard()
{
	for (int i = 0; i < newlinesToClear; i++)
		cout << endl;
}

int coordinate(int x, int y)
{
	return x * gridWidth + y;
}

void UpdateBoard()
{
	//This will be the new board written into as we parse the old one
	Grid newGrid = InitGrid(grid.size(), true);
	//The first two loops do the main pass over the array
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			//These next two loops check the 8 neighbors
			int neighbors = 0;
			for (int di = -1; di <= 1; di++)
			{
				for (int dj = -1; dj <= 1; dj++)
				{
					int index;
					//Make sure the index isn't out of bounds first.  Assume it is Dead if so, so just skip the checks and don't increment neighbors
					if (i + di < 0 || i + di >= gridWidth * gridHeight || j + dj < 0 || j + dj >= gridWidth * gridHeight)
						goto UpdateBoard_SkipNeighborCheck;
					else
						index = coordinate(i + di, j + dj);
					//Make one final check to see if it is necessary to increment neighbors, and do it if so
					if (index < 0 || index >= gridWidth + gridHeight)
						goto UpdateBoard_SkipNeighborCheck;
					if (grid[index] == Alive)
						neighbors++;
UpdateBoard_SkipNeighborCheck:; //The goto jumps to here so that the loop still increments
				}
			}
			//These decide the value of the cell based on the number of living neighbors
			if (grid[coordinate(i, j)] == Alive) //Handle if the cell was initially alive
			{
				if (neighbors < 2 || neighbors > 3)
					newGrid[coordinate(i, j)] = Dead;
				else
					newGrid[coordinate(i, j)] = Alive;
			}
			else //Handle if the cell was initially dead
			{
				if (neighbors == 3)
					newGrid[coordinate(i, j)] = Alive;
				else
					newGrid[coordinate(i, j)] = Dead;
			}
		}
	}
	grid.swap(newGrid);
}

void DrawBoard()
{
	for (unsigned i = 0; i < grid.size(); i++)
	{
		cout << (grid[i] == Alive ? 'O' : ' ') << ' ';
		if ( (i + 1) % gridWidth == 0)
			cout << endl;
	}
}

void RunSimulation()
{
	//This should run forever, let the person running decide when to close the window with the GUI
	while (true)
	{
		ClearPreviousBoard();
		DrawBoard();
		UpdateBoard();
		Sleep(waitTimeMS);
	}
}

void debug()
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			cout << i << " " << j << ": " << coordinate(i, j) << endl;
		}
	}
}

int main()
{
	debug();
	InitRNG();
	grid = InitGrid(gridWidth * gridHeight, false);
	RunSimulation();
}

//There seems to be a bug related to indexing.  When you index off the right edge, it checks the left item in the next row, 
//and when you index off the left edge, it indexes the rightmost element one row up.
