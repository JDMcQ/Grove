/*
 * PIR.h
 *
 *  Created on: Mar 11, 2018
 *      Author: john
 */

#ifndef PIR_H_
#define PIR_H_

class PIR{
	public:
		int value;
		int status;
		char *Sstatus;

	private:
		int pin;
		int countdown;
		int lastvalue;
		int ccount;

	public: PIR(int ppin, int cdown);

	public: void check();

};

#endif /* PIR_H_ */
