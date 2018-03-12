// Analog Temperature Object
// JDM 2018
#ifndef LM35_H
#define LM35_H

class LM35{
	public:
		float Value;
		char  *strValue;
	
	private: 
		float smooth [16];
		int signal;
		float iTemp;
		int idx;
		int apin;
		float sum;
		
	public: LM35(int pin);
	
	public: void getT();
};
#endif
