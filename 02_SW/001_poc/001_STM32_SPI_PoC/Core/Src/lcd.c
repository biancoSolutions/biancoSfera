/**
  ******************************************************************************
  * @file           : lcd.c
  * @brief          : LCD handling body
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

void LCD_Init(SPI_HandleTypeDef * spi_handler)
{
  //Start unlocking the EEProm
  uint8_t initFrequence[] = {0x38u, 0x38u, 0x38u, 0x38u, 0x08u, 0x01u, 0x06u, 0x0Fu};

  for (uint8_t i; i < sizeof(initFrequence); i++)
  {
    HAL_GPIO_WritePin(GPIOF, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(spi_handler, &initFrequence[i], 1, 10);
    HAL_GPIO_WritePin(GPIOF, LCD_CS_Pin, GPIO_PIN_SET);
    HAL_Delay(10);
  }
}
