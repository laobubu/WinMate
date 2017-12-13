#include "MainForm.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib, "user32.lib")

using namespace WinMate;
using namespace System;

System::Void WinMate::MainForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e) {
	notifyIcon->Icon = this->Icon;
}
