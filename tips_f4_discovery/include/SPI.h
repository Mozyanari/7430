/* SPI.h */

// ----------------------------------------------------------------------------

#ifndef SPI_H_
#define SPI_H_

// ----------------------------------------------------------------------------

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// ----------------------------------------------------------------------------

extern SPI_HandleTypeDef 	SPI2_HandleStructure,SPI3_HandleStructure;

extern uint16_t SPI2_RX_Data,SPI2_TX_Data,SPI3_RX_Data,SPI3_TX_Data;

typedef volatile struct ps3st {                      //ps3data格納
    char up;
    char down;
    char right;
    char left;
    char sankaku;
    char batsu;
    char maru;
    char shikaku;
    char L1;
    char L2;
    char R1;
    char R2;
    char start;
    char select;
    char right_analog_updown;
    char right_analog_rightleft;
    char left_analog_updown;
    char left_analog_rightleft;
}ps3;

extern ps3 ps3buff;

// ----------------------------------------------------------------------------

extern
void
SPI_Param_Config(void);

extern
void
SPI_DMA_Config(void);

extern
HAL_StatusTypeDef
SPI2_Read(void);

extern
HAL_StatusTypeDef
SPI3_Read(void);

extern
void
SPI2_IRQHandler(void);

extern
void
SPI3_IRQHandler(void);

extern
void
HAL_SPI_RxCpltCallback (SPI_HandleTypeDef * );

extern
void
PS3_buffclear(void);

extern
void
PS3_datawait(void);
// ----------------------------------------------------------------------------

#endif // SPI_H_
