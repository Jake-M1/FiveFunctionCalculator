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
	error = false;

	traceMode = true;
	firstNumOld = 0;
	secondNumOld = 0;
	currentTraceDecisions = L"";
	currentTraceDecisionCount = 0;
}

double Calculate::GetDisplay()
{
	return display;
}

void Calculate::NumberPress(int digit)
{
	error = false;
	if (state == 0)
	{
		AddTraceDecision(L"if state==0 -> ");
		if (decimalMode)
		{
			AddTraceDecision(L"if decimalMode -> ");
			CreateFirstNumDecimal(digit);
		}
		else
		{
			AddTraceDecision(L"else decimalMode -> ");
			CreateFirstNum(digit);
		}
		display = firstNum;
		AddTraceDecisionCount(2);
	}
	else if (state == 1)
	{
		AddTraceDecision(L"else if state==1 -> ");
		if (decimalMode)
		{
			AddTraceDecision(L"if decimalMode -> ");
			CreateSecondNumDecimal(digit);
		}
		else
		{
			AddTraceDecision(L"else decimalMode -> ");
			CreateSecondNum(digit);
		}
		display = secondNum;
		AddTraceDecisionCount(3);
	}
	else //state == 2
	{
		AddTraceDecision(L"else state==2 -> ");

		// If on result screen, reset back to first num
		firstNum = 0;
		if (decimalMode)
		{
			AddTraceDecision(L"if decimalMode -> ");
			CreateFirstNumDecimal(digit);
		}
		else
		{
			AddTraceDecision(L"else decimalMode -> ");
			CreateFirstNum(digit);
		}
		display = firstNum;
		state = 0;
		AddTraceDecisionCount(3);
	}
}

void Calculate::CreateFirstNum(int digit)
{
	if (firstNum >= 0)
	{
		firstNum = (firstNum * 10) + digit;
		AddTraceDecision(L"if firstNum >= 0 -> ");
	}
	else
	{
		firstNum = (firstNum * 10) - digit;
		AddTraceDecision(L"else firstNum < 0 -> ");
	}

	if (negate && digit != 0)
	{
		firstNum *= -1;
		negate = false;
		AddTraceDecision(L"if negate -> ");
		AddTraceDecisionCount(1);
	}

	AddTraceDecision(L"Result");
	AddTraceDecisionCount(1);
	AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), false));
}

void Calculate::CreateSecondNum(int digit)
{
	if (secondNum >= 0)
	{
		secondNum = (secondNum * 10) + digit;
		AddTraceDecision(L"if secondNum >= 0 -> ");
	}
	else
	{
		secondNum = (secondNum * 10) - digit;
		AddTraceDecision(L"else secondNum < 0 -> ");
	}

	if (negate && digit != 0)
	{
		secondNum *= -1;
		negate = false;
		AddTraceDecision(L"if negate -> ");
		AddTraceDecisionCount(1);
	}

	AddTraceDecision(L"Result");
	AddTraceDecisionCount(1);
	AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), false));
}

void Calculate::OperatorPress(int operatorCode)
{
	if (error)
	{
		AddTraceDecision(L"if error -> Result");
		AddTraceDecisionCount(1);
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
		return;
	}

	// Subtract operator can also mean a negative sign if used at the beginning of a number
	if (operatorCode == 2 && !negate)
	{
		if ((state == 0 && firstNum == 0) || (state == 1 && secondNum == 0))
		{
			negate = true;
			AddTraceDecision(L"if neg sign -> Result");
			AddTraceDecisionCount(2);
			AddTraceLogEntry(CreateTraceLogEntry(L"-", false));
			return;
		}
	}

	state = 1;
	operatorState = operatorCode;
	decimalMode = false;
	decimalMult = 0.1;
	negate = false;

	AddTraceDecision(L"Result");
	AddTraceDecisionCount(1);

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
	// If not on the second number, do nothing
	if (state != 1)
	{
		AddTraceDecision(L"if state != 1 -> Result");
		AddTraceDecisionCount(1);
		return;
	}

	firstNumOld = firstNum;
	secondNumOld = secondNum;

	if (operatorState == 1)
	{
		firstNum = firstNum + secondNum;
		display = firstNum;

		AddTraceDecision(L"if operatorState == 1 -> Result");
		AddTraceDecisionCount(2);
	}
	else if (operatorState == 2)
	{
		firstNum = firstNum - secondNum;
		display = firstNum;

		AddTraceDecision(L"else if operatorState == 2 -> Result");
		AddTraceDecisionCount(3);
	}
	else if (operatorState == 3)
	{
		firstNum = firstNum * secondNum;
		display = firstNum;

		AddTraceDecision(L"else if operatorState == 3 -> Result");
		AddTraceDecisionCount(4);
	}
	else // operatorState == 4
	{
		// Account for / by 0
		if (secondNum != 0)
		{
			firstNum = firstNum / secondNum;
		}
		else
		{
			error = true;
		}
		
		display = firstNum;

		AddTraceDecision(L"else operatorState == 4 -> Result");
		AddTraceDecisionCount(4);
	}

	secondNum = 0;
	state = 2;
	negate = false;
	AddTraceLogEntry(CreateTraceLogEntry(L"=", false));
}

