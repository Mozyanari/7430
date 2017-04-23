/* ADC.h */

// ----------------------------------------------------------------------------

#ifndef ADC_H_
#define ADC_H_

// ----------------------------------------------------------------------------

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// ----------------------------------------------------------------------------

extern uint32_t *ADCBuffer[4];

// ----------------------------------------------------------------------------

extern
void
ADC_Param_Config(void);

extern
void
ADC_DMA_Config(void);

extern
void
ADC_Start(void);

extern
void
ADC_DMA_Start(void);

extern
uint32_t
ADC1_Read(void);

// ----------------------------------------------------------------------------

#endif // ADC_H_
