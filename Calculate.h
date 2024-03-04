#pragma once

#include <string>

class Calculate
{
private:
	double firstNum;
	double secondNum;

	// For state:
	// 0 means it is on the first num
	// 1 means it is on the second num
	// 2 means it is on the result
	int state;

	double display;

	// For operatorState:
	// 0 means none
	// 1 means add
	// 2 means subtract
	// 3 means multiply
	// 4 menas divide
	int operatorState;

	bool decimalMode;
	double decimalMult;

public:
	Calculate();
	double GetDisplay();
	void NumberPress(int digit);
	void CreateFirstNum(int digit);
	void CreateSecondNum(int digit);
	void OperatorPress(int operatorCode);
	void EqualsPress();
	void DecimalPress();
	void CreateFirstNumDecimal(int digit);
	void CreateSecondNumDecimal(int digit);
	void Clear();
	void ClearEntry();
};

