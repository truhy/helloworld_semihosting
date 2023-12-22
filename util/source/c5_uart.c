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

#include "c5_uart.h"

/*
	Blocking wait on the transmit empty register to become empty.  It becomes
	empty when all pending data in the FIFO (FIFO mode) or holding register
	(non-FIFO mode) is transmitted.  This ensures all pending data has gone out.
*/
void c5_uart_wait_empty(uint32_t uart_base_addr){
	while((c5_io_rd_word(uart_base_addr + C5_UART_LSR_OFFSET) & 0x00000040) == 0);  // Flush UART and wait
}

void c5_uart_write_str(uint32_t uart_base_addr, const char *str, uint32_t len){
	// FIFO & threshold mode enabled?
	char fifo_th_en = (c5_io_rd_word(uart_base_addr + C5_UART_SFE_OFFSET) && c5_io_rd_word(uart_base_addr + C5_UART_STET_OFFSET)) ? 1 : 0;

	// Write input bytes to UART controller, one at a time
	for(uint32_t i = 0; i < len; i++){
		// Wait until the UART controller is ready to accept a byte in its transmit buffer, i.e. there is free space?
		// They are masochists - using the same bit but with the opposite logic depending on the mode set!
		if(fifo_th_en){
			while(c5_io_rd_word(uart_base_addr + C5_UART_LSR_OFFSET) & 0x00000020);  // Wait while not empty. Bit 5 of LSR reg (THRE bit), 1 = not empty, 0 = empty
		}else{
			while((c5_io_rd_word(uart_base_addr + C5_UART_LSR_OFFSET) & 0x00000020) == 0);  // Wait while not empty. Bit 5 of LSR reg (THRE bit), 0 = not empty, 1 = empty
		}

		// Write a single character to UART controller transmit holding register
		c5_io_wr_word(uart_base_addr + C5_UART_RBR_THR_DLL_OFFSET, str[i]);
	}
}

void c5_uart_write_char(uint32_t uart_base_addr, const char c){
	// FIFO & threshold mode enabled?
	char fifo_th_en = (c5_io_rd_word(uart_base_addr + C5_UART_SFE_OFFSET) && c5_io_rd_word(uart_base_addr + C5_UART_STET_OFFSET)) ? 1 : 0;

	// Wait until the UART controller is ready to accept a byte in its transmit buffer, i.e. there is free space?
	// They are masochists - using the same bit but with the opposite logic depending on the mode set!
	if(fifo_th_en){
		while(c5_io_rd_word(uart_base_addr + C5_UART_LSR_OFFSET) & 0x00000020);  // Wait while not empty. Bit 5 of LSR reg (THRE bit), 1 = not empty, 0 = empty
	}else{
		while((c5_io_rd_word(uart_base_addr + C5_UART_LSR_OFFSET) & 0x00000020) == 0);  // Wait while not empty. Bit 5 of LSR reg (THRE bit), 0 = not empty, 1 = empty
	}

	// Write a single character to UART controller transmit holding register
	c5_io_wr_word(uart_base_addr + C5_UART_RBR_THR_DLL_OFFSET, c);
}
