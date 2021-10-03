/*
 * Dice.cpp
 *
 *  Created on: Jan 21, 2020
 *      Author: User
 */

#include "Dice.h"

Dice::Dice():led1(1,9,false),led2(0,29,false),led3(0,9,false),led4(0,10,false),
led5(0,16,false),led6(1,3,false),led7(0,0,false)
{
 display0();
}

Dice::~Dice() {
	// TODO Auto-generated destructor stub
}

void Dice::Show(int figure){

	if(figure==0)
		display0();
	else if(figure==1){
		display1();
	}
	else if(figure==2){
		display2();
	}
	else if(figure==3){
		display3();
	}
	else if(figure==4){
		display4();
	}
	else if(figure==5){
		display5();
	}
	else if(figure==6){
		display6();
	}
	else if(figure==7){
		display7();
	}
}



void Dice::display0(){
	led1.write(0);
	led2.write(0);
	led3.write(0);
	led4.write(0);
	led5.write(0);
	led6.write(0);
	led7.write(0);
}

void Dice::display1(){
	led1.write(0);
	led2.write(0);
	led3.write(0);
	led4.write(1);
	led5.write(0);
	led6.write(0);
	led7.write(0);
}

void Dice::display2(){
	led1.write(0);
	led2.write(0);
	led3.write(1);
	led4.write(0);
	led5.write(0);
	led6.write(0);
	led7.write(1);
}

void Dice::display3(){
	led1.write(0);
	led2.write(0);
	led3.write(1);
	led4.write(1);
	led5.write(0);
	led6.write(0);
	led7.write(1);
}

void Dice::display4(){
	led1.write(1);
	led2.write(0);
	led3.write(1);
	led4.write(0);
	led5.write(1);
	led6.write(0);
	led7.write(1);
}

void Dice::display5(){
	led1.write(1);
	led2.write(0);
	led3.write(1);
	led4.write(1);
	led5.write(1);
	led6.write(0);
	led7.write(1);
}

void Dice::display6(){
	led1.write(1);
	led2.write(1);
	led3.write(1);
	led4.write(0);
	led5.write(1);
	led6.write(1);
	led7.write(1);
}

void Dice::display7(){
	led1.write(1);
	led2.write(1);
	led3.write(1);
	led4.write(1);
	led5.write(1);
	led6.write(1);
	led7.write(1);
}


