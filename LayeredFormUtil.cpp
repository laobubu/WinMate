#define USE_WIN32_API
#include "LayeredFormUtil.h"
#include "Common.h"

using namespace System;
using namespace System::Windows;
using namespace System::Drawing;

// hard stuff that CLI is not capable to manage
struct LayeredFormUtilInner {
	POINT ptDst;
	POINT ptSrc;
	SIZE size;
	BLENDFUNCTION blend;

	HWND hWnd;

	HDC screenDC;
	HDC memDC;
	HGDIOBJ hBitmap;
};

WinMate::LayeredFormUtil::LayeredFormUtil(Forms::Form ^ target)
	: target(target)
{
	s = new struct LayeredFormUtilInner;
	memset(s, 0, sizeof(struct LayeredFormUtilInner));

	HWND m_hWnd = s->hWnd = (HWND)target->Handle.ToPointer();
	LONG ws_ex = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, ws_ex | WS_EX_LAYERED);

	s->screenDC = GetDC(0);
	s->memDC = CreateCompatibleDC(s->screenDC);

	BLENDFUNCTION &blend = s->blend;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;
}

WinMate::LayeredFormUtil::~LayeredFormUtil()
{
	if (s->hBitmap) DeleteObject(s->hBitmap);
	DeleteDC(s->memDC);
	ReleaseDC(0, s->screenDC);

	delete s;
}

void WinMate::LayeredFormUtil::SetImage(Bitmap ^ bitmap)
{
	auto &screenDC = s->screenDC;
	auto &memDC = s->memDC;
	auto &hBitmap = s->hBitmap;

	auto &size = s->size;
	auto &ptSrc = s->ptSrc;
	auto &ptDst = s->ptDst;
	auto &blend = s->blend;

	if (bitmap->PixelFormat != Imaging::PixelFormat::Format32bppArgb)
		throw gcnew ApplicationException("The bitmap must be 32ppp with alpha-channel.");

	if (hBitmap) DeleteObject(hBitmap);
	hBitmap = bitmap->GetHbitmap(Color::FromArgb(0)).ToPointer();
	SelectObject(memDC, hBitmap);

	this->width = size.cx = bitmap->Width;
	this->height = size.cy = bitmap->Height;

	RECT rect;
	GetWindowRect(s->hWnd, &rect);
	ptDst.x = rect.left;
	ptDst.y = rect.top;

	UpdateLayeredWindow(s->hWnd, screenDC, &ptDst, &size, memDC, &ptSrc, 0, &blend, ULW_ALPHA);
}
