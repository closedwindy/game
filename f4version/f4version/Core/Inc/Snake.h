#ifndef __SNAKE_H
#define __SNAKE_H
#include <stdlib.h>
#include <stdbool.h>


typedef enum {
    H =64/4,
    W = 128/4
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
    uint8_t x, y;
}Pos;

typedef struct{
    BlockType map_pos[W][H];
    bool HasFood;

}map;
typedef struct {
    Pos Snake[W * H];
    SnakeDirType SnakeDir;
    uint8_t SnakeLength;
    uint8_t Time;

}Snake;

void Snake_Init(Snake* snake);
void Snake_Tick(Snake* snake);


void drawUnit(Pos p, const char unit[]);
//????????????
void Random_Food(map* map, Snake* snake);
//?????????
void Remove(Snake* snake);
//???????????????
void Control_Dirction(Snake* snake);
void Map_Init(map* map);
void EatFood(map* map, Snake* snake);
bool Gameover(Snake* snake);

#endif
