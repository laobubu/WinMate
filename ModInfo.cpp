#include "ModInfo.h"
#include "EntryButton.h"
#include "Common.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib, "user32.lib")

using namespace WinMate;
using namespace System;
using namespace System::Collections;
using namespace System::Runtime::InteropServices;

namespace WinMate {
	static gcroot<Dictionary<IntPtr, ModInfo^>^> _dict;

	void CleanInvalidModInfo()
	{
		LOG(L"Start clean invalid ModInfo...");
		auto dict = GetModInfoDict();
		auto keys = dict->Keys;
		for (int i = 0; i<keys->Count; i++)
		{
			IntPtr key = keys[i];
			HWND hWnd = (HWND)key.ToPointer();
			if (!IsWindow(hWnd)) {
				LOG(L" - Clean hWnd {0}", key);
				dict->Remove(key);
				i--;
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
			Timer ^ purgeTimer = gcnew Timer(5e3);
			purgeTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(&WinMate::CleanInvalidModInfo);
			purgeTimer->Start();
			inited = true;
		}
		return _dict;
	}
}

void WinMate::ModInfo::DisplayTo(EntryButton ^ ebtn) {
	ebtn->menuTopmost->Checked = Topmost;
}

void WinMate::ModInfo::ApplyTopmost(bool topmost) {
	SetWindowPos(hWnd, topmost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, 3);
}
