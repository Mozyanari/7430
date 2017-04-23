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

//UART1��Handle�\���̐���
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
	//�V�X�e���̏�����
	SystemInit();
	//HAL���C�u�������g�����߂̏������֐�
	HAL_Init();

/************************************************************
 * �N���b�N����
*************************************************************/

	//�N���b�N����
	//USART�̋@�\�ɃN���b�N����
	__HAL_RCC_USART1_CLK_ENABLE();
	//GPIO_B�ɃN���b�N����
	__HAL_RCC_GPIOB_CLK_ENABLE();

	__HAL_RCC_PWR_CLK_ENABLE();

/************************************************************
 * GPIO�ݒ�
*************************************************************/
	//PinAssign
	//GPIO_B�̍\���̐���
	GPIO_InitTypeDef GPIO_Assign_B;

	//PB6��UART1_TX�ɐݒ肷��
	//PB��ݒ�
	GPIO_Assign_B.Pin = GPIO_PIN_6;
	//���͂ɂ���
	GPIO_Assign_B.Mode = GPIO_MODE_AF_PP;
	//�v���A�b�v�C�v���_�E���Ȃ�
	GPIO_Assign_B.Pull = GPIO_NOPULL;
	//2Mhz�̔������x
	GPIO_Assign_B.Speed = GPIO_SPEED_FREQ_LOW;
	//USART1��PB6(Tx)��PB7(Rx)�Ŏg��
	GPIO_Assign_B.Alternate = GPIO_AF7_USART1;

	//UART1�̐ݒ����������
	HAL_GPIO_Init(GPIOB,&GPIO_Assign_B);

/************************************************************
 * UART1�ݒ�
*************************************************************/
	//UART1Config
	//UART1�̐ݒ�\���̐���
	USART_InitTypeDef USART1_Config;

	//�{�[�g���[�g��38400
	USART1_Config.BaudRate = 38400;
	//���M�̂ݎg�p
	USART1_Config.Mode = UART_MODE_TX;
	//8bit�ʐM
	USART1_Config.WordLength = UART_WORDLENGTH_8B;
	//�X�g�b�v�r�b�g��1
	USART1_Config.StopBits = UART_STOPBITS_1;
	//�p���e�B�Ȃ�
	USART1_Config.Parity = UART_PARITY_NONE;

	//CLKPolarity,CLKPhase,CLKLastBit��CLK�̐ݒ�͂킩��񂯂ǓK���ɐݒ�
	//�ɐ���LOW��
	USART1_Config.CLKPolarity = USART_POLARITY_LOW;
	//�G�b�W��1��
	USART1_Config.CLKPhase = USART_PHASE_1EDGE;
	//Lastbit�͎g��Ȃ�
	USART1_Config.CLKLastBit = USART_LASTBIT_DISABLE;




	//Handle�̒l�ݒ�
	//�C���X�^���X����
	UART1_Handle_Config.Instance = USART1;
	//Handle��Config��o�^
	UART1_Handle_Config.Init = USART1_Config;

	//UART1�̏�����
	HAL_USART_Init(&UART1_Handle_Config);

/************************************************************
 * L�`�J�ݒ�
*************************************************************/
	//�N���b�N����
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	//GPIO.C��������
	//�\���̐���
	GPIO_InitTypeDef GPIO_Assign_C;

	//C_PIN13�̐ݒ�
	GPIO_Assign_C.Pin = GPIO_PIN_13;
	GPIO_Assign_C.Mode = GPIO_MODE_INPUT;
	GPIO_Assign_C.Pull = GPIO_PULLUP;
	GPIO_Assign_C.Speed = GPIO_SPEED_FREQ_LOW;

	//PIN13�̐ݒ����������
	HAL_GPIO_Init(GPIOC,&GPIO_Assign_C);

	//GPIO.A��������
	//�\���̂�������
	GPIO_InitTypeDef GPIO_Assign_A;

	//A_PIN5�̐ݒ�
	GPIO_Assign_A.Pin = GPIO_PIN_5;
	GPIO_Assign_A.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Assign_A.Speed = GPIO_SPEED_FREQ_LOW;

	//PIN5�̐ݒ����������
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
