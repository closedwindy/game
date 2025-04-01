#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Snake.h"

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
        OLED_DrawPoint(x * 4 + i, y * 4 + j);
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
    My_Remove (snake );
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
    Remove (snake );
	Count=0;
	}

}

//随机生成食物函数
void Random_Food(map* map, Snake* snake)
{
	if (!map->HasFood)
	{
		while (1)
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
				map->map_pos[p.y][p.x] =FOOD;
				map->HasFood = true;
				map->Food_Pos = p;
				DrawUint(p.x ,p.y );
				OLED_Update ();
				break;
			}
		}
	}
}

//蛇移动函数
void Remove(Snake* snake)
{
	OLED_ClearArea((snake->Snake[snake->SnakeLength - 1].x)*4,(snake->Snake[snake->SnakeLength - 1].y)*4,4,4);
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
	// 判断是否撞地图边界
	/*if (snake->Snake[0].x >= W|| snake->Snake[0].y >= H||snake->Snake[0].x<=0||snake->Snake[0].y<=0)
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
	
	}*/
	
	for (int i = snake->SnakeLength - 1;i > 0;i--)
	{
		snake->Snake[i] = snake->Snake[i - 1];
	}
	
	
	DrawUint(snake->Snake[0].x, snake->Snake[0].y);
	OLED_Update ();
}

//蛇移动函数
void My_Remove(Snake* snake)
{
	OLED_ClearArea((snake->Snake[snake->SnakeLength - 1].x)*4,(snake->Snake[snake->SnakeLength - 1].y)*4,4,4);
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
	OLED_Update ();
}

//人机控制方向函数
void Auto_Control_Dirction(Snake* snake, map* map)
{
	Pos Food_Pos=map->Food_Pos;
	int dx=Food_Pos .x -snake->Snake [0].x;
	int dy=Food_Pos .y -snake->Snake [0].y;
	
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
void My_Control_Dirction(Snake* snake,uint8_t KeyNum)
{
	if(KeyNum)
	{
	switch (KeyNum )
	{
		case 1:if(snake->SnakeDir !=UP)snake->SnakeDir=DOWN;break;
		case 2:if(snake->SnakeDir !=LEFT)snake->SnakeDir=RIGHT;break;
		case 3:if(snake->SnakeDir !=DOWN)snake->SnakeDir=UP;break;
		case 4:if(snake->SnakeDir !=RIGHT)snake->SnakeDir=LEFT;break;
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

}
