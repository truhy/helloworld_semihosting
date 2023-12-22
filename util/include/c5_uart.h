/*
	MIT License

	Copyright (c) 2023 Truong Hy

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

	Version: 20231126

	UART functions for Cyclone V SoC (HPS).
*/

#ifndef C5_UART_H
#define C5_UART_H

#include "c5_util.h"
#include <stdint.h>

// UART base registers
#define C5_UART0_BASE_ADDR         0xffc02000UL
// UART register offsets
#define C5_UART_RBR_THR_DLL_OFFSET 0x0UL
#define C5_UART_LSR_OFFSET         0x14UL
#define C5_UART_SFE_OFFSET         0x98UL
#define C5_UART_STET_OFFSET        0xa0UL
// UART0 registers
#define C5_UART0_RBR_THR_DLL_ADDR  0xffc02000UL
#define C5_UART0_LSR_ADDR          0xffc02014UL
#define C5_UART0_SFE_ADDR          0xffc02098UL
#define C5_UART0_STET_ADDR         0xffc020a0UL

void c5_uart_wait_empty(uint32_t uart_base_addr);
void c5_uart_write_str(uint32_t uart_base_addr, const char *str, uint32_t len);
void c5_uart_write_char(uint32_t uart_base_addr, const char c);

#endif
