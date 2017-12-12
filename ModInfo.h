#pragma once

typedef struct HWND__ *HWND;

namespace WinMate {
	ref class EntryButton;

	public ref class ModInfo
	{
	private:
		bool _Topmost;
		void ApplyTopmost(bool);

	public:
		ModInfo(HWND hWnd) : hWnd(hWnd) , _Topmost(false)
		{}

		HWND hWnd;

		void DisplayTo(EntryButton ^ ebtn);

		property bool Topmost{
			bool get() { return _Topmost; }
			void set(bool topmost) { _Topmost = topmost; ApplyTopmost(topmost); }
		};

	};

	System::Collections::Generic::Dictionary<System::IntPtr, ModInfo^> ^ GetModInfoDict();
	void CleanInvalidModInfo();
}