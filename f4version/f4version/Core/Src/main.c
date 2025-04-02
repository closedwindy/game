/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MPU6050.h"
#include "u8g2.h"
#include "stm32_u8g2.h"
#include "Snake.h"
#include "menu.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Snake mySnake;
map myMap;
int desktop=0;
int z=0,s=0,_TEMP=0,w=0,difficult=0,_CLEAR=1;
int mode =0;
u8g2_t u8g2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int f;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

    //Desktop1_direction=126;






    /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

      MPU6050_Init();

    HAL_TIM_Base_Start_IT(&htim2);


    u8g2Init(&u8g2);
    OPENUI(&u8g2);
    Snake_Init(&mySnake);
    Map_Init(&myMap);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      if(w>=32){
          w=32;
      }
      if(w<=0)
      {
          w=0;
      }
    if(roll>10&&desktop!=4)
    {
     mode = 1;

    }
    if(roll>-10&&roll<10)
    {
        mode =0;
    }
if(roll<-10)
    {
         mode = 2;
    }
      if(pitch<-30)
      { if((Desktop1_direction==42||Desktop1_direction==-84)&&desktop!=4)
          {
              desktop = 1;
          }
          if(Desktop1_direction==84||Desktop1_direction==-42)
          {
              _TEMP=1;
              if(_CLEAR==1)
              {
                  u8g2_ClearBuffer(&u8g2);
                  _CLEAR=0;
              }
              desktop=4;
          }
      }
      if(pitch>30&&desktop!=4)
      {
          desktop=0;
      }

      switch(desktop)
      {
          case 0:
              Desktop1();
              break;
          case 1:
              Desktop2_SET(w);
              break;
          case 2:
              HELL();
          case 3:;
              break;
      }


//      Random_Food(&myMap,&mySnake);
//      MPU6050_Read_Result();
//      Control_Dirction(&mySnake,roll,pitch);
      u8g2_SetFont(&u8g2, u8g2_font_ncenB08_te);




//if(z==2) {
//    u8g2_DrawFrame(&u8g2, 0, 0, 128, 64);
//    u8g2_SendBuffer(&u8g2);
//}

if(_TEMP==1)
{
    Random_Food(&myMap,&mySnake);
    Control_Dirction(&mySnake);
}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }



  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        f++;
        z++;

        if (f > 50) {
            MPU6050_Read_Result();
        }
        if (_TEMP == 1) {
            s+=4;
            switch (w/16) {
                case 0:
                    if (s == 24) {
                        Remove(&mySnake);
                        s = 0;
                    }
                    break;
                case 1:
                    if (s == 16) {
                        Remove(&mySnake);
                        s = 0;
                    }
                    break;
                case 2:
                    if (s == 8) {
                        Remove(&mySnake);
                        s = 0;
                    }
                    break;
            }


        }


        if (z == 5) {
            switch (mode) {
                case 1:
                    if (desktop == 0) { Desktop1_direction += 42; }
                    if (desktop == 1) { w -= 16; }
                    break;
                case 2:
                    if (desktop == 0) { Desktop1_direction -= 42; }
                    if (desktop == 1) { w += 16; }
                    break;
            }
////          Remove(&mySnake);

            z = 0;
        }
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
