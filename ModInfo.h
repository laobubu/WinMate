#pragma once

typedef struct HWND__ *HWND;

namespace WinMate {
	ref class ModToolbox;

	public ref class ModInfo
	{
	private:
		bool _Topmost;
		void ApplyTopmost(bool);

		int _Alpha;
		void ApplyAlpha(int);

	public:
		ModInfo(HWND hWnd) : hWnd(hWnd) , _Topmost(false), _Alpha(0)
		{}

		HWND hWnd;

		void DisplayTo(ModToolbox ^);

		property bool Topmost {
			bool get() { return _Topmost; }
			void set(bool topmost) { _Topmost = topmost; ApplyTopmost(topmost); }
		};

		property int Alpha {	// Transparent Level. 0: Not Transparent. 100: Hidden
			int  get() { return _Alpha; }
			void set(int alpha) { _Alpha = alpha; ApplyAlpha(alpha); }
		};

	};

	System::Collections::Generic::Dictionary<System::IntPtr, ModInfo^> ^ GetModInfoDict();
	void CleanInvalidModInfo();
}