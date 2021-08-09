#include "Circle_Progress.h"

constexpr double pi = 3.141592653589793238462643383279502884L;

Circle_Progress::Circle_Progress()
	:font_(Gdiplus::FontFamily::GenericMonospace(),10)
{
	GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput_, NULL);

	animation_controller_.SetRelatedWnd(this);
	animation_controller_.EnableAnimationTimerEventHandler();

	format_.SetAlignment(Gdiplus::StringAlignmentCenter);
	format_.SetLineAlignment(Gdiplus::StringAlignmentCenter);

}

Circle_Progress::~Circle_Progress()
{
	Gdiplus::GdiplusShutdown(gdiplusToken_);
}

void Circle_Progress::setBackGroundColor(COLORREF color)
{
	backgroundColor_ = color;
}

void Circle_Progress::setInnerColor(COLORREF color)
{
	ballColor_ = color;
}

void Circle_Progress::setAnimationSeconds(double seconds)
{
	seconds_ = seconds;
}

void Circle_Progress::setBallCount(int count)
{
	ballCount_ = count;
}

void Circle_Progress::setBallSize(double size)
{
	ballSize_ = size;
}

void Circle_Progress::setBallDistanceDegree(double degree)
{
	distance_ = degree;
}

void Circle_Progress::start()
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

void Circle_Progress::stop()
{
	state_ = State::Stop;
}
void Circle_Progress::setText(CString text)
{
	text_ = text;
}
void Circle_Progress::setAlignment(StringAlignment alignment)
{
	format_.SetAlignment(alignment);
}
void Circle_Progress::setLineAlignment(StringAlignment alignment)
{
	format_.SetLineAlignment(alignment);
}
BEGIN_MESSAGE_MAP(Circle_Progress, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void Circle_Progress::OnPaint()
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


	memG.DrawString(text_, text_.GetLength(), &font_, rectF, &format_, &brushEllipse);

	graphics.DrawImage(&memBmp, 0, 0);
}


BOOL Circle_Progress::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_PAINT)
	{
		static int cnt = 0;
		text_.Format(_T("%d"), cnt++);
	}
	return __super::PreTranslateMessage(pMsg);
}
