#include "../include/ApplicationWindow.h"

static ApplicationWindow* appPointer;              //Global pointer to application

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return appPointer->MsgProc(hWnd, message, wParam, lParam);
}

ApplicationWindow::ApplicationWindow(HINSTANCE hInstance, const TCHAR appTitle[], const WNDCLASSEX* wndClass)
{
	appPointer = this;
	hInst_ = hInstance;
    wcscpy(szTitle_, appTitle);

    if (wndClass != nullptr)
    {
        wcscpy(szWindowClass_, wndClass->lpszClassName);
        MyRegisterClass(wndClass);
    }
    else
    {
        wcscpy(szWindowClass_, L"Default Window Class");
        MyRegisterClass();
    }
}

//  Saves instance handle and creates main window. 
bool ApplicationWindow::InitWindow(int nCmdShow, int width, int height)
{
   hAppMainWindow_ = CreateWindow(szWindowClass_, szTitle_, WS_OVERLAPPEDWINDOW,
      0, 0, width, height, NULL, NULL, hInst_, NULL);

   if (!hAppMainWindow_)
   {
      return FALSE;
   }

   ShowWindow(hAppMainWindow_, nCmdShow);
   UpdateWindow(hAppMainWindow_);

   return TRUE;
}

// Registers the window class.
ATOM ApplicationWindow::MyRegisterClass(const WNDCLASSEX* wndClass)
{
    if (wndClass != nullptr)
    {
        return RegisterClassEx(wndClass);
    }

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MainWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInst_;
    wcex.hIcon = LoadIcon(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDI_APPLICATION);
    wcex.lpszClassName = szWindowClass_;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	return RegisterClassEx(&wcex);
}

// Processes messages for the main window.
LRESULT CALLBACK ApplicationWindow::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}	

int ApplicationWindow::Run()
{
	MSG msg = {0};

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render();
		}
	}
	
	return (int)msg.wParam;
}

void ApplicationWindow::Render()
{
}