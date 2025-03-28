#include "stm32f10x.h"                  // Device header
#include "bsp_OLED.h"
#include "Snake.h"
#include "bsp_Key.h"
extern Snake mySnake;

const int dir[4][2] = {
	{0, -1},
	{0, 1},
	{-1, 0},
	{1, 0}
};

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

void Snake_Init(Snake* snake)
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

}
void Snake_Tick(void)
{
	static int Count = 0;  // 使用静态变量来保存中断计数
	Count++;
	if (Count >=mySnake.Time)
	{
    Remove (&mySnake );
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
				if (p.x == snake->Snake[i].x && p.y == snake->Snake[i].y || p.x == W || p.y == H || p.x == 0 || p.y == 0)
				{
					break;
				}
			}
			if (i >= snake->SnakeLength)
			{
				map->map_pos[p.y][p.x] =FOOD;
				map->HasFood = true;
				DrawUint(p.x ,p.y );
				OLED_Update();
				return;
			}
		}
	}
}

//蛇移动函数
void Remove(Snake* snake)
{
	OLED_ClearArea((snake->Snake[snake->SnakeLength - 1].x)*4,(snake->Snake[snake->SnakeLength - 1].y)*4,4,4);
	for (int i = snake->SnakeLength - 1;i > 0;i--)
	{
		snake->Snake[i] = snake->Snake[i - 1];
	}
	snake->Snake[0].x += dir[snake->SnakeDir][0];
	snake->Snake[0].y += dir[snake->SnakeDir][1];
	
	DrawUint(snake->Snake[0].x, snake->Snake[0].y);
	OLED_Update ();
}

//控制蛇移动方向函数
/*void Control_Dirction(Snake* snake)
{
	static int KeyNum;
	KeyNum=Key_GetNum ();
	if(KeyNum )
	{
	switch(KeyNum)
	{
		case '2': if (snake->SnakeDir != DOWN) { snake->SnakeDir = UP; }break;
		case '1': if (snake->SnakeDir != RIGHT) { snake->SnakeDir = LEFT; }break;
		case '3': if (snake->SnakeDir != UP) { snake->SnakeDir = DOWN; }break;
		case '4': if (snake->SnakeDir != LEFT) { snake->SnakeDir = RIGHT; }break;
	}

	}

}*/
void Control_Dirction(Snake* snake)
{
	uint8_t KeyNum=0;
	KeyNum=Key_GetNum ();
	if(KeyNum==2)
	{
		 if (snake->SnakeDir != LEFT) 
		{ 
		snake->SnakeDir = RIGHT;
		}
	}
		if(KeyNum==3)
	{
		 if (snake->SnakeDir != DOWN) 
		{ 
		snake->SnakeDir = UP;
		}
	}
	if(KeyNum==4)
	{
		 if (snake->SnakeDir!= RIGHT) 
		{ 
		snake->SnakeDir = LEFT;
		}
	}
		if(KeyNum==1)
	{
		 if (snake->SnakeDir!= UP) 
		{ 
		snake->SnakeDir= DOWN;
		}
	}

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
		Random_Food(map, snake);
	}

}

bool Gameover(Snake* snake)
{
	// 判断是否撞地图边界
	if (snake->Snake[0].x < 1 || snake->Snake[0].x >= W+1 || snake->Snake[0].y < 1 || snake->Snake[0].y >= H+1)
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
