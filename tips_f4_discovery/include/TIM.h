/* TIM.h */

// ----------------------------------------------------------------------------

#ifndef TIM_H_
#define TIM_H_

// ----------------------------------------------------------------------------

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// ----------------------------------------------------------------------------

extern
TIM_HandleTypeDef 	TIM1_HandleStructure,TIM2_HandleStructure,TIM3_HandleStructure,TIM4_HandleStructure,TIM5_HandleStructure;

extern
TIM_HandleTypeDef	TIM8_HandleStructure,TIM9_HandleStructure,TIM10_HandleStructure,TIM11_HandleStructure,TIM13_HandleStructure,TIM14_HandleStructure;

extern
TIM_OC_InitTypeDef	TIM2_OCInitStructure[2],TIM3_OCInitStructure[2],TIM8_OCInitStructure[4],TIM9_OCInitStructure[2],TIM10_OCInitStructure,TIM11_OCInitStructure,TIM13_OCInitStructure,TIM14_OCInitStructure;

// ----------------------------------------------------------------------------

extern
void
TIM_Param_Config(void);

extern
void
TIM_OC_Start(void);

extern
void
TIM_Encoder_Start(void);

extern
uint32_t
TIM1_Encoder_Read(void);

extern
uint32_t
TIM4_Encoder_Read(void);

extern
uint32_t
TIM5_Encoder_Read(void);

extern
void
Encoder_Clear(void);

// ----------------------------------------------------------------------------

#endif // TIM_H_
