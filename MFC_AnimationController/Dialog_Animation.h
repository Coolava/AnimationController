#pragma once
#include <afxdialogex.h>
#include "OleInitializer.h"
#include "Button_Animation.h"

#include <thread>
#include <memory>
#include <chrono>
class Dialog_Animation :
    public CDialogEx, public OleInitializer
{
	DECLARE_DYNAMIC(Dialog_Animation)

public:
	Dialog_Animation(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Dialog_Animation();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANIMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CAnimationController animation_controller_;
	CAnimationRect animation_rect_;
	CRect target_;

	enum class State : int { Stop, Move };
	State state_ = State::Stop;

	Button_Animation buttonLeft;
	Button_Animation buttonRight;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
