// winapi ���2_1.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "winapi ���2_1.h"
#include <tchar.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
HINSTANCE Prev, 	// � ����������� �������� ������ 0 
LPTSTR cmd, 		// ��������� ������ 
int mode) 		// ����� ����������� ����
{ 
	HWND hWnd;		// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	// ����������� ������ ���� 
	wc.hInstance = This; 
	wc.lpszClassName = WinName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1); 	// ���������� ���� ����� ������ 

	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0; 	

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_T("���� 1"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 ������� ���� 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 

	ShowWindow(hWnd, mode); 
	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 	
	} 
	return 0;// �������� ����
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			HWND hWnd1 = FindWindow(0, _T("���� 2"));
			if (hWnd1)
				MessageBox(hWnd, TEXT("���������� ������!"), TEXT("Message box from first project"), MB_OK);
			else
				PostQuitMessage(0);
			SendMessage(hWnd1, WM_USER + 1, (WPARAM)hWnd, lParam);
			MessageBox(hWnd, TEXT("���������� ��������� ������� ����."), TEXT("Message box from first project"), MB_OK);
			break;
		}
	case WM_RBUTTONDOWN:
		{
		HWND hWnd2_2 = FindWindow(0, _T("���� 2"));
		MessageBox(hWnd2_2, TEXT("��������� �������."), TEXT("Message box from first project"), MB_OK);
		break;
		}
	case WM_CREATE:
		default: // ��������� ��������� �� ���������
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

