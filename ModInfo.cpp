#include "ModInfo.h"
#include "EntryButton.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib, "user32.lib")

using namespace WinMate;
using namespace System;

void WinMate::ModInfo::DisplayTo(EntryButton ^ ebtn) {
	ebtn->menuTopmost->Checked = Topmost;
}

void WinMate::ModInfo::ApplyTopmost(bool topmost) {
	SetWindowPos(hWnd, topmost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, 3);
}
