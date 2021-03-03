#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#include "OleInitializer.h"


class Button_Animation :
    public OleInitializer, public CWnd
{
public:
    Button_Animation();
    virtual ~Button_Animation();

    void setBackGroundColor(COLORREF color);
    void setTextColor(COLORREF color);
    void setHighlightColor(COLORREF color);
    void setClickColor(COLORREF color);
    void setAnimationSeconds(double seconds);

    void setTextAlign(Gdiplus::StringAlignment align);
private:

    ULONG_PTR gdiplusToken_;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput_;

    CAnimationColor animation_color_;
    CAnimationRect animation_rect_;
    CAnimationController animation_controller_;

    enum class State : int { Leave, Hover, LClick };
    State state_ = State::Leave;
    bool mouse_leave_ = true;
    COLORREF backgroundColor_ = RGB(45, 45, 48);
    COLORREF textColor_ = RGB(255, 255, 255);
    COLORREF highlightColor_ = RGB(62, 62, 64);
    COLORREF clickColor_ = RGB(0, 122, 204);

    Gdiplus::StringFormat stringFormat_;

    double seconds_ = 0.2;

    void ChangeState(State state, COLORREF default_color, COLORREF target_color);
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnMouseLeave();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnMouseHover(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

