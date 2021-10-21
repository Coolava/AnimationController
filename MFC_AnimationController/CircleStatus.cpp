#include "CircleStatus.h"

constexpr double pi = 3.141592653589793238462643383279502884L;

CircleStatus::CircleStatus()
	:font_(Gdiplus::FontFamily::GenericMonospace(),10)
{
	GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput_, NULL);

	animation_controller_.SetRelatedWnd(this);
	animation_controller_.EnableAnimationTimerEventHandler();

	format_.SetAlignment(Gdiplus::StringAlignmentCenter);
	format_.SetLineAlignment(Gdiplus::StringAlignmentCenter);

}

CircleStatus::~CircleStatus()
{
	Gdiplus::GdiplusShutdown(gdiplusToken_);
}

void CircleStatus::setBackGroundColor(COLORREF color)
{
	backgroundColor_ = color;
}

void CircleStatus::setInnerColor(COLORREF color)
{
	ballColor_ = color;
}

void CircleStatus::setAnimationSeconds(double seconds)
{
	seconds_ = seconds;
}

void CircleStatus::setBallCount(int count)
{
	ballCount_ = count;
}

void CircleStatus::setBallSize(double size)
{
	ballSize_ = size;
}

void CircleStatus::setBallDistanceDegree(double degree)
{
	distance_ = degree;
}

void CircleStatus::start()
{
	state_ = State::InProgress;
	animation_controller_.CleanUpGroup(1);

	animation_degree_ = 0;
	animation_degree_.AddTransition(
		new CSinusoidalTransitionFromRange(seconds_, 0, 360.0 + (distance_ * ballCount_), seconds_ * 2.0, UI_ANIMATION_SLOPE::UI_ANIMATION_SLOPE_DECREASING));

	animation_degree_.SetID(0, 1);

	animation_controller_.AddAnimationObject(&animation_degree_);

	animation_controller_.AnimateGroup(1);
}

void CircleStatus::stop()
{
	state_ = State::Stop;
}
void CircleStatus::SetWindowTextA(LPCSTR lpString)
{
	isSetText = true;
	text_ = lpString;
}

void CircleStatus::SetWindowTextW(LPCWSTR lpString)
{
	isSetText = true;
	text_ = lpString;
}

void CircleStatus::GetWindowTextA(LPSTR& lpString)
{
	//lpString = text_.GetBuffer();
}

void CircleStatus::GetWindowTextW(LPWSTR& lpString)
{
	lpString = text_.GetBuffer();
}

void CircleStatus::setAlignment(StringAlignment alignment)
{
	format_.SetAlignment(alignment);
}
void CircleStatus::setLineAlignment(StringAlignment alignment)
{
	format_.SetLineAlignment(alignment);
}
BEGIN_MESSAGE_MAP(CircleStatus, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CircleStatus::OnPaint()
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
	
	memG.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	/*Background*/
	Gdiplus::SolidBrush brush_rect(Gdiplus::Color(GetRValue(backgroundColor_), GetGValue(backgroundColor_), GetBValue(backgroundColor_)));

	Gdiplus::RectF rectF(rc.left, rc.top, rc.Width(), rc.Height());
	memG.FillRectangle(&brush_rect, rectF);

	/*Get Animate value*/
	COLORREF clr;
	double degree = 0;
	if (state_ == State::Stop)
	{
		clr = backgroundColor_;
	}
	else
	{
		clr = ballColor_;
		animation_degree_.GetValue(degree);

		if (degree == (360.0 + distance_ * ballCount_))
		{
			start();
		}
	}

	Gdiplus::SolidBrush brushEllipse(Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));

	CPoint center = rc.CenterPoint();

	double radius = (rc.Width() > rc.Height() ? rc.Height() / 2 : rc.Width() / 2) * 0.7;

	for (int i = 0; i < ballCount_; i++)
	{
		if ((degree > 0.0) && (degree < 360.0))
		{
			Gdiplus::PointF pt(
				center.x + radius * sin(degree * pi / 180.0) ,
				center.y - radius * cos(degree * pi / 180.0)
			);

			memG.FillEllipse(&brushEllipse, Gdiplus::RectF(pt.X - ballSize_ / 2, pt.Y - ballSize_ / 2, ballSize_, ballSize_));
		}

		degree -= distance_;
	}

	CString text = text_;
	if (isSetText == false)
		CWnd::GetWindowText(text);


	memG.DrawString(text, text.GetLength(), &font_, rectF, &format_, &brushEllipse);

	graphics.DrawImage(&memBmp, 0, 0);
}


BOOL CircleStatus::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_PAINT)
	{
		//static int cnt = 0;
		//text_.Format(_T("%d"), cnt++);
	}
	return __super::PreTranslateMessage(pMsg);
}
