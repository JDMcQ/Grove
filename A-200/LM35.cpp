/*
 * ATemperature.cpp
 *
 *  Created on: Mar 6, 2018
 *      Author: john
 */
#include "Arduino.h"

#include "LM35.h"

LM35::LM35(int pin){
	analogReference(INTERNAL);
	Value = 0.0;
	strValue = "srTT_201";
	sum = 0.0;
	iTemp = 0.0;
	signal = 0.0;
	idx = 0;
	apin = pin;
}

void LM35::getT(){
	signal = analogRead(apin);

	smooth(idx) = signal / 9.31;

	idx++;
	if (idx >=9 )
		idx = 0;

	sum = 0.0;
	for (int i = 0; i<10; i++){
		sum = sum + smooth(idx);
	}
    iTemp = sum/10;

    Value = iTemp;
    dtostrf(Value,6,3,strValue);
	//return iTemp;
}
