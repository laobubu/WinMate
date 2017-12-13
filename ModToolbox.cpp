#define USE_WIN32_API
#include "ModToolbox.h"
#include "Common.h"

using namespace System;
using namespace System::Windows;

Void WinMate::ModToolbox::topmost_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	m_modInfo->Topmost = topmost->Checked;
	SetWindowPos((HWND)this->Handle.ToPointer(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}