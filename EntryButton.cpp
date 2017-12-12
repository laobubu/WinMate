#include "EntryButton.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib, "user32.lib")

using namespace System;
using namespace System::IO;
using namespace System::Drawing;

WinMate::EntryButton::EntryButton(void)
{
	InitializeComponent();

	wwatch = gcnew WindowWatch();
	wwatch->RectChanged += gcnew WindowWatch::RectChangedEventHandler(this, &EntryButton::OnTargetResize);
	wwatch->ForegroundChanged += gcnew WindowWatch::ForegroundChangedEventHandler(this, &EntryButton::OnForegroundChanged);

	m_hWnd = (HWND)Handle.ToPointer();
	m_hidden = false;

	// make this window transparent
	{
		FileStream ^stream = gcnew FileStream("UI/normal.png", FileMode::Open, FileAccess::Read);
		imgNormal = gcnew Bitmap(Image::FromStream(stream));
		stream->Close();
	}
	{
		FileStream ^stream = gcnew FileStream("UI/hover.png", FileMode::Open, FileAccess::Read);
		imgHover = gcnew Bitmap(Image::FromStream(stream));
		stream->Close();
	}

	alphaFx = gcnew LayeredFormUtil(this);
	alphaFx->SetImage(imgNormal);
}

/// Attach EntryButton to a window. Make sure the hWnd is not a button.
void WinMate::EntryButton::AttachTo(void *hWnd) {
	HWND current = static_cast<HWND>(hWnd);

	bool caught_self = current == m_hWnd;
	if (current) {
		if ((GetWindowLong(current, GWL_STYLE) & WS_CAPTION) != WS_CAPTION) current = NULL; // do not attach titlebar-less window
	}

	if (m_target != current) {
		m_target = current;

		bool shall_hide = (current == NULL);
		if (m_hidden != shall_hide) {
			m_hidden = shall_hide;

			// If the visibility shall change. use WIN32 API to change, avoid getting focus.
			if (shall_hide)
				SetWindowPos((HWND)m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
		}

		// Change target, and OnTargetResize will be trigged
		wwatch->SetTarget(current);
	}
}

void WinMate::EntryButton::OnTargetResize(void *win, System::Drawing::Rectangle ^rect)
{
	if (m_hovering) return;

	int x, y, w, h;
	w = alphaFx->width;
	h = alphaFx->height;
	x = rect->Right - 145 - w;
	y = rect->Y + 1;

	UINT flag2 = (!m_hidden && x > rect->X) ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;
	SetWindowPos(m_hWnd, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE | flag2);

#if _DEBUG
	Console::WriteLine("Size changed. {0}, {1}, {2}", (int)win, flag2 == SWP_SHOWWINDOW, m_hidden);
#endif
}

System::Void WinMate::EntryButton::menuTopmost_Click(System::Object ^ sender, System::EventArgs ^ e) {
	menuTopmost->Checked = !menuTopmost->Checked;
	m_modInfo->Topmost = menuTopmost->Checked;
	
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE);
}


void WinMate::EntryButton::OnForegroundChanged(void *win)
{
	m_hovering = (win == m_hWnd);
	if (m_hovering) return;

#if _DEBUG
	Console::WriteLine("ATTACH TO {0}", (int)win);
#endif

	this->AttachTo(win);
}
