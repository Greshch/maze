#include <windows.h>
#include "Settings.h"

char const* Title = "title Super Maze!";
int maze[height][width];
char mode[BUFFER_SIZE];

COORD const EXIT {width - 1, height - 3};