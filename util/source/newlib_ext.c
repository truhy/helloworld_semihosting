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

	Version: 20240202
*/
#include <errno.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include "newlib_ext.h"
#ifdef TRU_PRINTF_UART
	#include "c5_uart.h"
#endif

#ifdef SEMIHOSTING
	// ======================================
	// Minimal implementation for Semihosting
	// ======================================

	int _kill(int pid, int sig){
		errno = ENOSYS;  // Function not implemented
		return -1;
	}
#else
	// Process ID
	#define __MYPID 1U

	#ifdef TRU_PRINTF_UART
		// ==========================================================================================
		// Minimal implementation for a serial terminal (TTY) device based on newlib/libgloss sources
		// ==========================================================================================

		int _close(int fd){
			return 0;  // Pretend to close
		}

		int _fstat(int fd, struct stat *buf){
			buf->st_mode = S_IFCHR;   // Pretend to be a TTY
			buf->st_blksize = 0;
			return 0;
		}

		int _isatty(int fd){
			return 1;  // Pretend to be a TTY
		}

		int _lseek(int fd, int ptr, int dir){
			errno = ESPIPE;  // Invalid seek
			return (ptr - 1);  // TTY is not seekable, return error
		}

		int _read(int fd, char *ptr, int len){
			errno = EIO;  // Input/output error
			return -1;  // Too complicated to implement read for TTY, return error
		}

		int _write(int fd, char *ptr, int len){
			c5_uart_write_str(C5_UART0_BASE_ADDR, ptr, len);  // Re-target to UART controller
			return len;
		}
	#else
		// ==============================================================================
		// Minimal implementation for no system based on newlib/libgloss/libnosys sources
		// ==============================================================================

		int _close(int fd){
			errno = ENOSYS;  // Function not implemented
			return -1;
		}

		int _fstat(int fd, struct stat *buf){
			errno = ENOSYS;  // Function not implemented
			return 1;
		}

		int _isatty(int fd){
			errno = ENOSYS;  // Function not implemented
			return 0;
		}

		int _lseek(int fd, int ptr, int dir){
			errno = ENOSYS;  // Function not implemented
			return -1;
		}

		int _read(int fd, char *ptr, int len){
			errno = ENOSYS;  // Function not implemented
			return -1;
		}

		int _write(int fd, char *ptr, int len){
			errno = ENOSYS;  // Function not implemented
			return -1;
		}
	#endif

	int _getpid(){
		return __MYPID;
	}

	int _kill(int pid, int sig){
		if(pid == __MYPID) _exit(sig);
		return 0;
	}
#endif
