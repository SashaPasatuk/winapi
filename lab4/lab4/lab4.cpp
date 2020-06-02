// lab4.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "lab4.h"
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <wchar.h>
#define DIV 1024
#define WIDTH 7
//#pragma warning(disable:4996)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Каркас Windows-приложения"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно
	
	//HMENU WINAPI a;
	HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	HMENU hPopupMenu2 = CreatePopupMenu();
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Фигура");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"Включить");
		//AppendMenu(hPopupMenu, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu, MF_STRING, 1002, L"Выключить");
	}
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu2, L"&Текст");
	{
		AppendMenu(hPopupMenu2, MF_STRING, 1003, L"Включить");
		//AppendMenu(hPopupMenu2, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu2, MF_STRING, 1004, L"Выключить");
	}
	SetMenu(hWnd, MainMenu);

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

HANDLE hThread1;
HANDLE hThread2;
DWORD WINAPI Thread1(LPVOID t);
DWORD WINAPI Thread2(LPVOID t);
static RECT clientRect= {600,100, 900, 200};
static int size = 0;
static wchar_t*symbol = new wchar_t[10];
static RECT rect;
int a = 0;
BOOL fin1 = true;
BOOL fin2 = true;

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ 
	HDC hdc;
	//static int size = 0;
//	static wchar_t*symbol = new wchar_t[10];
	//wchar_t text[10];
	//static RECT rect = { 300,100, 500, 200};
	//static RECT clientRect= { 300,100, 500, 200};
	PAINTSTRUCT paintStruct;
    
	switch (message)		 // Обработчик сообщений
	{
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &paintStruct);
           /* GetClientRect(hWnd, &clientRect);
            if (size > 0)
                DrawText(hdc, (LPCWSTR)symbol, size, &clientRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);*/
            
			EndPaint(hWnd, &paintStruct);
            break;
		}
	case WM_CHAR:
		{
			if (fin2)
			{
				  if (wParam == VK_BACK)
			      {
				     size--;
				     InvalidateRect(hWnd, NULL, TRUE);
			      }
				  else
		          {
					 symbol[size] = (wchar_t)wParam;
					 size++;
				  }
				  InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_COMMAND:
		{
			
			
		switch (wParam)
		{
		case 1001:
		{
			fin1 = true;
			hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
			break;
		}
		case 1002:
		{
			TerminateThread(hThread1, 0);
			CloseHandle(hThread1);
			fin1 = FALSE;
			HDC hdc = GetDC(hWnd);
			HBRUSH hBrush;
			HPEN hPen;
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			hPen = CreatePen(PS_NULL, 1, RGB(255, 255, 255));
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			Ellipse(hdc, 20, 20, 120, 570);
			break;
		}
		case 1003:
		{
			fin2 = TRUE;
			hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);
			break;
		}
		case 1004:
		{
			TerminateThread(hThread2, 0);
			CloseHandle(hThread2);
			fin2 = FALSE;
			InvalidateRect(hWnd, NULL, true);
		    UpdateWindow(hWnd);
			for (int i=0; i<size; i++)
			{
				symbol[i]=NULL;
			}
			size=0;
			break;
		}
		}   
	}
	}
	return 0;
}

DWORD WINAPI Thread1(LPVOID t)
{
	int height=0;
	while (fin1)
	{
		GetWindowRect(HWND(t), &rect);
      // int width = (int)(rect.right - rect.left);
        int height = (int)(rect.bottom - rect.top);
		height = height-100;
		int i=0;
		int a=-1,b=49;
		for (i=0; i<height; i++)
		{
			a=a+1;
			b=b+1;
			HDC hdc = GetDC(HWND(t));
			HBRUSH hBrush;
			HPEN hPen;
			hBrush = CreateSolidBrush(RGB(0, 240, 250));
			hPen = CreatePen(PS_NULL, 1, RGB(255, 255, 255));
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			Ellipse(hdc, 50, a, 100, b);
			Sleep(5);
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			hPen = CreatePen(PS_NULL, 1, RGB(255, 255, 255));
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);
			Ellipse(hdc, 50, a, 100, b);
			ReleaseDC(HWND(t), hdc);
		}
		for ( i; i>=1; i--)
		{
			a=a-1;
			b=b-1;
			HDC hdc = GetDC(HWND(t));
			HBRUSH hBrush;
			HPEN hPen;
			hBrush = CreateSolidBrush(RGB(0, 240, 250));
			hPen = CreatePen(PS_NULL, 1, RGB(255, 255, 255));
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			Ellipse(hdc, 50, a, 100, b);
			Sleep(5);
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			hPen = CreatePen(PS_NULL, 1, RGB(255, 255, 255));
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);
			Ellipse(hdc, 50, a, 100, b);
			ReleaseDC(HWND(t), hdc);
		}
	}
	return (0);
}

DWORD WINAPI Thread2(LPVOID t)
{
	while (fin2)
	{
		HDC hdc = GetDC(HWND(t));
		
		GetClientRect(HWND(t), &clientRect);
	    if (size > 0)
		      DrawText(hdc, (LPCWSTR)symbol, size, &clientRect, DT_RIGHT | DT_SINGLELINE | DT_VCENTER);
		ReleaseDC(HWND(t), hdc);
	}
	return 0;

}





	/*static int x = 600, y = 100;
    static wchar_tsymbol = new wchar_t[100];
    static int size = 0;
    wchar_t text[255];
    HDC hdc;
    PAINTSTRUCT paintStruct;
    RECT clientRect;
    RECT rect = { x,y,x + 70,y + 70 };
    HFONT hFont = CreateFont(90, 0, 0, 0, 0, 0, 0, 0,
        DEFAULT_CHARSET,
        0, 0, 0, 0,
        L"Arial Bold");
    switch (message)
    {
   
        hDC = BeginPaint(hwnd, &paintStruct);
        GetClientRect(hwnd, &clientRect);
        if (size > 0)
            DrawText(hDC, (LPCWSTR)symbol, size, &clientRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        EndPaint(hwnd, &paintStruct);
        break;
        if (wParam == VK_BACK)
        {
            size--;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else
        {
            symbol[size] = (wchar_t)wParam;
            size++;
        }
        InvalidateRect(hwnd, NULL, TRUE);

    }
    return 0;
}*/