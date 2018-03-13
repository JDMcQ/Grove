/*
 * CR.cpp
 *
 *  Created on: Mar 12, 2018
 *      Author: john
 */

#include "Arduino.h"

#include "CR.h"

CR::CR(int ppin){
	pin = ppin;
	laststate = false;
	energized = false;

}

void CR::energize(){
	if(!laststate){
		digitalWrite(pin,HIGH);
		laststate = true;
		energized = true;
	}
}

void CR::denergize(){
	if(laststate){
		digitalWrite(pin,LOW);
		laststate = false;
		energized = false;
	}
}
