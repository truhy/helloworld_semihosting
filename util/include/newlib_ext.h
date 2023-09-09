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

	Version: 20230619

	Contains functions for some newlib stub functions to support the DE10-Nano
	development board.

	Contains mostly minimal implementation (fake return success or failure).
	Added in debug print to HPS UART0.
*/

#ifndef NEWLIB_EXT_H_
#define NEWLIB_EXT_H_

// Set the base address to the UART controller you want to use for the debug printf
#define TRU_PRINTF_UART_ADDR ALT_UART0_ADDR

#endif /* NEWLIB_EXT_H_ */
