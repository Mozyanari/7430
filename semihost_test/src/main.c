/**
  ******************************************************************************
  /**
  ******************************************************************************
  * @file    main.c
  * @author  yuqlid
  * @version V1.0
  * @date    23-Dece-2016
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

extern void initialise_monitor_handles(void);

int main(void)
{
    int time = 0;
    initialise_monitor_handles();

    HAL_Init();

    BSP_LED_Init(LED2);

    for(;;){
      HAL_Delay(500);
      BSP_LED_Toggle(LED2);
      time++;
      printf("time = %d\n",time);
      printf("Hello");
    }
}
