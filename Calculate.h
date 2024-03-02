#pragma once

#include <string>

class Calculate
{
private:
	int firstNum;
	int secondNum;
	std::string firstNumStr;
	std::string secondNumStr;

	// For state:
	// 0 means it is on the first num
	// 1 means it is on the second num
	// 2 means it is on the result
	int state;

	int display;

public:
	Calculate();
	int GetDisplay();
	void NumberPress(int digit);
	void CreateFirstNum(int digit);
	void CreateSecondNum(int digit);
};

