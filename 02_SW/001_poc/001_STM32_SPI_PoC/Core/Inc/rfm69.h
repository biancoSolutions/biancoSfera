/*
 * rfm69.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Kreuter
 */

#ifndef INC_RFM69_H_
#define INC_RFM69_H_

#include <stdint.h>
#include <stm32u5xx_hal.h>

void RFM69_Init(uint8_t freqBand, uint8_t nodeID, uint8_t networkID);
uint8_t chipPresent(SPI_HandleTypeDef * spi_handler);
void writeREG(SPI_HandleTypeDef * spi_handler, uint8_t addr, uint8_t value);
HAL_StatusTypeDef readREG(SPI_HandleTypeDef * spi_handler, uint8_t addr);


#endif /* INC_RFM69_H_ */
