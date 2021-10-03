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
#include "DigitalIoPin.h"
#include "Dice.h"

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
	if (counter > 0) counter--;
}
#ifdef __cplusplus
}
#endif


void Sleep(int ms)
{
	counter =ms;
	while(counter > 0)
	{
		__WFI();

	}
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



	DigitalIoPin testButton(0,8,true,true,true);
	DigitalIoPin operateButton(1,6,true,true,true);

	Dice dice;
	int cnt;
	while(1){

		if(secureRead(testButton)){
			dice.Show(7);
			while(testButton.read()){}
			cnt=0;
			dice.Show(cnt);
		}

		if(secureRead(operateButton)){

			while(operateButton.read()){
				dice.Show(0);
				if(cnt==6){
					cnt=1;
				}else{
					cnt++;
					//Sleep(1);
				}
				Sleep(1);
			}
		}
		Sleep(1);
		dice.Show(cnt);
	}




	// Force the counter to be placed into memory
	// volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter


#if 0
	DigitalIoPin SW1(0,17,true,true,true);
	DigitalIoPin SW2(1,11,true,true,true);
	DigitalIoPin SW3(1,9,true,true,true);


    int counter1=0;
    int counter2=0;
    int counter3=0;

    while(1) {

    	if(SW1.read()){
    			Board_LED_Set(0, true);
    			counter1 =10;
    		}
    		if(SW2.read()){
    			Board_LED_Set(1, true);
    			counter2 = 10;
    		}
    		if(SW3.read()){
    			 Board_LED_Set(2, true);
    			counter3 =10;
    		}

    		if(counter1 ==0){
    			Board_LED_Set(0, false);
    		}
    		if(counter2 ==0){
    			Board_LED_Set(1, false);
    		}
    		if(counter3 ==0){
    			Board_LED_Set(2,false);
    		}

    		--counter1;
    		--counter2;
    		--counter3;
    		Sleep(100);

           __asm volatile ("nop");
       }
#endif
#if 0

    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 17,(IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0,17);

    while(1) {


		if(Chip_GPIO_GetPinState(LPC_GPIO,0,17)){
			  Board_LED_Set(0, true);
			  Sleep(1000);
			  Board_LED_Set(0, false);
			  Board_LED_Set(1, true);
			  Sleep(1000);
			  Board_LED_Set(1, false);
			  Board_LED_Set(2, true);
			  Sleep(1000);
			  Board_LED_Set(2, false);

    	}
        i++ ;
        __asm volatile ("nop");
    }
#endif

    return 0;
}
