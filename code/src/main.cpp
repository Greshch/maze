#include <windows.h>
#include <iostream>
#include <ctime>
#include <conio.h>
#include "Settings.h"
#include "Game.h"
using namespace std;

int main()
{
	//srand(time(0));
	//system("mode con cols=120 lines=45");
	sprintf(mode, "mode con cols=%d lines=%d", cols, lines);
	system(mode);
	system(Title);

	//// hide standard console cursor
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 100;
	SetConsoleCursorInfo(h, &cci);

	int maze[height][width];

	// http://www.quizful.net/post/enum-types-c

	GenerateMazeRandomly((int*)maze, height, width);
	DrawMaze(h, (int*)maze, height, width);

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
// êàê îòïðàâèòü çíà÷åíèå èíòîâîé ïåðåìåííîé â çàãîëîâîê êîíñîëè: //
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