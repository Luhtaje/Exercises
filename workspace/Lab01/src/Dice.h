/*
 * Dice.h
 *
 *  Created on: Jan 21, 2020
 *      Author: User
 */

#ifndef DICE_H_
#define DICE_H_


#include "DigitalIoPin.h"
class Dice {
public:
	Dice();
	virtual ~Dice();
	void Show(int number);
private:

	void testLeds(DigitalIoPin);
	void display0();
	void display1();
	void display2();
	void display3();
	void display4();
	void display5();
	void display6();
	void display7();

	DigitalIoPin led1;
	DigitalIoPin led2;
	DigitalIoPin led3;
	DigitalIoPin led4;
	DigitalIoPin led5;
	DigitalIoPin led6;
	DigitalIoPin led7;


};

#endif /* DICE_H_ */
