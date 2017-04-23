// ----------------------------------------------------------------------------
/**
 * @file	SPI.c
 * @brief	Configure the SPI in master mode
 * @author	Kensuke Ota
 * @date	2016/12/19
 */
// ----------------------------------------------------------------------------

#include "SPI.h"

// ----------------------------------------------------------------------------

SPI_HandleTypeDef 	SPI2_HandleStructure,SPI3_HandleStructure;

DMA_HandleTypeDef SPI2_DMA1_RX_HandleStructure,SPI2_DMA1_TX_HandleStructure,SPI3_DMA1_RX_HandleStructure,SPI3_DMA1_TX_HandleStructure;

uint16_t SPI2_RX_Data,SPI2_TX_Data = 0x01, SPI3_RX_Data,SPI3_TX_Data = 0x02,data;

ps3 ps3buff = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,64,64,64};

// ----------------------------------------------------------------------------

void
SPI_Param_Config()
{
	SPI_InitTypeDef		SPI_InitStructure;

  /*Program the Mode, BidirectionalMode , Data size, Baudrate Prescaler, NSS
	management, Clock polarity and phase, FirstBit and CRC configuration in the Init structure.*/

	SPI_InitStructure.Mode = SPI_MODE_MASTER;						//the SPI operating mode.Master mode.
	SPI_InitStructure.Direction = SPI_DIRECTION_2LINES;				//the SPI bidirectional mode state.Lines are twice.
	SPI_InitStructure.DataSize = SPI_DATASIZE_16BIT;					//the SPI data size.
	SPI_InitStructure.CLKPolarity = SPI_POLARITY_HIGH;				//the serial clock steady state
	SPI_InitStructure.CLKPhase = SPI_PHASE_2EDGE;					//the clock active edge for the bit capture
	SPI_InitStructure.NSS = SPI_NSS_SOFT;							//whether the NSS signal is managed by software using the SSI bit.
	SPI_InitStructure.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;//the Baud Rate prescaler value which will be used to configure the transmit and receive SCK clock.
	SPI_InitStructure.FirstBit = SPI_FIRSTBIT_MSB;					//whether data transfers start from MSB or LSB bit. Usually, SPI use MSB First.
	SPI_InitStructure.TIMode = SPI_TIMODE_DISABLE;					//the TI mode is disabled
	SPI_InitStructure.CRCCalculation = SPI_CRCCALCULATION_DISABLE;	//the CRC calculation is enabled
	SPI_InitStructure.CRCPolynomial = 10;							//the polynomial used for the CRC calculation

	SPI2_HandleStructure.Instance = SPI2;
	SPI2_HandleStructure.Init = SPI_InitStructure;

	SPI3_HandleStructure.Instance = SPI3;
	SPI3_HandleStructure.Init = SPI_InitStructure;

  /*Initialize the SPI according to the specified parameters in the
	SPI_InitTypeDef and initialize the associated handle.*/

	HAL_SPI_Init (&SPI2_HandleStructure);
	HAL_SPI_Init (&SPI3_HandleStructure);

  /* SPI2 interrupt configuration */
	HAL_NVIC_SetPriorityGrouping (NVIC_PRIORITYGROUP_2);
	HAL_NVIC_SetPriority(SPI2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(SPI2_IRQn);
	__HAL_SPI_ENABLE_IT(&SPI2_HandleStructure,SPI_IT_RXNE);

  /* SPI3 interrupt configuration */
	HAL_NVIC_SetPriorityGrouping (NVIC_PRIORITYGROUP_2);
	HAL_NVIC_SetPriority(SPI3_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(SPI3_IRQn);
	__HAL_SPI_ENABLE_IT(&SPI3_HandleStructure,SPI_IT_RXNE);
}

void
SPI_DMA_Config(){

  // Configure Direct Memory Access

	DMA_InitTypeDef SPI2_DMA1_RX_InitStructure,SPI2_DMA1_TX_InitStructure,SPI3_DMA1_RX_InitStructure,SPI3_DMA1_TX_InitStructure;

	HAL_DMA_DeInit(&SPI2_DMA1_RX_HandleStructure);
	HAL_DMA_DeInit(&SPI2_DMA1_TX_HandleStructure);
	HAL_DMA_DeInit(&SPI3_DMA1_RX_HandleStructure);
	HAL_DMA_DeInit(&SPI3_DMA1_TX_HandleStructure);

	HAL_NVIC_DisableIRQ(DMA1_Stream2_IRQn);
	HAL_NVIC_DisableIRQ(DMA1_Stream3_IRQn);
	HAL_NVIC_DisableIRQ(DMA1_Stream4_IRQn);
	HAL_NVIC_DisableIRQ(DMA1_Stream5_IRQn);

	SPI2_DMA1_RX_InitStructure.Channel = DMA_CHANNEL_0;
	SPI2_DMA1_RX_InitStructure.Direction = DMA_PERIPH_TO_MEMORY;
	SPI2_DMA1_RX_InitStructure.PeriphInc = DMA_PINC_DISABLE;
	SPI2_DMA1_RX_InitStructure.MemInc = DMA_MINC_ENABLE;
	SPI2_DMA1_RX_InitStructure.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	SPI2_DMA1_RX_InitStructure.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	SPI2_DMA1_RX_InitStructure.Mode = DMA_CIRCULAR;
	SPI2_DMA1_RX_InitStructure.Priority = DMA_PRIORITY_HIGH;
	SPI2_DMA1_RX_InitStructure.FIFOMode = DMA_FIFOMODE_DISABLE;
	SPI2_DMA1_RX_InitStructure.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	SPI2_DMA1_RX_InitStructure.MemBurst = DMA_MBURST_SINGLE;
	SPI2_DMA1_RX_InitStructure.PeriphBurst = DMA_PBURST_SINGLE;

	SPI2_DMA1_TX_InitStructure.Channel = DMA_CHANNEL_0;
	SPI2_DMA1_TX_InitStructure.Direction = DMA_MEMORY_TO_PERIPH;
	SPI2_DMA1_TX_InitStructure.PeriphInc = DMA_PINC_DISABLE;
	SPI2_DMA1_TX_InitStructure.MemInc = DMA_MINC_ENABLE;
	SPI2_DMA1_TX_InitStructure.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	SPI2_DMA1_TX_InitStructure.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	SPI2_DMA1_TX_InitStructure.Mode =  DMA_CIRCULAR;
	SPI2_DMA1_TX_InitStructure.Priority = DMA_PRIORITY_HIGH;
	SPI2_DMA1_TX_InitStructure.FIFOMode = DMA_FIFOMODE_DISABLE;
	SPI2_DMA1_TX_InitStructure.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	SPI2_DMA1_TX_InitStructure.MemBurst = DMA_MBURST_SINGLE;
	SPI2_DMA1_TX_InitStructure.PeriphBurst = DMA_PBURST_SINGLE;

	SPI3_DMA1_RX_InitStructure.Channel = DMA_CHANNEL_0;
	SPI3_DMA1_RX_InitStructure.Direction = DMA_PERIPH_TO_MEMORY;
	SPI3_DMA1_RX_InitStructure.PeriphInc = DMA_PINC_DISABLE;
	SPI3_DMA1_RX_InitStructure.MemInc = DMA_MINC_ENABLE;
	SPI3_DMA1_RX_InitStructure.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	SPI3_DMA1_RX_InitStructure.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	SPI3_DMA1_RX_InitStructure.Mode = DMA_CIRCULAR;
	SPI3_DMA1_RX_InitStructure.Priority = DMA_PRIORITY_HIGH;
	SPI3_DMA1_RX_InitStructure.FIFOMode = DMA_FIFOMODE_DISABLE;
	SPI3_DMA1_RX_InitStructure.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	SPI3_DMA1_RX_InitStructure.MemBurst = DMA_MBURST_SINGLE;
	SPI3_DMA1_RX_InitStructure.PeriphBurst = DMA_PBURST_SINGLE;

	SPI3_DMA1_TX_InitStructure.Channel = DMA_CHANNEL_0;
	SPI3_DMA1_TX_InitStructure.Direction = DMA_MEMORY_TO_PERIPH;
	SPI3_DMA1_TX_InitStructure.PeriphInc = DMA_PINC_ENABLE;
	SPI3_DMA1_TX_InitStructure.MemInc = DMA_MINC_DISABLE;
	SPI3_DMA1_TX_InitStructure.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	SPI3_DMA1_TX_InitStructure.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	SPI3_DMA1_TX_InitStructure.Mode =  DMA_CIRCULAR;
	SPI3_DMA1_TX_InitStructure.Priority = DMA_PRIORITY_HIGH;
	SPI3_DMA1_TX_InitStructure.FIFOMode = DMA_FIFOMODE_DISABLE;
	SPI3_DMA1_TX_InitStructure.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	SPI3_DMA1_TX_InitStructure.MemBurst = DMA_MBURST_SINGLE;
	SPI3_DMA1_TX_InitStructure.PeriphBurst = DMA_PBURST_SINGLE;


	SPI2_DMA1_RX_HandleStructure.Init = SPI2_DMA1_RX_InitStructure;
	SPI2_DMA1_RX_HandleStructure.Instance = DMA1_Stream3;

	SPI2_DMA1_TX_HandleStructure.Init = SPI2_DMA1_TX_InitStructure;
	SPI2_DMA1_TX_HandleStructure.Instance = DMA1_Stream4;

	SPI2_DMA1_RX_HandleStructure.Init = SPI3_DMA1_RX_InitStructure;
	SPI2_DMA1_RX_HandleStructure.Instance = DMA1_Stream2;

	SPI2_DMA1_TX_HandleStructure.Init = SPI3_DMA1_TX_InitStructure;
	SPI2_DMA1_TX_HandleStructure.Instance = DMA1_Stream5;


	HAL_DMA_Init(&SPI2_DMA1_RX_HandleStructure);
	HAL_DMA_Init(&SPI2_DMA1_TX_HandleStructure);
	HAL_DMA_Init(&SPI3_DMA1_RX_HandleStructure);
	HAL_DMA_Init(&SPI3_DMA1_TX_HandleStructure);


	__HAL_DMA_ENABLE_IT(&SPI2_DMA1_RX_HandleStructure,DMA_IT_TC);
	__HAL_DMA_ENABLE_IT(&SPI2_DMA1_TX_HandleStructure,DMA_IT_TC);
	__HAL_DMA_ENABLE_IT(&SPI3_DMA1_RX_HandleStructure,DMA_IT_TC);
	__HAL_DMA_ENABLE_IT(&SPI3_DMA1_TX_HandleStructure,DMA_IT_TC);


	__HAL_LINKDMA(&SPI2_HandleStructure,hdmarx,SPI2_DMA1_RX_HandleStructure);
	__HAL_LINKDMA(&SPI2_HandleStructure,hdmatx,SPI2_DMA1_TX_HandleStructure);

	__HAL_LINKDMA(&SPI3_HandleStructure,hdmarx,SPI3_DMA1_RX_HandleStructure);
	__HAL_LINKDMA(&SPI3_HandleStructure,hdmatx,SPI3_DMA1_TX_HandleStructure);


  /* DMA1_Stream2_IRQn interrupt configuration */
	HAL_NVIC_SetPriorityGrouping (NVIC_PRIORITYGROUP_2);
	HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);

  /* DMA1_Stream3_IRQn interrupt configuration */
	HAL_NVIC_SetPriorityGrouping (NVIC_PRIORITYGROUP_2);
	HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

  /* DMA1_Stream4_IRQn interrupt configuration */
	HAL_NVIC_SetPriorityGrouping (NVIC_PRIORITYGROUP_2);
	HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

  /* DMA1_Stream5_IRQn interrupt configuration */
	HAL_NVIC_SetPriorityGrouping (NVIC_PRIORITYGROUP_2);
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 3);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);


	while(HAL_DMA_GetState(&SPI2_DMA1_RX_HandleStructure) == HAL_DMA_STATE_RESET);
	while(HAL_DMA_GetState(&SPI2_DMA1_TX_HandleStructure) == HAL_DMA_STATE_RESET);
	while(HAL_DMA_GetState(&SPI3_DMA1_RX_HandleStructure) == HAL_DMA_STATE_RESET);
	while(HAL_DMA_GetState(&SPI3_DMA1_TX_HandleStructure) == HAL_DMA_STATE_RESET);


}


