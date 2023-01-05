#include "framework.h"
#include "Operation.h"
#include "Subtractor.h"

double Subtractor::Do()
{
	result = num1 - num2;
	return result;
}