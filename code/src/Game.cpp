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
			maze[y * cols + x] = rand() % 6;
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
			else if (maze[y * cols + x] == MEDICINE)
			{
				int r = rand() % 100; // 0...9
				if (r == 91 )
				{
					maze[y * cols + x] = MEDICINE;
				}
				else
				{
					maze[y * cols + x] = HALL;
				}
			}
			else if (maze[y * cols + x] == COFFEE)
			{
				int r = rand() % 100; // 0...9
				if (r  > 95 )
				{
					maze[y * cols + x] = COFFEE;
				}
				else
				{
					maze[y * cols + x] = HALL;
				}
			}
			else if (maze[y * cols + x] == GOLD)
			{
				++totalCoins;
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
			else if (maze[y * cols + x] == MEDICINE)
			{
				SetConsoleTextAttribute(h, WHITE);
				cout << '+';
			}
			else if (maze[y * cols + x] == COFFEE)
			{
				SetConsoleTextAttribute(h, BROWN);
				cout << 'U';
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

///////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////

int GetBytcoins(int maze[],int col, COORD const& pers)
{
	static int bytcoins = 0;
	if (maze[pers.Y * col + pers.X] == GOLD)
		++bytcoins;
	return bytcoins;
}

void DrawBitcoins(HANDLE& handle, COORD const& pos, int bytcoins)
{
	SetConsoleCursorPosition(handle, pos);
	SetConsoleTextAttribute(handle, YELLOW);
	printf("COINS: %d", bytcoins);
}

void UpdateCoins(int maze[], int col, COORD const& pers)
{
	if (maze[pers.Y * col + pers.X] == GOLD)
		maze[pers.Y * col + pers.X] = HALL;
}

void DrawTotalCoins(HANDLE& h, COORD const& pos)
{
	SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, DARKGREEN);
	printf("TOTAL COINS: %d", totalCoins);
}

//////////////////////////////////////////////////////////////////////////////

bool IsCollisionEnemy(HANDLE& h, int maze[], int col, COORD const& pers)
{
	return maze[pers.Y * col + pers.X] == VRAG;
}

void DrawHealth(HANDLE& handle, COORD const& pos, int health)
{
	SetConsoleCursorPosition(handle, pos);
	SetConsoleTextAttribute(handle, DARKGREEN);
	printf("HEALTH: %d  ", health);
}

void HurtPerson(int& health)
{
	int ran = rand() % 2;
	health -= (ran) ? 20 : 25;
	health = (health < 0) ? 0 : health;
}

void UpdateEnemy(HANDLE& h, int maze[], int col, COORD const& pers, int& health)
{
	if (IsCollisionEnemy(h, maze, col, pers))
	{
		maze[pers.Y * col + pers.X] = HALL;
		HurtPerson(health);
	}
}

/////////////////////////////////////////////////////////////////////////

bool IsCollisionMedicine(HANDLE& h, int maze[], int col, COORD const& pers)
{
	return maze[pers.Y * col + pers.X] == MEDICINE;
}

void RecoverPerson(int& health)
{
	health += 5;
} 

void UpdateMedicine(HANDLE& h, int maze[], int col, COORD const& pers, int& health)
{
	static bool VisitMedicineWithFullHealth = false;
	static COORD medicine {};
	if (IsCollisionMedicine(h, maze, col, pers))
	{
		if (health < 100)
		{
			maze[pers.Y * col + pers.X] = HALL;
			RecoverPerson(health);
		}
		else
		{
			maze[pers.Y * col + pers.X] = MEDICINE;
			VisitMedicineWithFullHealth = true;
			medicine.X = pers.X;
			medicine.Y = pers.Y;
		}
	}
	else if (VisitMedicineWithFullHealth)
	{
		DrawObject(h, medicine, WHITE, '+');
		VisitMedicineWithFullHealth = false;
	}
}

/////////////////////////////////////////////////////////////////////////

bool IsCollisionCoffee(HANDLE& h, int maze[], int col, COORD const& pers)
{
	return maze[pers.Y * col + pers.X] == COFFEE;
}

void SpendEnergy(int& energy)
{
	--energy;
}

void MealPerson(int& energy)
{
	energy += 25;
}

void UpdateCoffee(HANDLE& h, int maze[], int col, COORD const& pers, int& energy)
{
	static int timesMedicine = 10;
	static COORD coffee {};
	static bool flag = false;
	if (IsCollisionMedicine(h, maze, col, pers) )
	{
		timesMedicine = 0;
	}
	else
	{
		++timesMedicine;
	}
	SpendEnergy(energy);
	if (IsCollisionCoffee(h, maze, col, pers))
	{
		if (timesMedicine >= 10)
		{
			MealPerson(energy);
			maze[pers.Y * col + pers.X] = HALL;
		}
		else
		{
			coffee.X = pers.X;
			coffee.Y = pers.Y;
			flag = true;
		}
	}
	else if (flag)
	{
		DrawObject(h, coffee, BROWN, 'U');
		flag = false;
	}
}

void DrawEnergy(HANDLE& handle, COORD const& pos, int energy)
{
	SetConsoleCursorPosition(handle, pos);
	SetConsoleTextAttribute(handle, YELLOW);
	printf("ENERGY: %d  ", energy);
}