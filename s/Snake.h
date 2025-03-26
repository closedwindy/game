#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;
enum {
	 H = 20,
	 W = 70
};

const int dir[4][2] = {
	{0, -1},
	{0, 1},
	{-1, 0},
	{1, 0}
};

enum SnakeDirType
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

enum BlockType {
	EMPTY = 0,
	FOOD = 1,
};
struct Pos {
	uint16_t x, y;
};

struct map {
	BlockType map_pos[W][H];
	bool HasFood;

};
struct Snake {
	Pos Snake[W * H];
	SnakeDirType SnakeDir;
	uint32_t lastMoveTime;
	uint16_t SnakeLength;
	uint16_t time;

};

void setConsoleTextColor(int color);
void Snake_Init(Snake* snake);
//��ʱˢ�º�����Ӳ���Ͽ��԰������Snake_Tick�������ע��
bool frequency(Snake* snake);

/*bool Snake_Tick(void);
*/

void drawUnit(Pos p, const char unit[]);
//�������ʳ�ﺯ��
void Rand_food(map* map, Snake* s);
//���ƶ�����
void Remove(Snake* snake);
//�������ƶ�������
void Control_Dirction(Snake* snake);
void Game_Init(void);//���ع�������ʾЧ��
void Map_Init(map* map);
void drawMap();
void EatFood(map* map, Snake* snake);
bool Gameover(Snake* snake);