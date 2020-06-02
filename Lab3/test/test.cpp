// test.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "test.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	static HDC hdc;
	HFONT newfont;
	static int a=0;
	static int b=0;
	RECT rect = {290,90,900, 150};
	switch (message)
	{

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_EXIT:
		{
			DestroyWindow(hWnd);
			break;
		}
		case IDM_KURS:
		{
			b=1;
			InvalidateRect(hWnd, NULL, true);
		    UpdateWindow(hWnd);
			break;
		}
		case IDM_PODCH:
		{
			b=2;
			InvalidateRect(hWnd, NULL, true);
		    UpdateWindow(hWnd);
			break;
		}
		case IDM_GIRN:
		{
			b=3;
			InvalidateRect(hWnd, NULL, true);
			UpdateWindow(hWnd);
			ReleaseDC(hWnd, hdc);
			break;
		}
		case IDM_FONT1:
		{
			a=1;
			InvalidateRect(hWnd, NULL, true);
			UpdateWindow(hWnd);
			break;
		}
		case IDM_FONT2:
		{
			a=2;
			InvalidateRect(hWnd, NULL, true);
			UpdateWindow(hWnd);
			break;
		}
		case IDM_FONT3:
		{	
			a=3;
			InvalidateRect(hWnd, NULL, true);
			UpdateWindow(hWnd);
			break;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps); // начало перерисовки
		if (a==1)
		{	if (b==0)
			{
				newfont=CreateFontW (40, 0, 0, 0, 400, 0, 0, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Calibri"));
				SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Обычный Calibri"), 15);
			}
			if (b==1)
			{
				newfont=CreateFontW (40, 0, 0, 0, 400, 1, 0, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Calibri"));
			    SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Calibri курсив"),14);
			}
			if (b==2)
			{
				newfont=CreateFontW (40, 0, 0, 0, 400, 0, 1, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Calibri"));
			    SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Calibri подчеркнутый"), 20);
			}
			if (b==3)
			{
				newfont=CreateFontW (40, 0, 0, 0, 1000, 0, 0, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Calibri"));
			    SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Calibri полужирный"), 18);
			}
		}
		if (a==2)
		{
			if (b==0)
			{
				newfont=CreateFontW (40, 0, 0, 0, 400, 0, 0, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Times New Roman"));
				SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Обычный Times New Roman"), 23);	
			}
			if (b==1)
			{
				newfont=CreateFontW (40, 0, 0, 0, 400, 1, 0, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Times New Roman"));
			    SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Times New Roman курсив"),22);
			}
			if (b==2)
			{
				newfont=CreateFontW (40, 0, 0, 0, 400, 0, 1, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Times New Roman"));
			    SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Times New Roman подчеркнутый"), 28);
			}
			if (b==3)
			{
				newfont=CreateFontW (40, 0, 0, 0, 1000, 0, 0, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Times New Roman"));
			    SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Times New Roman полужирный"), 26);
			}
		}
		if (a==3)
		{
			if(b==0)
			{
				newfont=CreateFontW (40, 0, 0, 0, 400, 0, 0, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Arial"));
				SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Обычный Arial"), 13);
			}
			if (b==1)
			{
				newfont=CreateFontW (40, 0, 0, 0, 400, 1, 0, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Arial"));
			    SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Arial курсив"),12);
			}
			if (b==2)
			{
				newfont=CreateFontW (40, 0, 0, 0, 400, 0, 1, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Arial"));
			    SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Arial подчеркнутый"), 18);
			}
			if (b==3)
			{
				newfont=CreateFontW (40, 0, 0, 0, 1000, 0, 0, 0, 204, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 0, 0,  TEXT("Arial"));
			    SelectObject(hdc, newfont);
				TextOut( hdc, 300, 100, TEXT("Arial полужирный"), 16);
			}
		}
		b=0;	
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
