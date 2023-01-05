#include "framework.h"
#include "Operation.h"

Operation::~Operation()
{
}

void Operation::Set(double x, double y)
{
	num1 = x;
	num2 = y;
	result = 0.0;
}

