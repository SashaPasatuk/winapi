// winapi лаб2_1.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "winapi лаб2_1.h"
#include <tchar.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

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
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1); 	// Заполнение окна белым цветом 

	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0; 	

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Окно 1"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 
	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 	
	} 
	return 0;// Показать окно
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			HWND hWnd1 = FindWindow(0, _T("Окно 2"));
			if (hWnd1)
				MessageBox(hWnd, TEXT("Дискриптор найден!"), TEXT("Message box from first project"), MB_OK);
			else
				PostQuitMessage(0);
			SendMessage(hWnd1, WM_USER + 1, (WPARAM)hWnd, lParam);
			MessageBox(hWnd, TEXT("Дискриптор отправлен второму окну."), TEXT("Message box from first project"), MB_OK);
			break;
		}
	case WM_RBUTTONDOWN:
		{
		HWND hWnd2_2 = FindWindow(0, _T("Окно 2"));
		MessageBox(hWnd2_2, TEXT("Сообщение принято."), TEXT("Message box from first project"), MB_OK);
		break;
		}
	case WM_CREATE:
		default: // Обработка сообщения по умолчанию
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

