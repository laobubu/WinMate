#define USE_WIN32_API
#include "ModInfo.h"
#include "ModToolbox.h"
#include "Common.h"

using namespace WinMate;
using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace WinMate {
	static gcroot<Dictionary<IntPtr, ModInfo^>^> _dict;

	void CleanInvalidModInfo()
	{
		LOG(L"Start clean invalid ModInfo...");
		auto dict = GetModInfoDict();
		array<IntPtr> ^ keys = gcnew array<IntPtr>(dict->Count);
		dict->Keys->CopyTo(keys, 0);
		for each (IntPtr key in keys)
		{
			HWND hWnd = (HWND)key.ToPointer();
			if (!IsWindow(hWnd)) {
				LOG(L" - Clean hWnd {0}", key);
				dict->Remove(key);
			}
		}
	}

	static void CleanInvalidModInfo(System::Object ^sender, System::Timers::ElapsedEventArgs ^e) {
		CleanInvalidModInfo();
	}

	Dictionary<IntPtr, ModInfo^> ^ GetModInfoDict() {
		using Timer = System::Timers::Timer;
		static bool inited = false;
		if (!inited) {
			_dict = gcnew Dictionary<IntPtr, ModInfo^>;

			// Create a timer, CleanInvalidModInfo every 20 seconds. 
			Timer ^ purgeTimer = gcnew Timer(20e3);
			purgeTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(&WinMate::CleanInvalidModInfo);
			purgeTimer->Start();
			
			inited = true;
		}
		return _dict;
	}
}

void WinMate::ModInfo::DisplayTo(ModToolbox ^ box) {
	box->topmost->Checked = _Topmost;
	box->alphaTrackBar->Value = _Alpha;
}

void WinMate::ModInfo::ApplyTopmost(bool topmost) {
	SetWindowPos(hWnd, topmost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
}

void WinMate::ModInfo::ApplyAlpha(int a)
{
	LONG nRet = GetWindowLong(hWnd, GWL_EXSTYLE);
	nRet = nRet | WS_EX_LAYERED;
	SetWindowLong(hWnd, GWL_EXSTYLE, nRet);

	SetLayeredWindowAttributes(hWnd, 0, 255 - a, LWA_ALPHA);
}
