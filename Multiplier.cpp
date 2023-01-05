#include "framework.h"
#include "Operation.h"
#include "Multiplier.h"

double Multiplier::Do()
{
	result = num1 * num2;
	return result;
}