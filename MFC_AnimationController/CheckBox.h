#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
class CheckBox :
	public CWnd
{
public:
	CheckBox();
	~CheckBox();

	void setCheckColor(COLORREF color);
	void setBoxColor(COLORREF color);
	void setTextColor(COLORREF color);
	void setTextAlign(Gdiplus::StringAlignment align);


private:

	ULONG_PTR gdiplusToken_;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput_;

	Gdiplus::StringFormat stringFormat_;

	COLORREF textColor_ = RGB(255, 255, 255);
	COLORREF boxColor_ = RGB(62, 62, 64);
	COLORREF checkColor_ = RGB(255, 255, 255);
	
	enum class State { None , Checked};
	State checkedState_ = State::None;


	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();


public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

