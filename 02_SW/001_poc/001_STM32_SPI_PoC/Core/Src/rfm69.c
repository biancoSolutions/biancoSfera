/*
 * rfm69.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Kreuter
 */

#include "rfm69.h"

#include "rfm69_registers.h"
#include "gpio.h"
#include "spi.h"


/*
 * Function:  RFM69_Init
 * --------------------
 * Initializes the RFM69 Chip.
 *
 *
 *  freqBand: TODO
 *
 *  nodeID: Sets the nodeID
 *
 *  networkID: Sets the networkID
 *
 */
void RFM69_Init(uint8_t freqBand, uint8_t nodeID, uint8_t networkID){
	HAL_Delay(100);
	int test = chipPresent(&hspi1);
}


/*
 * Function:  chipPresent
 * --------------------
 * Checks if the RFM69 Chip is present on the chosen SPI Interface.
 * Sets the green LED when the chip is present.
 * Sets the red LED when the chip is not present.
 *
 *  spi_handler: Pointer to the chosen SPI Interface
 *
 *  returns: 	1 if no Chip is found
 *  			0 if a RFM69 Chip is found
 */
uint8_t chipPresent(SPI_HandleTypeDef * spi_handler){
	uint8_t return_status = 1;

	writeREG(spi_handler, REG_SYNCVALUE1, 0xAA);
	HAL_Delay(100);

	if (readREG(spi_handler, REG_SYNCVALUE1) == 0xAA){
		writeREG(spi_handler, REG_SYNCVALUE1, 0x55);
		HAL_Delay(100);

		if (readREG(spi_handler, REG_SYNCVALUE1) == 0x55){
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
			return_status = 0;

			return return_status;
		}
		else{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);

			return return_status;
		}
	}
	else{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);

		return return_status;
	}
}

/*
 * Function:  writeREG
 * --------------------
 * Writes a Message to the RFM69 Chip over the chosen Interface.
 *
 *
 *  spi_handler: [PTR] Pointer to the chosen SPI Interface
 *
 *  addr: [HEX] The Address to write to (See RFM69registers.h for predefined values)
 *
 *  value: [HEX] The Value
 */
void writeREG(SPI_HandleTypeDef * spi_handler, uint8_t addr, uint8_t value){
	HAL_Delay(100);
	// & 0x80 to set the 7th Bit to 1 (write)
	HAL_SPI_Transmit(&hspi1, &addr, 1, 100);
	HAL_SPI_Transmit(spi_handler, &value, 1, 100);
}

/*
 * Function:  readREG
 * --------------------
 * Writes a Message to the RFM69 Chip over the chosen Interface.
 *
 *
 *  spi_handler: [PTR] Pointer to the chosen SPI Interface
 *
 *  addr: [HEX] The Address to write to (See RFM69registers.h for predefined values)
 *
 *  returns: The value of the register addr.
 */
HAL_StatusTypeDef readREG(SPI_HandleTypeDef * spi_handler, uint8_t addr){
	HAL_Delay(100);
	HAL_StatusTypeDef value;
	// & 0x7F to set the 7th Bit to 0 (read)
	HAL_SPI_TransmitReceive(spi_handler, &addr, &value, 1, 100);

	return value;
}
