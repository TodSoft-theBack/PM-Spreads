#pragma once
#include <Windows.h>

LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM windowPrams, LPARAM loadParams);

class Form
{	
	private:
		const wchar_t* className = L"Generic Form Class";
		HINSTANCE instance;
		HWND window;

	public:
		Form();
		Form(const Form& form) = delete;
		Form& operator=(const Form& form) = delete;
		bool ProcessMessages();
		~Form();
};

