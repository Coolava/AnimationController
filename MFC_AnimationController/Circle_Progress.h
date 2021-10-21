#pragma once
#include <afxwin.h>
#include "OleInitializer.h"
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

using StringAlignment = Gdiplus::StringAlignment;

class Circle_Progress :
    public OleInitializer, public CWnd
{
public:
    Circle_Progress();
    virtual ~Circle_Progress();

    enum class State : int { Stop, InProgress };
    void setBackGroundColor(COLORREF color);
    void setInnerColor(COLORREF color);
    /*For 360 degrees*/
    void setAnimationSeconds(double seconds);
    void setBallCount(int count);
    void setBallSize(double size);
    void setBallDistanceDegree(double degree);

    void start();
    void stop();

    void SetWindowTextA(LPCSTR lpString);
    void SetWindowTextW(LPCWSTR lpString);

    void GetWindowTextA(LPSTR& lpString);
    void GetWindowTextW(LPWSTR& lpString);

    void setAlignment(StringAlignment alignment);
    void setLineAlignment(StringAlignment alignment);
private:

    ULONG_PTR gdiplusToken_;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput_;

    CAnimationController animation_controller_;

    CAnimationValue animation_degree_;
    COLORREF backgroundColor_ = RGB(45, 45, 48);
    COLORREF ballColor_ = RGB(255, 255, 255);
    double seconds_ = 2.0;

    int ballCount_ = 10;
    double ballSize_ = 8;
    double distance_ = 30.0;

    State state_ = State::Stop;

    Gdiplus::StringFormat format_;
    Gdiplus::Font font_;

    bool isSetText = false;
    CString text_;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();

public:
    State getState() {
        return state_;
    }
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};
