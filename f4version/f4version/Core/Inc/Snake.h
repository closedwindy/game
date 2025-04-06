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

typedef enum {
    EMPTY = 0,
    FOOD = 1,
    PROP_SLOW_DOWN = 2  // 新增道具类型
} BlockType;

typedef struct {
    int x;
    int y;
} Pos;

typedef struct {
    BlockType map_pos[W][H];
    bool HasFood;
    bool HasProp;  // 添加道具标志
    Pos Food_Pos;
    Pos prop;  // 道具坐标
} map;

typedef struct {
    Pos Snake[W * H];
    SnakeDirType SnakeDir;
    uint8_t SnakeLength;
    uint16_t Time;
    uint16_t SlowDownTime; // 蛇变慢的剩余时间
    uint8_t GameOver;
    bool IsSlowDown; // 蛇是否处于变慢状态
} Snake;

void My_Snake_Init(Snake* snake);
void Robot_Snake_Init(Snake* snake);

void Snake_Tick(Snake *snake);
void Robot_Snake_Tick(Snake *snake);
void drawUnit(Pos p, const char unit[]);
void Random_Foodandprop(map* map, Snake* snake);
void Random_Food(map* map, Snake* snake);
void RobotRemove(Snake* snake);
void MyRemove(Snake* snake);
void UseProp(Snake* snake);
void Auto_Control_Dirction(Snake* snake, map* map);
void Control_Dirction(Snake* snake);
void Map_Init(map* map);
//void EatFood(map* map, Snake* snake);
void EatFood(map* map, Snake* snake,int *point);

#endif
