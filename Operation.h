#pragma once
class Operation
{
protected:
		double num1, num2, result;
public:
		virtual ~Operation();
		virtual double Do() = 0;
		void Set(double, double);
};

