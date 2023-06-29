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

	Version: 20230319
	Target: Arm Cortex A9 on the DE10-Nano development board

	A simple semihosting "Hello, World!" bare-metal C program for the DE10-
	Nano development board.  It demonstrates the use of semihosting debug
	features which enables your program to send and receive debug messages
	through the debug adapter and console.

	Noticed that I've used fgets which is now deprecated, but the semihosting
	library doesn't support the getline at this time.  Anyway, semihosting code
	will never get into the production/release version so really it doesn't
	matter at all.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef SEMIHOSTING
	extern void initialise_monitor_handles(void);  // Reference function header from the external Semihosting library
#endif

void semihosting_test(){
	// Test Semihosting printf displaying a message to the debugger console
	printf("Hello, World!\n");

	// Test Semihosting fgets getting an input from the debugger console
	char buffer[255];
	printf("Let's do an input test\n");
	printf("Enter a number then press enter: ");
	fflush(stdout);
	char *line = fgets(buffer, sizeof(buffer), stdin);

	// Got input?
	if(line){
		// Convert the input string to an integer number
		int input_num = (int)strtol(buffer, NULL, 10);

		// Test Semihosting printf displaying a loop count to the debugger console
		printf("Counting: ");
		fflush(stdout);
		int i;
		for(i = 0; i < input_num; ++i){
			printf("%i ", i);
			fflush(stdout);
		}
		printf("Test completed\n");
	}else{
		printf("Error: fgets returned NULL\n");
	}
}

void wait_forever(){
	volatile unsigned char i = 1;
	while(i);
}

int main(int argc, char **argv){
	#ifdef SEMIHOSTING
		initialise_monitor_handles();  // Initialise Semihosting
	#endif

	semihosting_test();
	wait_forever();

	return 0;
}
