#pragma once

#include <vcclr.h>
#include <cassert>

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
