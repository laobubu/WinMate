#pragma once

struct LayeredFormUtilInner;

namespace WinMate {
	using namespace System;
	using namespace System::Windows;
	using namespace System::Drawing;

	public ref class LayeredFormUtil
	{
	public:
		LayeredFormUtil(Forms::Form ^ target);
		~LayeredFormUtil();

		void SetImage(Bitmap ^ bitmap);
		int width;
		int height;

	private:
		Forms::Form ^ target;
		struct LayeredFormUtilInner *s;
	};
}

