// ----------------------------------------------------------------------------
/**
 * @file	USART.c
 * @brief	Configure USART3
 * 			Use UART for debug
 * @author	Kensuke Ota
 * @date	2016/12/19
 */
// ----------------------------------------------------------------------------

#include "USART.h"
#include <stdarg.h>
#include <stdlib.h>

// ----------------------------------------------------------------------------

USART_HandleTypeDef		USART_HandleStructure;

// ----------------------------------------------------------------------------
void
USART_Param_Config()
{
	USART_InitTypeDef		USART_InitStructure;

	USART_InitStructure.BaudRate = 38400;
	USART_InitStructure.WordLength = USART_WORDLENGTH_8B;
	USART_InitStructure.StopBits = USART_STOPBITS_1;
	USART_InitStructure.Parity = USART_PARITY_NONE;
	USART_InitStructure.Mode = USART_MODE_TX;
	USART_InitStructure.CLKPolarity = USART_POLARITY_LOW;
	USART_InitStructure.CLKPhase = USART_PHASE_1EDGE;
	USART_InitStructure.CLKLastBit = USART_LASTBIT_DISABLE;


	USART_HandleStructure.Instance = USART3;
	USART_HandleStructure.Init = USART_InitStructure;

	HAL_USART_Init(&USART_HandleStructure);

}

void
USART_DMA_Config(){

  // Configure Direct Memory Access

	DMA_InitTypeDef DMA_InitStructure;

	DMA_InitStructure.Channel = DMA_CHANNEL_4;
	DMA_InitStructure.Direction = DMA_PERIPH_TO_MEMORY;
	DMA_InitStructure.PeriphInc = DMA_MINC_DISABLE;
	DMA_InitStructure.MemInc = DMA_MINC_ENABLE;
	DMA_InitStructure.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	DMA_InitStructure.MemDataAlignment = DMA_MDATAALIGN_WORD;
	DMA_InitStructure.Mode = DMA_CIRCULAR;
	DMA_InitStructure.Priority = DMA_PRIORITY_HIGH;
	DMA_InitStructure.FIFOMode = DMA_FIFOMODE_DISABLE;
	DMA_InitStructure.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
	DMA_InitStructure.MemBurst = DMA_MBURST_SINGLE;
	DMA_InitStructure.PeriphBurst = DMA_PBURST_SINGLE;

	DMA_HandleTypeDef DMA1_HandleStructure;

	DMA1_HandleStructure.Init = DMA_InitStructure;
	DMA1_HandleStructure.Instance = DMA1_Stream3;

	HAL_DMA_Init(&DMA1_HandleStructure);

	__HAL_LINKDMA(&USART_HandleStructure,hdmatx ,DMA1_HandleStructure);
}


void
USART_puts(uint8_t USART_TX_data[]){

	int i;

	for(i=0;USART_TX_data[i]!='\0';i++){
		HAL_USART_Transmit(&USART_HandleStructure,&USART_TX_data[i],sizeof(USART_TX_data[i]),0x1000);
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


// ----------------------------------------------------------------------------
