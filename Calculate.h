#pragma once

#include <string>

class Calculate
{
private:
	int firstNum;
	int secondNum;

	// For state:
	// 0 means it is on the first num
	// 1 means it is on the second num
	// 2 means it is on the result
	int state;

	int display;

	// For operatorState:
	// 0 means none
	// 1 means add
	// 2 means subtract
	// 3 means multiply
	// 4 menas divide
	int operatorState;

public:
	Calculate();
	int GetDisplay();
	void NumberPress(int digit);
	void CreateFirstNum(int digit);
	void CreateSecondNum(int digit);
	void OperatorPress(int operatorCode);
	void EqualsPress();
};

