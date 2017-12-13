#define USE_WIN32_API
#include "EntryButton.h"
#include "Common.h"

using namespace System;
using namespace System::IO;
using namespace System::Drawing;

WinMate::EntryButton::EntryButton(void)
{
	InitializeComponent();

	modBox = gcnew ModToolbox();
	modBox->Hide();

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
	LONG wstyle = 0;

	bool caught_self = current == m_hWnd;
	if (current) {
		wstyle = GetWindowLong(current, GWL_STYLE);
		if ((wstyle & WS_CAPTION) != WS_CAPTION) current = NULL; // do not attach titlebar-less window
	}

	m_btnXoffset = (wstyle & (WS_MAXIMIZEBOX | WS_MINIMIZEBOX)) ? 145 : 45;

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
	x = rect->Right - m_btnXoffset - w;
	y = rect->Y + 1;

	UINT flag2 = (!m_hidden && x > rect->X) ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;
	SetWindowPos(m_hWnd, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE | flag2);

	LOG("Size changed. {0}, {1}, {2}", (int)win, flag2 == SWP_SHOWWINDOW, m_hidden);
}

inline System::Void WinMate::EntryButton::EntryButton_MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e) {
	IntPtr key(m_target);
	auto m_AllModInfo = GetModInfoDict();

	if (!m_AllModInfo->ContainsKey(key)) {
		m_AllModInfo->Add(key, gcnew ModInfo(m_target));
	}

	m_modInfo = m_AllModInfo[key];

	modBox->UseModInfo(m_modInfo);
	modBox->Show(this);

	POINT pt;
	GetCursorPos(&pt);
	SetWindowPos((HWND)modBox->Handle.ToPointer(), HWND_TOPMOST, pt.x, pt.y, 0, 0, SWP_NOSIZE);
}


void WinMate::EntryButton::OnForegroundChanged(void *win)
{
	m_hovering = (win == m_hWnd);
	if (m_hovering) return;

	LOG("ATTACH TO {0}", (int)win);

	this->AttachTo(win);
}
