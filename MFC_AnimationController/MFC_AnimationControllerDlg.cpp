
// MFC_AnimationControllerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_AnimationController.h"
#include "MFC_AnimationControllerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAnimationControllerDlg 대화 상자



CMFCAnimationControllerDlg::CMFCAnimationControllerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_ANIMATIONCONTROLLER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAnimationControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ANIMATION, animation_);
	DDX_Control(pDX, IDC_STATIC_ANIMATION2, animation2_);
	DDX_Control(pDX, IDC_STATIC_ANIMATION3, animation3_);
	DDX_Control(pDX, IDC_STATIC_ANIMATION4, circleProgress_);
	DDX_Control(pDX, IDC_STATIC_LED, led_);
}

BEGIN_MESSAGE_MAP(CMFCAnimationControllerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_STATIC_ANIMATION, &CMFCAnimationControllerDlg::OnStnClickedStaticAnimation)
	ON_STN_CLICKED(IDC_STATIC_ANIMATION2, &CMFCAnimationControllerDlg::OnStnClickedStaticAnimation2)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_STATIC_ANIMATION3, &CMFCAnimationControllerDlg::OnStnClickedStaticAnimation3)
END_MESSAGE_MAP()


// CMFCAnimationControllerDlg 메시지 처리기

BOOL CMFCAnimationControllerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	dialog_animation_ = std::make_unique<Dialog_Animation>();

	circleProgress_.setBallCount(5);
	circleProgress_.setBallDistanceDegree(30.0);
	circleProgress_.setAnimationSeconds(3.0);

	
	animation_.loadImages({ _T("res\\Icon Power Off.png") , _T("res\\Icon Power On.png") });
	//animation_.showImage(0);

	animation2_.setText(_T("Animation Dialog"));
	animation2_.setTextAlign(Gdiplus::StringAlignment::StringAlignmentCenter);


	animation3_.setText(_T("Change LED"));
	animation3_.setTextAlign(Gdiplus::StringAlignment::StringAlignmentCenter);


	SetBackgroundColor(RGB(45, 45, 48));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCAnimationControllerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCAnimationControllerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCAnimationControllerDlg::OnStnClickedStaticAnimation()
{
	if (circleProgress_.getState() == Circle_Progress::State::InProgress)
	{
		KillTimer(10);
		circleProgress_.stop();
		animation_.showImage(0);
	}
	else
	{
		circleProgress_.start();
		SetTimer(10, 1000, NULL);
		animation_.showImage(1);
	}

}


void CMFCAnimationControllerDlg::OnStnClickedStaticAnimation2()
{
	if (dialog_animation_->IsWindowVisible())
	{
		dialog_animation_->ShowWindow(SW_HIDE);
	}
	else
	{
		CRect rcAnimation, rcParent, rcButton;
		GetClientRect(rcParent);
		ClientToScreen(rcParent);
		//dialog_animation_->GetWindowRect(rcAnimation);

		animation2_.GetWindowRect(rcButton);

		rcAnimation = CRect(rcButton.right, rcParent.top, rcParent.right, rcParent.bottom);
		//rcAnimation.MoveToXY(rcButton.right, rcParent.top);

		dialog_animation_->MoveWindow(rcAnimation);
		dialog_animation_->ShowWindow(SW_SHOW);

	}
	// TODO: Add your control notification handler code here

}


void CMFCAnimationControllerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	switch (nIDEvent)
	{
	case 10:
	{

		CString str;
		str.Format(_T("%d"), progress_++);
		/*CircleProgress*/
		circleProgress_.setText(str);
	}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCAnimationControllerDlg::OnStnClickedStaticAnimation3()
{
	if (led_.get() == true)
		led_.off();
	else
		led_.on();
}