void Calculate::DecimalPress()
{
	decimalMode = true;

	AddTraceDecision(L"Result");
	AddTraceLogEntry(CreateTraceLogEntry(L".", false));
}

bool Calculate::GetDecimalMode()
{
	return decimalMode;
}

void Calculate::CreateFirstNumDecimal(int digit)
{
	if (firstNum >= 0)
	{
		firstNum = firstNum + (digit * decimalMult);
		AddTraceDecision(L"if firstNum >= 0 -> ");
	}
	else
	{
		firstNum = firstNum - (digit * decimalMult);
		AddTraceDecision(L"else firstNum < 0 -> ");
	}

	decimalMult = decimalMult * 0.1;

	if (negate && digit != 0)
	{
		firstNum *= -1;
		negate = false;
		AddTraceDecision(L"if negate -> ");
		AddTraceDecisionCount(1);
	}

	AddTraceDecision(L"Result");
	AddTraceDecisionCount(1);
	AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), true));
}

void Calculate::CreateSecondNumDecimal(int digit)
{
	if (secondNum >= 0)
	{
		secondNum = secondNum + (digit * decimalMult);
		AddTraceDecision(L"if secondNum >= 0 -> ");
	}
	else
	{
		secondNum = secondNum - (digit * decimalMult);
		AddTraceDecision(L"else secondNum < 0 -> ");
	}

	decimalMult = decimalMult * 0.1;

	if (negate && digit != 0)
	{
		secondNum *= -1;
		negate = false;
		AddTraceDecision(L"if negate -> ");
		AddTraceDecisionCount(1);
	}

	AddTraceDecision(L"Result");
	AddTraceDecisionCount(1);
	AddTraceLogEntry(CreateTraceLogEntry(std::to_wstring(digit), true));
}

void Calculate::Clear()
{
	// Clear the whole calulcator

	firstNum = 0;
	secondNum = 0;
	state = 0;
	display = 0;
	operatorState = 0;
	decimalMode = false;
	decimalMult = 0.1;
	error = false;

	AddTraceDecision(L"Result");
	AddTraceLogEntry(CreateTraceLogEntry(L"C", false));
}

void Calculate::ClearEntry()
{
	// Only clear the current entry

	if (state != 1)
	{
		firstNum = 0;
		AddTraceDecision(L"if state != 1 -> Result");
	}
	else
	{
		secondNum = 0;
		AddTraceDecision(L"else state == 1 -> Result");
	}

	display = 0;
	decimalMode = false;
	decimalMult = 0.1;
	error = false;

	AddTraceDecisionCount(1);
	AddTraceLogEntry(CreateTraceLogEntry(L"CE", false));
}

void Calculate::PercentPress()
{
	AddTraceDecision(L"state == 1 -> Result");
	AddTraceDecisionCount(1);

	// Check whether it is on the first or second number
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

bool Calculate::GetError()
{
	return error;
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

	entry += L"\nDecisions: " + currentTraceDecisions + L"\n";
	currentTraceDecisions = L"";

	entry += L"Decision Count: " + std::to_wstring(currentTraceDecisionCount) + L"\n";
	currentTraceDecisionCount = 0;

	return entry;
}

void Calculate::ChangeTraceMode(bool newTraceMode)
{
	traceMode = newTraceMode;
}

void Calculate::AddTraceDecision(std::wstring decision)
{
	currentTraceDecisions += decision;
}

void Calculate::AddTraceDecisionCount(int num)
{
	currentTraceDecisionCount += num;
}

void Calculate::ResetTraceDecision()
{
	currentTraceDecisions = L"";
}