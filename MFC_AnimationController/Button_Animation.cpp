#include "Button_Animation.h"

Button_Animation::Button_Animation()
{
	GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput_, NULL);

	animation_controller_.SetRelatedWnd(this);
	animation_controller_.EnableAnimationTimerEventHandler();
}

Button_Animation::~Button_Animation()
{
	imageList.clear();
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
void Button_Animation::setBorderColor(COLORREF color)
{
	borderColor_ = color;
}

void Button_Animation::setBorderWidth(float width)
{
	borderWidth_ = width;
}



void Button_Animation::setAnimationSeconds(double seconds)
{
	seconds_ = seconds;
}
void Button_Animation::setTextAlign(Gdiplus::StringAlignment align)
{
	stringFormat_.SetAlignment(align);
	stringFormat_.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
}
bool Button_Animation::loadImages(std::vector<std::wstring> imagePath)
{
	if (imagePath.size() == 0)
	{
		return false;
	}

	imageList.clear();

	for (auto path : imagePath)
	{
		imageList.emplace_back(new Gdiplus::Image(path.c_str()));
	}

	return true;

}

bool Button_Animation::showImage(size_t index)
{
	if (index >= imageList.size())
	{
		return false;
	}

	imageIndex = index;

	Invalidate();

	return true;
}

void Button_Animation::setText(CString text)
{
	text_ = text;
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

	/*Draw background*/
	memG.FillRectangle(&brush_rect, Gdiplus::Rect(rc.left, rc.top, rc.Width(), rc.Height()));

	/*Draw border*/
	if(borderColor_ != MAXDWORD)
	{
		Gdiplus::Pen borderPen(Gdiplus::Color(GetRValue(borderColor_), GetGValue(borderColor_), GetBValue(borderColor_)), borderWidth_);
		memG.DrawRectangle(&borderPen, Gdiplus::Rect(rc.left, rc.top, rc.Width(), rc.Height()));
	}

	/*Draw Image*/
	if (imageList.size() > 0)
	{
		if (imageIndex < imageList.size())
		{
			float imageWidth = (float)imageList[imageIndex]->GetWidth();
			float imageHeight = (float)imageList[imageIndex]->GetHeight();

			float controlWidth = (float)rc.Width();
			float controlHeight = (float)rc.Height();

			float horizontalScalingFactor = 0;
			float verticalScalingFactor = 0;

			if (imageWidth > controlWidth)
			{
				horizontalScalingFactor = controlWidth / imageWidth;
			}
			else
			{
				horizontalScalingFactor = imageWidth / controlWidth;
			}

			if (imageHeight > controlHeight)
			{
				verticalScalingFactor = controlHeight / imageHeight;
			}
			else
			{
				verticalScalingFactor = imageHeight / controlHeight;

			}

			float scalingFactor = 0;
			if (horizontalScalingFactor > verticalScalingFactor)
			{
				scalingFactor = horizontalScalingFactor;
			}
			else
			{
				scalingFactor = verticalScalingFactor;
			}

			scalingFactor = scalingFactor * 0.9f;

			if (scalingFactor != 0)
			{
				Gdiplus::Image* img = new Gdiplus::Bitmap(static_cast<int>(controlWidth * 0.9f), static_cast<int>(controlHeight * 0.9f));
				Gdiplus::Graphics g(img);
				g.ScaleTransform(scalingFactor, scalingFactor);
				g.DrawImage(imageList[imageIndex].get(), 0, 0);

				float width = imageList[imageIndex]->GetWidth()* scalingFactor;
				float height = imageList[imageIndex]->GetHeight()* scalingFactor;

				float marginLeft = (controlWidth - width) / 2;
				float marginTop = (controlHeight - height) / 2;

				memG.DrawImage(img, marginLeft, marginTop);
			}
		}

	}
	//CString text;
	//GetWindowText(text);

	memG.DrawString(text_, text_.GetLength(), &gpFont, Gdiplus::RectF(static_cast<float>(rc.left), static_cast<float>(rc.top), static_cast<float>(rc.Width()), static_cast<float>(rc.Height())), &stringFormat_, &brush_text);

	graphics.DrawImage(&memBmp, 0, 0);
}

void Button_Animation::OnMouseHover(UINT nFlags, CPoint point)
{
	if (state_ != State::Hover && state_ != State::LClick)
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
