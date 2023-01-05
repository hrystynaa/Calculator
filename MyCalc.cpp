#include "framework.h"
#include "resource1.h"
#include "MyCalc.h"
#include "Adder.h"
#include "Divider.h"
#include "Multiplier.h"
#include "Subtractor.h"
#include "data.h"


BOOL CALLBACK CalcProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId;
    MyCalc* myCalc;
    switch (message)
    {
    case WM_INITDIALOG:
        myCalc->point = FALSE;
        for (int i = 0; i < 26; i++)
        {
            bool flag = false;
            EnableWindow(GetDlgItem(hDlg, buttons[i]), flag);
        }
        return TRUE;
        break;

    case WM_SYSCOMMAND:
        if (wParam == SC_CLOSE) {
            DestroyWindow(hDlg);
        }
        break;

    case WM_COMMAND:
    {
        wmId = LOWORD(wParam);

        switch (wmId)
        {
        case IDC_BPOINT:
            if(!myCalc->point && !(myCalc->nums.empty()))
            myCalc->Add(L".");
            break;
        case IDC_B0:
            myCalc->Add(L"0");
            break;
        case IDC_B1:
            myCalc->Add(L"1");
            break;
        case IDC_B2:
            myCalc->Add(L"2");
            break;
        case IDC_B3:
            myCalc->Add(L"3");
            break;
        case IDC_B4:
            myCalc->Add(L"4");
            break;
        case IDC_B5:
            myCalc->Add(L"5");
            break;
        case IDC_B6:
            myCalc->Add(L"6");
            break;
        case IDC_B7:
            myCalc->Add(L"7");
            break;
        case IDC_B8:
            myCalc->Add(L"8");
            break;
        case IDC_B9:
            myCalc->Add(L"9");
            break;
        case IDC_BA:
            myCalc->Add(L"A");
            break;
        case IDC_BB:
            myCalc->Add(L"B");
            break;
        case IDC_BC:
            myCalc->Add(L"C");
            break;
        case IDC_BD:
            myCalc->Add(L"D");
            break;
        case IDC_BE:
            myCalc->Add(L"E");
            break;
        case IDC_BF:
            myCalc->Add(L"F");
            break;
        case IDC_BPLUS:
            myCalc->OnOperation(new Adder);
            break;
        case IDC_BMINUS:
            myCalc->OnOperation(new Subtractor);
            break;
        case IDC_BMULTI:
            myCalc->OnOperation(new Multiplier);
            break;
        case IDC_BDIV:
            myCalc->OnOperation(new Divider);
            break;
        case IDC_BDIVBY:
            myCalc->Invert();
            break;
        case IDC_BEQUAL:
            myCalc->Result(myCalc->curOp);
            break;
        case IDC_BCANCEL:
            myCalc->Cancel();
            break;
        case IDC_BCLEAN:
            myCalc->Clean();
            break;
        case IDC_BSIGN:
            myCalc->Oppose();
            break;
        case IDC_RDEC:
            for (int i = 0; i < 26; i++)
            {
                bool flag = i < 6 ? false : true;
                EnableWindow(GetDlgItem(hDlg, buttons[i]), flag);
            }
            myCalc->ChangeRadix(10);
            break;
        case IDC_RBIN:
            for (int i = 0; i < 26; i++)
            {
                bool flag = ((i > 13) && (i < 23)) ? true : false;
                EnableWindow(GetDlgItem(hDlg, buttons[i]), flag);
            }
            myCalc->ChangeRadix(2);
            break;
        case IDC_RHEX:
            for (int i = 0; i < 26; i++)
            {
                bool flag = i > 22 ? false : true;
                EnableWindow(GetDlgItem(hDlg, buttons[i]), flag);
            }
            myCalc->ChangeRadix(16);
            break;
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE;
}

void MyCalc::Create(HINSTANCE hInst, HWND hWnd)
{
    nums.clear();
    hWndCalc = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CALCULATOR), hWnd, (DLGPROC)CalcProc);
    ShowWindow(hWndCalc, SW_SHOW);
}

void MyCalc::Add(std::wstring input)
{
    if (next) {  
        if (input != L".") {       
            nums = input;
            next = FALSE;
        }
    }
    else {    
        if (!point)
            point = input == L"." ? TRUE : FALSE;
        nums.append(input);
    }
    SetDlgItemText(hWndCalc, IDC_EDIT, (LPCWSTR)nums.c_str());
}

