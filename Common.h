#pragma once

#include <vcclr.h>

#ifdef _DEBUG 
#define LOG(...) System::Console::WriteLine( __VA_ARGS__ )

#else
#define LOG(...) void( __VA_ARGS__ )

#endif