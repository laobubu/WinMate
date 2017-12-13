#define USE_WIN32_API
#include "WindowWatch.h"
#include "Common.h"

using namespace WinMate;
using namespace System::Timers;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

enum WatchMethod {
	WM_WM_POLL,
	WM_WM_WINDOWS_HOOK,
};
const WatchMethod method = WM_WM_WINDOWS_HOOK;


namespace HookWatcher {
	static HHOOK winhook;
	static gcroot<WindowWatch^> active_watcher;
	static LRESULT CALLBACK winhook_func(int nCode, WPARAM wParam, LPARAM lParam);

	static void Start(WindowWatch^ watcher) {
		active_watcher = watcher;
		HINSTANCE appInstance = GetModuleHandle(NULL);
		winhook = SetWindowsHookEx(WH_MOUSE_LL, winhook_func, appInstance, 0);

		LOG("Hook {0}", (long)winhook);
	}

	static void Stop() {
		UnhookWindowsHookEx(winhook);
		active_watcher = nullptr;
	}

	static LRESULT CALLBACK winhook_func(int nCode, WPARAM wParam, LPARAM lParam) {
		auto d = (const MSLLHOOKSTRUCT*)lParam;

		//if (wParam == WM_MOUSEMOVE) {
		//	HWND win = WindowFromPoint(d->pt);
		//	
		//	{
		//		HWND parent;
		//		while (parent = GetParent(win)) win = parent; 
		//	}

		//	Console::WriteLine("MouseMove! {0}, {1}    window = {2}", d->pt.x, d->pt.y, (int)win);
		//}
		active_watcher->Poll();

		return CallNextHookEx(winhook, nCode, wParam, lParam);
	}
};

WinMate::WindowWatch::WindowWatch()
{
	target = nullptr;

	switch (method) {
	case WM_WM_POLL:
		watchTimer = gcnew Timer(50);
		watchTimer->Elapsed += gcnew ElapsedEventHandler(this, &WinMate::WindowWatch::OnElapsed);
		watchTimer->Start();
		break;

	case WM_WM_WINDOWS_HOOK:
		HookWatcher::Start(this);
		break;
	}

	rect = gcnew Drawing::Rectangle();
}

WinMate::WindowWatch::~WindowWatch()
{
	switch (method) {
	case WM_WM_POLL:
		watchTimer->Stop();
		break;

	case WM_WM_WINDOWS_HOOK:
		HookWatcher::Stop();
		break;
	}

	SetTarget(nullptr);
}

void WinMate::WindowWatch::SetTarget(void * t) {
	target = t;
	rect->X = -215133; // use a random number to make RectChanged always emitted
	Poll();
}

void WinMate::WindowWatch::Poll()
{
	static HWND lastWindow = 0;
	static bool last_CursorOnTitlebar = false;
	{
		POINT pt;
		HWND win;
		HWND parent;

		GetCursorPos(&pt);
		win = WindowFromPoint(pt);
		while (parent = GetParent(win)) win = parent;

		if (win) {
			RECT rect;
			GetWindowRect(win, &rect);
			bool cursor_on_titlebar = pt.x >= rect.left && pt.x <= rect.right && pt.y >= rect.top && pt.y <= rect.top + 60;
			if (!cursor_on_titlebar) win = NULL;
		}

		if (lastWindow != win) {
			lastWindow = win;
			ForegroundChanged(win);
		}
	}

	if (!target) return;
	HWND win = static_cast<HWND>(target);

	//String ^title;
	//{
	//	int len = GetWindowTextLength(win) + 2;
	//	TCHAR *buf = new TCHAR[len];
	//	GetWindowText(win, buf, len);
	//	title = gcnew String(buf);
	//	delete[] buf;
	//}
	//Console::WriteLine(title);

	bool sizeChanged = false;
	{
		RECT newRect;
		GetWindowRect(win, &newRect);
		if (newRect.left != rect->X) { sizeChanged = true; rect->X = newRect.left; }
		if (newRect.top != rect->Y) { sizeChanged = true; rect->Y = newRect.top; }
		if (newRect.right != rect->Right) { sizeChanged = true; rect->Width = newRect.right - newRect.left; }
		if (newRect.bottom != rect->Bottom) { sizeChanged = true; rect->Height = newRect.bottom - newRect.top; }
	}
	if (sizeChanged) {
		//Console::WriteLine(L"Loading {0} {1} {2} {3}", rect->X, rect->Y, rect->Width, rect->Height);
		RectChanged(win, rect);
	}
}

void WinMate::WindowWatch::OnElapsed(System::Object ^sender, System::Timers::ElapsedEventArgs ^e)
{
	Poll();
}
