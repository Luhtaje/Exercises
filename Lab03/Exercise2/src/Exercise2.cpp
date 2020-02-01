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
#include <cstring>

// TODO: insert other include files here

#include "MorseEncoder.h"
#include <atomic>
#include "LpcUart.h"



// TODO: insert other definitions and declarations here
#define TICKRATE_HZ1 (1000)
#define C_LIMIT (80)
enum {wmp,send,set};


static volatile std::atomic_int counter;

void Sleep(int ms) {  counter = ms;  while(counter > 0) {   __WFI();  } }



void handleState(int state, LpcUart& uart,MorseEncoder& Encoder){
	int i=0;
	char c;
	char string[C_LIMIT]= {};

	while(c != '\r' && i < C_LIMIT){
		if(uart.read(c)!=0){
			string[i]=c;
			uart.write(c);
		}
	}
	uart.write("\r\n");
	string[i-1]= '\0';
	//state 0 = wmp, state 1= sen , state 2=set.
	if(state==0){

	}else if(state ==1){

	}else if(state==2){

	}else{
		uart.write("...How...how did you get here? Leave now! This is no place for your kind... Only death awaits here...");
	}
}




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

    // TODO: insert code here

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

	DigitalIoPin Led1{0,25,false};
	DigitalIoPin MorseDecoder{0,8,false};

	MorseEncoder Encoder(&Led1,&MorseDecoder);



#if 1
	LpcPinMap none = {-1, -1}; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig cfg = { LPC_USART0, 115200, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1,
			false, txpin, rxpin, none, none };
	LpcUart uart(cfg);


#endif
	char c;
	char line[6];
	int i=0;
while(1){

	//Initiates input state
	if(uart.read(c) != 0){
		line[0]=c;
		uart.write(c);
		i=1;
		//The real input state
		while(c != ' ' && i != 6){
			if(uart.read(c) != 0){
				uart.write(c);
				line[i]=c;
				++i;
			}
		}
		//Terminate string so strcmp works
		line[i-1] ='\0';

		if(i==6){
			uart.write("\r\nCharacter limit reached without a command. Commands are wpm, send, and set.\n\r");
		}else if(!strcmp(line, "wmp")){
			//Initiate words per minute state
			handleState(wmp,uart,Encoder);
		}else if(!strcmp(line,"send")){
			//Initiate send state
			handleState(send,uart,Encoder);
		}else if(!strcmp(line,"set")){
			// Initiate set state
			handleState(set,uart,Encoder);
		}else{
			//Incorrect input
			uart.write("\r\nInvalid input. Try again\r\n");
		}
	}
}



#if 0
	char c;
	char cstring[81]={};

    while(1){

    	uart.read(c);
    	if(c != EOF){
    		uart.write(c);
    		cstring[0]=c;
    		int i=1;

    		while(c != '\r' && i < 80){
    			uart.read(c);
    			if(c!= EOF){
    				uart.write(c);
    				cstring[i]=c;
    			i++;
      			}
    		}
    		uart.write('\n');
    		uart.write('\r');
    		cstring[i-1]= '\0';
    		Encoder.morse_out(cstring);
    	}

    	Sleep(1);

    }

#endif


    return 0 ;
}
