
#include "CheckBox.h"
BEGIN_MESSAGE_MAP(CheckBox, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()

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

void CheckBox::setCheckedState(bool check)
{
	if (check == true)
		checkedState_ = State::Checked;
	else
		checkedState_ = State::None;
}

void CheckBox::enable(bool enable)
{
	enable_ = enable;
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
	memG.MeasureString(text, text.GetLength(), &gpFont, Gdiplus::RectF(static_cast<float>(rc.left), static_cast<float>(rc.top), static_cast<float>(rc.Width()), static_cast<float>(rc.Height())), &stringFormat_, &textBox);
	
	CRect rcText = rc;
	Gdiplus::RectF rcBox(static_cast<float>(rc.left), static_cast<float>(rc.top), static_cast<float>(rc.Width()), static_cast<float>(rc.Height()));
	if (stringFormat_.GetAlignment() == Gdiplus::StringAlignmentNear)
	{
		rcText.right -= static_cast<long>(textBox.Height);
		rcBox.X = static_cast<float>(rcText.right);
	}
	else
	{
		rcText.left -= static_cast<long>(textBox.Height);
		rcBox.X = static_cast<float>(rc.left);
	}
	rcBox.Width = textBox.Height;
	rcBox.Y = rc.top + (rc.Height() - textBox.Height) / 2;
	rcBox.Height = textBox.Height;

	memG.DrawString(text, text.GetLength(), &gpFont, Gdiplus::RectF(static_cast<float>(rcText.left), static_cast<float>(rcText.top), static_cast<float>(rcText.Width()), static_cast<float>(rcText.Height())), &stringFormat_, &brush_text);

	////////////////////////////////////////////////////////////////////////////////////////

	/*Draw check*/
	Gdiplus::SolidBrush brush_rect(Gdiplus::Color(GetRValue(boxColor_), GetGValue(boxColor_), GetBValue(boxColor_)));
	memG.FillRectangle(&brush_rect, rcBox);

	if (checkedState_ == State::Checked)
	{
		Gdiplus::RectF rcCheck(rcBox);
		rcCheck.X = rcCheck.X + rcCheck.Width * 0.2f;
		rcCheck.Y = rcCheck.Y + rcCheck.Height * 0.2f;
		rcCheck.Width *= 0.6f;
		rcCheck.Height *= 0.6f;

		Gdiplus::SolidBrush brush_check(Gdiplus::Color(GetRValue(checkColor_), GetGValue(checkColor_), GetBValue(checkColor_)));
		memG.FillEllipse(&brush_check, rcCheck);
	}

	graphics.DrawImage(&memBmp, 0, 0);

}


void CheckBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);
	if (enable_ == true)
	{
		checkedState_ == State::None ? checkedState_ = State::Checked : checkedState_ = State::None;
		Invalidate();
	}
}


void CheckBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	CWnd::OnLButtonDown(nFlags, point);
}
