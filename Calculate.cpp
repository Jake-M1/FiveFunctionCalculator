#include "Calculate.h"

Calculate::Calculate()
{
	firstNum = 0;
	secondNum = 0;
	state = 0;
	display = 0;
	operatorState = 0;
	decimalMode = false;
	decimalMult = 0.1;
}

double Calculate::GetDisplay()
{
	return display;
}

void Calculate::NumberPress(int digit)
{
	if (state == 0)
	{
		if (decimalMode)
		{
			CreateFirstNumDecimal(digit);
		}
		else
		{
			CreateFirstNum(digit);
		}
		display = firstNum;
	}
	else if (state == 1)
	{
		if (decimalMode)
		{
			CreateSecondNumDecimal(digit);
		}
		else
		{
			CreateSecondNum(digit);
		}
		display = secondNum;
	}
	else if (state == 2)
	{
		firstNum = 0;
		if (decimalMode)
		{
			CreateFirstNumDecimal(digit);
		}
		else
		{
			CreateFirstNum(digit);
		}
		display = firstNum;
		state = 0;
	}
}

void Calculate::CreateFirstNum(int digit)
{
	firstNum = (firstNum * 10) + digit;
}

void Calculate::CreateSecondNum(int digit)
{
	secondNum = (secondNum * 10) + digit;
}

void Calculate::OperatorPress(int operatorCode)
{
	state = 1;
	operatorState = operatorCode;
	decimalMode = false;
	decimalMult = 0.1;
}

void Calculate::EqualsPress()
{
	if (state != 1)
	{
		return;
	}

	if (operatorState == 1)
	{
		firstNum = firstNum + secondNum;
		display = firstNum;
	}
	else if (operatorState == 2)
	{
		firstNum = firstNum - secondNum;
		display = firstNum;
	}
	else if (operatorState == 3)
	{
		//firstNum = firstNum * secondNum;
		//display = firstNum;
	}
	else if (operatorState == 4)
	{
		// Account for / by 0
		//firstNum = firstNum / secondNum;
		//display = firstNum;
	}

	secondNum = 0;
	state = 2;
}

void Calculate::DecimalPress()
{
	decimalMode = true;
}

void Calculate::CreateFirstNumDecimal(int digit)
{
	firstNum = firstNum + (digit * decimalMult);
	decimalMult = decimalMult * 0.1;
}

void Calculate::CreateSecondNumDecimal(int digit)
{
	secondNum = secondNum + (digit * decimalMult);
	decimalMult = decimalMult * 0.1;
}

void Calculate::Clear()
{
	firstNum = 0;
	secondNum = 0;
	state = 0;
	display = 0;
	operatorState = 0;
	decimalMode = false;
	decimalMult = 0.1;
}

void Calculate::ClearEntry()
{
	if (state == 0 || state == 2)
	{
		firstNum = 0;
	}
	else if (state == 1)
	{
		secondNum = 0;
	}

	display = 0;
	decimalMode = false;
	decimalMult = 0.1;
}