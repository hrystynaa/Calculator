#pragma once

HWND MyCalc::hWndCalc = NULL;
Operation* MyCalc::curOp = NULL;
double MyCalc::x = NULL;
double MyCalc::y = NULL;
double MyCalc::rez = NULL;
int MyCalc::radix = NULL;
bool MyCalc::next = FALSE;
bool MyCalc::point = FALSE;
std::wstring MyCalc::nums = L"";
std::wstring MyCalc::tmpres = L"";

static int buttons[26] = { IDC_BA,  IDC_BB,  IDC_BC,  IDC_BD, IDC_BE,  IDC_BF,
                  IDC_B2,  IDC_B3,  IDC_B4,  IDC_B5,  IDC_B6, IDC_B7,  IDC_B8,  IDC_B9, IDC_B0,  IDC_B1, 
                  IDC_BCANCEL, IDC_BCLEAN, IDC_BDIV, IDC_BMINUS, IDC_BMULTI, IDC_BEQUAL, IDC_BPLUS, IDC_BSIGN,
                  IDC_BDIVBY, IDC_BPOINT };