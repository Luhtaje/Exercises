/*
 * Menu.cpp
 *
 *  Created on: Jan 24, 2020
 *      Author: User
 */

#include "Menu.h"


Menu::Menu():SW1(0,17,1,1,1),SW2(1,11,1,1,1),SW3(1,9,1,1,1),led1(0,25,false),led2(0,3,false),led3(1,1,false){
	// TODO Auto-generated constructor stub
printMenu();
}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
}

//Mover cursor down
//If cursor is at the bottom move it to the top
void Menu::movedown(){
	if(cursorFlag>=2){
		cursorFlag=0;
	}else{
		cursorFlag++;
	}

	printMenu();
}

//Move cursor up
//If cursor is at the top move it to the bottom
void Menu::moveup(){
	if(cursorFlag<=0){
		cursorFlag=2;
	}else{
		cursorFlag--;
	}
	printMenu();
}

void Menu::toggle(){
	if(cursorFlag==0){
		//Read value is inverted, returns true when led is off.
		if(led1.read())
		{
			led1.write(true);
		}else
		{
			led1.write(false);
		}
	}else if(cursorFlag==1)
	{
		if(led2.read())
		{
			led2.write(true);
		}else
		{
			led2.write(false);
		}
	}else if(cursorFlag==2)
	{
		if(led3.read())
		{
			led3.write(true);
		}else
		{
			led3.write(false);
		}
	}else{
		printer.print("Error: Cursor flag not in range of acceptable values\n");
	}

	printMenu();
}

void Menu::printMenu(){
	string cursor{" <--"};
	string endl{"\n"};
	printer.print("Select LED: \n");

	switch(cursorFlag){
	case 0:
		printer.print("RED " + btoString(led1.read())+cursor+endl);
		printer.print("GREEN " + btoString(led2.read())+endl);
		printer.print("BLUE " + btoString(led3.read())+endl);
		break;
	case 1:
		printer.print("RED " + btoString(led1.read())+endl);
		printer.print("GREEN " + btoString(led2.read())+cursor+endl);
		printer.print("BLUE " + btoString(led3.read())+endl);
		break;
	case 2:
		printer.print("RED " + btoString(led1.read())+endl);
		printer.print("GREEN " + btoString(led2.read())+endl);
		printer.print("BLUE " + btoString(led3.read())+cursor+endl);
	}
}

string Menu::btoString(bool value){

	if(value){
		string temp{"OFF"};
		return temp;
	}else{
		string temp{"ON"};
		return temp;
	}
}

