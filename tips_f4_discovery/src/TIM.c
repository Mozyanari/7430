// ----------------------------------------------------------------------------
/**
 * @file	TIM.c
 * @brief	Configure Advanced-control timers (TIM1 & TIM8) and General-purpose timers(TIM2 to TIM5 & TIM9 to TIM14)
 * @author	Kensuke Ota
 * @date	2016/12/19
 */
// ----------------------------------------------------------------------------

#include "TIM.h"

// ----------------------------------------------------------------------------

TIM_HandleTypeDef 	TIM1_HandleStructure,TIM2_HandleStructure,TIM3_HandleStructure,TIM4_HandleStructure,TIM5_HandleStructure;
TIM_HandleTypeDef	TIM8_HandleStructure,TIM9_HandleStructure,TIM10_HandleStructure,TIM11_HandleStructure,TIM13_HandleStructure,TIM14_HandleStructure;

TIM_OC_InitTypeDef	TIM2_OCInitStructure[2],TIM3_OCInitStructure[2],TIM8_OCInitStructure[4],TIM9_OCInitStructure[2],TIM10_OCInitStructure,TIM11_OCInitStructure,TIM13_OCInitStructure,TIM14_OCInitStructure;

// ----------------------------------------------------------------------------

/**
 * @brief	Configure TIM
 * @detail	Encoder use TIM1 & 4 & 5
 * 			PWM use TIM2 & 3 & 8 & 9 & 10 & 11 & 13 & 14
 */
