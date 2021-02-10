#include "pch.h"
#include "Static_Animation.h"
#include <math.h>
#define _USE_MATH_DEFINES
OleFactoryClass* OleFactoryClass::instance_ = nullptr;

Button_Animation::Button_Animation()
{
	GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput_, NULL);

	oleFactory_.getInstance();

	animation_controller_.SetRelatedWnd(this);
	animation_controller_.EnableAnimationTimerEventHandler();
}

Button_Animation::~Button_Animation()
{
	Gdiplus::GdiplusShutdown(gdiplusToken_);
}
void Button_Animation::setBackGroundColor(COLORREF color)
{
	backgroundColor_ = color;
}
void Button_Animation::setTextColor(COLORREF color)
{
	textColor_ = color;
}
void Button_Animation::setHighlightColor(COLORREF color)
{
	highlightColor_ = color;
}
void Button_Animation::setClickColor(COLORREF color)
{
	clickColor_ = color;
}
void Button_Animation::setAnimationSeconds(double seconds)
{
	seconds_ = seconds;
}
BEGIN_MESSAGE_MAP(Button_Animation, CWnd)
	ON_WM_MOUSELEAVE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void Button_Animation::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TRACKMOUSEEVENT tme;
	ZeroMemory(&tme, sizeof(TRACKMOUSEEVENT));
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = m_hWnd;
	tme.dwFlags = TME_LEAVE | TME_HOVER;
	tme.dwHoverTime = 1;
	_TrackMouseEvent(&tme);

	CWnd::OnMouseMove(nFlags, point);
}

void Button_Animation::OnMouseLeave()
{	
	state_ = State::Leave;
	Invalidate();
	CWnd::OnMouseLeave();
}

void Button_Animation::OnPaint()
{
	CPaintDC dc(this);

	CRect rc;
	GetClientRect(rc);

	Gdiplus::Graphics graphics(dc);

	/*Initialize buffer bitmap */
	Gdiplus::Bitmap memBmp(rc.Width(), rc.Height());
	Gdiplus::Graphics memG(&memBmp);

	COLORREF clr;
	if (state_ == State::Leave)
	{
		clr = backgroundColor_;
	}
	else
	{
		animation_color_.GetValue(clr);
	}

	CFont* font = GetFont();
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	font->GetLogFont(&lf);

	Gdiplus::Font gpFont(dc, &lf);

	Gdiplus::SolidBrush brush_text(Gdiplus::Color(GetRValue(textColor_), GetGValue(textColor_), GetBValue(textColor_)));
	Gdiplus::SolidBrush brush_rect(Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));

	memG.FillRectangle(&brush_rect, Gdiplus::Rect(rc.left, rc.top, rc.Width(), rc.Height()));

	CString text;
	GetWindowText(text);
	memG.DrawString(text, text.GetLength(), &gpFont, Gdiplus::PointF(rc.left, rc.top), &brush_text);

	graphics.DrawImage(&memBmp, 0, 0);
}

void Button_Animation::OnMouseHover(UINT nFlags, CPoint point)
{
	if( state_ != State::Hover && state_ != State::LClick)
	{

		ChangeState(State::Hover, backgroundColor_, highlightColor_);

	}
	CWnd::OnMouseHover(nFlags, point);
}


void Button_Animation::OnLButtonDown(UINT nFlags, CPoint point)
{
	ChangeState(State::LClick, highlightColor_, clickColor_);
	
	CWnd::OnLButtonDown(nFlags, point);
}


void Button_Animation::ChangeState(State state, COLORREF default_color, COLORREF target_color)
{
	state_ = state;
	animation_controller_.CleanUpGroup(1);

	animation_color_ = default_color;
	animation_color_.AddTransition(
		new CAccelerateDecelerateTransition(seconds_, GetRValue(target_color)),
		new CAccelerateDecelerateTransition(seconds_, GetGValue(target_color)),
		new CAccelerateDecelerateTransition(seconds_, GetBValue(target_color)));

	animation_color_.SetID(0, 1);
	animation_controller_.AddAnimationObject(&animation_color_);

	animation_controller_.AnimateGroup(1);
}

Circle_Progress::Circle_Progress()
{
	GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput_, NULL);

	oleFactory_.getInstance();

	animation_controller_.SetRelatedWnd(this);
	animation_controller_.EnableAnimationTimerEventHandler();
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

void Circle_Progress::start()
{
	state_ = State::InProgress;
	animation_controller_.CleanUpGroup(1);

	animation_degree_ = 0;
	animation_degree_.AddTransition(
		new CSinusoidalTransitionFromRange(seconds_, 0, 430, seconds_ * 2, UI_ANIMATION_SLOPE::UI_ANIMATION_SLOPE_DECREASING));

	animation_degree_.SetID(0, 1);

	animation_controller_.AddAnimationObject(&animation_degree_);

	animation_controller_.AnimateGroup(1);
	//Invalidate();
}

void Circle_Progress::stop()
{
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

	memG.FillRectangle(&brush_rect, Gdiplus::Rect(rc.left, rc.top, rc.Width(), rc.Height()));

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

		if (degree == 430)
		{
			start();
		}
	}

	Gdiplus::SolidBrush brushEllipse(Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));



	CPoint center = rc.CenterPoint();

	int radius = (rc.Width() > rc.Height() ? rc.Height() / 2 : rc.Width() / 2)*0.7;

	constexpr double pi = 3.141592653589793238462643383279502884L;

	for (int i = 0; i < 3; i++)
	{
		if ((degree > 0) && (degree < 360))
		{
			Gdiplus::PointF pt(
				center.x + radius * sin(degree * pi / 180)
				, center.y - radius * cos(degree * pi / 180)
			);

			memG.FillEllipse(&brushEllipse, Gdiplus::RectF(pt.X, pt.Y, 8, 8));
		}

		degree -= 20;
	}
	

	graphics.DrawImage(&memBmp, 0, 0);
}
