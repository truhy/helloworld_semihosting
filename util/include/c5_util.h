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

#ifndef C5_UTIL_H
#define C5_UTIL_H

#include <stdint.h>

// Support macros
#define C5_REG_TYPE uint32_t
#define C5_CAST(type, ptr) ((type)(ptr))
#define c5_io_rd_word(src_addr) (*C5_CAST(volatile C5_REG_TYPE *, (src_addr)))
#define c5_io_wr_word(dst_addr, src_addr) (*C5_CAST(volatile C5_REG_TYPE *, (dst_addr)) = (src_addr))

#endif
