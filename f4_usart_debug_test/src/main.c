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
#include "stm32f4xx_hal_usart.h"
#include "stm32f4xx_hal_gpio.h"

#include <stdarg.h>
#include <stdlib.h>

//UART1のHandle構造体生成
USART_HandleTypeDef UART1_Handle_Config;

void
USART_puts(uint8_t USART_TX_data[]){

	int i;

	for(i=0;USART_TX_data[i]!='\0';i++){
		HAL_USART_Transmit(&UART1_Handle_Config,&USART_TX_data[i],sizeof(USART_TX_data[i]),0x1000);
	}

}


void uart3_printf(const char *format, ...) {

	va_list list;

	va_start(list, format);

	int len = vsnprintf(0, 0, format, list);
	char *s;

	s = (char *)malloc(len + 1);
	vsprintf(s, format, list);

	USART_puts(s);

	free(s);

	va_end(list);

	return;
}

			

int main(void)
{
	//システムの初期化
	SystemInit();
	//HALライブラリを使うための初期化関数
	HAL_Init();

/************************************************************
 * クロック生成
*************************************************************/

	//クロック供給
	//USARTの機能にクロック供給
	__HAL_RCC_USART1_CLK_ENABLE();
	//GPIO_Bにクロック供給
	__HAL_RCC_GPIOB_CLK_ENABLE();

/************************************************************
 * GPIO設定
*************************************************************/
	//PinAssign
	//GPIO_Bの構造体生成
	GPIO_InitTypeDef GPIO_Assign_B;

	//PB6をUART1_TXに設定する
	//PBを設定
	GPIO_Assign_B.Pin = GPIO_PIN_6;
	//入力にする
	GPIO_Assign_B.Mode = GPIO_MODE_AF_PP;
	//プルアップ，プルダウンなし
	GPIO_Assign_B.Pull = GPIO_NOPULL;
	//2Mhzの反応速度
	GPIO_Assign_B.Speed = GPIO_SPEED_FREQ_LOW;
	//USART1をPB6(Tx)とPB7(Rx)で使う
	GPIO_Assign_B.Alternate = GPIO_AF7_USART1;

	//UART1の設定を書き込み
	HAL_GPIO_Init(GPIOB,&GPIO_Assign_B);

/************************************************************
 * UART1設定
*************************************************************/
	//UART1Config
	//UART1の設定構造体生成
	USART_InitTypeDef USART1_Config;

	//ボートレートは38400
	USART1_Config.BaudRate = 38400;
	//送信のみ使用
	USART1_Config.Mode = UART_MODE_TX;
	//8bit通信
	USART1_Config.WordLength = UART_WORDLENGTH_8B;
	//ストップビットは1
	USART1_Config.StopBits = UART_STOPBITS_1;
	//パリティなし
	USART1_Config.Parity = UART_PARITY_NONE;

	//CLKPolarity,CLKPhase,CLKLastBitはCLKの設定はわからんけど適当に設定
	//極性をLOWに
	USART1_Config.CLKPolarity = USART_POLARITY_LOW;
	//エッジは1で
	USART1_Config.CLKPhase = USART_PHASE_1EDGE;
	//Lastbitは使わない
	USART1_Config.CLKLastBit = USART_LASTBIT_DISABLE;




	//Handleの値設定
	//インスタンス生成
	UART1_Handle_Config.Instance = USART1;
	//HandleにConfigを登録
	UART1_Handle_Config.Init = USART1_Config;

	//UART1の初期化
	HAL_USART_Init(&UART1_Handle_Config);

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
		uart3_printf("Hello");
		//HAL_USART_Transmit(&UART1_Handle_Config,"Hello",sizeof("Hello"),1000);

	}

}
