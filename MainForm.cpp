#include "MainForm.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib, "user32.lib")

using namespace WinMate;
using namespace System;
using namespace System::Drawing;
using namespace System::Resources;

System::Void WinMate::MainForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e) {
	notifyIcon->Icon = this->Icon;
}

inline System::Void WinMate::MainForm::menuShow_Click(System::Object ^ sender, System::EventArgs ^ e) {
	if (this->Visible) {
		this->Hide();
	}
	else {
		this->Show();
		SetWindowPos((HWND)Handle.ToPointer(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
}

inline System::Void WinMate::MainForm::MainForm_FormClosing(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e) {
	if (this->exiting) return;

	if (!hideBalloon) {
		notifyIcon->BalloonTipTitle = L"WinMate is running";
		notifyIcon->BalloonTipText = L"To exit WinMate, click the [Exit] button.";
		notifyIcon->ShowBalloonTip(500);
		hideBalloon = true;
	}

	e->Cancel = true;
	this->Hide();
}

inline System::Void WinMate::MainForm::btnExit_Click(System::Object ^ sender, System::EventArgs ^ e) {
	this->exiting = true;
	this->Close();
}

inline System::Void WinMate::MainForm::btnRunBackground_Click(System::Object ^ sender, System::EventArgs ^ e) {
	menuShow->PerformClick();
}

inline System::Void WinMate::MainForm::notifyIcon_MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e) {
	using System::Windows::Forms::MouseButtons;
	using System::Windows::Forms::Cursor;
	if (e->Button == MouseButtons::Right) {
		//contextMenu->Show(Cursor::Position);
	}
	else {
		menuShow->PerformClick();
	}
}
