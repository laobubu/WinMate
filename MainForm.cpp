#include "MainForm.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib, "user32.lib")

using namespace System;

System::Void WinMate::MainForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e) {
	HWND win = GetForegroundWindow();
	entryBtn->AttachTo(win);
}

System::Void WinMate::MainForm::tmrAutoAttach_Tick(System::Object ^ sender, System::EventArgs ^ e) {
	HWND win = GetForegroundWindow();
	entryBtn->AttachTo(win);
}
