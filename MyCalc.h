#pragma once
#include <string>
#include "Operation.h"

class MyCalc
{
protected:
	static int radix;
	static bool next;
	static HWND hWndCalc;
	static double x, y, rez;
public:
	static bool point;
	static std::wstring nums, tmpres;
	static Operation* curOp;
	void Create(HINSTANCE, HWND);
	static void Add(std::wstring);
	static void Set();
	static void OnOperation(Operation*);
	static void Result(Operation*);
	static void ChangeRadix(int);
	static std::wstring Convert(int, int);
	static void Invert();
	static void Oppose();
	static void Cancel();
	static void Clean();	
};