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
#include <atomic>
#include "Menu.h"

// TODO: insert other definitions and declarations here


#define TICKRATE_HZ1 (1000)	/* 1000 ticks per second */


static volatile std::atomic_int counter;

#ifdef __cplusplus
extern "C" {
#endif /**
 * @brief Handle interrupt from SysTick timer
 * * @return Nothing
 * */

void SysTick_Handler(void)
{
	counter++;
}

#ifdef __cplusplus
}
#endif


void Sleep(int ms)
{
	ms += counter;
	while(ms >  counter)
	{
		__WFI();

	}
}

int Count(DigitalIoPin& button)
{

	while(button.read())
	{
		__WFI();

	}
	return counter;
}


bool secureRead(DigitalIoPin& button){
	int presses = 0;
	int releases = 0;

	while(presses < 5 && releases < 5){
		if(button.read()){
			presses++;
			releases =0;
		}else{
			releases++;
			presses=0;
		}
		Sleep(10);
	}

	if(presses > releases){
		return true;
	}
	else return false;
}


int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable     SystemCoreClockUpdate();
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


#if 1


#endif


#if 1

	Menu mainMenu;


 	while(1){

 		//Check if buttons for moving cursor are pressed
 		if((secureRead(mainMenu.SW3)) ||(secureRead(mainMenu.SW1))){
 			//Check which one and call a function according to them.
 			mainMenu.SW1.read() ? mainMenu.moveup() : mainMenu.movedown();
 			//Empty loop to prevent multiple entries with a single press
 			while(mainMenu.SW1.read() || mainMenu.SW3.read()){
 				Sleep(10);
 			};
 		}
 		else if(secureRead(mainMenu.SW2)){
 			//toggle current led
 			mainMenu.toggle();
 			//Empty loop to prevent multiple entries with a single press
 			while(mainMenu.SW2.read()){
 				Sleep(10);
 			};
 		}
 		Sleep(10);
 	}

#endif
#if 0
 	 int timer;

	DigitalIoPin SW1(0,17,true,true,true);
	DigitalIoPin SW2(1,11,true,true,true);
	DigitalIoPin SW3(1,9,true,true,true);

	ITM_Wrapper printer;
	string toBePrinted{};

	while(1){

		counter=0;

		if(SW1.read()){
			timer = Count(SW1);
			toBePrinted = "SW1 pressed for " + std::to_string(timer) + " ms\n";
			printer.print(toBePrinted);
		}
		if(SW2.read()){
			timer = Count(SW2);
			toBePrinted = "SW2 pressed for " + std::to_string(timer) + " ms\n";
			printer.print(toBePrinted);
		}
		if(SW3.read()){
			timer = Count(SW3);
			toBePrinted = "SW3 pressed for " + std::to_string(timer) + " ms\n";
			printer.print(toBePrinted);
		}
	}




#endif

	  // Force the counter to be placed into memory
	    volatile static int i = 0 ;
	    // Enter an infinite loop, just incrementing a counter

    while(1) {
        i++ ;
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}
