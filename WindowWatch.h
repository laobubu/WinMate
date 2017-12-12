#pragma once

namespace WinMate {
	using namespace System;

	public ref class WindowWatch
	{
	public:
		WindowWatch();
		~WindowWatch();

		void SetTarget(void *t);
		void Poll();

		delegate void RectChangedEventHandler(void *win, Drawing::Rectangle ^rect);
		event RectChangedEventHandler ^ RectChanged;	// Trigged when the size of selected target changed.

		delegate void ForegroundChangedEventHandler(void *win);
		event ForegroundChangedEventHandler ^ ForegroundChanged; // Trigged when OS foreground window changed.

	private: // Current watched patricular target
		void *target;
		Drawing::Rectangle ^rect;

	private: // Use timer to poll
		Timers::Timer ^watchTimer;
		void OnElapsed(System::Object ^sender, System::Timers::ElapsedEventArgs ^e);
	};
}
