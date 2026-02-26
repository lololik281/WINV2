#include <windows.h>
#include <commctrl.h>
#include <tchar.h>

#define IDC_EDIT_LOGIN      1001
#define IDC_COMBOBOX        1002
#define IDC_LISTBOX         1003

typedef struct {
	TCHAR szText[64];
	int iIconIndex;
} LIST_ITEM, *PLIST_ITEM;

HIMAGELIST g_himl = NULL;
HICON g_hIconFolder = NULL;
HICON g_hIconFile = NULL;
HICON g_hIconDrive = NULL;
HICON g_hIconSystem = NULL;

BOOL InitGlobalImageList()
{
	if (g_himl)
		return TRUE;

	g_himl = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, 4, 0);
	if (!g_himl)
		return FALSE;

	g_hIconFolder = (HICON)LoadImage(NULL, IDI_FOLDER, IMAGE_ICON, 16, 16, LR_SHARED);
	g_hIconFile = (HICON)LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 16, 16, LR_SHARED);
	g_hIconDrive = (HICON)LoadImage(NULL, IDI_WINLOGO, IMAGE_ICON, 16, 16, LR_SHARED);
	g_hIconSystem = (HICON)LoadImage(NULL, IDI_SHIELD, IMAGE_ICON, 16, 16, LR_SHARED);

	ImageList_AddIcon(g_himl, g_hIconFolder ? g_hIconFolder : LoadIcon(NULL, IDI_APPLICATION));
	ImageList_AddIcon(g_himl, g_hIconFile ? g_hIconFile : LoadIcon(NULL, IDI_APPLICATION));
	ImageList_AddIcon(g_himl, g_hIconDrive ? g_hIconDrive : LoadIcon(NULL, IDI_APPLICATION));
	ImageList_AddIcon(g_himl, g_hIconSystem ? g_hIconSystem : LoadIcon(NULL, IDI_APPLICATION));

	return TRUE;
}

void CleanupGlobalResources()
{
	if (g_himl)
	{
		ImageList_Destroy(g_himl);
		g_himl = NULL;
	}
}

void InitComboBoxWithData(HWND hCombo)
{
	LIST_ITEM items[] = {
		{ TEXT("Мои документы"), 0 },
		{ TEXT("Рабочий стол"), 0 },
		{ TEXT("readme.txt"), 1 },
		{ TEXT("config.ini"), 1 },
		{ TEXT("Локальный диск (C:)"), 2 },
		{ TEXT("Система (Windows)"), 3 },
		{ TEXT("program.exe"), 1 },
		{ TEXT("Загрузки"), 0 }
	};

	for (int i = 0; i < 8; i++)
	{
		PLIST_ITEM pItem = (PLIST_ITEM)malloc(sizeof(LIST_ITEM));
		if (pItem)
		{
			_tcscpy_s(pItem->szText, items[i].szText);
			pItem->iIconIndex = items[i].iIconIndex;

			int index = (int)SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)pItem->szText);
			SendMessage(hCombo, CB_SETITEMDATA, index, (LPARAM)pItem);
		}
	}
}

void InitListBoxWithData(HWND hListBox)
{
	LIST_ITEM items[] = {
		{ TEXT("Мои документы"), 0 },
		{ TEXT("Рабочий стол"), 0 },
		{ TEXT("readme.txt"), 1 },
		{ TEXT("config.ini"), 1 },
		{ TEXT("Локальный диск (C:)"), 2 },
		{ TEXT("Система (Windows)"), 3 },
		{ TEXT("program.exe"), 1 },
		{ TEXT("Загрузки"), 0 },
		{ TEXT("Новая папка"), 0 },
		{ TEXT("data.dat"), 1 }
	};

	for (int i = 0; i < 10; i++)
	{
		PLIST_ITEM pItem = (PLIST_ITEM)malloc(sizeof(LIST_ITEM));
		if (pItem)
		{
			_tcscpy_s(pItem->szText, items[i].szText);
			pItem->iIconIndex = items[i].iIconIndex;

			int index = (int)SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)pItem->szText);
			SendMessage(hListBox, LB_SETITEMDATA, index, (LPARAM)pItem);
		}
	}
}

