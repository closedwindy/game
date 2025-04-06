#include "stm32f4xx_hal.h"
#include "u8g2.h"
#include "main.h"
#include "Snake.h"

#include <stm32_u8g2.h>
#include "mpu6050.h"
extern u8g2_t u8g2;
volatile int dir[4][2] = {
	{0, -1},
	{0, 1},
	{-1, 0},
	{1, 0}
};
//画蛇函数
void DrawUint(uint8_t x, uint8_t y)
{
for (int i = 0; i < 4; ++i)
{
    for (int j = 0; j < 4; ++j)
    {
        u8g2_DrawPixel(&u8g2,x * 4 + i, y * 4 + j);
    }
}
}
//蛇初始化
void My_Snake_Init(Snake* snake)
{
	snake->SnakeLength = 3;
	snake->SnakeDir = LEFT;
	snake->Snake[0].x=W / 2;
	snake->Snake[0].y=H / 2;
	snake->Snake[1].x=W / 2 - 1;
	snake->Snake[1].y=H / 2;
	snake->Snake[2].x = W / 2 - 2;
	snake->Snake[2].y=H / 2 ;
	snake->Time=200;
	snake->GameOver=0;
	snake->IsSlowDown=false;
}
//人机初始化
void Robot_Snake_Init(Snake* snake)
{
	snake->SnakeLength = 3;
	snake->SnakeDir = LEFT;
	snake->Snake[0].x=4;
	snake->Snake[0].y=4;
	snake->Snake[1].x=3;
	snake->Snake[1].y=4;
	snake->Snake[1].x=2;
	snake->Snake[1].y=4;
	snake->Time=200;
}
//蛇刷新
void Snake_Tick(Snake *snake)
{
	static int Count = 0;  // 使用静态变量来保存中断计数
	Count++;
	if (Count >=snake->Time)
	{
    MyRemove (snake );
	Count=0;
	}

}

//蛇刷新
void Robot_Snake_Tick(Snake *snake)
{
	static int Count = 0;  // 使用静态变量来保存中断计数
	Count++;
	if (Count >=snake->Time)
	{
    RobotRemove (snake );
	Count=0;
	}

}

//随机生成食物函数
void Random_Foodandprop(map* map, Snake* snake)
{ int temp;
	temp=rand()%7;
	if (!map->HasFood&&!map->HasProp)
	{
		while (!map->HasFood&&!map->HasProp)
		{
			Pos p;
			int i = 0;
			p.x = rand() % W;
			p.y = rand() % H;
			for (i = 0; i < snake->SnakeLength; ++i)
			{
				if ((p.x == snake->Snake[i].x && p.y == snake->Snake[i].y) || p.x == W || p.y == H || p.x == 0 || p.y == 0)
				{
					break;
				}
			}
			if (i >= snake->SnakeLength)
			{
				if(temp>=5)
				{
					map->map_pos[p.y][p.x] = FOOD; // 生成食物
					map->HasFood = true;  // 设置食物标志
					map->Food_Pos = p;
					DrawUint(p.x, p.y);
					u8g2_SendBuffer(&u8g2);

				}
               else
                {

               	map->map_pos[p.y][p.x] = PROP_SLOW_DOWN; // 生成道具
               	map->HasProp = true;  // 设置道具标志
               	map->prop = p; // 存储道具坐标
               	u8g2_DrawFrame(&u8g2,p.x*4,p.y*4,4,4);
               	u8g2_SendBuffer(&u8g2);


                }

                break;
			}
		}
	}
}

//随机生成食物函数
void Random_Food(map* map, Snake* snake)
{
	if (!map->HasFood&&!map->HasProp)
	{
		while (!map->HasFood&&!map->HasProp)
		{
			Pos p;
			int i = 0;
			p.x = rand() % W;
			p.y = rand() % H;
			for (i = 0; i < snake->SnakeLength; ++i)
			{
				if ((p.x == snake->Snake[i].x && p.y == snake->Snake[i].y) || p.x == W || p.y == H || p.x == 0 || p.y == 0)
				{
					break;
				}
			}
			if (i >= snake->SnakeLength)
			{


                    map->map_pos[p.y][p.x] = FOOD; // 生成食物
                    map->HasFood = true;  // 设置食物标志
                    map->Food_Pos = p;
					DrawUint(p.x, p.y);
					u8g2_SendBuffer(&u8g2);


                break;
			}
		}
	}
}


