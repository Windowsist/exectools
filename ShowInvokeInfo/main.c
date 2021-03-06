
#include "main.h"

DWORD Startup()
{
	ExitProcess((UINT)DialogBoxParamW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(IDD_DIALOG1), NULL, DlgProc, 0LL));
	return 0UL;
}

INT_PTR DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT1), GetCommandLineW());
		{
			wchar_t curdir[MAX_PATH];
			GetCurrentDirectoryW(MAX_PATH, curdir);
			SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT2), curdir);
		}
		LPWCH env = GetEnvironmentStringsW();
		int envlen = 0;
		for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
		{
			envlen += lstrlenW(i) + 2;
		}
		LPWSTR envString = calloc((envlen + 1) , sizeof(wchar_t));
		envString[0] = L'\0';
		for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
		{
			lstrcatW(envString, i);
			lstrcatW(envString, L"\r\n");
		}
		FreeEnvironmentStringsW(env);
		SetWindowTextW(GetDlgItem(hDlg, IDC_EDIT3), envString);
		free(envString);
	}
	return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, (INT_PTR)0);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}