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

inline Grid InitGrid(int length, bool blank)
{
	Grid g(length);
	//Init the values in the grid
	for (int i = 0; i < grid.size(); i++)
	{
		g[i] = (blank ? 0 : GetStartValue() );
	}
	return g;
}

void ClearPreviousBoard()
{
	for (int i = 0; i < newlinesToClear; i++)
		cout << endl;
}

inline void UpdateBoard()
{
	Grid newBoard = InitGrid(gridWidth * gridHeight, true);
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
