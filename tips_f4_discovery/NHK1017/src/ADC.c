// ----------------------------------------------------------------------------
/**
 * @file	ADC.c
 * @brief	Configure Analog-to-Digital Converter (ADC) Ports
 * @author	Kensuke Ota
 * @date	2016/12/19
 */
// ----------------------------------------------------------------------------

#include "ADC.h"

// ----------------------------------------------------------------------------

ADC_HandleTypeDef ADC1_HandleSTructure;

uint32_t *ADCBuffer[4];

// ----------------------------------------------------------------------------

void
ADC_Param_Config()
{

  // Configure Analog to Digital Converter

	ADC_InitTypeDef ADC1_IintStructure;

	ADC1_IintStructure.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	ADC1_IintStructure.Resolution = ADC_RESOLUTION_12B;
	ADC1_IintStructure.DataAlign = ADC_DATAALIGN_RIGHT;
	ADC1_IintStructure.ScanConvMode = ENABLE;
	ADC1_IintStructure.ContinuousConvMode = ENABLE;
	ADC1_IintStructure.DiscontinuousConvMode = DISABLE;
	ADC1_IintStructure.NbrOfDiscConversion = 0;
	ADC1_IintStructure.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	ADC1_IintStructure.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	ADC1_IintStructure.NbrOfConversion = 4;
	ADC1_IintStructure.DMAContinuousRequests = ENABLE;
	ADC1_IintStructure.EOCSelection = DISABLE;

	ADC1_HandleSTructure.Init = ADC1_IintStructure;
	ADC1_HandleSTructure.Instance = ADC1;


	HAL_ADC_Init(&ADC1_HandleSTructure);


	ADC_ChannelConfTypeDef ADC1_IN10_ChannelConfStructure , ADC1_IN11_ChannelConfStructure , ADC2_IN12_ChannelConfStructure ;

	ADC1_IN10_ChannelConfStructure.Channel = ADC_CHANNEL_10 ;
	ADC1_IN10_ChannelConfStructure.Rank = 1;
	ADC1_IN10_ChannelConfStructure.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC1_IN10_ChannelConfStructure.Offset = 0;

	ADC1_IN11_ChannelConfStructure.Channel = ADC_CHANNEL_11 ;
	ADC1_IN11_ChannelConfStructure.Rank = 2;
	ADC1_IN11_ChannelConfStructure.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC1_IN11_ChannelConfStructure.Offset = 0;

	ADC2_IN12_ChannelConfStructure.Channel = ADC_CHANNEL_12 ;
	ADC2_IN12_ChannelConfStructure.Rank = 3;
	ADC2_IN12_ChannelConfStructure.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC2_IN12_ChannelConfStructure.Offset = 0;

	/*ADC3_IN13_ChannelConfStructure.Channel = ADC_CHANNEL_13 ;
	ADC3_IN13_ChannelConfStructure.Rank = 4;
	ADC3_IN13_ChannelConfStructure.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC3_IN13_ChannelConfStructure.Offset = 0;*/

	HAL_ADC_ConfigChannel(&ADC1_HandleSTructure,&ADC1_IN10_ChannelConfStructure);
	HAL_ADC_ConfigChannel(&ADC1_HandleSTructure,&ADC1_IN11_ChannelConfStructure);
	HAL_ADC_ConfigChannel(&ADC1_HandleSTructure,&ADC2_IN12_ChannelConfStructure);
	//HAL_ADC_ConfigChannel(&ADC1_HandleSTructure,&ADC3_IN13_ChannelConfStructure);

}


void
ADC_DMA_Config(){

  // Configure Direct Memory Access

	DMA_InitTypeDef DMA_InitStructure;

	DMA_InitStructure.Channel = DMA_CHANNEL_0;
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

	DMA_HandleTypeDef DMA2_HandleStructure;

	DMA2_HandleStructure.Init = DMA_InitStructure;
	DMA2_HandleStructure.Instance = DMA2_Stream0;

	HAL_DMA_Init(&DMA2_HandleStructure);

	__HAL_LINKDMA(&ADC1_HandleSTructure,DMA_Handle,DMA2_HandleStructure);
}


void
ADC_Start(){

	HAL_ADC_Start(&ADC1_HandleSTructure);

}

void
ADC_DMA_Start(){

	HAL_ADC_Start_DMA(&ADC1_HandleSTructure, ADCBuffer ,4);

}

uint32_t
ADC1_Read()
{

	uint32_t ADCValue;

	ADCValue = HAL_ADC_GetValue(&ADC1_HandleSTructure);

	return ADCValue;
}

// ----------------------------------------------------------------------------
