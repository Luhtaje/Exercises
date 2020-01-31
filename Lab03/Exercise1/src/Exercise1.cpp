/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
#define TICKRATE_HZ1 (1000)

#include "DigitalIoPin.h"
#include <atomic>
#include <ctype.h>

static volatile std::atomic_int counter;

#ifdef __cplusplus
extern "C" {
#endif /**  * @brief Handle interrupt from SysTick timer  * @return Nothing  */

void SysTick_Handler(void) {
	if(counter > 0)
		counter--;
}

#ifdef __cplusplus
}
#endif

void Sleep(int ms) {  counter = ms;  while(counter > 0) {   __WFI();  } }

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
#endif
#endif

    uint32_t sysTickRate;

	/* The sysTick counter only has 24 bits of precision, so it will
	   overflow quickly with a fast core clock. You can alter the
	   sysTick divider to generate slower sysTick clock rates. */
	Chip_Clock_SetSysTickClockDiv(1);

	/* A SysTick divider is present that scales the sysTick rate down
	   from the core clock. Using the SystemCoreClock variable as a
	   rate reference for the SysTick_Config() function won't work,
	   so get the sysTick rate by calling Chip_Clock_GetSysTickClockRate() */
	sysTickRate = Chip_Clock_GetSysTickClockRate();

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(sysTickRate / TICKRATE_HZ1);

	DigitalIoPin SW1{0,17,true,true,true};
	DigitalIoPin Led1{0,25,false,false,false};


    // TODO: insert code here
    Board_UARTPutSTR("\r\nHello, World\r\n");
    Board_UARTPutChar('!');
    Board_UARTPutChar('\r');
    Board_UARTPutChar('\n');
    int c;

    while(1) {
    	// echo back what we receive
    	if(SW1.read()){
    		//Why is this loop not needed?
    		//while(SW1.read()){};
    		if(Led1.read()){
    			Led1.write(true);
    		}else{
    			Led1.write(false);
    		}
    	}
    	c = Board_UARTGetChar();
    	if(c != EOF) {
    		if(c == '\n'){
    			Board_UARTPutChar('\r');
    		// precede linefeed with carriage return
    		}
    		else if(c == '\r') {
    			Board_UARTPutChar('\n');
    		}
    		// send line feed after carriage return

    		if(Led1.read()){
    			Board_UARTPutChar(tolower(c));
    		}else{
    			Board_UARTPutChar(toupper(c));
    		}

    	}
    }
    // Force the counter to be placed into memory


    return 0 ;
}
