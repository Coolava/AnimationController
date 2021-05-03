#include "pch.h"
#include "RoundedEdit.h"
#include <imm.h>
#pragma comment(lib,"imm32.lib")

using namespace Gdiplus;

RoundedEdit::RoundedEdit()
	:font_(Gdiplus::FontFamily::GenericMonospace(), 10)
{
	GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput_, NULL);


	format_.SetAlignment(Gdiplus::StringAlignmentCenter);
	format_.SetLineAlignment(Gdiplus::StringAlignmentCenter);

}

RoundedEdit::~RoundedEdit()
{
	Gdiplus::GdiplusShutdown(gdiplusToken_);
}

BEGIN_MESSAGE_MAP(RoundedEdit, CWnd)

	ON_WM_TIMER()

	ON_WM_NCPAINT()
	//ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_PARENTNOTIFY_REFLECT()
	ON_WM_PAINT()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &RoundedEdit::OnEnKillfocus)
END_MESSAGE_MAP()


void RoundedEdit::setText(CString text)
{
	text_ = text;
}
void RoundedEdit::setAlignment(StringAlignment alignment)
{
	format_.SetAlignment(alignment);
}
void RoundedEdit::setLineAlignment(StringAlignment alignment)
{
	format_.SetLineAlignment(alignment);
}

void RoundedEdit::prepareBackground(int cx, int cy, Color color)
{
	if(background_)
	{
		Gdiplus::Graphics memG(background_.get());
		memG.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
		RectF paintRect(0, 0, cx, cy);

		SolidBrush backBrush(color);

		GraphicsPath roundPath;
		getRoundedPath(&roundPath, paintRect);
		memG.FillPath(&backBrush, &roundPath);
	}
}

void RoundedEdit::getRoundedPath(GraphicsPath* pPath, RectF baseRect) {
	float diameter = 0;

	TRY{
		if (baseRect.Width > baseRect.Height) {
			diameter = baseRect.Height;
			RectF arc(baseRect.X, baseRect.Y, diameter, diameter);
			pPath->AddArc(arc, 90, 180);
			arc.X = baseRect.GetRight() - diameter;
			pPath->AddArc(arc, 270, 180);
		}
		else if (baseRect.Width < baseRect.Height) {
		   diameter = baseRect.Width;

		   RectF arc(baseRect.X, baseRect.Y, diameter, diameter);
		   pPath->AddArc(arc, 180, 180);
		   arc.Y = baseRect.GetBottom() - diameter;
		   pPath->AddArc(arc, 0, 180);
		}
		else {
		   pPath->AddEllipse(baseRect);
		}


	}CATCH(CException, ex) {
		pPath->AddEllipse(baseRect);
	}
	END_CATCH
		pPath->CloseFigure();
	margin = static_cast<int>(diameter / 4);

}


void RoundedEdit::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == Timer::Cursor)
	{
		cursorState = !cursorState;
		Invalidate();
	}
	CWnd::OnTimer(nIDEvent);
}





//
//void RoundedEdit::OnNcPaint()
//{
//	// TODO: Add your message handler code here
//	// Do not call CEdit::OnNcPaint() for painting messages
//	// TODO: Add your message handler code here and/or call default
//	CClientDC dc(this); // device context for painting
//					   // TODO: Add your message handler code here
//					   // Do not call CWnd::OnPaint() for painting messages
//
//
//	CRect rc;
//	GetClientRect(rc);
//
//	Graphics graphics(dc);
//	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
//
//	Gdiplus::Bitmap memBmp(rc.Width(), rc.Height());
//	Gdiplus::Graphics memG(&memBmp);
//
//	memG.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
//
//	if (rc != prevRect)
//	{
//		background_.reset(new Bitmap(rc.Width(), rc.Height()));
//		prepareBackground(rc.Width(), rc.Height(), Color::DarkGray);
//		prevRect = rc;
//
//		CRect editRect(rc);
//		editRect.left += margin;
//		editRect.top += margin;
//		editRect.right -= margin;
//		editRect.bottom -= margin;
//		SetRect(editRect);
//
//
//	}
//	memG.DrawImage(background_.get(), 0, 0);
//	graphics.DrawImage(&memBmp, 0, 0);
//
//}



void RoundedEdit::OnNcPaint()
{
	CPaintDC dc(this); // device context for painting
				   // TODO: Add your message handler code here
				   // Do not call CWnd::OnPaint() for painting messages


	CRect rc;
	GetClientRect(rc);

	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	Gdiplus::Bitmap memBmp(rc.Width(), rc.Height());
	Gdiplus::Graphics memG(&memBmp);

	memG.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	if (rc != prevRect)
	{
		background_.reset(new Bitmap(rc.Width(), rc.Height()));
		prepareBackground(rc.Width(), rc.Height(), Color::DarkGray);
		prevRect = rc;



	}
	memG.DrawImage(background_.get(), 0, 0);
	graphics.DrawImage(&memBmp, 0, 0);
}


BOOL RoundedEdit::OnEraseBkgnd(CDC* pDC)
{


	return TRUE; // 작업이 성공적으로 수행됨을 알림.

}


BOOL RoundedEdit::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL rtn = CEdit::Create(dwStyle, rect, pParentWnd, nID);


	return rtn;
}


int RoundedEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void RoundedEdit::OnSize(UINT nType, int cx, int cy)
{
	CEdit::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

}


void RoundedEdit::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
{
	// TODO: Add your specialized code here and/or call the base class

	CEdit::CalcWindowRect(lpClientRect, nAdjustType);
}


void RoundedEdit::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CEdit::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}


void RoundedEdit::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CEdit::OnWindowPosChanged(lpwndpos);

	// TODO: Add your message handler code here
}


void RoundedEdit::ParentNotify(UINT /*message*/, LPARAM /*lParam*/)
{
	// TODO: Add your message handler code here
}


void RoundedEdit::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class

	CEdit::DoDataExchange(pDX);
}


void RoundedEdit::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CEdit::PreSubclassWindow();

}


void RoundedEdit::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CEdit::OnPaint() for painting messages


	CRect editRect;
	GetRect(editRect);
	editRect.left += 6;
	editRect.top += 6;
	editRect.right -= 6;
	editRect.bottom -= 6;
	SetRect(editRect);
}


BOOL RoundedEdit::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	
	CRect editRect;
	GetRect(editRect);
	editRect.left += 6;
	editRect.top += 6;
	editRect.right -= 6;
	editRect.bottom -= 6;
	return CEdit::PreCreateWindow(cs);
}


void RoundedEdit::OnEnKillfocus()
{
	// TODO: Add your control notification handler code here

	CRect editRect;
	GetRect(editRect);
	editRect.left += 6;
	editRect.top += 6;
	editRect.right -= 6;
	editRect.bottom -= 6;
}
