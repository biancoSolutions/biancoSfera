/*
 * rfm69.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Kreuter
 */

#ifndef INC_RFM69_H_
#define INC_RFM69_H_

void RFM69_Init(uint8_t freqBand, uint8_t nodeID, uint8_t networkID);
void writeREG(SPI_HandleTypeDef * spi_handler, uint8_t addr, uint8_t value);
uint8_t readREG(SPI_HandleTypeDef * spi_handler, uint8_t addr);
int chipPresent(SPI_HandleTypeDef * spi_handler);

#endif /* INC_RFM69_H_ */
