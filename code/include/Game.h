#pragma once
#include "Settings.h"

void GenerateMazeRandomly(int maze[], const int rows, const int cols);
void DrawMaze(HANDLE& h, int maze[], const int rows, const int cols);
void DrawObject(HANDLE& h, COORD const& obj, colors color, int what);

void CloseApp(HANDLE& handle);