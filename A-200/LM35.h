// Analog Temperature Object
// JDM 2018
#ifndef ATemp
#define ATemp

class LM35{
	public:
		float Value;
		char  *strValue;
	
	private: 
		float smooth [10];
		int signal;
		float iTemp;
		int idx;
		int apin;
		float sum;
		
	public: LM35(int pin,);
	
	public: void getT();
};
