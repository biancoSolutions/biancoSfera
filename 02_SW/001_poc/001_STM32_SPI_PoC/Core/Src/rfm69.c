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

#define CONFIG_LAST_ELEMENT 255
/*
 * Function:  RFM69_Init
 * --------------------
 * Initializes the RFM69 Chip.
 *
 *  nodeID: Sets the nodeID
 *
 *  networkID: Sets the networkID
 *
 */
void RFM69_Init(uint8_t nodeID, uint8_t networkID){
	const uint8_t CONFIG[][2] = {
			// Operating Mode -> Mode forced by user | Listen off -> required in standby | standby transceiver mode
			/* 0x01 */ { REG_OPMODE, RF_OPMODE_SEQUENCER_ON | RF_OPMODE_LISTEN_OFF | RF_OPMODE_STANDBY },
			// Data Mode -> packet mode | FSK modulation | no data shaping
			/* 0x02 */ { REG_DATAMODUL, RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_00 },
			// Bit Rate -> default is 4.8 kb/s
			/* 0x03 */ { REG_BITRATEMSB, RF_BITRATEMSB_4800 },
			/* 0x04 */ { REG_BITRATELSB, RF_BITRATELSB_4800 },
			// Frequency deviation -> default is 5 kHz
			/* 0x05 */ { REG_FDEVMSB, RF_FDEVMSB_50000 },
			/* 0x06 */ { REG_FDEVLSB, RF_FDEVLSB_50000 },
			// RF carrier frequency -> fixed to 868 MHz, everything else is not legal in Europe
			/* 0x07 */ { REG_FRFMSB, RF_FRFMSB_868 },
			/* 0x08 */ { REG_FRFMID, RF_FRFMID_868 },
			/* 0x09 */ { REG_FRFLSB, RF_FRFLSB_868 },
			// Enables the overload current protection for the power amplifier -> default is 95 mA
			/* 0x13 */ { REG_OCP, RF_OCP_ON | RF_OCP_TRIM_95 },
			// Cut-off frequency of the DC offset canceler (DCC) -> default is 4% | channel filter bandwidth control -> default is 24 (see data sheet)
			/* 0x19 */ { REG_RXBW, RF_RXBW_DCCFREQ_010 | RF_RXBW_MANT_24 | RF_RXBW_EXP_5 },
			// Activate DIO0 -> see table 21 in data sheet for reference
			/* 0x25 */ { REG_DIOMAPPING1, RF_DIOMAPPING1_DIO0_01 },
			// CLKOUT is turned off for power saving
			/* 0x26 */ { REG_DIOMAPPING2, RF_DIOMAPPING2_CLKOUT_OFF },
			// Set when FIFO overrun occurs. Flags and FIFO are cleared when bit is set (FIFO reset ?)
			/* 0x28 */ { REG_IRQFLAGS2, RF_IRQFLAGS2_FIFOOVERRUN },
			// RSSI trigger level for RSSI interrupt -> threshold / 2 dbM -> default is 0xE4 == 228
			/* 0x29 */ { REG_RSSITHRESH, 0XE4 },
			// Enables sync word generation & detection | sync address interrupt occurs | number of tolerated bit errors
			/* 0x2E */ { REG_SYNCCONFIG, RF_SYNC_ON | RF_SYNC_FIFOFILL_AUTO | RF_SYNC_SIZE_2 | RF_SYNC_TOL_0 },
			// TODO: check sync word byte of available / wanted networks
			/* 0x2F */ { REG_SYNCVALUE1, 0x2D },
			/* 0x30 */ { REG_SYNCVALUE2, networkID },
			// variable package length | DC free encoding is off | for starting CRC is turned off | for starting no address filtering is activated
			/* 0x37 */ { REG_PACKETCONFIG1, RF_PACKET1_FORMAT_VARIABLE | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_OFF | RF_PACKET1_ADRSFILTERING_OFF },
			// maximum payload length for RX (not used for TX) - only used in variable package format (0x37)
			/* 0x38 */ { REG_PAYLOADLENGTH, 0x55 },
			// Start transmission if at least on byte in FIFO | FIFO level interrupt trigger -> 0xF is default
			/* 0x3C */ { REG_FIFOTHRESH, RF_FIFOTHRESH_TXSTART_FIFONOTEMPTY | RF_FIFOTHRESH_VALUE },
			// Defines the delay between FIFO empty and start of new RSSI | No RX restart. -> RestartRX can be used | AES encryption turned off
			/* 0x3D */ { REG_PACKETCONFIG2, RF_PACKET2_RXRESTARTDELAY_2BITS | RF_PACKET2_AUTORXRESTART_OFF | RF_PACKET2_AES_OFF },
			/* 0xFF */ { CONFIG_LAST_ELEMENT, 0 }
	};

	HAL_Delay(100);
	uint8_t chip_select_status = chipPresent(&hspi1);

	// Wait for RFM69 module to come up, otherwise perform system reset
	if (chip_select_status == 0u) {
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		NVIC_SystemReset();
	}

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
			return_status = 0;

			return return_status;
		}
		else{

			return return_status;
		}
	}
	else{

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
	uint8_t write_addr = addr | 0x80;

	HAL_Delay(100);

	HAL_GPIO_WritePin(GPIOF, LCD_CS_Pin, GPIO_PIN_RESET);

	// & 0x80 to set the 7th Bit to 1 (write)
	HAL_SPI_Transmit(spi_handler, &write_addr, 1, 100);
	HAL_SPI_Transmit(spi_handler, &value, 1, 100);

	HAL_GPIO_WritePin(GPIOF, LCD_CS_Pin, GPIO_PIN_SET);
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
uint8_t readREG(SPI_HandleTypeDef * spi_handler, uint8_t addr){
	uint8_t read_addr = addr & 0x7F;
	uint8_t value;

	HAL_Delay(100);

	HAL_GPIO_WritePin(GPIOF, LCD_CS_Pin, GPIO_PIN_RESET);

	// & 0x7F to set the 7th Bit to 0 (read)
	HAL_SPI_Transmit(spi_handler, &read_addr, 1, 100);
	HAL_SPI_Receive(spi_handler, &value, 1, 100);

	HAL_GPIO_WritePin(GPIOF, LCD_CS_Pin, GPIO_PIN_SET);

	return value;
}
