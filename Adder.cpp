#include "framework.h"
#include "Operation.h"
#include "Adder.h"

double Adder::Do()
{
	if (num2)
		result = num1 + num2;
	else if (num1)
			result = num1;
	return result;
}
