/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include <stm32f401xe.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_rcc.h>
			

int main(void)
{
	//システムの初期化
	SystemInit();
	//HALライブラリを使うための初期化関数
	HAL_Init();

	//クロック供給
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	//GPIO.Cを初期化
	//構造体生成
	GPIO_InitTypeDef GPIO_Assign_C;

	//C_PIN13の設定
	GPIO_Assign_C.Pin = GPIO_PIN_13;
	GPIO_Assign_C.Mode = GPIO_MODE_INPUT;
	GPIO_Assign_C.Pull = GPIO_PULLUP;
	GPIO_Assign_C.Speed = GPIO_SPEED_FREQ_LOW;

	//PIN13の設定を書き込み
	HAL_GPIO_Init(GPIOC,&GPIO_Assign_C);

	//GPIO.Aを初期化
	//構造体を初期化
	GPIO_InitTypeDef GPIO_Assign_A;

	//A_PIN5の設定
	GPIO_Assign_A.Pin = GPIO_PIN_5;
	GPIO_Assign_A.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Assign_A.Speed = GPIO_SPEED_FREQ_LOW;

	//PIN5の設定を書き込み
	HAL_GPIO_Init(GPIOA,&GPIO_Assign_A);

	while(1){
		int push_state = 0;

		push_state = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13);

		if(push_state == 0){
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
		}else{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
		}

	}


}
