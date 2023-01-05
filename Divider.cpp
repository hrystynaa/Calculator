#include "framework.h"
#include "Operation.h"
#include "Divider.h"
#include <string>

double Divider::Do()
{	
	if (num1 == 0)
		result = 0;
	if (num2 == 0)
		throw std::exception();
	else
		result = num1 / num2;
	return result;
}