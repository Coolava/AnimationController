#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

class Static_Animation :
    public CWnd
{
public:
    Static_Animation();
    virtual ~Static_Animation();


private:
    ULONG_PTR m_gdiplusToken;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;

    CAnimationColor animation_color_;
    CAnimationRect animation_rect_;
    CAnimationController animation_controller_;

    enum State : int { Leave, Hover, LClick };
    State state_ = Leave;
    bool mouse_leave_ = true;
    COLORREF background_ = RGB(45, 45, 48);


    void ChangeState(State state, COLORREF default_color, COLORREF target_color);
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnMouseLeave();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnMouseHover(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

