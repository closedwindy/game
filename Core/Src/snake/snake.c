#include "u8g2.h"
#include "Snake.h"
extern u8g2_t u8g2;
const int dir[4][2] = {
        {0, -1},
        {0, 1},
        {-1, 0},
        {1, 0}
};

void Snake_Init(Snake* snake)
{
    snake->SnakeLength = 3;
    snake->SnakeDir = LEFT;
    snake->Snake[0].x = W / 2;
    snake->Snake[0].y = H / 2;
    snake->Snake[1].x = W / 2-1;
    snake->Snake[1].y = H / 2;
    snake->Snake[2].x = W / 2-2;
    snake->Snake[2].y = H / 2;
    snake->lastMoveTime = 0;
    snake->time = 200;

}
bool Snake_Tick(void)
{
    int Count = 0;
    Count++;
    if (Count == 200)
    {
        Count = 0;
        return true;
    }

    return false;

}

//随机生成食物函数
void Rand_food(map* map, Snake* s)
{

    int Count = 0;
    if (map->HasFood == false)
    {
        Pos p[W * H];
        for (int X = 1;X < W - 1;++X)
        {

            for (int Y = 1;Y < H - 1;++Y)
            {
                bool Has = true;
                for (int i = 0;i < s->SnakeLength;i++)
                {
                    if (X == s->Snake[i].x && Y == s->Snake[i].y)
                    {

                        Has = false;
                        break;

                    }

                }
                if (Has)
                {
                    Pos Temp = { X,Y };
                    p[Count++] = Temp;
                }

            }

        }

        if (Count > 0)
        {
            int coordinates = rand() % Count;
            Pos Food = p[coordinates];
            map->map_pos[Food.y][Food.x] = FOOD;
            u8g2_DrawCircle(&u8g2,Food.x,Food.y,3,1);
            u8g2_SendBuffer(&u8g2);
            map->HasFood = true;
        }
    }
}

//蛇移动函数
void Remove(Snake* snake)
{
    u8g2_DrawStr(&u8g2,snake->Snake[snake->SnakeLength - 1].x,snake->Snake[snake->SnakeLength - 1].y," " );
    u8g2_SendBuffer(&u8g2);
    for (int i = snake->SnakeLength - 1;i > 0;i--)
    {
        snake->Snake[i] = snake->Snake[i - 1];
    }
    snake->Snake[0].x += dir[snake->SnakeDir][0];
    snake->Snake[0].y += dir[snake->SnakeDir][1];
    u8g2_DrawBox(&u8g2,snake->Snake[0].x,snake->Snake[0].y,16,16);
    u8g2_SendBuffer(&u8g2);
}

//控制蛇移动方向函数
void Control_Dirction(Snake* snake)
{

}

void Map_Init(map* map)
{

    for (int i = 0;i < W;i++)
    {
        for (int j = 0;j < H;j++)
        {
            map->map_pos[i][j] = EMPTY;
        }
    }
    map->HasFood = false;
}
void EatFood(map* map, Snake* snake)
{
    if (map->map_pos[snake->Snake[0].y][snake->Snake[0].x] == FOOD)
    {
        snake->SnakeLength++;
        Pos previousBody = snake->Snake[snake->SnakeLength - 2];
        snake->Snake[snake->SnakeLength - 1] = previousBody;

        map->map_pos[snake->Snake[0].y][snake->Snake[0].x] = EMPTY;
        map->HasFood = false;
        //Random_Food(map, snake);
        Rand_food(map, snake);
    }

}

bool Gameover(Snake* snake)
{
    // 判断是否撞地图边界
    if (snake->Snake[0].x < 1 || snake->Snake[0].x >= W || snake->Snake[0].y < 1 || snake->Snake[0].y >= H)
    {
        return true; // 蛇头越界，游戏结束
    }

    if (snake->SnakeLength >= 5)//蛇长度大于四才开始判断，防止一开始就进行错误判断
    {
        for (int i = 1; i < snake->SnakeLength; i++)
        {
            if (snake->Snake[0].x == snake->Snake[i].x && snake->Snake[0].y == snake->Snake[i].y)
            {
                return true; //判断是否撞到自己
            }
        }
    }
    return false; // 没有越界也没有撞到自身，游戏继续
}