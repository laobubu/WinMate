#define USE_WIN32_API
#include "Common.h"

using namespace System;
using namespace System::IO;
using namespace System::Drawing;
using namespace System::Resources;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;

Image ^ WinMate::LoadFileOrResource(String ^ fileName, const TCHAR* resType, int resID)
{
	Image ^ retval;
	Stream ^stream;

	try {
		stream = gcnew FileStream(fileName, FileMode::Open, FileAccess::Read);
	}
	catch (...) {
		HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(resID), resType);
		size_t ResSize = SizeofResource(NULL, hRes);
		HGLOBAL hResLoad = LoadResource(NULL, hRes);
		void* data = LockResource(hResLoad);

		array<unsigned char>^ data_cli = gcnew array<unsigned char>(ResSize);
		Marshal::Copy(IntPtr(data), data_cli, 0, ResSize);
		stream = gcnew MemoryStream(data_cli);
	}

	retval = Image::FromStream(stream);
	stream->Close();

	return retval;
}
