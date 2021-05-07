
#include "CheckBox.h"
BEGIN_MESSAGE_MAP(CheckBox, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


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


	CFont* font = GetFont();
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));

	font->GetLogFont(&lf);

	Gdiplus::Font gpFont(dc, &lf);

	Gdiplus::SolidBrush brush_text(Gdiplus::Color::White);
	Gdiplus::SolidBrush brush_rect(Gdiplus::Color::Gray);

	CString text;
	GetWindowText(text);

	Gdiplus::RectF box;
	const Gdiplus::RectF layoutRect = Gdiplus::RectF(rc.left, rc.top, rc.Width(), rc.Height());
	graphics.MeasureString(text.GetBuffer(), text.GetLength(), &gpFont, layoutRect, &box);

	if (box.Width > box.Height)
	{
		box.Width = box.Height;
	}
	else
	{
		box.Height = box.Width;
	}

	memG.FillRectangle(&brush_rect, box);

	memG.DrawString(text, text.GetLength(), &gpFont, Gdiplus::RectF(rc.left + box.Width, rc.top, rc.Width() - box.Width, rc.Height()), &stringFormat_, &brush_text);

	graphics.DrawImage(&memBmp, 0, 0);
}
