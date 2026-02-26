#include<Windows.h>
#include<iostream>
#include<cstdio>
#include"resource.h"

CONST CHAR* ITEMS[] = { "This", "is", "my", "first", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
    return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
        SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

        HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
        
        
        for (int i = 0; i < sizeof(ITEMS) / sizeof(ITEMS[0]); i++)
        {
            SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)ITEMS[i]);
        }
        
        
        SendMessage(hCombo, CB_SETCURSEL, 0, 0);
    }
    break;
    
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            CONST INT SIZE = 256;
            CHAR sz_buffer[SIZE] = {};
            CHAR sz_message[SIZE] = {};
            HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);

            
            INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
            
            if (i != CB_ERR)  
            {
                
                SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
                
                
                sprintf(sz_message, "Вы выбрали пункт №%i со значением \"%s\".", i, sz_buffer);
                
                MessageBox(hwnd, sz_message, "Информация", MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(hwnd, "Пожалуйста, выберите элемент из списка", "Информация", MB_OK | MB_ICONWARNING);
            }
        }
        break;
        
        case IDCANCEL:
            EndDialog(hwnd, 0);
            break;
            
        case IDC_COMBO:  
            switch (HIWORD(wParam))
            {
            case CBN_SELCHANGE:  
                
                break;
            }
            break;
        }
        break;
        
    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;
    }
    return FALSE;
}