/*
 * MorseEncoder.h
 *
 *  Created on: Jan 29, 2020
 *      Author: User
 */

#ifndef MORSEENCODER_H_
#define MORSEENCODER_H_
#include "DigitalIoPin.h"
#include <ctype.h>
#include <string>

class MorseEncoder {
public:
	MorseEncoder(DigitalIoPin*, DigitalIoPin*);
	virtual ~MorseEncoder();
	void morse_out(const char *);
	void morse_out(std::string str);

private:
	DigitalIoPin* Led;
	DigitalIoPin* Decoder;
	void morseSignal(int)const;
	struct MorseCode {
		char symbol;
		unsigned char code[7];
	};
	MorseCode ITU_morse[37];
};

#endif /* MORSEENCODER_H_ */