HAL_StatusTypeDef
SPI2_Read(void){

	HAL_StatusTypeDef Status;

	Status = HAL_SPI_Receive(&SPI2_HandleStructure,(uint8_t *)&SPI2_RX_Data,sizeof(SPI2_RX_Data),0x1000);

	return Status;
}


HAL_StatusTypeDef
SPI3_Read(void){

	HAL_StatusTypeDef Status;

	Status = HAL_SPI_Receive(&SPI3_HandleStructure,(uint8_t *)&SPI3_RX_Data,sizeof(SPI3_RX_Data),0x1000);

	return Status;
}

/**
* @brief This function handles SPI2 global interrupt.
*/
void
SPI2_IRQHandler(void){

	HAL_SPI_IRQHandler(&SPI2_HandleStructure);

}

/**
* @brief This function handles SPI3 global interrupt.
*/
void
SPI3_IRQHandler(void){

	HAL_SPI_IRQHandler(&SPI3_HandleStructure);

}


void
HAL_SPI_TxRxCpltCallback (SPI_HandleTypeDef * hspi){

	if (hspi->Instance == SPI2_HandleStructure.Instance) {

		static char count = 0;

		//ボタンデータの先頭アドレスを確認
		if(SPI2_RX_Data & 32768){
			count = 0;
		}

		//データ代入
		//ボタンデータ代入
		if(count == 0){
			ps3buff.maru = SPI2_RX_Data & 1;
			ps3buff.batsu = (SPI2_RX_Data & 2) >> 1;
			ps3buff.sankaku = (SPI2_RX_Data & 4) >> 2;
			ps3buff.shikaku = (SPI2_RX_Data & 8) >> 3;

			ps3buff.right = (SPI2_RX_Data & 16) >> 4;
			ps3buff.down = (SPI2_RX_Data & 32) >> 5;
			ps3buff.up = (SPI2_RX_Data & 64) >> 6;
			ps3buff.left = (SPI2_RX_Data & 128) >> 7;

			ps3buff.R1 = (SPI2_RX_Data & 256) >> 8;
			ps3buff.R2 = (SPI2_RX_Data & 512) >> 9;
			ps3buff.L1 = (SPI2_RX_Data & 1024) >> 10;
			ps3buff.L2 = (SPI2_RX_Data & 2048) >> 11;

			ps3buff.start = (SPI2_RX_Data & 4096) >> 12;
			ps3buff.select = (SPI2_RX_Data & 8192) >> 13;
		}else if(count == 1){
			//右アナログデータ代入
			ps3buff.right_analog_rightleft = SPI2_RX_Data & 255;
			ps3buff.right_analog_updown = (SPI2_RX_Data & 65280) >> 8;
		}else if(count == 2){
			//左アナログデータ代入
			ps3buff.left_analog_rightleft = SPI2_RX_Data & 255;
			ps3buff.left_analog_updown = (SPI2_RX_Data & 65280) >> 8;
		}else{
			//受信エラー
			count = 0;
			PS3_buffclear();
		}

		count++;

	}
}


