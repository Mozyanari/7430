// ----------------------------------------------------------------------------
/**
 * @file	RCC.c
 * @brief	Configure Reset and Clock Control
 * @author	Kensuke Ota
 * @date	2016/12/19
 */
// ----------------------------------------------------------------------------

#include "RCC.h"

// ----------------------------------------------------------------------------

void
RCC_Config()
{
	RCC_ClkInitTypeDef RCC_ClkInitStructure;
	RCC_OscInitTypeDef RCC_OscInitStructure;

	// Configure Reset and Clock Control
	RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSE;	//Oscillator is HSE(High Speed External) Clock
	RCC_OscInitStructure.HSEState = RCC_HSE_ON;						//turn ON the HSE oscillator
	RCC_OscInitStructure.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStructure.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStructure.PLL.PLLM = 8;
	RCC_OscInitStructure.PLL.PLLN = 336;
	RCC_OscInitStructure.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStructure.PLL.PLLQ = 6;
	HAL_RCC_OscConfig(&RCC_OscInitStructure);

	RCC_ClkInitStructure.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStructure.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStructure.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStructure.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStructure.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStructure, FLASH_LATENCY_4);

	SystemCoreClockUpdate();

}