void OnMeasureItemCombo(LPMEASUREITEMSTRUCT lpMIS)
{
	if (lpMIS->CtlID == IDC_COMBOBOX)
	{
		lpMIS->itemHeight = 20;
	}
}

void OnMeasureItemListBox(LPMEASUREITEMSTRUCT lpMIS)
{
	if (lpMIS->CtlID == IDC_LISTBOX)
	{
		lpMIS->itemHeight = 20;
	}
}

void OnDrawItemCombo(LPDRAWITEMSTRUCT lpDIS)
{
	if (lpDIS->itemID == -1)
		return;

	PLIST_ITEM pItem = (PLIST_ITEM)SendMessage(lpDIS->hwndItem, CB_GETITEMDATA, lpDIS->itemID, 0);
	if (!pItem)
		return;

	if (lpDIS->itemState & ODS_SELECTED)
	{
		FillRect(lpDIS->hDC, &lpDIS->rcItem, GetSysColorBrush(COLOR_HIGHLIGHT));
		SetBkColor(lpDIS->hDC, GetSysColor(COLOR_HIGHLIGHT));
		SetTextColor(lpDIS->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		FillRect(lpDIS->hDC, &lpDIS->rcItem, GetSysColorBrush(COLOR_WINDOW));
		SetBkColor(lpDIS->hDC, GetSysColor(COLOR_WINDOW));
		SetTextColor(lpDIS->hDC, GetSysColor(COLOR_WINDOWTEXT));
	}

	ImageList_Draw(g_himl, pItem->iIconIndex, lpDIS->hDC,
		lpDIS->rcItem.left + 2,
		lpDIS->rcItem.top + (lpDIS->rcItem.bottom - lpDIS->rcItem.top - 16) / 2,
		ILD_TRANSPARENT);

	RECT textRect = lpDIS->rcItem;
	textRect.left += 22;
	DrawText(lpDIS->hDC, pItem->szText, -1, &textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

void OnDrawItemListBox(LPDRAWITEMSTRUCT lpDIS)
{
	if (lpDIS->itemID == -1)
		return;

	PLIST_ITEM pItem = (PLIST_ITEM)SendMessage(lpDIS->hwndItem, LB_GETITEMDATA, lpDIS->itemID, 0);
	if (!pItem)
		return;

	if (lpDIS->itemState & ODS_SELECTED)
	{
		FillRect(lpDIS->hDC, &lpDIS->rcItem, GetSysColorBrush(COLOR_HIGHLIGHT));
		SetBkColor(lpDIS->hDC, GetSysColor(COLOR_HIGHLIGHT));
		SetTextColor(lpDIS->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		FillRect(lpDIS->hDC, &lpDIS->rcItem, GetSysColorBrush(COLOR_WINDOW));
		SetBkColor(lpDIS->hDC, GetSysColor(COLOR_WINDOW));
		SetTextColor(lpDIS->hDC, GetSysColor(COLOR_WINDOWTEXT));
	}

	ImageList_Draw(g_himl, pItem->iIconIndex, lpDIS->hDC,
		lpDIS->rcItem.left + 2,
		lpDIS->rcItem.top + (lpDIS->rcItem.bottom - lpDIS->rcItem.top - 16) / 2,
		ILD_TRANSPARENT);

	RECT textRect = lpDIS->rcItem;
	textRect.left += 22;
	DrawText(lpDIS->hDC, pItem->szText, -1, &textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	if (lpDIS->itemState & ODS_FOCUS)
	{
		DrawFocusRect(lpDIS->hDC, &lpDIS->rcItem);
	}
}

void OnComboBoxOK(HWND hDlg)
{
	HWND hCombo = GetDlgItem(hDlg, IDC_COMBOBOX);
	int selectedIndex = (int)SendMessage(hCombo, CB_GETCURSEL, 0, 0);

	if (selectedIndex != CB_ERR)
	{
		TCHAR selectedText[256];
		SendMessage(hCombo, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

		PLIST_ITEM pItem = (PLIST_ITEM)SendMessage(hCombo, CB_GETITEMDATA, selectedIndex, 0);

		TCHAR message[512];
		if (pItem)
		{
			TCHAR* typeText = TEXT("неизвестно");
			switch (pItem->iIconIndex)
			{
			case 0: typeText = TEXT("папка"); break;
			case 1: typeText = TEXT("файл"); break;
			case 2: typeText = TEXT("диск"); break;
			case 3: typeText = TEXT("системный"); break;
			}

			wsprintf(message,
				TEXT("Вы выбрали пункт №%d со значением '%s' (тип: %s)."),
				selectedIndex + 1, selectedText, typeText);
		}
		else
		{
			wsprintf(message,
				TEXT("Вы выбрали пункт №%d со значением '%s'."),
				selectedIndex + 1, selectedText);
		}

		MessageBox(hDlg, message, TEXT("Выбор в ComboBox"), MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(hDlg, TEXT("В ComboBox ничего не выбрано!"),
			TEXT("Ошибка"), MB_OK | MB_ICONWARNING);
	}
}

void OnListBoxOK(HWND hDlg)
{
	HWND hListBox = GetDlgItem(hDlg, IDC_LISTBOX);
	int selectedIndex = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);

	if (selectedIndex != LB_ERR)
	{
		TCHAR selectedText[256];
		SendMessage(hListBox, LB_GETTEXT, selectedIndex, (LPARAM)selectedText);

		PLIST_ITEM pItem = (PLIST_ITEM)SendMessage(hListBox, LB_GETITEMDATA, selectedIndex, 0);

		TCHAR message[512];
		if (pItem)
		{
			TCHAR* typeText = TEXT("неизвестно");
			switch (pItem->iIconIndex)
			{
			case 0: typeText = TEXT("папка"); break;
			case 1: typeText = TEXT("файл"); break;
			case 2: typeText = TEXT("диск"); break;
			case 3: typeText = TEXT("системный"); break;
			}

			wsprintf(message,
				TEXT("Вы выбрали пункт №%d со значением '%s' (тип: %s)."),
				selectedIndex + 1, selectedText, typeText);
		}
		else
		{
			wsprintf(message,
				TEXT("Вы выбрали пункт №%d со значением '%s'."),
				selectedIndex + 1, selectedText);
		}

		MessageBox(hDlg, message, TEXT("Выбор в ListBox"), MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(hDlg, TEXT("В ListBox ничего не выбрано!"),
			TEXT("Ошибка"), MB_OK | MB_ICONWARNING);
	}
}

void CleanupComboBoxItems(HWND hDlg)
{
	HWND hCombo = GetDlgItem(hDlg, IDC_COMBOBOX);
	if (hCombo)
	{
		int count = (int)SendMessage(hCombo, CB_GETCOUNT, 0, 0);
		for (int i = 0; i < count; i++)
		{
			PLIST_ITEM pItem = (PLIST_ITEM)SendMessage(hCombo, CB_GETITEMDATA, i, 0);
			if (pItem)
				free(pItem);
		}
	}
}

void CleanupListBoxItems(HWND hDlg)
{
	HWND hListBox = GetDlgItem(hDlg, IDC_LISTBOX);
	if (hListBox)
	{
		int count = (int)SendMessage(hListBox, LB_GETCOUNT, 0, 0);
		for (int i = 0; i < count; i++)
		{
			PLIST_ITEM pItem = (PLIST_ITEM)SendMessage(hListBox, LB_GETITEMDATA, i, 0);
			if (pItem)
				free(pItem);
		}
	}
}

INT_PTR CALLBACK ComboBoxDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hDlg, IDC_EDIT_LOGIN, TEXT("Введите имя пользователя"));
		InitGlobalImageList();
		InitComboBoxWithData(GetDlgItem(hDlg, IDC_COMBOBOX));
		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmNotification = HIWORD(wParam);

		if (wmId == IDC_EDIT_LOGIN)
		{
			static TCHAR szUserLogin[256] = TEXT("");

			switch (wmNotification)
			{
			case EN_SETFOCUS:
			{
				TCHAR currentText[256];
				GetDlgItemText(hDlg, IDC_EDIT_LOGIN, currentText, 256);
				if (_tcscmp(currentText, TEXT("Введите имя пользователя")) == 0)
				{
					SetDlgItemText(hDlg, IDC_EDIT_LOGIN, TEXT(""));
				}
				break;
			}

			case EN_KILLFOCUS:
			{
				TCHAR currentText[256];
				GetDlgItemText(hDlg, IDC_EDIT_LOGIN, currentText, 256);

				if (lstrlen(currentText) == 0)
				{
					SetDlgItemText(hDlg, IDC_EDIT_LOGIN, TEXT("Введите имя пользователя"));
				}
				else
				{
					_tcscpy_s(szUserLogin, currentText);
				}
				break;
			}
			}
			return (INT_PTR)TRUE;
		}

		if (wmId == IDOK)
		{
			OnComboBoxOK(hDlg);
			return (INT_PTR)TRUE;
		}

		if (wmId == IDCANCEL)
		{
			CleanupComboBoxItems(hDlg);
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
		}
		break;
	}

	case WM_MEASUREITEM:
	{
		OnMeasureItemCombo((LPMEASUREITEMSTRUCT)lParam);
		return (INT_PTR)TRUE;
	}

	case WM_DRAWITEM:
	{
		OnDrawItemCombo((LPDRAWITEMSTRUCT)lParam);
		return (INT_PTR)TRUE;
	}

	case WM_DESTROY:
	{
		CleanupComboBoxItems(hDlg);
		CleanupGlobalResources();
		return (INT_PTR)TRUE;
	}
	}

	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ListBoxDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hDlg, IDC_EDIT_LOGIN, TEXT("Введите имя пользователя"));
		InitGlobalImageList();

		HWND hListBox = GetDlgItem(hDlg, IDC_LISTBOX);
		SendMessage(hListBox, LB_SETHORIZONTALEXTENT, 300, 0);
		InitListBoxWithData(hListBox);
		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmNotification = HIWORD(wParam);

		if (wmId == IDC_EDIT_LOGIN)
		{
			static TCHAR szUserLogin[256] = TEXT("");

			switch (wmNotification)
			{
			case EN_SETFOCUS:
			{
				TCHAR currentText[256];
				GetDlgItemText(hDlg, IDC_EDIT_LOGIN, currentText, 256);
				if (_tcscmp(currentText, TEXT("Введите имя пользователя")) == 0)
				{
					SetDlgItemText(hDlg, IDC_EDIT_LOGIN, TEXT(""));
				}
				break;
			}

			case EN_KILLFOCUS:
			{
				TCHAR currentText[256];
				GetDlgItemText(hDlg, IDC_EDIT_LOGIN, currentText, 256);

				if (lstrlen(currentText) == 0)
				{
					SetDlgItemText(hDlg, IDC_EDIT_LOGIN, TEXT("Введите имя пользователя"));
				}
				else
				{
					_tcscpy_s(szUserLogin, currentText);
				}
				break;
			}
			}
			return (INT_PTR)TRUE;
		}

		if (wmId == IDOK)
		{
			OnListBoxOK(hDlg);
			return (INT_PTR)TRUE;
		}

		if (wmId == IDC_LISTBOX && wmNotification == LBN_DBLCLK)
		{
			OnListBoxOK(hDlg);
			return (INT_PTR)TRUE;
		}

		if (wmId == IDCANCEL)
		{
			CleanupListBoxItems(hDlg);
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
		}
		break;
	}

	case WM_MEASUREITEM:
	{
		OnMeasureItemListBox((LPMEASUREITEMSTRUCT)lParam);
		return (INT_PTR)TRUE;
	}

	case WM_DRAWITEM:
	{
		OnDrawItemListBox((LPDRAWITEMSTRUCT)lParam);
		return (INT_PTR)TRUE;
	}

	case WM_DESTROY:
	{
		CleanupListBoxItems(hDlg);
		CleanupGlobalResources();
		return (INT_PTR)TRUE;
	}
	}

	return (INT_PTR)FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_STANDARD_CLASSES;
	InitCommonControlsEx(&icex);

	return 0;
}