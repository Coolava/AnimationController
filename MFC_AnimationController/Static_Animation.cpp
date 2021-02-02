#include "pch.h"
#include "Static_Animation.h"

Static_Animation::Static_Animation()
{
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	if (!AfxOleInit())
	{
	}
	animation_controller_.SetRelatedWnd(this);
	animation_controller_.EnableAnimationTimerEventHandler();

	ChangeState(State::Hover, background_, RGB(62, 62, 64));

}

Static_Animation::~Static_Animation()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	AfxOleTerm(FALSE);
}
BEGIN_MESSAGE_MAP(Static_Animation, CWnd)
	ON_WM_MOUSELEAVE()
//	ON_WM_NCPAINT()
ON_WM_PAINT()
ON_WM_MOUSEMOVE()
ON_WM_MOUSEHOVER()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void Static_Animation::OnMouseMove(UINT nFlags, CPoint point)
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

void Static_Animation::OnMouseLeave()
{	
	state_ = State::Leave;
	Invalidate();
	CWnd::OnMouseLeave();
}

void Static_Animation::OnPaint()
{
	CPaintDC dc(this);

	CRect rc;
	GetClientRect(rc);

	Gdiplus::Graphics graphics(dc);
	Gdiplus::Bitmap memBmp(rc.Width(), rc.Height());
	Gdiplus::Graphics memG(&memBmp);

	COLORREF clr;
	if (state_ == State::Leave)
	{
		clr = background_;
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

	Gdiplus::SolidBrush brush_text(Gdiplus::Color::White);
	Gdiplus::SolidBrush brush_rect(Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));

	memG.FillRectangle(&brush_rect, Gdiplus::Rect(rc.left, rc.top, rc.Width(), rc.Height()));

	CString text;
	GetWindowText(text);
	memG.DrawString(text, text.GetLength(), &gpFont, Gdiplus::PointF(rc.left, rc.top), &brush_text);

	graphics.DrawImage(&memBmp, 0, 0);
}

void Static_Animation::OnMouseHover(UINT nFlags, CPoint point)
{
	if( state_ != State::Hover && state_ != State::LClick)
	{

		//ChangeState(State::Hover, background_, RGB(62, 62, 64));

	}
	CWnd::OnMouseHover(nFlags, point);
}


void Static_Animation::OnLButtonDown(UINT nFlags, CPoint point)
{

	animation_controller_.ScheduleGroup(1,0.01);
	//ChangeState(State::LClick, RGB(62, 62, 64),RGB(0,122,204));
	
	CWnd::OnLButtonDown(nFlags, point);
}


void Static_Animation::ChangeState(State state, COLORREF default_color, COLORREF target_color)
{
	state_ = state;
	animation_controller_.CleanUpGroup(1);

	animation_color_ = default_color;
	animation_color_.AddTransition(new CAccelerateDecelerateTransition(0.1, GetRValue(target_color)),
		new CAccelerateDecelerateTransition(0.1, GetGValue(target_color)),
		new CAccelerateDecelerateTransition(0.1, GetBValue(target_color)));

	animation_color_.SetID(0, 1);
	animation_controller_.AddAnimationObject(&animation_color_);

	animation_controller_.AnimateGroup(1);
}