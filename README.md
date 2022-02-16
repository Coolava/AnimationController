# MFC_AnimationController

![mfc_animationController](https://user-images.githubusercontent.com/45839935/152891260-72bbbec1-250e-4993-a266-c9590785be92.gif)
## Introduce  
MFC로 제작한 App에도 WPF의 Storyboard와 같은 이펙트를 넣어보고 싶어서 시작한 프로젝트

## Environment
* Windows 10
* Visual studio 2019 (v142)
* Visual studio 2022 (v143)

## Contents
- Button/
  - 마우스가 컨트롤 위에 Hover 상태 일 때 `Hightlight` 기능
  - 컨트롤에 손쉽게 이미지 삽입 할 수 있는 `loadImages` 함수 추가
- Circle Progress
  - 윈도우에서 작업 대기 상태를 표시하는 애니메이션을 흉내냄
  - OnPaint 내부에서 `GetWindowText`를 사용하고 있는데 해당부분을 다른방식으로 바꾸면 성능 개선 가능
- Dialog
  - 웹에서 어떤 화면이 나타날 때 두루마리가 펼쳐지듯이 나타나는것을 적용함 
  - Alpha값을 조절하는 기능을 추가하면 더 좋을것 같다.
- Led
  - 개인적으로 LED 컨트롤을 사용할 경우가 많아 만들어본 컨트롤

## Improvement point
- WM_PAINT 메세지가 너무 많이 발생함.
- Buffer DC를 다른곳에서 생성 하는 방식으로 하면 성능 개선이 가능할 듯
- 컨트롤 구현부와 Animation을 분리가능 
  - Animation을 Manager 형식으로 분리하거나 Script형식으로 분리하면 좀 더 사용하기 쉽지 않을까?
     
If you need more information about Animation in MFC Application, See [CAnimationController](https://docs.microsoft.com/ko-kr/cpp/mfc/reference/canimationcontroller-class?view=msvc-160) on MSDN.

