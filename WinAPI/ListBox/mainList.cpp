#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* INITIAL_VALUES[] = { "This", "is", "my", "first", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AddDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EditDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hMainWindow = NULL;

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
        hMainWindow = hwnd;
        HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
        for (int i = 0; i < sizeof(INITIAL_VALUES) / sizeof(INITIAL_VALUES[0]); i++)
        {
            SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)INITIAL_VALUES[i]);
        }
    }
    break;
    
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:  
        {
            CONST INT SIZE = 256;
            CHAR sz_buffer[SIZE] = {};
            HWND hListBox = GetDlgItem(hwnd, IDC_LIST);

            INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
            CHAR sz_message[SIZE] = {};
            sprintf(sz_message, "Вы выбрали пункт №%i со значением \"%s\".", i, sz_buffer);
            if(i != LB_ERR) MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
            else MessageBox(hwnd, "Для начала выберите элемент", "Info", MB_OK | MB_ICONINFORMATION);
        }
        break;
        
        case IDC_ADD:  
        {
            DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ADD_DIALOG), hwnd, AddDlgProc, 0);
        }
        break;
        
        case IDC_DELETE:  
        {
            HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
            INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            
            if (i != LB_ERR)
            {
                SendMessage(hListBox, LB_DELETESTRING, i, 0);
            }
            else
            {
                MessageBox(hwnd, "Выберите элемент для удаления", "Информация", MB_OK | MB_ICONINFORMATION);
            }
        }
        break;
        
        case IDCANCEL:  
            EndDialog(hwnd, 0);
            break;
        }
        break;
        
    case WM_NOTIFY:  
        
        break;
        
    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;
    }
    return FALSE;
}


BOOL CALLBACK AddDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        
        SetFocus(GetDlgItem(hwnd, IDC_EDIT));
        return FALSE;
        
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            CONST INT SIZE = 256;
            CHAR buffer[SIZE] = {};
            
            
            GetDlgItemText(hwnd, IDC_EDIT, buffer, SIZE);
            
            
            if (strlen(buffer) > 0)
            {
                HWND hMainListBox = GetDlgItem(hMainWindow, IDC_LIST);
                SendMessage(hMainListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
            }
            
            EndDialog(hwnd, 1);  
        }
        break;
        
        case IDCANCEL:
            EndDialog(hwnd, 0);  
            break;
        }
        return TRUE;
    }
    return FALSE;
}


BOOL CALLBACK EditDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int selectedIndex = -1;
    
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        
        selectedIndex = (int)lParam;
        
        if (selectedIndex != -1)
        {
            
            HWND hMainListBox = GetDlgItem(hMainWindow, IDC_LIST);
            CONST INT SIZE = 256;
            CHAR buffer[SIZE] = {};
            
            SendMessage(hMainListBox, LB_GETTEXT, selectedIndex, (LPARAM)buffer);
            
            
            SetDlgItemText(hwnd, IDC_EDIT, buffer);
        }
        
        SetFocus(GetDlgItem(hwnd, IDC_EDIT));
        return FALSE;
    }
        
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            if (selectedIndex != -1)
            {
                CONST INT SIZE = 256;
                CHAR buffer[SIZE] = {};
                
                
                GetDlgItemText(hwnd, IDC_EDIT, buffer, SIZE);
                
                if (strlen(buffer) > 0)
                {
                    
                    HWND hMainListBox = GetDlgItem(hMainWindow, IDC_LIST);
                    SendMessage(hMainListBox, LB_DELETESTRING, selectedIndex, 0);
                    SendMessage(hMainListBox, LB_INSERTSTRING, selectedIndex, (LPARAM)buffer);
                }
            }
            
            EndDialog(hwnd, 1);
        }
        break;
        
        case IDCANCEL:
            EndDialog(hwnd, 0);
            break;
        }
        return TRUE;
    }
    return FALSE;
}