void
TIM_Param_Config(void)
{
	/*Configure the TIM in the desired functioning mode using one of the initialization
	function of this driver*/


	TIM_Base_InitTypeDef 	TIM_PWM_BaseStructure,TIM_Encoder_BaseStructure;

	TIM_PWM_BaseStructure.Prescaler = 0;							//the prescaler value used to divide the TIM clock. Min_Data = 0x0000U and Max_Data = 0xFFFFU
	TIM_PWM_BaseStructure.CounterMode = TIM_COUNTERMODE_UP;			//the counter mode
	TIM_PWM_BaseStructure.Period = 320;								//the period value to be loaded into the active Auto-Reload Register at the next update event.Min_Data = 0x0000U and Max_Data = 0xFFFF.
	TIM_PWM_BaseStructure.ClockDivision = TIM_CLOCKDIVISION_DIV1;	//the clock division
	TIM_PWM_BaseStructure.RepetitionCounter = 0;					//the repetition counter value. Update event is generated and counting restarts from the RCR value.Min_Data = 0x00 and Max_Data = 0xFF

	TIM_Encoder_BaseStructure.Prescaler = 0;							//the prescaler value used to divide the TIM clock. Min_Data = 0x0000U and Max_Data = 0xFFFFU
	TIM_Encoder_BaseStructure.CounterMode = TIM_COUNTERMODE_UP;			//the counter mode
	TIM_Encoder_BaseStructure.Period = 0xFFFF;							//the period value to be loaded into the active Auto-Reload Register at the next update event.Min_Data = 0x0000U and Max_Data = 0xFFFF.
	TIM_Encoder_BaseStructure.ClockDivision = TIM_CLOCKDIVISION_DIV1;	//the clock division
	TIM_Encoder_BaseStructure.RepetitionCounter = 0;					//the repetition counter value. Update event is generated and counting restarts from the RCR value.Min_Data = 0x00 and Max_Data = 0xFF


	TIM1_HandleStructure.Init = TIM_Encoder_BaseStructure;	//TIM Time Base required parameters
	TIM1_HandleStructure.Instance = TIM1;					//Register base address

	TIM2_HandleStructure.Init = TIM_PWM_BaseStructure;
	TIM2_HandleStructure.Instance = TIM2;

	TIM3_HandleStructure.Init = TIM_PWM_BaseStructure;
	TIM3_HandleStructure.Instance = TIM3;

	TIM4_HandleStructure.Init = TIM_Encoder_BaseStructure;
	TIM4_HandleStructure.Instance = TIM4;

	TIM5_HandleStructure.Init = TIM_Encoder_BaseStructure;
	TIM5_HandleStructure.Instance = TIM5;

	TIM8_HandleStructure.Init = TIM_PWM_BaseStructure;
	TIM8_HandleStructure.Instance = TIM8;

	TIM9_HandleStructure.Init = TIM_PWM_BaseStructure;
	TIM9_HandleStructure.Instance = TIM9;

	TIM10_HandleStructure.Init = TIM_PWM_BaseStructure;
	TIM10_HandleStructure.Instance = TIM10;

	TIM11_HandleStructure.Init = TIM_PWM_BaseStructure;
	TIM11_HandleStructure.Instance = TIM11;

	TIM13_HandleStructure.Init = TIM_PWM_BaseStructure;
	TIM13_HandleStructure.Instance = TIM13;

	TIM14_HandleStructure.Init = TIM_PWM_BaseStructure;
	TIM14_HandleStructure.Instance = TIM14;

	HAL_TIM_PWM_Init(&TIM2_HandleStructure);
	HAL_TIM_PWM_Init(&TIM3_HandleStructure);
	HAL_TIM_PWM_Init(&TIM8_HandleStructure);
	HAL_TIM_PWM_Init(&TIM9_HandleStructure);
	HAL_TIM_PWM_Init(&TIM10_HandleStructure);
	HAL_TIM_PWM_Init(&TIM11_HandleStructure);
	HAL_TIM_PWM_Init(&TIM13_HandleStructure);
	HAL_TIM_PWM_Init(&TIM14_HandleStructure);


	TIM_Encoder_InitTypeDef TIM_Encoder_InitStructure;

	TIM_Encoder_InitStructure.EncoderMode = TIM_ENCODERMODE_TI12;
	TIM_Encoder_InitStructure.IC1Polarity = TIM_ICPOLARITY_RISING;
	TIM_Encoder_InitStructure.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	TIM_Encoder_InitStructure.IC1Prescaler = TIM_ICPSC_DIV1;
	TIM_Encoder_InitStructure.IC1Filter = 0;
	TIM_Encoder_InitStructure.IC2Polarity = TIM_ICPOLARITY_RISING;
	TIM_Encoder_InitStructure.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	TIM_Encoder_InitStructure.IC2Prescaler = TIM_ICPSC_DIV1;
	TIM_Encoder_InitStructure.IC2Filter = 0;

	HAL_TIM_Encoder_Init(&TIM1_HandleStructure,&TIM_Encoder_InitStructure);
	HAL_TIM_Encoder_Init(&TIM4_HandleStructure,&TIM_Encoder_InitStructure);
	HAL_TIM_Encoder_Init(&TIM5_HandleStructure,&TIM_Encoder_InitStructure);


	TIM2_OCInitStructure[0].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM2_OCInitStructure[0].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM2_OCInitStructure[0].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM2_OCInitStructure[0].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM2_OCInitStructure[0].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM2_OCInitStructure[0].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM2_OCInitStructure[0].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM2_OCInitStructure[1].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM2_OCInitStructure[1].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM2_OCInitStructure[1].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM2_OCInitStructure[1].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM2_OCInitStructure[1].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM2_OCInitStructure[1].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM2_OCInitStructure[1].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM3_OCInitStructure[0].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM3_OCInitStructure[0].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM3_OCInitStructure[0].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM3_OCInitStructure[0].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM3_OCInitStructure[0].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM3_OCInitStructure[0].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM3_OCInitStructure[0].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM3_OCInitStructure[1].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM3_OCInitStructure[1].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM3_OCInitStructure[1].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM3_OCInitStructure[1].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM3_OCInitStructure[1].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM3_OCInitStructure[1].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM3_OCInitStructure[1].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM8_OCInitStructure[0].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM8_OCInitStructure[0].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM8_OCInitStructure[0].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM8_OCInitStructure[0].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM8_OCInitStructure[0].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM8_OCInitStructure[0].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM8_OCInitStructure[0].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM8_OCInitStructure[1].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM8_OCInitStructure[1].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM8_OCInitStructure[1].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM8_OCInitStructure[1].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM8_OCInitStructure[1].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM8_OCInitStructure[1].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM8_OCInitStructure[1].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM8_OCInitStructure[2].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM8_OCInitStructure[2].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM8_OCInitStructure[2].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM8_OCInitStructure[2].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM8_OCInitStructure[2].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM8_OCInitStructure[2].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM8_OCInitStructure[2].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM8_OCInitStructure[3].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM8_OCInitStructure[3].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM8_OCInitStructure[3].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM8_OCInitStructure[3].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM8_OCInitStructure[3].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM8_OCInitStructure[3].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM8_OCInitStructure[3].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM9_OCInitStructure[0].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM9_OCInitStructure[0].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM9_OCInitStructure[0].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM9_OCInitStructure[0].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM9_OCInitStructure[0].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM9_OCInitStructure[0].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM9_OCInitStructure[0].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM9_OCInitStructure[1].OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM9_OCInitStructure[1].OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM9_OCInitStructure[1].Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM9_OCInitStructure[1].OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM9_OCInitStructure[1].OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM9_OCInitStructure[1].OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM9_OCInitStructure[1].OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM10_OCInitStructure.OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM10_OCInitStructure.OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM10_OCInitStructure.Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM10_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM10_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM10_OCInitStructure.OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM10_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM11_OCInitStructure.OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM11_OCInitStructure.OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM11_OCInitStructure.Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM11_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM11_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM11_OCInitStructure.OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM11_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM13_OCInitStructure.OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM13_OCInitStructure.OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM13_OCInitStructure.Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM13_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM13_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM13_OCInitStructure.OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM13_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	TIM14_OCInitStructure.OCMode = TIM_OCMODE_PWM1;			//the TIM mode. PWM_Mode1
	TIM14_OCInitStructure.OCFastMode = TIM_OCFAST_ENABLE;		//TIM Output Fast State
	TIM14_OCInitStructure.Pulse = 160;						//the pulse value to be loaded into the Capture Compare Register
	TIM14_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;	//the output polarity
	TIM14_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;	//the TIM Output Compare pin state during Idle state
	TIM14_OCInitStructure.OCNPolarity = TIM_OCPOLARITY_HIGH;
	TIM14_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_RESET;


	/*Initializes the TIM PWM channels according to the specified
	parameters in the TIM_OC_InitTypeDef*/

	HAL_TIM_PWM_ConfigChannel(&TIM2_HandleStructure,&TIM2_OCInitStructure[0],TIM_CHANNEL_3);
	HAL_TIM_PWM_ConfigChannel(&TIM2_HandleStructure,&TIM2_OCInitStructure[1],TIM_CHANNEL_4);

	HAL_TIM_PWM_ConfigChannel(&TIM3_HandleStructure,&TIM3_OCInitStructure[0],TIM_CHANNEL_3);
	HAL_TIM_PWM_ConfigChannel(&TIM3_HandleStructure,&TIM3_OCInitStructure[1],TIM_CHANNEL_4);

	HAL_TIM_PWM_ConfigChannel(&TIM8_HandleStructure,&TIM8_OCInitStructure[0],TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel(&TIM8_HandleStructure,&TIM8_OCInitStructure[1],TIM_CHANNEL_2);
	HAL_TIM_PWM_ConfigChannel(&TIM8_HandleStructure,&TIM8_OCInitStructure[2],TIM_CHANNEL_3);
	HAL_TIM_PWM_ConfigChannel(&TIM8_HandleStructure,&TIM8_OCInitStructure[3],TIM_CHANNEL_4);

	HAL_TIM_PWM_ConfigChannel(&TIM9_HandleStructure,&TIM9_OCInitStructure[0],TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel(&TIM9_HandleStructure,&TIM9_OCInitStructure[1],TIM_CHANNEL_2);

	HAL_TIM_PWM_ConfigChannel(&TIM10_HandleStructure,&TIM10_OCInitStructure,TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&TIM11_HandleStructure,&TIM11_OCInitStructure,TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&TIM13_HandleStructure,&TIM13_OCInitStructure,TIM_CHANNEL_1);

	HAL_TIM_PWM_ConfigChannel(&TIM14_HandleStructure,&TIM14_OCInitStructure,TIM_CHANNEL_1);

}


/**
 * @brief	Start PWM
 */
void
TIM_OC_Start(void)
{
	/*Activate the TIM peripheral using one of the start functions depending from the
	feature used*/

	HAL_TIM_Base_Start(&TIM2_HandleStructure);
	HAL_TIM_Base_Start(&TIM3_HandleStructure);
	HAL_TIM_Base_Start(&TIM8_HandleStructure);
	HAL_TIM_Base_Start(&TIM9_HandleStructure);
	HAL_TIM_Base_Start(&TIM10_HandleStructure);
	HAL_TIM_Base_Start(&TIM11_HandleStructure);
	HAL_TIM_Base_Start(&TIM13_HandleStructure);
	HAL_TIM_Base_Start(&TIM14_HandleStructure);


	HAL_TIM_PWM_Start(&TIM2_HandleStructure,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&TIM2_HandleStructure,TIM_CHANNEL_4);

	HAL_TIM_PWM_Start(&TIM3_HandleStructure,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&TIM3_HandleStructure,TIM_CHANNEL_4);

	HAL_TIM_PWM_Start(&TIM8_HandleStructure,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM8_HandleStructure,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&TIM8_HandleStructure,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&TIM8_HandleStructure,TIM_CHANNEL_4);

	HAL_TIM_PWM_Start(&TIM9_HandleStructure,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM9_HandleStructure,TIM_CHANNEL_2);

	HAL_TIM_PWM_Start(&TIM10_HandleStructure,TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&TIM11_HandleStructure,TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&TIM13_HandleStructure,TIM_CHANNEL_1);

	HAL_TIM_PWM_Start(&TIM14_HandleStructure,TIM_CHANNEL_1);

}


/**
 * @brief	Start to read encoder
 */
void
TIM_Encoder_Start(void)
{
	HAL_TIM_Base_Start(&TIM1_HandleStructure);
	HAL_TIM_Base_Start(&TIM4_HandleStructure);
	HAL_TIM_Base_Start(&TIM5_HandleStructure);

	HAL_TIM_Encoder_Start(&TIM1_HandleStructure,TIM_CHANNEL_3);
	HAL_TIM_Encoder_Start(&TIM1_HandleStructure,TIM_CHANNEL_4);

	HAL_TIM_Encoder_Start(&TIM4_HandleStructure,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&TIM4_HandleStructure,TIM_CHANNEL_2);

	HAL_TIM_Encoder_Start(&TIM5_HandleStructure,TIM_CHANNEL_3);
	HAL_TIM_Encoder_Start(&TIM5_HandleStructure,TIM_CHANNEL_4);

}


/**
 * @brief	Read Counter of TIM1
 * @return	Value of Encoder
 */
uint32_t
TIM1_Encoder_Read(void){
	return TIM1 ->CNT;
}


/**
 * @brief	Read Counter of TIM4
 * @return	Value of Encoder
 */
uint32_t
TIM4_Encoder_Read(void){
	return TIM4 -> CNT;
}


/**
 * @brief	Read Counter of TIM5
 * @return	Value of Encoder
 */
uint32_t
TIM5_Encoder_Read(void){
	return TIM5 -> CNT;
}


/**
 * @brief	Clear all value of encoder
 */
void
Encoder_Clear(void){
	TIM1 -> CNT = 32767;
	TIM4 -> CNT = 32767;
	TIM5 -> CNT = 32767;
}
// ----------------------------------------------------------------------------
