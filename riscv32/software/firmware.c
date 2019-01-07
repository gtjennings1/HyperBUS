// Copyright 2017 Gnarly Grey LLC

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <stdint.h>
#include <stdbool.h>

#define reg_uart_clkdiv (*(volatile uint32_t*)0x02000004)
#define reg_uart_data (*(volatile uint32_t*)0x02000008)

#define reg_io   ((volatile uint32_t*)0x03000000)

#define reg0_hbc  (*(volatile uint32_t*)0x08000000)
#define reg1_hbc  (*(volatile uint32_t*)0x08000004)

#define cfg0_hbc  (*(volatile uint32_t*)0x08002000)
#define cfg1_hbc  (*(volatile uint32_t*)0x08002004)

#define WDT_START (1 << 7)
#define WDT_RESTART (WDT_START | (1 << 6) )
#define WDT_STOP (~WDT_START)
#define LED_RED (1)
#define LED_GREEN (2)
#define LED_BLUE (4)

#define PRINT_VALUES

#define TEST_8
#define TEST_16
#define TEST_32


// --------------------------------------------------------
void putchar(char c)
{
	if (c == '\n')
		putchar('\r');		
	reg_uart_data = c;
}


void print(const char *p)
{
	while (*p)
		putchar(*(p++));
}

void print_hex(uint32_t v, int digits)
{
	for (int i = 7; i >= 0; i--) {
		char c = "0123456789abcdef"[(v >> (4*i)) & 15];
		if (c == '0' && i >= digits) continue;
		putchar(c);
		digits = i;
	}
}


// --------------------------------------------------------
void main()
{
	reg_uart_clkdiv = 1250;
	

	print("\n");
	print("  ____  _          ____         ____\n");
	print(" |  _ \\(_) ___ ___/ ___|  ___  / ___|\n");
	print(" | |_) | |/ __/ _ \\___ \\ / _ \\| |\n");
	print(" |  __/| | (_| (_) |__) | (_) | |___\n");
	print(" |_|   |_|\\___\\___/____/ \\___/ \\____|\n");
	print("\n");
	print("    FPGA 101 Workshop Badge \n");
	print("    26th May - Belgrade - Hackaday\n");

	
	// start wdt and swicth on the red led
	*reg_io = WDT_START | LED_RED;

	uint32_t t, pattern = 0xDEADBEEF;
	uint8_t error;
	uint8_t test_8[128];
	uint16_t test_16[64];
	uint32_t test_32[32];

	// read IDRs
	print("IDR0: 0x");print_hex((uint16_t)(reg0_hbc), 4);print("\n");
	print("IDR1: 0x");print_hex((uint16_t)(reg1_hbc), 4);print("\n");
	
	//start test
	while(1){

#ifdef TEST_8
		
		print("uint8_t test\n");  
		for(t = 0; t < 128; t++){
			test_8[t] = (uint8_t)pattern;
			uint32_t head = (pattern >> 28);
			pattern = (pattern << 4) | head;
		}
		error = 0;
	    for(t = 0; t < 128; t++){
 			if(test_8[t] != (uint8_t)pattern) error++;
 			uint32_t head = (pattern >> 28);
			pattern = (pattern << 4) | head;
			#ifdef PRINT_VALUES
	    		print_hex(test_8[t], 2); print("\n");
	    	#else
	    		print(".");
	    	#endif
	    }

	    #ifndef PRINT_VALUES
	   		print("\n");
	   	#endif

	   	print("error: "); print_hex(error, 2); print("\n\n");

#endif
#ifdef TEST_16

	   	print("uint16_t test\n");
		for(t = 0; t < 64; t++){
			test_16[t] = (uint16_t)pattern;
			uint32_t head = (pattern >> 28);
			pattern = (pattern << 4) | head;
		}
		error = 0;
	    for(t = 0; t < 64; t++){
 			if(test_16[t] != (uint16_t)pattern) error++;
 			uint32_t head = (pattern >> 28);
			pattern = (pattern << 4) | head;
			#ifdef PRINT_VALUES
	    		print_hex(test_16[t], 4); print("\n");
	    	#else
	    		print(".");
	    	#endif
	    }
	    #ifndef PRINT_VALUES
	   		print("\n");
	   	#endif

	   	print("error: "); print_hex(error, 2); print("\n\n");
#endif
#ifdef TEST_32
	    
	    print("uint32_t test\n");
		for(t = 0; t < 32; t++){
			test_32[t] = (uint32_t)pattern;
			uint32_t head = (pattern >> 28);
			pattern = (pattern << 4) | head;
		}
		error = 0;
	    for(t = 0; t < 32; t++){
 			if(test_32[t] != (uint32_t)pattern) error++;
 			uint32_t head = (pattern >> 28);
			pattern = (pattern << 4) | head;
			#ifdef PRINT_VALUES
	    		print_hex(test_32[t], 8); print("\n");
	    	#else
	    		print(".");
	    	#endif
	    }

	    #ifndef PRINT_VALUES
	   		print("\n");
	   	#endif

	   	print("error: "); print_hex(error, 2); print("\n\n");

#endif

	   	*reg_io = WDT_RESTART | (error?LED_BLUE:LED_GREEN);
	   	
	   	print("done!\n\n");
	
    } 
}

