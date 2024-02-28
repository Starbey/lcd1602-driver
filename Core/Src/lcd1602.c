/*
 * lcd1602.c
 *
 *  Created on: Feb 28, 2024
 *      Author: benja
 */

#include "lcd1602.h"

extern TIM_HandleTypeDef htim10;

//sends data to LCD (local helper function)
void lcdSend(uint8_t data, uint8_t rs);

void lcdDelayUs(uint16_t us){
	__HAL_TIM_SET_COUNTER(&htim10, 0);
	while(__HAL_TIM_GET_COUNTER(&htim10) < (us * DELAY_TIMER_RATE) );
}

void lcdSend(uint8_t data, uint8_t rs){
	HAL_GPIO_WritePin(RS_PORT, RS_PIN, rs); //rs = 0 => cmd, rs = 1 => data

	HAL_GPIO_WritePin(DB7_PORT, DB7_PIN, ( (data >> 3) & 1 ) );
	HAL_GPIO_WritePin(DB6_PORT, DB6_PIN, ( (data >> 2) & 1 ) );
	HAL_GPIO_WritePin(DB5_PORT, DB5_PIN, ( (data >> 1) & 1 ) );
	HAL_GPIO_WritePin(DB7_PORT, DB4_PIN, ( (data >> 0) & 1 ) );

	//pulse e pin
	HAL_GPIO_WritePin(E_PORT, E_PIN, 1);
	lcdDelayUs(50);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 0);
	lcdDelayUs(50);
}

void lcdSendCommand(uint8_t cmd){
	/* we're in 4-bit mode, so send 4 MSBs, then send 4 LSBs */

	//send 4 MSBs
	lcdSend( (cmd >> 4) & 0x0f, RS_CMD );

	//send 4 LSBs
	lcdSend( (cmd >> 0) & 0x0f, RS_CMD );
}

void lcdSendData(uint8_t data){
	/* we're in 4-bit mode, so send 4 MSBs, then send 4 LSBs */

	//send 4 MSBs
	lcdSend( (data >> 4) & 0x0f, RS_DATA );

	//send 4 LSBs
	lcdSend( (data >> 0) & 0x0f, RS_DATA );
}

void lcdMoveCursor(uint8_t row, uint8_t col){
	uint8_t cellAddr; //corresponds to a cell's address in DDRAM

	switch(row){
	case 0:
		cellAddr = 0x80 | col;
		break;
	case 1:
		cellAddr = 0xA0 | col;
		break;
	}

	lcdSendCommand(cellAddr);
}