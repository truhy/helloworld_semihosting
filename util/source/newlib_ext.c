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

	Version: 20231201
*/
#include <errno.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include "newlib_ext.h"
#ifdef TRU_PRINTF_UART
	#include "c5_uart.h"
#endif

#ifndef SEMIHOSTING
	int _close(int file){
	  return -1;
	}

	int _fstat(int file, struct stat *st){
	  st->st_mode = S_IFCHR;
	  return 0;
	}

	int _getpid(){
		return -1;
	}

	/*
		Minimal implementation.
		Query whether output stream is a terminal.
	*/
	int _isatty(int file){
		switch (file){
			case STDOUT_FILENO:
			case STDERR_FILENO:
			case STDIN_FILENO:
				return 1;
			default:
				//errno = ENOTTY;
				errno = EBADF;
				return 0;
		}
	}

	int _lseek(int file, int ptr, int dir){
		return 0;
	}

	int _read(int file, char *ptr, int len){
		errno = EBADF;
		return -1;
	}

	/*
		Minimal implementation.
		Re-target depending on compiler define.
	*/
	int _write(int file, char *ptr, int len){
		#ifdef TRU_PRINTF_UART
			// Re-target to UART controller

			// Not stdout?
			if(file != STDOUT_FILENO){
				// Return error
				errno = EBADF;
				return -1;
			}

			c5_uart_write_str(C5_UART0_BASE_ADDR, ptr, len);

			return len;
		#else
			errno = EBADF;
			return -1;
		#endif
	}
#endif

int _kill(int pid, int sig){
	errno = EINVAL;
	return -1;
}
