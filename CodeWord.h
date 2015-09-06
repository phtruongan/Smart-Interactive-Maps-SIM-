//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////	Name: PHAM Truong An
////	Module: Background Subtraction
////	Goal: Codebook data structure	
////	Version: 1.0.0
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <vector>
#include <math.h>
using namespace std;
class CCodeWord
{
private:
	float _RGB[3];
	// codeword
	float minBright;		// minimum brightness level of the codeword
	float maxBright;		// maximum brightness level of the codeword
	int freq;				// number of time the codeword occur
	int _MNRL;				// Maximum negative run-length defined as the longest interval during training period that the codeword has not occured
	int first_access;		// first time occur
	int last_access;		// last time occur
public:
	CCodeWord();
	CCodeWord(float* rgb, float minBr, float maxBr, int f, int ml, int fr, int lt);
	float* getRGB();
	float getMinBr();
	float getMaxBr();
	int getFreq();
	int getMNRL();
	int getFirst();
	int getLast();
	bool updateCodeWord(CCodeWord newWord);
	bool compareCodeWord(CCodeWord word);
	~CCodeWord();
};

