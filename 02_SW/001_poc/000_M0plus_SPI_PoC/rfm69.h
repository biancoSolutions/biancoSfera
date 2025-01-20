/*
 * rfm69.h
 *
 *  Created on: Jan 17, 2025
 *      Author: Jan Weiﬂ
 */

#ifndef INC_RFM69_H_
#define INC_RFM69_H_

#define ACTIVE_IRQ				0b01000100			// 0x28 Register ? FifoNotEmpty & PayloadReady

void RFM69_Init(uint8_t nodeID, uint8_t networkID);

uint8_t RFM69_Receiver_Mode();
uint8_t RFM69_Listen();

uint8_t chipPresent();
void writeREG(uint8_t addr, uint8_t value);
uint8_t readREG(uint8_t addr);


#endif /* INC_RFM69_H_ */