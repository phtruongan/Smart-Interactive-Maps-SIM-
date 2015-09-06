#include "CodeWord.h"



CCodeWord::CCodeWord()
{
	for (int i = 0; i < 3; i++)
	{
		_RGB[i] = 0;
	}
	minBright = 0;
	maxBright = 0;
	freq = 0;
	_MNRL = 0;
	first_access = 0;
	last_access = 0;
}

CCodeWord::CCodeWord(float* rgb, float minBr, float maxBr, int f, int ml, int fr, int lt)
{
	for (int i = 0; i < 3; i++)
	{
		_RGB[i] = *(rgb+i);
	}
	minBright = minBr;
	maxBright = maxBr;
	freq = f;
	_MNRL = ml;
	first_access = fr;
	last_access = lt;
}

float* CCodeWord::getRGB()
{
	return _RGB;
}

float CCodeWord::getMinBr()
{
	return minBright;
}

float CCodeWord::getMaxBr()
{
	return maxBright;
}

int CCodeWord::getFreq()
{
	return freq;
}

int CCodeWord::getMNRL()
{
	return _MNRL;
}

int CCodeWord::getFirst()
{
	return first_access;
}

int CCodeWord::getLast()
{
	return last_access;
}

bool CCodeWord::updateCodeWord(CCodeWord newWord)
{
	for (int i = 0; i < 3; i++)
	{
		_RGB[i] = (freq*_RGB[i] + *(newWord.getRGB() + 1))/(freq*1.0+1);
	}

	minBright = std::fmin(newWord.getMaxBr(), minBright);
	maxBright = std::fmax(newWord.getMaxBr(), maxBright);
	freq++;
	_MNRL = std::fmax(_MNRL, newWord.getLast() - last_access);
	last_access = newWord.getLast();
}

bool CCodeWord::compareCodeWord(CCodeWord word)
{
	// First, compare two words base on RGB - colordist
	double color1 = 0;
	double color2 = 0;
	double threshold = 8;
	double alpha = 0.4;			// alpha in interval 0.4-0.7
	double beta = 1.1;			// beta in interval 1.1-1.5
	double highI = 0;
	double lowI = 0;
	for (int i = 0; i < 3; i++)
	{
		color1 += _RGB[i] * _RGB[i];
		color2 += (*(word.getRGB()+i)) * (*(word.getRGB() + i));
	}
	// compare two colors
	if (color1 - color2 < threshold)
	{
		highI = std::fmin(beta*maxBright, minBright / alpha);
		lowI = alpha * maxBright;
		int temp = word.getMaxBr();
		// the brightness of the word lies inside the brightness interval of our codeword
		if (temp > lowI && temp < highI)
		{
			return true;
		}
	}
	
	// not equivalent to our codeword
	return false;
}



CCodeWord::~CCodeWord()
{
}
