#pragma once
#include <afxwin.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
class CheckBox :
	public CWnd
{
private:

	Gdiplus::StringFormat stringFormat_;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

