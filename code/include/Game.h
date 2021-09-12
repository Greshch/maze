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

void CloseApp(HANDLE& handle);