//蛇移动函数
void RobotRemove(Snake* snake)
{
	u8g2_cleararea(&u8g2,(snake->Snake[snake->SnakeLength - 1].x)*4,(snake->Snake[snake->SnakeLength - 1].y)*4,4,4);
	snake->Snake[0].x += dir[snake->SnakeDir][0];
	snake->Snake[0].y += dir[snake->SnakeDir][1];

	// 处理边界环绕逻辑
    if (snake->Snake[0].x >= W)  // 撞到右边界
    {
        snake->Snake[0].x = 0;  // 从左边界重新出现
    }
    else if (snake->Snake[0].x <= 0)  // 撞到左边界
    {
        snake->Snake[0].x = W-4;  // 从右边界重新出现
    }
    if (snake->Snake[0].y >= H)  // 撞到下边界
    {
        snake->Snake[0].y = 0;  // 从上边界重新出现
    }
    else if (snake->Snake[0].y <= 0)  // 撞到上边界
    {
        snake->Snake[0].y = H;  // 从下边界重新出现
    }

	for (int i = snake->SnakeLength - 1;i > 0;i--)
	{
		snake->Snake[i] = snake->Snake[i - 1];
	}


	DrawUint(snake->Snake[0].x, snake->Snake[0].y);
	u8g2_SendBuffer (&u8g2);
}

//蛇移动函数
void MyRemove(Snake* snake)
{
	u8g2_cleararea(&u8g2,(snake->Snake[snake->SnakeLength - 1].x)*4,(snake->Snake[snake->SnakeLength - 1].y)*4,4,4);
	snake->Snake[0].x += dir[snake->SnakeDir][0];
	snake->Snake[0].y += dir[snake->SnakeDir][1];


	if (snake->Snake[0].x >= W|| snake->Snake[0].y >= H||snake->Snake[0].x<=0||snake->Snake[0].y<=0)
	{
		snake->GameOver =1; // 蛇头越界，游戏结束
	}

	if(snake->SnakeLength >=4)
	{
	for (int i = 1; i < snake->SnakeLength; i++)
		{
			if (snake->Snake[0].x == snake->Snake[i].x && snake->Snake[0].y == snake->Snake[i].y)
			{
				snake->GameOver =1; //判断是否撞到自己
			}
		}

	}

	for (int i = snake->SnakeLength - 1;i > 0;i--)
	{
		snake->Snake[i] = snake->Snake[i - 1];
	}


	DrawUint(snake->Snake[0].x, snake->Snake[0].y);
	u8g2_SendBuffer (&u8g2);
}

//人机控制方向函数
void Auto_Control_Dirction(Snake* snake, map* map)
{
	Pos Food_Pos=map->Food_Pos;
	int dx=Food_Pos .x -snake->Snake [0].x;
	int dy=Food_Pos .y -snake->Snake [0] .y;

	if(abs(dx)>abs(dy))//如果水平方向离食物更近
	{
		if(dx>0)
		{
		if(snake->SnakeDir !=LEFT ){snake->SnakeDir =RIGHT;}
		}
		else
		{
		if(snake->SnakeDir !=RIGHT ){snake->SnakeDir =LEFT;}
		}

	}
	else
	{
		if(dy>0)
		{
		if(snake->SnakeDir !=UP ){snake->SnakeDir =DOWN;}
		}
		else
		{
		if(snake->SnakeDir !=DOWN ){snake->SnakeDir =UP;}
		}
	}
}
//控制方向函数
void Control_Dirction(Snake* snake)
{

	MPU6050_Read_Result();
	if(roll<=-20)
	{
		if (snake->SnakeDir != LEFT)
		{
			snake->SnakeDir = RIGHT;
		}
	}
	if(pitch<=-20)
	{
		if (snake->SnakeDir != DOWN)
		{
			snake->SnakeDir = UP;
		}
	}
	if(roll>=20)
	{
		if (snake->SnakeDir!= RIGHT)
		{
			snake->SnakeDir = LEFT;
		}
	}
	if(pitch>=20)
	{
		if (snake->SnakeDir!= UP)
		{
			snake->SnakeDir= DOWN;
		}
	}

}
//地图初始化
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
    map->HasProp = false;  // 初始化道具标志
}
//吃食物函数
void EatFood(map* map, Snake* snake,int *point)
{
	if (map->map_pos[snake->Snake[0].y][snake->Snake[0].x] == FOOD)
	{
		snake->SnakeLength++;
		Pos previousBody = snake->Snake[snake->SnakeLength - 2];
		snake->Snake[snake->SnakeLength - 1] = previousBody;

		map->map_pos[snake->Snake[0].y][snake->Snake[0].x] = EMPTY;
		map->HasFood = false;
		(*point)++;
		Random_Food(map, snake);
	}
	// 检测是否吃到道具
    else if (map->map_pos[snake->Snake[0].y][snake->Snake[0].x] == PROP_SLOW_DOWN)
    {
        UseProp(snake); // 调用道具功能
        map->map_pos[snake->Snake[0].y][snake->Snake[0].x] = EMPTY; // 清除道具
        map->HasProp = false; // 清除道具标志
        map->prop.x = -1; // 设置无效坐标
        map->prop.y = -1;
		Random_Foodandprop(map, snake);
    }
}
void UseProp(Snake* snake)
{
    // 道具功能：蛇变慢1000毫秒
    snake->Time=500; // 增加蛇的移动时间间隔，使蛇变慢
    snake->SlowDownTime = 4000; // 设置变慢时间为1000毫秒
    snake->IsSlowDown = true; // 设置变慢标志
}
