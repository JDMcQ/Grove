/*
 * PIR.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: john
 */

#include "Arduino.h"

#include "PIR.h"

	PIR::PIR(int ppin, int cdown){
		value = 0;
		lastvalue = 0;
		status = 0;
		Sstatus = "Still";
		pin = ppin;
		countdown = cdown;
		ccount = 0;
	}

	void PIR::check(){

		value = digitalRead(pin);

		if(value == 1){
			if(lastvalue == 0){
				Sstatus = "Motion";
				status = 1;
				ccount = countdown;
				lastvalue = value;
			}
		} else {
			if(lastvalue == 1){
				Sstatus = "Count-down";
				ccount--;
				lastvalue = value;
			}else{
				if(ccount > 0){
					ccount--;
				}else{
					status = 0;
					Sstatus = "Still";
				}

			}
		}
	}
