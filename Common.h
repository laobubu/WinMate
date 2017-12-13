#pragma once

#include <vcclr.h>
#include <cassert>

#include "resource.h"

#ifdef _DEBUG 
#define LOG(...) System::Console::WriteLine( __VA_ARGS__ )

#else
#define LOG(...) void(0)

#endif

#ifdef USE_WIN32_API
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#endif

namespace WinMate{
	using namespace System;
	using namespace System::Drawing;
	Image ^ LoadFileOrResource(String ^ fileName, const TCHAR* resType, int resID);
}
