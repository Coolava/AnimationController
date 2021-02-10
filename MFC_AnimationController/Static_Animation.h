#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#include <memory>
#pragma comment (lib,"Gdiplus.lib")

class OleFactoryClass
{
public:
    static OleFactoryClass& getInstance()
    {
        if( instance_ == nullptr)
        {
            static OleFactoryClass instance;
            instance_ = &instance;
        }

        return *instance_;
    }

private:
    static OleFactoryClass* instance_;
    OleFactoryClass() {
        AfxOleInit();
    };

    ~OleFactoryClass(){
        AfxOleTerm(FALSE);
    }
};

class Circle_Progress :
    public CWnd
{
public:
    Circle_Progress();
    virtual ~Circle_Progress();

    void setBackGroundColor(COLORREF color);
    void setInnerColor(COLORREF color);
    void setAnimationSeconds(double seconds);

    void start();
    void stop();
private:
    static OleFactoryClass oleFactory_;

    ULONG_PTR gdiplusToken_;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput_;

    CAnimationController animation_controller_;

    CAnimationValue animation_degree_;
    COLORREF backgroundColor_ = RGB(45, 45, 48);
    COLORREF ballColor_ = RGB(255, 255, 255);
    double seconds_ = 2.0;


    enum class State : int { Stop, InProgress };
    State state_ = State::Stop;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
};

class Button_Animation :
    public CWnd
{
public:
    Button_Animation();
    virtual ~Button_Animation();

    void setBackGroundColor(COLORREF color);
    void setTextColor(COLORREF color);
    void setHighlightColor(COLORREF color);
    void setClickColor(COLORREF color);
    void setAnimationSeconds(double seconds);
private:
    static OleFactoryClass oleFactory_;

    ULONG_PTR gdiplusToken_;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput_;

    CAnimationColor animation_color_;
    CAnimationRect animation_rect_;
    CAnimationController animation_controller_;

    enum class State : int { Leave, Hover, LClick };
    State state_ = State::Leave;
    bool mouse_leave_ = true;
    COLORREF backgroundColor_ = RGB(45, 45, 48);
    COLORREF textColor_ = RGB(255,255,255);
    COLORREF highlightColor_ = RGB(62, 62, 64);
    COLORREF clickColor_ = RGB(0, 122, 204);
    
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

