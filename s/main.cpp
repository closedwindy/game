
#include "Snake.h" 
int main()
{
	Snake mySnake;
	map mymap;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);/*设置游戏结束时的光标位置*/
	COORD coord;
	coord.X = 35;
	coord.Y = 10;
	 
	Snake_Init(&mySnake);
	Map_Init(&mymap);
	Game_Init();
	drawMap();
	while (1)
	{
		Control_Dirction(&mySnake);
		if (frequency(&mySnake))
		{
			Remove(&mySnake);
		}
		EatFood(&mymap, &mySnake);
		Rand_food(&mymap, &mySnake);
		if (Gameover(&mySnake))
		{
			SetConsoleCursorPosition(hOutput, coord);
			cout << "GameOver" << endl;
			return 0;
		}
	}

	return 0;
}