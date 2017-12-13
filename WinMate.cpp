#include "MainForm.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace System;
using namespace System::Windows;
using namespace WinMate;

static int execMain(array<String^> ^ args) {
	MainForm ^ win = gcnew MainForm;

	String ^ args_s = String::Join(" ", args);

	if (args_s->Contains(L"hide")) win->Hide();
	if (args_s->Contains(L"help")) {
		MessageBox::Show(
			L"Parameters: \n"
			L"  /help     Display these message \n"
			L"  /hide     Hide main window when starts.");
		return 0;
	}

	Application::Run(win);
	return 0;
}

int main(int argc, TCHAR **argv) {
	array<String^> ^ args = gcnew array<String^>(argc - 1);
	for (int i = 0; i < argc - 1; i++) {
		args[i] = gcnew String(argv[i + 1]);
	}

	return execMain(args);
}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int      nCmdShow)
{
	String^ args_str = gcnew String(lpCmdLine);
	array<String^> ^ args = args_str->Split();

	return execMain(args);
}
