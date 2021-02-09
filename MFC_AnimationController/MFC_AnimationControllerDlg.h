
// MFC_AnimationControllerDlg.h: 헤더 파일
//

#pragma once
#include "Static_Animation.h"

// CMFCAnimationControllerDlg 대화 상자
class CMFCAnimationControllerDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCAnimationControllerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_ANIMATIONCONTROLLER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	Button_Animation animation_;
	Button_Animation animation2_;
	Button_Animation animation3_;
	Button_Animation animation4_;
public:
	afx_msg void OnBnClickedButtonAnimation();
};
