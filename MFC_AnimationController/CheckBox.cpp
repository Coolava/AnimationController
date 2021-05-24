
#include "CheckBox.h"
BEGIN_MESSAGE_MAP(CheckBox, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


CheckBox::CheckBox()
{
	GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput_, NULL);

}
CheckBox::~CheckBox()
{
}

void CheckBox::setTextColor(COLORREF color)
{
	textColor_ = color;
}
void CheckBox::setTextAlign(Gdiplus::StringAlignment align)
{
	stringFormat_.SetAlignment(align);
	stringFormat_.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
}

void CheckBox::setCheckColor(COLORREF color)
{
	checkColor_ = color;
}

void CheckBox::setBoxColor(COLORREF color)
{
	boxColor_ = color;
	
}

void CheckBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages


	CRect rc;
	GetClientRect(rc);

	Gdiplus::Graphics graphics(dc);

	/*Initialize buffer bitmap */
	Gdiplus::Bitmap memBmp(rc.Width(), rc.Height());
	Gdiplus::Graphics memG(&memBmp);

	memG.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

	/*Text*/

	Gdiplus::SolidBrush brush_text(Gdiplus::Color(GetRValue(textColor_), GetGValue(textColor_), GetBValue(textColor_)));

	CFont* font = GetFont();
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));

	font->GetLogFont(&lf);

	Gdiplus::Font gpFont(dc, &lf);

	CString text;
	GetWindowText(text);

	Gdiplus::RectF textBox;
	memG.MeasureString(text, text.GetLength(), &gpFont, Gdiplus::RectF(rc.left, rc.top, rc.Width(), rc.Height()), &stringFormat_, &textBox);
	
	CRect rcText = rc;
	Gdiplus::Rect rcBox(rc.left, rc.top, rc.Width(), rc.Height());
	if (stringFormat_.GetAlignment() == Gdiplus::StringAlignmentNear)
	{
		rcText.right -= textBox.Height;
		rcBox.X = rcText.right;
	}
	else
	{
		rcText.left -= textBox.Height;
		rcBox.X = rc.left;
	}
	rcBox.Width = textBox.Height;
	rcBox.Y = rc.top + (rc.Height() - textBox.Height) / 2;
	rcBox.Height = textBox.Height;

	memG.DrawString(text, text.GetLength(), &gpFont, Gdiplus::RectF(rcText.left, rcText.top, rcText.Width(), rcText.Height()), &stringFormat_, &brush_text);

	////////////////////////////////////////////////////////////////////////////////////////

	/*Draw check*/
	Gdiplus::SolidBrush brush_rect(Gdiplus::Color(GetRValue(boxColor_), GetGValue(boxColor_), GetBValue(boxColor_)));
	memG.FillRectangle(&brush_rect, rcBox);

	if (checkedState_ == State::Checked)
	{
		Gdiplus::Rect rcCheck(rcBox);
		rcCheck.X = rcCheck.X + rcCheck.Width * 0.2;
		rcCheck.Y = rcCheck.Y + rcCheck.Height * 0.2;
		rcCheck.Width *= 0.6;
		rcCheck.Height *= 0.6;

		Gdiplus::SolidBrush brush_check(Gdiplus::Color(GetRValue(checkColor_), GetGValue(checkColor_), GetBValue(checkColor_)));
		memG.FillEllipse(&brush_check, rcCheck);
	}

	graphics.DrawImage(&memBmp, 0, 0);

}


void CheckBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	checkedState_ == State::None ? checkedState_ = State::Checked : checkedState_ = State::None;
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}
