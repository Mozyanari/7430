// ----------------------------------------------------------------------------
/**
 * @file	main.c
 * @brief	main file
 * @author	Kensuke Ota
 * @date	2016/12/19
 */
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"
#include "ADC.h"
#include "USART.h"
#include "SPI.h"

// ----------------------------------------------------------------------------

#define	Kp	0.2
#define	Ki	0
#define	Kd	0.001

// ----------------------------------------------------------------------------

uint32_t Encoder1,Encoder2,Encoder3;

int stick_right_left = 0;
int stick_up_down = 0;
double horizon = 0;
double vertical = 0;

int left_r = 0,right_r = 0;
double radian = 0;

float omuni_speed1,omuni_speed2,omuni_speed3;

//pid
int total_enc_count = 0;

int differential_enc_count = 0;

int integral_enc_count = 0;

int pid_value;

int rotation_total_enc_count = 0,rotation_integral_enc_count = 0;

int old_rotation_total_enc_count = 0;

int throw = 0,throw_left = 0,throw_right = 0;

int push = 0,push_motor = 0;

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
	SystemInit();

	HAL_Init();

	//RCC_Config();

	GPIO_Port_Config();

	TIM_Param_Config();
	Encoder_Clear();

	ADC_Param_Config();
	ADC_DMA_Config();

	USART_Param_Config();

	SPI_Param_Config();

	TIM_OC_Start();

	TIM_Encoder_Start();

	ADC_Start();
	ADC_DMA_Start();

	timer_start();

  // Infinite loop
	while (1)
	{
		//極座標変換
		stick_right_left = (ps3buff.left_analog_rightleft-64)*2;	//右が126左が-128
		stick_up_down = -(ps3buff.left_analog_updown-64)*2;			//上が128下が-126

		//horizon = -(ps3buff.right_analog_rightleft-64)*2;			//右が-126左が128
		//vertical = -(ps3buff.right_analog_updown-64)*2;				//上が128下が-126

		//rを求める
		left_r = sqrt(pow(stick_right_left,2)+pow(stick_up_down,2));		//r = √x^2+y^2
		if(left_r>127){
			left_r=127;						//アナログパッド補正
		}
		if(left_r < 20){
			stick_right_left = 0;
			stick_up_down = 0;
		}

		//right_r = sqrt(pow(horizon,2)+pow(vertical,2));		//r = √x^2+y^2
		/*if(right_r>127){
			right_r=127;						//アナログパッド補正
		}

		//角度(ラジアン)を求める
		if(right_r > 20){
			if((vertical > 0) && (horizon == 0)){
				radian = 0;					//0度
			}else if((vertical < 0) && (horizon == 0)){
				radian = 3.142;					//180度
			}else if((vertical == 0) && (horizon > 0)){
				radian = 1.571;					//90度
			}else if((vertical == 0) && (horizon < 0)){
				radian = -1.571;				//-90度
			}else{
				radian = atan2(horizon,vertical);		//それ以外の角度
			}
		}*/

		if(ps3buff.L1 == 1){
			radian += 0.01;
			if(radian >= 3.142) push_motor = 3.142;
		}
		if(ps3buff.R1 == 1){
			radian -= 0.01;
			if(push_motor <= -3.142) push_motor = -3.142;
		}

		omuni_speed1 = -stick_right_left;
		omuni_speed2 = -stick_right_left * cos(M_PI*2/3)  - stick_up_down * sin(M_PI*2/3);
		omuni_speed3 = stick_right_left * cos(M_PI/3) + stick_up_down * sin(M_PI/3);

		Encoder1 = TIM1_Encoder_Read();
		Encoder2 = TIM4_Encoder_Read();
		Encoder3 = TIM5_Encoder_Read();

		Encoder1 = 32767 - Encoder1;
		Encoder2 = 32767 - Encoder2;
		Encoder3 = Encoder3 - 32767;

		differential_enc_count = Encoder1 + Encoder2 + Encoder3;

		total_enc_count += differential_enc_count;

		rotation_total_enc_count = total_enc_count - (radian * 156 * 586.789 / M_PI / 125);
		//rotation_total_enc_count = total_enc_count;
		rotation_integral_enc_count += rotation_total_enc_count;

		//differential_enc_count = rotation_total_enc_count - old_rotation_total_enc_count;

		pid_value = Kp * rotation_total_enc_count + Ki * rotation_integral_enc_count + Kd * differential_enc_count;

		//old_rotation_total_enc_count = rotation_total_enc_count;

		omuni_speed1 = omuni_speed1 -  pid_value;
		omuni_speed2 = omuni_speed2 -  pid_value;
		omuni_speed3 = omuni_speed3 -  pid_value;

		TIM9_OCInitStructure[0].Pulse = 160 + (omuni_speed1 / 128 * 150 ) / 2 ;
		TIM9_OCInitStructure[1].Pulse = 160 - (omuni_speed1 / 128 * 150 ) / 2 ;
		TIM3_OCInitStructure[0].Pulse = 160 + (omuni_speed2 / 128 * 150 ) / 2 ;
		TIM3_OCInitStructure[1].Pulse = 160 - (omuni_speed2 / 128 * 150 ) / 2 ;
		TIM2_OCInitStructure[0].Pulse = 160 + (omuni_speed3 / 128 * 150 ) / 2 ;
		TIM2_OCInitStructure[1].Pulse = 160 - (omuni_speed3 / 128 * 150 ) / 2 ;

		HAL_TIM_PWM_ConfigChannel(&TIM9_HandleStructure,&TIM9_OCInitStructure[0],TIM_CHANNEL_1);
		HAL_TIM_PWM_ConfigChannel(&TIM9_HandleStructure,&TIM9_OCInitStructure[1],TIM_CHANNEL_2);
		HAL_TIM_PWM_ConfigChannel(&TIM3_HandleStructure,&TIM3_OCInitStructure[0],TIM_CHANNEL_3);
		HAL_TIM_PWM_ConfigChannel(&TIM3_HandleStructure,&TIM3_OCInitStructure[1],TIM_CHANNEL_4);
		HAL_TIM_PWM_ConfigChannel(&TIM2_HandleStructure,&TIM2_OCInitStructure[0],TIM_CHANNEL_3);
		HAL_TIM_PWM_ConfigChannel(&TIM2_HandleStructure,&TIM2_OCInitStructure[1],TIM_CHANNEL_4);

		switch(throw){
			case 0:	if(ps3buff.start == 1){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET);
						throw++;
					}
					break;
			case 1:	if(ps3buff.start == 0){
						throw++;
					}
					break;
			case 2:	if(ps3buff.R2 == 1){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_SET);
						throw++;
					}
					break;
			case 3:	if(ps3buff.R2 == 0){
						throw++;
					}
					break;
			case 4:	if(ps3buff.start == 1){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET);
						throw++;
					}
					break;
			case 5:	if(ps3buff.start == 0){
						throw++;
					}
					break;
			case 6:	if(ps3buff.shikaku == 1){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);
						throw_left = 1;
					}
					if(ps3buff.maru == 1){
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_RESET);
						throw_right = 1;
					}
					if(throw_left == 1 && throw_right == 1){
						throw_left = 0;
						throw_right = 0;
						throw = 0;
					}
					break;
		}

		if(ps3buff.up == 1){
			push_motor += 5;
			if(push_motor >= 70) push_motor = 70;
		}
		if(ps3buff.down == 1){
			push_motor -= 5;
			if(push_motor <= -70) push_motor = -70;
		}
		if(ps3buff.up == 0 && ps3buff.down == 0){
			push_motor = 0;
		}
		TIM13_OCInitStructure.Pulse = 160 + push_motor;
		TIM14_OCInitStructure.Pulse = 160 - push_motor;
		HAL_TIM_PWM_ConfigChannel(&TIM13_HandleStructure,&TIM13_OCInitStructure,TIM_CHANNEL_1);
		HAL_TIM_PWM_ConfigChannel(&TIM14_HandleStructure,&TIM14_OCInitStructure,TIM_CHANNEL_1);


		switch(push){
			case 0:
				if(ps3buff.sankaku == 1){
					TIM8_OCInitStructure[2].Pulse = 160 + 150;
					TIM8_OCInitStructure[3].Pulse = 160 - 150;
					HAL_TIM_PWM_ConfigChannel(&TIM8_HandleStructure,&TIM8_OCInitStructure[2],TIM_CHANNEL_3);
					HAL_TIM_PWM_ConfigChannel(&TIM8_HandleStructure,&TIM8_OCInitStructure[3],TIM_CHANNEL_4);
					push++;
				}
				break;
			case 1:
				if(ps3buff.sankaku == 0)	push++;
				break;
			case 2:
				if(HAL_GPIO_ReadPin (GPIOC,GPIO_PIN_3) == GPIO_PIN_RESET){
					TIM8_OCInitStructure[2].Pulse = 160;
					TIM8_OCInitStructure[3].Pulse = 160;
					HAL_TIM_PWM_ConfigChannel(&TIM8_HandleStructure,&TIM8_OCInitStructure[2],TIM_CHANNEL_3);
					HAL_TIM_PWM_ConfigChannel(&TIM8_HandleStructure,&TIM8_OCInitStructure[3],TIM_CHANNEL_4);
					push = 0;
				}
				break;
		}


		TIM_OC_Start();

		//uart3_printf("SPI2: %u  \n\r",SPI2_RX_Data);
		uart3_printf("Encoder1; %d Encoder2: %d Encoder3: %d total: %d \n\r",Encoder1, Encoder2, Encoder3, total_enc_count);
		//uart3_printf("radian: %d \n\r",radian);
		//uart3_printf("Encoder1: %d  percentage: %d \n\r",Encoder1,percentage);
		//uart3_printf("stick_right_left: %d stick_up_down: %d \n\r",stick_right_left,stick_up_down,ps3buff);
		//uart3_printf("AD1: %u \n\r",ADCBuffer[0]);

		Encoder_Clear();

	}
  // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
