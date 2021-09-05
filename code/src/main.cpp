#include <windows.h>
#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;

int main()
{
	srand(time(0));
	system("mode con cols=210 lines=70");
	system("title Super Maze!");

	// hide standard console cursor
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 100;
	SetConsoleCursorInfo(h, &cci);

	const int width = 200;
	const int height = 60;
	int maze[height][width];

	// http://www.quizful.net/post/enum-types-c

	enum maze_objects { HALL, WALL, GOLD, VRAG };
	enum direction { DOWN = 80, UP = 72, LEFT = 75, RIGHT = 77 };
	enum colors { BLUE = 9, RED = 12, YELLOW = 14, DARKGREEN = 2 };

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int random = rand() % 4;
			maze[y][x] = random;

			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
				maze[y][x] = WALL;

			// enter and exit
			if (x == 0 && y == 2 || x == 1 && y == 2
				|| x == width - 1 && y == height - 3)
				maze[y][x] = HALL;

			/////////////////////////////////////////////////////////

			if (maze[y][x] == WALL)
			{
				SetConsoleTextAttribute(h, DARKGREEN);
				cout << (char)178;
			}
			else if (maze[y][x] == GOLD)
			{
				SetConsoleTextAttribute(h, YELLOW);
				cout << (char)250;
			}
			else if (maze[y][x] == VRAG)
			{
				int r = rand() % 100; // 0...9
				if (r == 0)
				{
					SetConsoleTextAttribute(h, RED);
					cout << (char)1;
				}
				else
				{
					maze[y][x] = HALL;
					cout << " ";
				}
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\n";
	}

	COORD pers = { 0, 2 };
	SetConsoleCursorPosition(h, pers);
	SetConsoleTextAttribute(h, BLUE);
	cout << (char)1;

	while (true)
	{
		int direct = _getch();
		if (direct == 224)
			direct = _getch();

		SetConsoleCursorPosition(h, pers);
		cout << " ";

		if (direct == RIGHT && maze[pers.Y][pers.X + 1] != WALL)
		{
			pers.X++;
		}
		SetConsoleCursorPosition(h, pers);
		SetConsoleTextAttribute(h, BLUE);
		cout << (char)1;

	}
}

////////////////////////////////////////////////////////////////////
// как отправить значение интовой переменной в заголовок консоли: //
////////////////////////////////////////////////////////////////////

/*
#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	int coins = 25;

	// string representation of coins variable
	char* title = new char[200];
	_itoa_s(coins, title, 199, 10);

	SetConsoleTitleA(title);

	system("pause");
}
*/