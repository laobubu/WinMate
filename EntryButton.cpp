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

	m_AllModInfo = gcnew Dictionary<IntPtr, ModInfo^>;

	wwatch = gcnew WindowWatch();
	wwatch->OnRectChanged += gcnew WindowWatch::RectChangedEventHandler(this, &EntryButton::OnTargetResize);

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

void WinMate::EntryButton::AttachTo(void *hWnd) {
	HWND current = static_cast<HWND>(hWnd);
	
	while (current && current != m_hWnd && (GetWindowLong(current, GWL_STYLE) & WS_CAPTION) != WS_CAPTION) current = GetParent(current);

	// make sure we use the outest window, not a button or textbox
	HWND parent;
	while (parent = GetParent(current)) current = parent;

	bool caught_self = current == m_hWnd;
	if (current) {
		if (caught_self) current = nullptr; // do not attach self
		if ((GetWindowLong(current, GWL_STYLE) & WS_CAPTION) != WS_CAPTION) current = nullptr; // do not attach titlebar-less window
	}

	if (m_target_temp != current) {
		wwatch->SetTarget(current);
		m_target_temp = current;
		if (current) m_target = current;

		if (!caught_self && m_hidden != (current == nullptr)) {
			// the visibility shall change. use WIN32 API to change, avoid getting focus.
			UINT flag2 = m_hidden ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;
			SetWindowPos((HWND)m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | flag2);
			m_hidden = !m_hidden;
		}
	}
}

void WinMate::EntryButton::OnTargetResize(void *win, System::Drawing::Rectangle ^rect)
{
	int x, y, w, h;
	w = alphaFx->width;
	h = alphaFx->height;
	x = rect->Right - 145 - w;
	y = rect->Y + 1;

	UINT flag2 = (!m_hidden && x > rect->X) ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;
	SetWindowPos(m_hWnd, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE | flag2);
}

System::Void WinMate::EntryButton::menuTopmost_Click(System::Object ^ sender, System::EventArgs ^ e) {
	menuTopmost->Checked = !menuTopmost->Checked;
	m_modInfo->Topmost = menuTopmost->Checked;
	
	SetWindowPos(m_hWnd,HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE);
}
