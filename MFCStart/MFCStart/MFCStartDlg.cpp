
// MFCStartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCStart.h"
#include "MFCStartDlg.h"
#include "afxdialogex.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCStartDlg 대화 상자



CMFCStartDlg::CMFCStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSTART_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POINT_RADIUS, m_model.m_nPointRadius);
	DDV_MinMaxInt(pDX, m_model.m_nPointRadius, 1, 100);
	DDX_Text(pDX, IDC_EDIT_BORDER_THICKNESS, m_model.m_nThickness);
	DDV_MinMaxInt(pDX, m_model.m_nThickness, 1, 50);
}

BEGIN_MESSAGE_MAP(CMFCStartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_RESET, &CMFCStartDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_RANDOM_MOVE, &CMFCStartDlg::OnBnClickedBtnRandomMove)
	ON_MESSAGE(WM_USER_REFRESH_UI, &CMFCStartDlg::OnUserRefreshUI)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMFCStartDlg 메시지 처리기

BOOL CMFCStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_controller = std::make_unique<CCircleController>(m_model, *this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCStartDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCStartDlg::OnPaint()
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
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);

		// 1. 메모리 DC 및 비트맵 생성 (임시 도화지)
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		
		CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

		// 2. 배경 지우기 (메모리 DC에)
		memDC.FillSolidRect(&rect, RGB(255, 255, 255));

		// 3. 메모리 DC에 그리기
		UpdateData(TRUE); // UI에서 반지름과 두께 값을 가져옴

		// 저장된 점 그리기
		for (const auto& pt : m_model.m_vPoints)
		{
			CPixelPainter::DrawFilledCircle(&memDC, pt, m_model.m_nPointRadius, RGB(0, 0, 0));
		}

		// 3개의 점이 있을 경우 외접원 그리기
		if (m_model.IsReadyForCircle())
		{
			CPoint center;
			double radius;
			if (CGeometry::CalculateCircumcircle(m_model.m_vPoints, center, radius))
			{
				CPixelPainter::DrawHollowCircle(&memDC, center, radius, m_model.m_nThickness, RGB(0, 0, 0));
			}
		}

		// 4. 메모리 DC의 내용을 실제 화면 DC로 한 번에 복사
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		// 5. 정리
		memDC.SelectObject(pOldBitmap);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCStartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCStartDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_controller->OnLButtonDown(nFlags, point);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCStartDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	m_controller->OnMouseMove(nFlags, point);
	CDialogEx::OnMouseMove(nFlags, point);
}

void CMFCStartDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_controller->OnLButtonUp(nFlags, point);
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMFCStartDlg::UpdateCoordinateDisplay()
{
	UINT nIDs[] = { IDC_STATIC_COORD1, IDC_STATIC_COORD2, IDC_STATIC_COORD3 };
	
	for (int i = 0; i < 3; i++)
	{
		CString str;
		if (i < static_cast<int>(m_model.m_vPoints.size()))
		{
			str.Format(_T("Point %d: (%d, %d)"), i + 1, m_model.m_vPoints[i].x, m_model.m_vPoints[i].y);
		}
		else
		{
			str.Format(_T("Point %d: (- , -)"), i + 1);
		}
		SetDlgItemText(nIDs[i], str);
	}
}

void CMFCStartDlg::OnBnClickedBtnReset()
{
	m_controller->OnReset();
}

void CMFCStartDlg::OnBnClickedBtnRandomMove()
{
	m_controller->OnRandomMove();
}

LRESULT CMFCStartDlg::OnUserRefreshUI(WPARAM wParam, LPARAM lParam)
{
	UpdateCoordinateDisplay();
	Invalidate();

	// wParam이 0보다 크면 남은 횟수 표시, 0이면 원래대로 복구
	if (wParam > 0)
	{
		CString strStatus;
		strStatus.Format(_T("Point Coordinates (Remaining: %d)"), (int)wParam);
		SetDlgItemText(IDC_STATIC_COORD_LABEL, strStatus);
	}
	else
	{
		SetDlgItemText(IDC_STATIC_COORD_LABEL, _T("Point Coordinates:"));
	}

	return 0;
}

BOOL CMFCStartDlg::OnEraseBkgnd(CDC* pDC)
{
	// 더블 버퍼링을 위해 배경 지우기 기능을 비활성화합니다.
	return TRUE;
}

BOOL CMFCStartDlg::PreTranslateMessage(MSG* pMsg)
{
	// WM_KEYDOWN 메시지 중 엔터와 ESC 키를 필터링합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE; // 메시지를 처리하지 않고 무시함
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

