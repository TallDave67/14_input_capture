/*
 * uart.h
 *
 *  Created on: 11 Dec 2021
 *      Author: bellisd
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

void uart2_rxtx_init(void);
void uart2_tx_init(void);

char uart2_read();

#endif /* UART_H_ */
