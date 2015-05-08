#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

#define coordinate(x,y) y*gridWidth+x

using namespace std;

typedef enum states { Dead = 0, Alive = 1 };
typedef vector<int> Grid;

const int gridWidth  = 20;
const int gridHeight = 20;
const int waitTimeMS = 1250;
const int newlinesToClear = 50;

Grid grid (gridWidth * gridHeight);

//TODO make this use buckets
inline void InitRNG()
{
	srand(time(NULL));
}

//TODO generalize this so it can be customized
inline int GetStartValue()
{
	return rand() % 2;
}

Grid InitGrid(int length, bool blank)
{
	if (blank)
	{
		Grid g(length, 0);
		return g;
	}
	else
	{
		Grid g(length);
		//Init the values in the grid
		for (int i = 0; i < grid.size(); i++)
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
					int index = coordinate(i + di, j + dj);
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
	for (int i = 0; i < grid.size(); i++)
	{
		cout << (grid[i] == Alive ? 'O' : ' ') << ' ';
		if (i % gridWidth == 0)
			cout << endl;
	}
}

void RunSimulation()
{
	//This should run forever, let the person running decide when to close the window with the GUI
	while (true)
	{
		ClearPreviousBoard();
		UpdateBoard();
		DrawBoard();
		Sleep(waitTimeMS);
	}
}

int main()
{
	InitRNG();
	grid = InitGrid(gridWidth * gridHeight, false);
	RunSimulation();
}
