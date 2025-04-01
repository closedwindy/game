#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Snake.h"
#include "bsp_Timer.h"
#include "bsp_Key.h"
Snake RobotSnake;
Snake mySnake; 
map myMap;

int main (void)
{
	
	uint8_t KeyNum=0;
	int My_point=0;
	int Robot_point=0;
	OLED_Init();
	Timer_Init ();
	Robot_Snake_Init(&RobotSnake);
	My_Snake_Init (&mySnake);
	Map_Init (&myMap );
	Key_Init();
	
	
	while (1)
	{	
		KeyNum=Key_GetNum ();
		EatFood(&myMap, &mySnake,&My_point);
		EatFood(&myMap, &RobotSnake,&Robot_point);
		Random_Food(&myMap,&RobotSnake);
		Auto_Control_Dirction(&RobotSnake, &myMap);
		My_Control_Dirction(&mySnake,KeyNum );
		OLED_ShowNum(1,1,My_point ,5,OLED_6X8);
		OLED_Update();
	if(mySnake.GameOver)
	{
	OLED_Clear();
	OLED_ShowString(32,24,"GameOver",OLED_8X16);
	OLED_Update();
	return 0;
	
	}
	}
}
void TIM2_IRQHandler(void)
{
	 
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
	Snake_Tick (&mySnake);
	Robot_Snake_Tick(&RobotSnake);
	Key_Tick();
	
	    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}


}