void
PS3_buffclear(void){

    ps3buff.up = 0;
    ps3buff.down = 0;
    ps3buff.right = 0;
    ps3buff.left = 0;
    ps3buff.sankaku = 0;
    ps3buff.batsu = 0;
    ps3buff.maru = 0;
    ps3buff.shikaku = 0;
    ps3buff.L1 = 0;
    ps3buff.L2 = 0;
    ps3buff.R1 = 0;
    ps3buff.R2 = 0;
    ps3buff.start = 0;
    ps3buff.select = 0;
    ps3buff.left_analog_rightleft = 64;
    ps3buff.left_analog_updown = 64;
    ps3buff.right_analog_rightleft = 64;
    ps3buff.right_analog_updown = 64;

}


void
PS3_datawait(void){
	while(1){

		if(ps3buff.up == 0 &&  ps3buff.down == 0 && ps3buff.right == 0 &&  ps3buff.left == 0 &&  ps3buff.sankaku == 0 &&  ps3buff.batsu == 0 &&  ps3buff.maru == 0 &&  ps3buff.shikaku == 0 &&  ps3buff.L1 == 0 && ps3buff.L2 == 0 && ps3buff.R1 == 0 && ps3buff.R2 == 0 && ps3buff.start == 0 && ps3buff.select == 0 && ps3buff.left_analog_rightleft == 64 && ps3buff.left_analog_updown == 64 && ps3buff.right_analog_rightleft == 64 && ps3buff.right_analog_updown == 64){
			break;
		}
	}
}
// ----------------------------------------------------------------------------
