// ----------------------------------------------------------------------------
/**
 * @file	GPIO.c
 * @brief	Configure the General Purpose IO (GPIO) Ports
 * @author	Kensuke Ota
 * @date	2016/12/19
 */
// ----------------------------------------------------------------------------

#include "GPIO.h"

// ----------------------------------------------------------------------------

GPIO_InitTypeDef 	GPIOA_InitStructure,GPIOB_InitStructure,GPIOC_InitStructure,GPIOD_InitStructure,GPIOE_InitStructure;

// ----------------------------------------------------------------------------

void
GPIO_Port_Config()
{
  // Enable Peripheral clock

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	__HAL_RCC_TIM1_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();
	__HAL_RCC_TIM5_CLK_ENABLE();
	__HAL_RCC_TIM8_CLK_ENABLE();
	__HAL_RCC_TIM9_CLK_ENABLE();
	__HAL_RCC_TIM10_CLK_ENABLE();
	__HAL_RCC_TIM11_CLK_ENABLE();
	__HAL_RCC_TIM13_CLK_ENABLE();
	__HAL_RCC_TIM14_CLK_ENABLE();

	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_ADC2_CLK_ENABLE();
	__HAL_RCC_ADC3_CLK_ENABLE();

	__HAL_RCC_USART3_CLK_ENABLE();

	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_SPI3_CLK_ENABLE();

	__HAL_RCC_DMA1_CLK_ENABLE();
	__HAL_RCC_DMA2_CLK_ENABLE();

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  // pins configuration

	GPIOA_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;	//TIM5 ch1 & ch2
	GPIOA_InitStructure.Mode = GPIO_MODE_AF_PP;			//Alternate Function Push Pull Mode
	GPIOA_InitStructure.Speed = GPIO_SPEED_FAST;		//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOA_InitStructure.Pull = GPIO_NOPULL;				//No Pull-up or Pull-down activation
	GPIOA_InitStructure.Alternate = GPIO_AF2_TIM5;		//Alternate Function is TIM5

	HAL_GPIO_Init(GPIOA, &GPIOA_InitStructure);

	GPIOA_InitStructure.Pin = GPIO_PIN_6 ;			//TIM13 ch1
	GPIOA_InitStructure.Mode = GPIO_MODE_AF_PP;		//Alternate Function Push Pull Mode
	GPIOA_InitStructure.Speed = GPIO_SPEED_FAST;	//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOA_InitStructure.Pull = GPIO_NOPULL;			//No Pull-up or Pull-down activation
	GPIOA_InitStructure.Alternate = GPIO_AF9_TIM13;	//Alternate Function is TIM13

	HAL_GPIO_Init(GPIOA, &GPIOA_InitStructure);

	GPIOA_InitStructure.Pin = GPIO_PIN_7 ;			//TIM14 ch1
	GPIOA_InitStructure.Mode = GPIO_MODE_AF_PP;		//Alternate Function Push Pull Mode
	GPIOA_InitStructure.Speed = GPIO_SPEED_FAST;	//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOA_InitStructure.Pull = GPIO_NOPULL;			//No Pull-up or Pull-down activation
	GPIOA_InitStructure.Alternate = GPIO_AF9_TIM14;	//Alternate Function is TIM14

	HAL_GPIO_Init(GPIOA, &GPIOA_InitStructure);

	GPIOA_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_15;
	GPIOA_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;									//Output Push Pull Mode
	GPIOA_InitStructure.Speed = GPIO_SPEED_FAST;									//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOA_InitStructure.Pull = GPIO_NOPULL;											//No Pull-up or Pull-down activation

	HAL_GPIO_Init(GPIOA, &GPIOA_InitStructure);

	GPIOB_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;		//TIM3 ch3 & ch4
	GPIOB_InitStructure.Mode = GPIO_MODE_AF_PP;				//Alternate Function Push Pull Mode
	GPIOB_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOB_InitStructure.Pull = GPIO_NOPULL;					//No Pull-up or Pull-down activation
	GPIOB_InitStructure.Alternate = GPIO_AF2_TIM3;			//Alternate Function is TIM3

	HAL_GPIO_Init(GPIOB, &GPIOB_InitStructure);

	GPIOB_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;		//SPI3 SCK & MISO & MOSI
	GPIOB_InitStructure.Mode = GPIO_MODE_AF_PP;							//Alternate Function Push Pull Mode
	GPIOB_InitStructure.Speed = GPIO_SPEED_FAST;						//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOB_InitStructure.Pull = GPIO_NOPULL;								//No Pull-up or Pull-down activation
	GPIOB_InitStructure.Alternate = GPIO_AF6_SPI3;						//Alternate Function is SPI3

	HAL_GPIO_Init(GPIOB, &GPIOB_InitStructure);

	GPIOB_InitStructure.Pin = GPIO_PIN_7;
	GPIOB_InitStructure.Mode = GPIO_MODE_INPUT;				//Input Floating Mode
	GPIOB_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOB_InitStructure.Pull = GPIO_PULLDOWN;				//Pull-down activation

	HAL_GPIO_Init(GPIOB, &GPIOB_InitStructure);

	GPIOB_InitStructure.Pin = GPIO_PIN_8;			//TIM10 ch1
	GPIOB_InitStructure.Mode = GPIO_MODE_AF_PP;		//Alternate Function Push Pull Mode
	GPIOB_InitStructure.Speed = GPIO_SPEED_FAST;	//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOB_InitStructure.Pull = GPIO_NOPULL;			//No Pull-up or Pull-down activation
	GPIOB_InitStructure.Alternate = GPIO_AF3_TIM10;	//Alternate Function is TIM10

	HAL_GPIO_Init(GPIOB, &GPIOB_InitStructure);

	GPIOB_InitStructure.Pin = GPIO_PIN_9;			//TIM11 ch1
	GPIOB_InitStructure.Mode = GPIO_MODE_AF_PP;		//Alternate Function Push Pull Mode
	GPIOB_InitStructure.Speed = GPIO_SPEED_FAST;	//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOB_InitStructure.Pull = GPIO_NOPULL;			//No Pull-up or Pull-down activation
	GPIOB_InitStructure.Alternate = GPIO_AF3_TIM11;	//Alternate Function is TIM11

	HAL_GPIO_Init(GPIOB, &GPIOB_InitStructure);

	GPIOB_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11;	//TIM2 ch3 & ch4
	GPIOB_InitStructure.Mode = GPIO_MODE_AF_PP;				//Alternate Function Push Pull Mode
	GPIOB_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOB_InitStructure.Pull = GPIO_NOPULL;					//No Pull-up or Pull-down activation
	GPIOB_InitStructure.Alternate = GPIO_AF1_TIM2;			//Alternate Function is TIM2

	HAL_GPIO_Init(GPIOB, &GPIOB_InitStructure);

	GPIOB_InitStructure.Pin = GPIO_PIN_12;					//SPI2 CS(Chip Select)
	GPIOB_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Push Pull Mode
	GPIOB_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOB_InitStructure.Pull = GPIO_PULLDOWN;				//Pull-down activation

	HAL_GPIO_Init(GPIOB, &GPIOB_InitStructure);

	GPIOB_InitStructure.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;	//SPI2 SCK & MISO & MOSI
	GPIOB_InitStructure.Mode = GPIO_MODE_AF_PP;							//Alternate Function Push Pull Mode
	GPIOB_InitStructure.Speed = GPIO_SPEED_FAST;						//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOB_InitStructure.Pull =  GPIO_NOPULL;							//No Pull-up or Pull-down activation
	GPIOB_InitStructure.Alternate = GPIO_AF5_SPI2;						//Alternate Function is SPI2

	HAL_GPIO_Init(GPIOB, &GPIOB_InitStructure);

	GPIOC_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;					//ADC123 IN10 & IN11 & IN12
	GPIOC_InitStructure.Mode = GPIO_MODE_ANALOG;									//Analog Mode
	GPIOC_InitStructure.Speed = GPIO_SPEED_FAST;									//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOC_InitStructure.Pull = GPIO_NOPULL;											//No Pull-up or Pull-down activation

	HAL_GPIO_Init(GPIOC, &GPIOC_InitStructure);

	GPIOC_InitStructure.Pin = GPIO_PIN_3;
	GPIOC_InitStructure.Mode = GPIO_MODE_INPUT;								//Input Floating Mode
	GPIOC_InitStructure.Speed = GPIO_SPEED_FAST;							//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOC_InitStructure.Pull = GPIO_NOPULL;									//No Pull-up or Pull-down activation

	HAL_GPIO_Init(GPIOC, &GPIOC_InitStructure);

	GPIOC_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;	//TIM8 ch1 & ch2 & ch3 & ch4
	GPIOC_InitStructure.Mode = GPIO_MODE_AF_PP;										//Alternate Function Push Pull Mode
	GPIOC_InitStructure.Speed = GPIO_SPEED_FAST;									//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOC_InitStructure.Pull = GPIO_NOPULL;											//No Pull-up or Pull-down activation
	GPIOC_InitStructure.Alternate = GPIO_AF3_TIM8;									//Alternate Function is TIM8

	HAL_GPIO_Init(GPIOC, &GPIOC_InitStructure);

	GPIOC_InitStructure.Pin = GPIO_PIN_10;				//UART3_TX
	GPIOC_InitStructure.Mode = GPIO_MODE_AF_PP;			//Alternate Function Push Pull Mode
	GPIOC_InitStructure.Speed = GPIO_SPEED_FAST;		//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOC_InitStructure.Pull = GPIO_NOPULL;				//No Pull-up or Pull-down activation
	GPIOC_InitStructure.Alternate = GPIO_AF7_USART3;	//Alternate Function is USART3

	HAL_GPIO_Init(GPIOC, &GPIOC_InitStructure);

	GPIOC_InitStructure.Pin = GPIO_PIN_11 | GPIO_PIN_12;
	GPIOC_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Push Pull Mode
	GPIOC_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOC_InitStructure.Pull = GPIO_NOPULL;					//No Pull-up or Pull-down activation

	HAL_GPIO_Init(GPIOC, &GPIOC_InitStructure);

	GPIOD_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_7;
	GPIOD_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Push Pull Mode
	GPIOD_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOD_InitStructure.Pull = GPIO_NOPULL;					//No Pull-up or Pull-down activation

	HAL_GPIO_Init(GPIOD, &GPIOD_InitStructure);

	GPIOD_InitStructure.Pin = GPIO_PIN_6 ;
	GPIOD_InitStructure.Mode = GPIO_MODE_INPUT;				//Input Floating Mode
	GPIOD_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOD_InitStructure.Pull = GPIO_PULLDOWN;				//Pull-down activation

	HAL_GPIO_Init(GPIOD, &GPIOD_InitStructure);

	GPIOD_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13;	//TIM4 ch1 & ch2
	GPIOD_InitStructure.Mode = GPIO_MODE_AF_PP;				//Alternate Function Push Pull Mode
	GPIOD_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOD_InitStructure.Pull = GPIO_NOPULL;					//No Pull-up or Pull-down activation
	GPIOD_InitStructure.Alternate = GPIO_AF2_TIM4;			//Alternate Function is TIM3

	HAL_GPIO_Init(GPIOD, &GPIOD_InitStructure);

	GPIOE_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;
	GPIOE_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Push Pull Mode
	GPIOE_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOE_InitStructure.Pull = GPIO_NOPULL;					//No Pull-up or Pull-down activation

	HAL_GPIO_Init(GPIOE, &GPIOE_InitStructure);

	GPIOE_InitStructure.Pin = GPIO_PIN_5 | GPIO_PIN_6;	//TIM9 ch1 & ch2
	GPIOE_InitStructure.Mode = GPIO_MODE_AF_PP;			//Alternate Function Push Pull Mode
	GPIOE_InitStructure.Speed = GPIO_SPEED_FAST;		//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOE_InitStructure.Pull = GPIO_NOPULL;				//No Pull-up or Pull-down activation
	GPIOE_InitStructure.Alternate = GPIO_AF3_TIM9;		//Alternate Function is TIM9

	HAL_GPIO_Init(GPIOE, &GPIOE_InitStructure);

	GPIOE_InitStructure.Pin = GPIO_PIN_9 | GPIO_PIN_11;		//TIM1 ch1 & ch2
	GPIOE_InitStructure.Mode = GPIO_MODE_AF_PP;				//Alternate Function Push Pull Mode
	GPIOE_InitStructure.Speed = GPIO_SPEED_FAST;			//range 25 MHz to 100 MHz, please refer to the product datasheet
	GPIOE_InitStructure.Pull = GPIO_NOPULL;					//No Pull-up or Pull-down activation
	GPIOE_InitStructure.Alternate = GPIO_AF1_TIM1;			//Alternate Function is TIM1

	HAL_GPIO_Init(GPIOE, &GPIOE_InitStructure);

}


// ----------------------------------------------------------------------------
