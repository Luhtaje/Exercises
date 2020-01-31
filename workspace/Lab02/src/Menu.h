/*
 * Menu.h
 *
 *  Created on: Jan 24, 2020
 *      Author: User
 */

#include "ITMWrapper.h"
#include "DigitalIoPin.h"
using namespace std;

#ifndef MENU_H_
#define MENU_H_

class Menu {
public:
	Menu();
	virtual ~Menu();
	void moveup();
	void movedown();
	void toggle();

	DigitalIoPin SW1;
	DigitalIoPin SW2;
	DigitalIoPin SW3;


private:
	void printMenu();
	string btoString(bool);
	ITM_Wrapper printer;
	int cursorFlag;

	DigitalIoPin led1;
	DigitalIoPin led2;
	DigitalIoPin led3;
};

#endif /* MENU_H_ */
