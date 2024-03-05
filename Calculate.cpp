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
	negate = false;

	traceMode = true;
	firstNumOld = 0;
	secondNumOld = 0;
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
			AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), true));
		}
		else
		{
			CreateFirstNum(digit);
			AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), false));
		}
		display = firstNum;
	}
	else if (state == 1)
	{
		if (decimalMode)
		{
			CreateSecondNumDecimal(digit);
			AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), true));
		}
		else
		{
			CreateSecondNum(digit);
			AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), false));
		}
		display = secondNum;
	}
	else if (state == 2)
	{
		firstNum = 0;
		if (decimalMode)
		{
			CreateFirstNumDecimal(digit);
			AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), true));
		}
		else
		{
			CreateFirstNum(digit);
			AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), false));
		}
		display = firstNum;
		state = 0;
	}
}

void Calculate::CreateFirstNum(int digit)
{
	if (firstNum >= 0)
	{
		firstNum = (firstNum * 10) + digit;
	}
	else
	{
		firstNum = (firstNum * 10) - digit;
	}
	
	if (negate && digit != 0)
	{
		firstNum *= -1;
		negate = false;
	}
}

void Calculate::CreateSecondNum(int digit)
{
	if (secondNum >= 0)
	{
		secondNum = (secondNum * 10) + digit;
	}
	else
	{
		secondNum = (secondNum * 10) - digit;
	}
	
	if (negate && digit != 0)
	{
		secondNum *= -1;
		negate = false;
	}
}

void Calculate::OperatorPress(int operatorCode)
{
	if (operatorCode == 2 && !negate)
	{
		if (state == 0 && firstNum == 0)
		{
			negate = true;
			return;
		}
		else if (state == 1 && secondNum == 0)
		{
			negate = true;
			return;
		}
	}

	state = 1;
	operatorState = operatorCode;
	decimalMode = false;
	decimalMult = 0.1;
	negate = false;

	if (operatorCode == 1)
	{
		AddTraceLogEntry(CreateTraceLogEntry(L"+", false));
	}
	else if (operatorCode == 2)
	{
		AddTraceLogEntry(CreateTraceLogEntry(L"-", false));
	}
	else if (operatorCode == 3)
	{
		AddTraceLogEntry(CreateTraceLogEntry(L"*", false));
	}
	else if (operatorCode == 4)
	{
		AddTraceLogEntry(CreateTraceLogEntry(L"/", false));
	}
}

void Calculate::EqualsPress()
{
	if (state != 1)
	{
		return;
	}

	firstNumOld = firstNum;
	secondNumOld = secondNum;

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
		firstNum = firstNum * secondNum;
		display = firstNum;
	}
	else if (operatorState == 4)
	{
		// Account for / by 0
		if (secondNum != 0)
		{
			firstNum = firstNum / secondNum;
		}
		
		display = firstNum;
	}

	secondNum = 0;
	state = 2;
	negate = false;
	AddTraceLogEntry(CreateTraceLogEntry(L"=", false));
}

void Calculate::DecimalPress()
{
	decimalMode = true;
	AddTraceLogEntry(CreateTraceLogEntry(L".", false));
}

void Calculate::CreateFirstNumDecimal(int digit)
{
	if (firstNum >= 0)
	{
		firstNum = firstNum + (digit * decimalMult);
	}
	else
	{
		firstNum = firstNum - (digit * decimalMult);
	}

	decimalMult = decimalMult * 0.1;

	if (negate && digit != 0)
	{
		firstNum *= -1;
		negate = false;
	}
}

void Calculate::CreateSecondNumDecimal(int digit)
{
	if (secondNum >= 0)
	{
		secondNum = secondNum + (digit * decimalMult);
	}
	else
	{
		secondNum = secondNum - (digit * decimalMult);
	}

	decimalMult = decimalMult * 0.1;

	if (negate && digit != 0)
	{
		secondNum *= -1;
		negate = false;
	}
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

	AddTraceLogEntry(CreateTraceLogEntry(L"C", false));
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

	AddTraceLogEntry(CreateTraceLogEntry(L"CE", false));
}

void Calculate::PercentPress()
{
	if (state == 1)
	{
		secondNum = firstNum * (secondNum * 0.01);
		display = secondNum;
	}
	else
	{
		firstNum = firstNum * 0.01;
		display = firstNum;
	}

	AddTraceLogEntry(CreateTraceLogEntry(L"%", false));
}

bool Calculate::GetNegate()
{
	return negate;
}

int Calculate::GetState()
{
	return state;
}

std::list<std::wstring> Calculate::GetTraceLog()
{
	return traceLog;
}

void Calculate::AddTraceLogEntry(std::wstring entry)
{
	if (traceMode)
	{
		traceLog.push_front(entry);
	}
}

std::wstring Calculate::CreateTraceLogEntry(std::wstring input, bool decimal)
{
	std::wstring entry = L"Input: " + input;
	if (decimal)
	{
		entry += L" (decimal), ";
	}
	else
	{
		entry += L", ";
	}

	if (state != 2)
	{
		entry += L"State: " + std::to_wstring(firstNum);
	}
	else
	{
		entry += L"State: " + std::to_wstring(firstNumOld);
	}
	

	if (operatorState == 0)
	{
		entry += L" ? ";
	}
	else if (operatorState == 1)
	{
		entry += L" + ";
	}
	else if (operatorState == 2)
	{
		entry += L" - ";
	}
	else if (operatorState == 3)
	{
		entry += L" * ";
	}
	else if (operatorState == 4)
	{
		entry += L" / ";
	}

	if (state == 0)
	{
		entry += L"?";
	}
	else if (state == 1)
	{
		entry += std::to_wstring(secondNum);
	}
	else
	{
		entry += std::to_wstring(secondNumOld);
	}

	entry += L" = ";
	if (state == 2)
	{
		entry += std::to_wstring(firstNum);
	}
	else
	{
		entry += L"?";
	}

	return entry;
}

void Calculate::ChangeTraceMode(bool newTraceMode)
{
	traceMode = newTraceMode;
}