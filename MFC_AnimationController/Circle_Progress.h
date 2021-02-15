#pragma once
#include <afxwin.h>
#include "OleInitializer.h"
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

class Circle_Progress :
    public OleInitializer, public CWnd
{
public:
    Circle_Progress();
    virtual ~Circle_Progress();

    enum class State : int { Stop, InProgress };
    void setBackGroundColor(COLORREF color);
    void setInnerColor(COLORREF color);
    void setAnimationSeconds(double seconds);
    void setBallCount(int count);
    void setBallSize(double size);

    void start();
    void stop();
private:

    ULONG_PTR gdiplusToken_;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput_;

    CAnimationController animation_controller_;

    CAnimationValue animation_degree_;
    COLORREF backgroundColor_ = RGB(45, 45, 48);
    COLORREF ballColor_ = RGB(255, 255, 255);
    double seconds_ = 2.0;

    int ballCount_ = 3;
    double ballSize_ = 8;

    State state_ = State::Stop;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();

public:
    State getState() {
        return state_;
    }
};
