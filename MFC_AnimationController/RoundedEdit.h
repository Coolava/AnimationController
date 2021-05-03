#pragma once
#include <afxwin.h>
#include <memory>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

class RoundedEdit :
    public CEdit
{
public:
    RoundedEdit();
    virtual ~RoundedEdit();

    void setText(CString text);
    void setAlignment(Gdiplus::StringAlignment alignment);
    void setLineAlignment(Gdiplus::StringAlignment alignment);
private:


    ULONG_PTR gdiplusToken_;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput_;

    CRect prevRect;
    using pBitmap = std::unique_ptr<Gdiplus::Bitmap>;
    pBitmap background_, cursor_;
    void prepareBackground(int cx, int cy, Gdiplus::Color color);

    Gdiplus::StringFormat format_;
    Gdiplus::Font font_;
    CString text_;


    void RoundedEdit::getRoundedPath(Gdiplus::GraphicsPath* pPath, Gdiplus::RectF baseRect);
    //void GetRoundedPath(Gdiplus::GraphicsPath* pPath, Gdiplus::RectF baseRect, float radius);

    enum class FocusState { none, focus };
    FocusState focusState;

    bool cursorState;
    enum Timer : UINT_PTR {Cursor = 1};

    int margin;
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CBrush   m_brBkgnd;
    afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);

    afx_msg void OnNcPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg void ParentNotify(UINT /*message*/, LPARAM /*lParam*/);
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual void PreSubclassWindow();
    afx_msg void OnPaint();
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    afx_msg void OnEnKillfocus();
};

