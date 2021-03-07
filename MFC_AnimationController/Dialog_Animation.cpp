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
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
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
		else
		{
			MoveWindow(rc);
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


BOOL Dialog_Animation::OnInitDialog()
{
	__super::OnInitDialog();


	SetBackgroundColor(RGB(65, 65, 68));

	buttonLeft.setTextAlign(Gdiplus::StringAlignment::StringAlignmentCenter);
	buttonRight.setTextAlign(Gdiplus::StringAlignment::StringAlignmentCenter);
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

		rc.right = rc.left + 1;

		MoveWindow(rc);
		threadRect.get_id();

		if (threadRect.joinable())
		{
			threadRect.join();
		}

		/*Using CAnimationController in OnShowWindow can't draw background.*/
		threadRect = std::thread(&Dialog_Animation::rectProcessor, this);

	}

}

void Dialog_Animation::rectProcessor()
{
	const double targetSecond = 0.2;
	const double fps = 60;
	const double frameCount = targetSecond * fps;
	const double secondsPerFrame = 1 / fps;

	CRect targetRect = target_, startRect;

	GetWindowRect(startRect);

	RectDouble rectPerFrame{
		((double)targetRect.left - startRect.left) / frameCount,
		((double)targetRect.right - startRect.right) / frameCount,
		((double)targetRect.top - startRect.top) / frameCount,
		((double)targetRect.bottom - startRect.bottom) / frameCount
	};

	double currentSecond = 0;
	auto targetTime = std::chrono::system_clock::now();
	for (double i = 0; i < frameCount; i++)
	{
		startRect.left += rectPerFrame.left;
		startRect.right += rectPerFrame.right;
		startRect.top += rectPerFrame.top;
		startRect.bottom += rectPerFrame.bottom;

		MoveWindow(startRect);

		targetTime += std::chrono::milliseconds((int)(secondsPerFrame *1000));
		std::this_thread::sleep_until(targetTime);
	}

	/*double to long will be loss some rect.*/
	MoveWindow(targetRect);



}
