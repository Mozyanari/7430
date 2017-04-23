/* USART.h */

// ----------------------------------------------------------------------------

#ifndef USART_H_
#define USART_H_

// ----------------------------------------------------------------------------

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// ----------------------------------------------------------------------------

extern
void
USART_Param_Config(void);

extern
void
USART_DMA_Config(void);

extern
void
USART_puts(uint8_t*);

extern
void
uart3_printf(const char* , ...);

// ----------------------------------------------------------------------------

#endif // USART_H_
