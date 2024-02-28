/*
 * lcd1602.h
 *
 *  Created on: Feb 28, 2024
 *      Author: benja
 */

#ifndef INC_LCD1602_H_
#define INC_LCD1602_H_

#include <string.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/* delay timer rate macro */
#define DELAY_TIMER_RATE		42

/* lcd pin macros */
#define RS_PORT 				GPIOB
#define RS_PIN 					GPIO_PIN_7
//#define RW_PORT
//#define RW_PIN
#define E_PORT 					GPIOA
#define E_PIN 					GPIO_PIN_15
#define DB4_PORT 				GPIOA
#define DB4_PIN 				GPIO_PIN_4
#define DB5_PORT 				GPIOB
#define DB5_PIN 				GPIO_PIN_0
#define DB6_PORT 				GPIOC
#define DB6_PIN 				GPIO_PIN_1
#define DB7_PORT 				GPIOC
#define DB7_PIN 				GPIO_PIN_0

/* rs pin macros */
#define RS_CMD					0
#define RS_DATA					1

/* lcd functions */

//delays processor for specified number of us
void lcdDelayUs(uint16_t us);

//sends command
void lcdSendCommand(uint8_t cmd);

//sends data
void lcdSendData(uint8_t data);

//moves cursor to specified row and column
void lcdMoveCursor(uint8_t row, uint8_t column);

#endif /* INC_LCD1602_H_ */
