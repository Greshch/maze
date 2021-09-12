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
	int bytcoins = 0;
	int health = 100;
	DrawObject(h, pers, BLUE, 1);
	DrawTotalCoins(h, {width + 2, 1});
	DrawBitcoins(h, {width + 2, 3}, bytcoins);
	DrawHealth(h, {width + 2, 5}, health);

	while (true)
	{
		int direct = _getch();
		if (direct == 224)
			direct = _getch();

		//quit
		if (direct == 'q')
			break;

		//1 move pers
		ErasePersonsOldPosition(h, pers);
		UpdatePerson((int*)maze, width, direct, pers);
		DrawObject(h, pers, BLUE, 1);
		///////////////////////////////////////////////////////

		//2 count bytcoins
		bytcoins = GetBytcoins((int*)maze, width, pers);
		UpdateCoins((int*)maze, width, pers);
		DrawBitcoins(h, {width + 2, 3}, bytcoins);

		//3
		UpdateEnemy(h, (int*) maze, width, pers, health);
		UpdateMedicine(h, (int*) maze, width, pers, health);
		DrawHealth(h, {width + 2, 5}, health);

		//1 check achieve EXIT
		if (IsEqualCoord(pers, EXIT))
		{
			MessageBoxW(NULL, L"Победа найден выход!", L"Победа", MB_OK);
			break;
		}
		//2 check collect of ALL GOLD
		if (bytcoins == totalCoins)
		{
			MessageBoxW(NULL, L"Победа все биткоины собраны!", L"Победа", MB_OK);
			break;
		}
		//3 check health
		if (health == 0)
		{
			MessageBoxW(NULL, L"Поражение закончилось здоровье...", L"Поражение", MB_OK);
			break;
		}

	}

	CloseApp(h);
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