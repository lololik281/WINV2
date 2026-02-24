#include<Windows.h>
#include<iostream>
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
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//https://stackoverflow.com/questions/15543571/allocconsole-not-displaying-cout
		for (int i = 0; i < sizeof(ITEMS) / sizeof(ITEMS[0]); i++)
		{
			//std::cout << ITEMS[i] << std::endl;
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)ITEMS[i]);
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
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);

			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);	//Получаем номер выбранного элемента
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);	//Считываем содержимое выбранной строки в буфер

			MessageBox(hwnd, sz_buffer, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}