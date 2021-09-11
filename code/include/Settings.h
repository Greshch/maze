#pragma once

const int cols = 120;
const int lines = 45;

const int width = 100;
const int height = 40;

///////////////////////////////////////////////////////////////////////////////////////
const int BUFFER_SIZE = 80;
extern char mode[BUFFER_SIZE];
//////////////////////////////////////////////////////////////////////////////////////
extern char const* Title;
//////////////////////////////////////////////////////////////////////////////////////
enum maze_objects { HALL, WALL, GOLD, VRAG };
enum direction { DOWN = 80, UP = 72, LEFT = 75, RIGHT = 77 };
enum colors { BLUE = 9, RED = 12, YELLOW = 14, DARKGREEN = 2 };
//////////////////////////////////////////////////////////////////////////////////////