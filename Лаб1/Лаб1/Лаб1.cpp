// Лаб1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Лаб1.h"



#include <tchar.h>

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

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 	
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int a = 0, b = 0, c = 255;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT custom;
	RECT rect1 = { 0,0,50,50 };
	RECT rect2 = { 0,0,100,100 };
	RECT rect3 = { 0,0,150,150 };
	switch (message) // Обработчик сообщений
	{
	case WM_PAINT:
	{
		HDC hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &custom);
		FillRect(hdc, &rect3, CreateSolidBrush(RGB(c, a, b)));
		GetClientRect(hWnd, &custom);
		FillRect(hdc, &rect2, CreateSolidBrush(RGB(b, c, a)));
		GetClientRect(hWnd, &custom);
		FillRect(hdc, &rect1, CreateSolidBrush(RGB(a, b, c)));
		break;
	}
	case WM_LBUTTONDOWN:
	{
		int z = a;
		a = b;
		b = c;
		c = z;

		HDC hdc = GetDC(hWnd);
		GetClientRect(hWnd, &custom);
		FillRect(hdc, &rect3, CreateSolidBrush(RGB(c, a, b)));
		GetClientRect(hWnd, &custom);
		FillRect(hdc, &rect2, CreateSolidBrush(RGB(b, c, a)));
		GetClientRect(hWnd, &custom);
		FillRect(hdc, &rect1, CreateSolidBrush(RGB(a, b, c)));
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		Sleep(150);
		PostQuitMessage(0);
		break;
	}
	case WM_CREATE:
	default: // Обработка сообщения по умолчанию
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
