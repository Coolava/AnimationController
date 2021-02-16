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
}


BEGIN_MESSAGE_MAP(Dialog_Animation, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &Dialog_Animation::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &Dialog_Animation::OnBnClickedButtonRight)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
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
		new CAccelerateDecelerateTransition(2.0, target_.left),
		new CAccelerateDecelerateTransition(2.0, target_.top),
		new CAccelerateDecelerateTransition(2.0, target_.right),
		new CAccelerateDecelerateTransition(2.0, target_.bottom)

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
		new CAccelerateDecelerateTransition(2.0, target_.left),
		new CAccelerateDecelerateTransition(2.0, target_.top),
		new CAccelerateDecelerateTransition(2.0, target_.right),
		new CAccelerateDecelerateTransition(2.0, target_.bottom)

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
		else
		{
			MoveWindow(rc,FALSE);
		}
	}
}


BOOL Dialog_Animation::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	if (state_ == State::Move)
	{
		return FALSE;
	}
	else
	{
		return __super::OnEraseBkgnd(pDC);
	}
}