void MyCalc::Set()
{   
    if (!x && !curOp) {    
        if (radix == 10) x = stod(nums);
        else x = stoi(nums, NULL, radix);
    } else {       
        if (radix == 10) y = stod(nums);
        else y = stoi(nums, NULL, radix);
    }
    next = TRUE;
}

 void MyCalc::Result(Operation* oop)
 {
     try { Set(); }
     catch (...) {
        Add(L"Enter number");
        next = TRUE;
        return;
     }
     if (!curOp) return;
     nums.clear();
     try {
        oop->Set(x, y);
        rez = oop->Do();
     }
     catch (...) {
        Add(L"You can't divide by 0");
        next = TRUE; x = NULL; y = NULL;
        rez = NULL; curOp = NULL;
        return;
     }
     if (radix != 10)
        tmpres = Convert(radix, (int)rez);
     else {
        tmpres = std::to_wstring(rez);
        if (tmpres.length() > 1) {
            while (tmpres.back() == '0') tmpres.pop_back();
            if (tmpres.back() == '.') tmpres.pop_back();
        }
     }
     x = NULL; y = NULL; rez = NULL;
     Add(tmpres);
     next = FALSE; curOp = NULL;
 }

void MyCalc::OnOperation(Operation* oop)
{
    try { Set(); }
    catch (...) {
        next = TRUE;
        Add(L"Enter number");
        next = TRUE;
        return;
    }   
    nums.clear();    
    if (!curOp) {
        curOp = oop;
        rez = x;
    }    
    else {
        try {   
            curOp->Set(x, y);
            rez = curOp->Do();
        } 
        catch (...) {            
            Add(L"You can't divide by 0");
            next = TRUE; x = NULL; y = NULL; rez = NULL; curOp = NULL;
            return;    
        }    
        x = rez; y = NULL;        
    }            
    if (radix != 10)
        tmpres = Convert(radix, (int)rez);            
    else {
        tmpres = std::to_wstring(rez);
        if (tmpres.length() > 1) {
            while (tmpres.back() == '0') tmpres.pop_back();
            if (tmpres.back() == '.') tmpres.pop_back();
        }
    }
    Add(tmpres);
    next = TRUE;
    point = FALSE;
    curOp = oop;
}

void MyCalc::Invert()
{
    Operation * pp = new Divider;  
    x = 1;
    try { Set();}
    catch (...) {
        Add(L"Enter number");
        next = TRUE;
        return;
    }
    pp->Set(x, y);
    try { rez = pp->Do(); }
    catch (...) {
        Add(L"You can't divide by 0");
        next = TRUE; x = NULL; y = NULL; rez = NULL; curOp = NULL;
        return;
    }
    x = rez; y = NULL;
    tmpres = std::to_wstring(rez);
    if (tmpres.length() > 1) {
        while (tmpres.back() == '0') tmpres.pop_back();
        if (tmpres.back() == '.') tmpres.pop_back();
    }
    Add(tmpres);
    next = TRUE;
    point = FALSE;
    curOp = NULL;
    delete pp;     
}

void MyCalc::Oppose()
{   
    if (nums.empty()) return;
    std::wstring temp;
    temp = std::to_wstring((-1) * stod(nums));
    while (temp.back() == '0') temp.pop_back();
    if (temp.back() == '.') temp.pop_back();   
    next = TRUE;
    Add(temp);
}

void MyCalc::Cancel()
{
    if (nums.empty()) return;
    nums.pop_back();
    if (nums.find(L".", 0) > (nums.length() - 1)) point = FALSE;
    next = TRUE;
    Add(nums);
}

void MyCalc::Clean()
{
    next = TRUE;
    nums = L"";
    Add(nums);
    point = FALSE;
    x = NULL;
    y = NULL;
    rez = NULL;
    tmpres = L"";
    curOp = NULL;
}

std::wstring MyCalc::Convert(int r, int N)
{ 
    wchar_t buff[100];
#pragma warning(suppress : 4996)
    _itow(N, buff, r);
    return buff;
}

void MyCalc::ChangeRadix(int r)
{
    if (!nums.empty()) {
        next = TRUE;
        Add(Convert(r, stoi(nums, NULL, radix)));
        next = TRUE;
    }
    radix = r;
}
