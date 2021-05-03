
#include "LedControl.h"

LedControl::LedControl()
{
}

LedControl::~LedControl()
{
}

void LedControl::setColor(COLORREF onState, COLORREF offState)
{
	colorOn_ = onState;
	colorOff_ = offState;
}
BEGIN_MESSAGE_MAP(LedControl, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void LedControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call __super::OnPaint() for painting messages

	
	CRect rc;
	GetClientRect(rc);

	if (memBackground == false)
	{
		memBackground.reset(new CDC());
		memBitmap.reset(new CBitmap());
		memBackground->CreateCompatibleDC(&dc);

		memBitmap->CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());

		CBitmap* pOldBitmap = memBackground->SelectObject(memBitmap.get());
		memBackground->BitBlt(0, 0, rc.Width(), rc.Height(), &dc, rc.left, rc.top, SRCCOPY);
;	}

	dc.BitBlt(0, 0, rc.Width(), rc.Height(), memBackground.get(), rc.left, rc.top, SRCCOPY);


	Gdiplus::Graphics graphics(dc);

	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	COLORREF clr = colorOff_;

	if (state == true)
	{
		clr = colorOn_;
	}

	Gdiplus::SolidBrush brush(Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));

	graphics.FillEllipse(&brush, Gdiplus::RectF(rc.left + rc.Width() * 0.1, rc.top + rc.Height() * 0.1, rc.Width() * 0.8, rc.Height() * 0.8));

}
