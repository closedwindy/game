#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "bsp_OLED.h"
#include "Snake.h"
#include "bsp_Timer.h"
#include "bsp_Key.h"
Snake mySnake;
map myMap;
int i=123;
int main (void)
{
	OLED_Init();
	Timer_Init ();
	Snake_Init(&mySnake );
	Map_Init (&myMap );
	Key_Init();
	
	
	while (1)
	{	
		uint8_t KeyNum=0;
		KeyNum=Key_GetNum ();
		EatFood(&myMap, &mySnake);
		Random_Food(&myMap,&mySnake);
		Control_Dirction(&mySnake,KeyNum);
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
	Key_Tick();
	
	    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}


}
