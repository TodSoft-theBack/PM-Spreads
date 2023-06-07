#include "Form.h"

Form::Form() : instance(GetModuleHandle(nullptr))
{
	WNDCLASS windowClass = {};

	windowClass.lpszClassName = className;
	windowClass.hInstance = instance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpfnWndProc = WindowProcess; 

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	int initialWidth = 1280;
	int initialHeight = 720;

	RegisterClass(&windowClass);

	RECT rectangle;

	rectangle.left = 1920 / 2 - 1280 / 2;
	rectangle.top = 1080 / 2 - 720 / 2;
	rectangle.right = rectangle.left + initialWidth;
	rectangle.bottom = rectangle.top + initialHeight;

	AdjustWindowRect(&rectangle, style, false);

	window = CreateWindowEx(
		0,
		className,
		L"Hello, GUI",
		style,
		rectangle.left,
		rectangle.top,
		rectangle.right - rectangle.left,
		rectangle.bottom - rectangle.top,
		NULL,
		NULL,
		instance,
		NULL
	);
}

bool Form::ProcessMessages()
{
	MSG message = { };

	while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
			return false;
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return true;
}

Form::~Form()
{
	UnregisterClass(className, instance);
}

LRESULT WindowProcess(HWND window, UINT message, WPARAM windowPrams, LPARAM loadParams)
{
	switch (message)
	{
		case WM_CLOSE:
			DestroyWindow(window);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(window, message, windowPrams, loadParams);
}
