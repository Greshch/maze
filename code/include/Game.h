#pragma once
#include "Settings.h"

void GenerateMazeRandomly(int maze[], const int rows, const int cols);
void DrawMaze(HANDLE& h, int maze[], const int rows, const int cols);
void DrawObject(HANDLE& h, COORD const& obj, colors color, int what);

void UpdatePerson(int arr[], int const& col, int dir, COORD& person);
void ErasePersonsOldPosition(HANDLE& handle, COORD const& person);

bool IsEqualCoord(COORD const& a, COORD const& b);

void DrawPersonPosition(HANDLE& handle, COORD const& person, COORD const& pos);

void UpdateCoins(int maze[], int width, COORD const& pers);
int GetBytcoins(int maze[],int width, COORD const& pers);
void DrawBitcoins(HANDLE& h, COORD const& pos, int bytcoins);
void DrawTotalCoins(HANDLE& h, COORD const& pos);

bool IsCollisionEnemy(HANDLE& h, int maze[], int col, COORD const& pers);
void HurtPerson(int& health);
void DrawHealth(HANDLE& h, COORD const& pos, int health);
void UpdateEnemy(HANDLE& h, int maze[], int width, COORD const& pers, int& health);

bool IsCollisionMedicine(HANDLE& h, int maze[], int col, COORD const& pers);
void RecoverPerson(int& health);
void UpdateMedicine(HANDLE& h, int maze[], int width, COORD const& pers, int& health);

bool IsCollisionCoffee(HANDLE& h, int maze[], int col, COORD const& pers);
void MealPerson(int& energy);
void SpendEnergy(int& energy);
void UpdateCoffee(HANDLE& h, int maze[], int width, COORD const& pers, int& health);
void DrawEnergy(HANDLE& h, COORD const& pos, int energy);

void CloseApp(HANDLE& handle);