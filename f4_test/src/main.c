/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "stm32f4xx_hal_uart.h"


int main(void)
{
	int PB_state = 0;

	//HAL���C�u�������g�����߂̏������֐�
	HAL_Init();
	//�{�[�h���LED2��L����
	BSP_LED_Init(LED2);
	//�{�[�h��̃{�^����L����
	BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);


	while(1){
		PB_state = BSP_PB_GetState(BUTTON_KEY);
		if(PB_state == 0){
			BSP_LED_On(LED2);
		}else{
			BSP_LED_Off(LED2);
		}
	}
}
