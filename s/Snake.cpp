#include "Snake.h"
void setConsoleTextColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
void Snake_Init(Snake* snake)
{
	snake->SnakeLength = 3;
	snake->SnakeDir = LEFT;
	snake->Snake[0] = { W / 2, H / 2 };
	snake->Snake[1] = { W / 2 - 1, H / 2 };
	snake->Snake[2] = { W / 2 - 2, H / 2 };
	snake->lastMoveTime = 0;
	snake->time = 200;

}
//��ʱˢ�º�����Ӳ���Ͽ��԰������Snake_Tick�������ע��
bool frequency(Snake* snake)
{
	uint32_t Gettime = static_cast<uint32_t>(GetTickCount());
	if (Gettime - (snake->time) >= snake->lastMoveTime)
	{
		snake->lastMoveTime = Gettime;
		return true;
	}

	return false;
}

/*bool Snake_Tick(void)
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
*/

void drawUnit(Pos p, const char unit[])
{
	COORD coord;//COORD���ͱ�����windows.h��Ľṹ�壬ͨ���������ù���λ�û��߻�ȡ����λ�á�
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡϵͳ����̨Ȩ��
	coord.X = p.x+1;
	coord.Y = p.y+1;
	SetConsoleCursorPosition(hOutput, coord);
	setConsoleTextColor(FOREGROUND_RED); // ������ɫΪ��ɫ
	cout << unit;
}
//�������ʳ�ﺯ��
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
			drawUnit(Food, "��");
			map->HasFood = true;
		}
	}
}

//���ƶ�����
void Remove(Snake* snake)
{
	drawUnit(snake->Snake[snake->SnakeLength - 1], " ");
	for (int i = snake->SnakeLength - 1;i > 0;i--)
	{
		snake->Snake[i] = snake->Snake[i - 1];
	}
	snake->Snake[0].x += dir[snake->SnakeDir][0];
	snake->Snake[0].y += dir[snake->SnakeDir][1];

	drawUnit(snake->Snake[0], "��");
}

//�������ƶ�������
void Control_Dirction(Snake* snake)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w': if (snake->SnakeDir != DOWN) { snake->SnakeDir = UP; }break;
		case 'a': if (snake->SnakeDir != RIGHT) { snake->SnakeDir = LEFT; }break;
		case 's': if (snake->SnakeDir != UP) { snake->SnakeDir = DOWN; }break;
		case 'd': if (snake->SnakeDir != LEFT) { snake->SnakeDir = RIGHT; }break;
		}
	}
}

void Game_Init(void)//���ع�������ʾЧ��
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curInfo = { 1, FALSE };
	SetConsoleCursorInfo(hOutput, &curInfo);
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

void drawMap()
{
	cout << "��";
	for (int x = 0; x < W; ++x)
	{
		cout << "��";
	}
	cout << "��" << endl;

	for (int y = 0; y < H; ++y)
	{
		cout << "��";
		for (int x = 0; x < W; ++x)
		{
			cout << " ";
		}
		cout << "��" << endl;
	}
	cout << "��";
	for (int x = 0; x < W; ++x)
	{
		cout << "��";
	}
	cout << "��";
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
	// �ж��Ƿ�ײ��ͼ�߽�
	if (snake->Snake[0].x < 1 || snake->Snake[0].x >= W || snake->Snake[0].y < 1 || snake->Snake[0].y >= H)
	{
		return true; // ��ͷԽ�磬��Ϸ����
	}

	if (snake->SnakeLength >= 5)//�߳��ȴ����Ĳſ�ʼ�жϣ���ֹһ��ʼ�ͽ��д����ж�
	{
		for (int i = 1; i < snake->SnakeLength; i++)
		{
			if (snake->Snake[0].x == snake->Snake[i].x && snake->Snake[0].y == snake->Snake[i].y)
			{
				return true; //�ж��Ƿ�ײ���Լ�
			}
		}
	}
	return false; // û��Խ��Ҳû��ײ��������Ϸ����
}