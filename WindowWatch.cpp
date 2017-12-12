#include "WindowWatch.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib, "user32.lib")

using namespace System::Timers;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

WinMate::WindowWatch::WindowWatch()
{
	target = nullptr;

	watchTimer = gcnew Timer(50);
	watchTimer->Elapsed += gcnew ElapsedEventHandler(this, &WinMate::WindowWatch::OnElapsed);
	watchTimer->Start();

	rect = gcnew Drawing::Rectangle();
}

WinMate::WindowWatch::~WindowWatch()
{
	watchTimer->Stop();
	SetTarget(nullptr);
}

void WinMate::WindowWatch::SetTarget(void * t) {
	target = t;
	rect->X = -215133; // use a random number to make OnRectChanged always emitted
}

void WinMate::WindowWatch::OnElapsed(System::Object ^sender, System::Timers::ElapsedEventArgs ^e)
{
	if (!target) return;
	HWND win = static_cast<HWND>(target);

	String ^title;

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
		OnRectChanged(win, rect);
	}
}
