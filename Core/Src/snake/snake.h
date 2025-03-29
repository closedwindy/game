#ifndef __SNAKE_H
#define __SNAKE_H
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"
typedef enum {
    H = 64,
    W = 128
};

typedef enum
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
}SnakeDirType;

typedef enum  {
    EMPTY = 0,
    FOOD = 1,
}BlockType;
typedef struct{
    uint16_t x, y;
}Pos;

typedef struct{
    BlockType map_pos[W][H];
    bool HasFood;

}map;
typedef struct {
    Pos Snake[W * H];
    SnakeDirType SnakeDir;
    uint32_t lastMoveTime;
    uint16_t SnakeLength;
    uint16_t time;

}Snake;

void Snake_Init(Snake* snake);
bool Snake_Tick(void);


void drawUnit(Pos p, const char unit[]);
//随机生成食物函数
void Rand_food(map* map, Snake* s);
//蛇移动函数
void Remove(Snake* snake);
//控制蛇移动方向函数
void Control_Dirction(Snake* snake);
void Map_Init(map* map);
void EatFood(map* map, Snake* snake);
bool Gameover(Snake* snake);

#endif