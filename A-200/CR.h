/*
 * CR.h
 *
 *  Created on: Mar 12, 2018
 *      Author: john
 */

#ifndef CR_H_
#define CR_H_

class CR{
	public:
		bool energized;

	private:
		bool laststate;
		int pin;

	public: CR(int ppin);

	public: void energize();

	public: void denergize();

};

#endif /* CR_H_ */
