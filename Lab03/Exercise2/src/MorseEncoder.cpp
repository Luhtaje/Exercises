/*
 * MorseEncoder.cpp
 *
 *  Created on: Jan 29, 2020
 *      Author: User
 */
extern void Sleep(int ms);
#include "MorseEncoder.h"
#define DOT (1)
#define DASH (3)
#define CHAR_X (23)

MorseEncoder::MorseEncoder(DigitalIoPin* LedPin, DigitalIoPin* decoderPin):Led(LedPin),Decoder(decoderPin),ITU_morse({{ 'A', { DOT, DASH } }, // A
		{ 'B', { DASH, DOT, DOT, DOT } }, // B
		{ 'C', { DASH, DOT, DASH, DOT } }, // C
		{ 'D', { DASH, DOT, DOT } }, // D
		{ 'E', { DOT } }, // E
		{ 'F', { DOT, DOT, DASH, DOT } }, // F
		{ 'G', { DASH, DASH, DOT } }, // G
		{ 'H', { DOT, DOT, DOT, DOT } }, // H
		{ 'I', { DOT, DOT } }, // I
		{ 'J', { DOT, DASH, DASH, DASH } }, // J
		{ 'K', { DASH, DOT, DASH } }, // K
		{ 'L', { DOT, DASH, DOT, DOT } }, // L
		{ 'M', { DASH, DASH } }, // M
		{ 'N', { DASH, DOT } }, // N
		{ 'O', { DASH, DASH, DASH } }, // O
		{ 'P', { DOT, DASH, DASH, DOT } }, // P
		{ 'Q', { DASH, DASH, DOT, DASH } }, // Q
		{ 'R', { DOT, DASH, DOT } }, // R
		{ 'S', { DOT, DOT, DOT } }, // S
		{ 'T', { DASH } }, // T
		{ 'U', { DOT, DOT, DASH } }, // U
		{ 'V', { DOT, DOT, DOT, DASH } }, // V
		{ 'W', { DOT, DASH, DASH } }, // W
		{ 'X', { DASH, DOT, DOT, DASH } }, // X
		{ 'Y', { DASH, DOT, DASH, DASH } },  // Y
		{ 'Z', { DASH, DASH, DOT, DOT } }, // Z
		{ '1', { DOT, DASH, DASH, DASH, DASH } }, // 1
		{ '2', { DOT, DOT, DASH, DASH, DASH } }, // 2
		{ '3', { DOT, DOT, DOT, DASH, DASH } }, // 3
		{ '4', { DOT, DOT, DOT, DOT, DASH } }, // 4
		{ '5', { DOT, DOT, DOT, DOT, DOT } }, // 5
		{ '6', { DASH, DOT, DOT, DOT, DOT } }, // 6
		{ '7', { DASH, DASH, DOT, DOT, DOT } }, // 7
		{ '8', { DASH, DASH, DASH, DOT, DOT } }, // 8
		{ '9', { DASH, DASH, DASH, DASH, DOT } }, // 9
		{ '0', { DASH, DASH, DASH, DASH, DASH } }, // 0
		{ 0, { 0 } } // terminating entry - Do not remove!
})//Initializer list ends here.
{


}

MorseEncoder::~MorseEncoder() {
	// TODO Auto-generated destructor stub
}

void MorseEncoder::morse_out(std::string str){
	morse_out(str.c_str());
}

void MorseEncoder::morse_out(const char* str){
	//Loop for going through characters in string that is to be sent as morse code.
	for(int index_Char=0 ; str[index_Char] !='\0' ; index_Char++){

		if(str[index_Char]== ' '){
			//No need for inter-element delay when space is inside.
			Sleep(2*timeUnit);

		}else if(isalnum(str[index_Char]) && (str[index_Char] < 128) ){
			//Loop for going through the array of morse patterns for specific characters.
			for(int i =0 ; ITU_morse[i].symbol !=0 ; i++){

				//If a character is found, proceed to morse out.
				if(ITU_morse[i].symbol == toupper(str[index_Char])){
					//Send dots/dashes for that symbol to Decoder and Led.
					for(int k=0;ITU_morse[i].code[k]!=0;k++){
						morseSignal(ITU_morse[i].code[k]);
						//Inter-Element gap
						Sleep(1*timeUnit);
					}

				}

			}
		}

		else{
			for(int k=0;ITU_morse[CHAR_X].code[k]!=0;k++){
				morseSignal(ITU_morse[CHAR_X].code[k]);
				//Inter-Element gap
				Sleep(1*timeUnit);
			}
		}

	//Letter gap
	Sleep(2*timeUnit);
	}

}



void MorseEncoder::morseSignal(int pattern)const{
	if(pattern==1){
		Led->write(1);
		Decoder->write(0);
		Sleep(1*timeUnit);
		Led->write(0);
		Decoder->write(1);

	}else if(pattern ==3){
		Led->write(1);
		Decoder->write(0);
		Sleep(3*timeUnit);
		Led->write(0);
		Decoder->write(1);
	}
}

