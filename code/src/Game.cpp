#include <windows.h>
#include <iostream>
#include <ctime>
#include <conio.h>
#include "Game.h"
#include "Settings.h"

void GenerateMazeRandomly(int maze[], const int rows, const int cols)
{
	using namespace std;
	srand(time(0));
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			maze[y * cols + x] = rand() % 4;
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
				maze[y * cols + x] = WALL;

			// enter and exit
			if (x == 0 && y == 2 || x == 1 && y == 2
				|| x == width - 1 && y == height - 3)
				maze[y * cols + x] = HALL;
			if (maze[y * cols + x] == VRAG)
			{
				int r = rand() % 100; // 0...9
				if (r)
				{
					maze[y * cols + x] = HALL;
				}
			}
		}
	}
}

void DrawMaze(HANDLE& h, int maze[], const int rows, const int cols)
{
	using namespace std;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (maze[y*cols +x] == WALL)
			{
				SetConsoleTextAttribute(h, DARKGREEN);
				cout << (char)178;
			}
			else if (maze[y * cols + x] == GOLD)
			{
				SetConsoleTextAttribute(h, YELLOW);
				cout << (char)250;
			}
			else if (maze[y * cols + x] == VRAG)
			{
				SetConsoleTextAttribute(h, RED);
				cout << (char)1;
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\n";
	}
}

void DrawObject(HANDLE& h, COORD const& obj, colors color, int  what)
{
	SetConsoleCursorPosition(h, obj);
	SetConsoleTextAttribute(h, color);
	std::cout << (char)what;
}

void CloseApp(HANDLE& handle)
{
	system("cls");
	SetConsoleCursorPosition(handle, {0, 0});
	SetConsoleTextAttribute(handle, WHITE);
	//Set visible cursor
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = true;
	cci.dwSize = 10;
	SetConsoleCursorInfo(handle, &cci);
}

void UpdatePerson(int arr[], int const& col, int direct, COORD& pers)
{
	if (direct == RIGHT && arr[pers.Y * col + pers.X + 1] != WALL)
	{
		pers.X++;
	}
	else if (direct == LEFT && arr[pers.Y * col + pers.X - 1] != WALL)
	{
		pers.X--;
	}
	else if (direct == DOWN && arr[(pers.Y + 1) * col  + pers.X] != WALL)
	{
		pers.Y++;
	}
	else if (direct == UP && arr[(pers.Y - 1) * col  + pers.X] != WALL)
	{
		pers.Y--;
	}
}

void ErasePersonsOldPosition(HANDLE& handle, COORD const& person)
{
	SetConsoleCursorPosition(handle, person);
	std::cout << " ";
}

void DrawPersonPosition(HANDLE& handle, COORD const& person, COORD const& pos)
{
	SetConsoleCursorPosition(handle, pos);
	SetConsoleTextAttribute(handle, RED);
	printf("{y=%d, x=%d}", person.Y, person.X);
}

bool IsEqualCoord(COORD const& a, COORD const& b)
{
	return a.X == b.X && a.Y == b.Y;
}