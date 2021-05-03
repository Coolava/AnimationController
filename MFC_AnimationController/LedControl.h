#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#include <memory>
class LedControl :public CWnd
{
public:
    LedControl();
    virtual ~LedControl();

    void setColor(COLORREF onState, COLORREF offState);

    bool get() { return state; }
    void on() { state = true; Invalidate(); }
    void off() { state = false; Invalidate(); }
private:

    bool state;
    COLORREF colorOn_ = 0x858585;
    COLORREF colorOff_ = 0x2DD821;


	std::unique_ptr < CDC> memBackground;
	std::unique_ptr < CBitmap> memBitmap;

public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
};

