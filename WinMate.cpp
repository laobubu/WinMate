#include "MainForm.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace System;
using namespace System::Windows;
using namespace WinMate;

int main() {
	Application::Run(gcnew MainForm);
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int      nCmdShow)
{
	Application::Run(gcnew MainForm);
	return 0;
}
