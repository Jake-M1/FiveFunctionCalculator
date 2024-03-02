#include "Calculate.h"

Calculate::Calculate()
{
	firstNum = 0;
	secondNum = 0;
	firstNumStr = "";
	secondNumStr = "";
	state = 0;
	display = 0;
}

int Calculate::GetDisplay()
{
	return display;
}

void Calculate::NumberPress(int digit)
{
	if (state == 0)
	{
		CreateFirstNum(digit);
		display = firstNum;
	}
}

void Calculate::CreateFirstNum(int digit)
{

	firstNum = (firstNum * 10) + digit;
	firstNumStr = std::to_string(firstNum);
}

void Calculate::CreateSecondNum(int digit)
{
	secondNum = (secondNum * 10) + digit;
	secondNumStr = std::to_string(secondNum);
}