#include "pch.h"
#include "MFC_AnimationController.h"
#include "Dialog_Animation.h"


IMPLEMENT_DYNAMIC(Dialog_Animation, CDialogEx)

Dialog_Animation::Dialog_Animation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANIMATION, pParent)
{
	Create(IDD_DIALOG_ANIMATION, pParent);

	animation_controller_.SetRelatedWnd(this);
	animation_controller_.EnableAnimationTimerEventHandler();
}

Dialog_Animation::~Dialog_Animation()
{
}

void Dialog_Animation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_LEFT, buttonLeft);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, buttonRight);
	
}


BEGIN_MESSAGE_MAP(Dialog_Animation, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &Dialog_Animation::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &Dialog_Animation::OnBnClickedButtonRight)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
END_MESSAGE_MAP()



void Dialog_Animation::OnBnClickedButtonLeft()
{
	state_ = State::Move;
	animation_controller_.CleanUpGroup(1);

	CRect rc;
	GetWindowRect(rc);
	animation_rect_ = rc;
	target_ = rc;
	target_.left -= 100;
	target_.right -= 100;

	animation_rect_.AddTransition(
		new CAccelerateDecelerateTransition(1.0, target_.left, 0.5, 0.3),
		new CAccelerateDecelerateTransition(1.0, target_.top, 0.5, 0.3),
		new CAccelerateDecelerateTransition(1.0, target_.right, 0.5, 0.3),
		new CAccelerateDecelerateTransition(1.0, target_.bottom, 0.5, 0.3)

	);
	animation_rect_.SetID(0, 1);

	animation_controller_.AddAnimationObject(&animation_rect_);

	animation_controller_.AnimateGroup(1);

}


void Dialog_Animation::OnBnClickedButtonRight()
{
	state_ = State::Move;
	animation_controller_.CleanUpGroup(1);

	CRect rc;
	GetWindowRect(rc);
	animation_rect_ = rc;
	target_ = rc;
	target_.left += 100;
	target_.right += 100;

	animation_rect_.AddTransition(
		new CAccelerateDecelerateTransition(1.0, target_.left, 0.5,0.3),
		new CAccelerateDecelerateTransition(1.0, target_.top, 0.5, 0.3),
		new CAccelerateDecelerateTransition(1.0, target_.right, 0.5, 0.3),
		new CAccelerateDecelerateTransition(1.0, target_.bottom, 0.5, 0.3)

	);
	animation_rect_.SetID(0, 1);

	animation_controller_.AddAnimationObject(&animation_rect_);

	animation_controller_.AnimateGroup(1);
}


void Dialog_Animation::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call __super::OnPaint() for painting messages

	CRect rc;
	if (state_ == State::Move)
	{
		animation_rect_.GetValue(rc);
		if (rc == target_)
		{
			state_ = State::Stop;
		}
		MoveWindow(rc);
	}
}


BOOL Dialog_Animation::OnInitDialog()
{
	__super::OnInitDialog();


	SetBackgroundColor(RGB(65, 65, 68));

	buttonLeft.setTextAlign(Gdiplus::StringAlignment::StringAlignmentCenter);
	buttonLeft.setText(_T("<--"));
	buttonLeft.setBackGroundColor(RGB(65, 65, 68));
	buttonLeft.setHighlightColor(0x3C3C3C);

	buttonRight.setTextAlign(Gdiplus::StringAlignment::StringAlignmentCenter);
	buttonRight.setText(_T("-->"));
	buttonRight.setBackGroundColor(RGB(65, 65, 68));
	buttonRight.setHighlightColor(0x3C3C3C);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void Dialog_Animation::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	if( bShow == TRUE)
	{
		CRect rc;
		GetWindowRect(rc);

		target_ = rc;


		CRect rcStart = rc;
		/* If cx is zero, it couldn't be work*/
		//rcStart.right = rcStart.left + 0;
		rcStart.right = rcStart.left + 1;

		MoveWindow(rcStart);

		state_ = State::Move;

		animation_rect_ = rcStart;

		animation_rect_.AddTransition(
			new CAccelerateDecelerateTransition(0.5, target_.left, 0.5, 0.3),
			new CAccelerateDecelerateTransition(0.5, target_.top, 0.5, 0.3),
			new CAccelerateDecelerateTransition(0.5, target_.right, 0.5, 0.3),
			new CAccelerateDecelerateTransition(0.5, target_.bottom, 0.5, 0.3)

		);
		animation_rect_.SetID(0, 1);

		animation_controller_.AddAnimationObject(&animation_rect_);

		animation_controller_.AnimateGroup(1);
	}

}

