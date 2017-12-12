#pragma once

namespace WinMate {
	using namespace System;

	public ref class WindowWatch
	{
	public:
		WindowWatch();
		~WindowWatch();

		void SetTarget(void *t);

		delegate void RectChangedEventHandler(void *win, Drawing::Rectangle ^rect);
		event RectChangedEventHandler ^ OnRectChanged;

	private:
		void *target;
		Drawing::Rectangle ^rect;

	private:
		Timers::Timer ^watchTimer;
		void OnElapsed(System::Object ^sender, System::Timers::ElapsedEventArgs ^e);
	};
}
