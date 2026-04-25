
// AdrBookView.cpp: CAdrBookView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AdrBook.h"
#endif

#include "AdrBookDoc.h"
#include "AdrBookView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdrBookView

IMPLEMENT_DYNCREATE(CAdrBookView, CView)

BEGIN_MESSAGE_MAP(CAdrBookView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CAdrBookView 생성/소멸

CAdrBookView::CAdrBookView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CAdrBookView::~CAdrBookView()
{
}

BOOL CAdrBookView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAdrBookView 그리기

void CAdrBookView::OnDraw(CDC* /*pDC*/)
{
	CAdrBookDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CAdrBookView 인쇄

BOOL CAdrBookView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAdrBookView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAdrBookView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CAdrBookView 진단

#ifdef _DEBUG
void CAdrBookView::AssertValid() const
{
	CView::AssertValid();
}

void CAdrBookView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAdrBookDoc* CAdrBookView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAdrBookDoc)));
	return (CAdrBookDoc*)m_pDocument;
}
#endif //_DEBUG


// CAdrBookView 메시지 처리기

int CAdrBookView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 리스트 박스 윈도우 생성
	m_wndList.Create(WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_HSCROLL,
		CRect(10, 10, 200, 200), this, 1234);

	return 0;
}
